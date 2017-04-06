/****************************************************************************
** 
** Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
** 
** This file is part of a Qt Solutions component.
**
** Commercial Usage  
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Solutions Commercial License Agreement provided
** with the Software or, alternatively, in accordance with the terms
** contained in a written agreement between you and Nokia.
** 
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
** 
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.1, included in the file LGPL_EXCEPTION.txt in this
** package.
** 
** GNU General Public License Usage 
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
** 
** Please note Third Party Software included with Qt Solutions may impose
** additional restrictions and it is the user's responsibility to ensure
** that they have met the licensing requirements of the GPL, LGPL, or Qt
** Solutions Commercial license and the relevant license of the Third
** Party Software they are using.
** 
** If you are unsure which license is appropriate for your use, please
** contact Nokia at qt-info@nokia.com.
** 
****************************************************************************/

#include <string.h>

#include <libxml/parser.h>
#include <libxml/SAX2.h>
#include <libxml/uri.h>
#include <libxml/parserInternals.h>

#include <QtCore/QList>
#include <QtCore/QStack>
#include <QtCore/QMap>

#include "qtlibxmlreader.h"

#define DEFAULT_CHUNK_SIZE 1024

struct LibxmlFeature
{
    const char *name;
    int feature;
};


static LibxmlFeature g_libxml_feature_list[] = {
#define ADD_FEATURE(name) { "http://qtsoftware.com/xml/features/LIBXML2_" #name, XML_PARSE_##name }
    ADD_FEATURE(NOENT),
    ADD_FEATURE(RECOVER)
#undef ADD_FEATURE
};

static int g_num_libxml_features = sizeof(g_libxml_feature_list)/sizeof(LibxmlFeature);

struct QtXmlHandler
{
    QXmlContentHandler *content_handler;
    QXmlDTDHandler *dtd_handler;
    QXmlErrorHandler *error_handler;
    QXmlDeclHandler *decl_handler;
    QXmlLexicalHandler *lexical_handler;
};

class QtXmlLocatorImpl : public QXmlLocator
{
    public:
        QtXmlLocatorImpl()
            : m_libxml_loc(0), m_libxml_ctxt(0) {}
        void set(xmlParserCtxt *libxml_ctxt, xmlSAXLocator *libxml_loc)
            { m_libxml_ctxt = libxml_ctxt; m_libxml_loc = libxml_loc; }
        int columnNumber() const
            { return m_libxml_ctxt == 0 ? 0 : m_libxml_loc->getColumnNumber(m_libxml_ctxt); }
        int lineNumber() const
            { return m_libxml_ctxt == 0 ? 0 : m_libxml_loc->getLineNumber(m_libxml_ctxt); }

    private:
        xmlSAXLocator *m_libxml_loc;
        xmlParserCtxt *m_libxml_ctxt;
};

struct QtNamespace
{
    QString prefix, uri;

    QtNamespace(const QString &_prefix = QString::null, const QString &_uri = QString::null)
        : prefix(_prefix), uri(_uri) {}
};

typedef QList<QtNamespace> QtNamespaceList;
typedef QStack<QtNamespaceList> QtNamespaceStack;
typedef QMap<QString, xmlEntity*> EntityMap;

struct QtLibxmlReaderPrivate
{
    xmlParserCtxt *libxml_ctxt;
    xmlSAXHandler libxml_handler;
    QtXmlHandler qxml_handler;
    QtXmlLocatorImpl qxml_locator;
    QtNamespaceStack namespace_stack;

    int libxml_parser_ftrs;

    bool in_dtd;

    // used for callback arguments to save mallocs
    QString arg0, arg1, arg2, arg3, arg4;

    int columnNumber() const { return qxml_locator.columnNumber(); }
    int lineNumber() const { return qxml_locator.lineNumber(); }

    void raiseFatalError(const QString &msg);
    void checkEndDtd();
    void cleanup();
};

static QString &mkQStr(QString &s, const xmlChar *utf8, int len = -1)
{
    s = QString::fromUtf8((const char*)utf8, len);
    return s;
}

/*******************************************************************************
 Mapping from a QXmlInputSource to a xmlParserInput
 *******************************************************************************/

extern "C" int readQXmlInputSource(void *ioctxt, char *buff, int len)
{
    Q_ASSERT(ioctxt != 0);
    QXmlInputSource *input = static_cast<QXmlInputSource*>(ioctxt);

    int i = 0;
    while (i < len - 1) {
        QChar ic = input->next();

        if (ic == QXmlInputSource::EndOfData) {
            if (i > 0)
                break;
            else
                ic = input->next();
        }

        if (ic == QXmlInputSource::EndOfDocument)
            break;

        buff[i++] = ic.unicode() % 255;
        buff[i++] = ic.unicode() / 255;
    }

    return i;
}

extern "C" int closeQXmlInputSource(void *)
{
    return 0;
}

/*******************************************************************************
 QtLibxmlReaderPrivate
 *******************************************************************************/

void QtLibxmlReaderPrivate::raiseFatalError(const QString &msg)
{
    QXmlParseException ex(msg, columnNumber(), lineNumber());

    if (qxml_handler.error_handler != 0) {
        qxml_handler.error_handler->fatalError(ex);
    }

    xmlStopParser(libxml_ctxt);
}

void QtLibxmlReaderPrivate::checkEndDtd()
{
    if (!in_dtd)
        return;

    if (libxml_ctxt->inSubset != 0)
        return;

    if (qxml_handler.lexical_handler != 0) {
        if (!qxml_handler.lexical_handler->endDTD())
            raiseFatalError(qxml_handler.lexical_handler->errorString());
    }

    in_dtd = false;
}

void QtLibxmlReaderPrivate::cleanup()
{
    if (libxml_ctxt != 0) {
        xmlFreeDoc(libxml_ctxt->myDoc);
        xmlFreeParserCtxt(libxml_ctxt);
        libxml_ctxt = 0;
    }

    namespace_stack.clear();

    libxml_parser_ftrs = 0;
    in_dtd = false;
}

static QtLibxmlReaderPrivate *extractCtxt(void *ctx)
{
    Q_ASSERT(ctx != 0);
    xmlParserCtxt *libxml_ctxt = static_cast<xmlParserCtxt*>(ctx);
    QtLibxmlReaderPrivate *d = static_cast<QtLibxmlReaderPrivate*>(libxml_ctxt->_private);
    Q_ASSERT(d != 0);
    return d;
}

/*******************************************************************************
 QXmlContentHandler callbacks
 *******************************************************************************/


extern "C" void handle_setDocumentLocator(void *ctx, xmlSAXLocatorPtr loc)
{
    QtLibxmlReaderPrivate *d = extractCtxt(ctx);

    if (d->qxml_handler.content_handler == 0)
        return;

    d->qxml_locator.set(d->libxml_ctxt, loc);
    d->qxml_handler.content_handler->setDocumentLocator(&d->qxml_locator);
}

extern "C" void handle_startDocument(void *ctx)
{
    QtLibxmlReaderPrivate *d = extractCtxt(ctx);
    d->checkEndDtd();

    if (d->qxml_handler.content_handler == 0)
        return;

    if (!d->qxml_handler.content_handler->startDocument())
        d->raiseFatalError(d->qxml_handler.content_handler->errorString());
}

extern "C" void handle_endDocument(void *ctx)
{
    QtLibxmlReaderPrivate *d = extractCtxt(ctx);
    d->checkEndDtd();

    if (d->qxml_handler.content_handler == 0)
        return;

    if (!d->qxml_handler.content_handler->endDocument())
        d->raiseFatalError(d->qxml_handler.content_handler->errorString());
}

extern "C" void handle_characters(void *ctx, const xmlChar *ch, int len)
{
    if (len == 0)
        return;

    QtLibxmlReaderPrivate *d = extractCtxt(ctx);
    d->checkEndDtd();

    if (d->qxml_handler.content_handler == 0)
        return;

    if (!d->qxml_handler.content_handler->characters(mkQStr(d->arg0, ch, len)))
        d->raiseFatalError(d->qxml_handler.content_handler->errorString());
}

extern "C" void handle_ignorableWhitespace(void *ctx, const xmlChar *ch, int len)
{
    QtLibxmlReaderPrivate *d = extractCtxt(ctx);
    d->checkEndDtd();

    if (d->qxml_handler.content_handler == 0)
        return;

    if (!d->qxml_handler.content_handler->ignorableWhitespace(mkQStr(d->arg0, ch, len)))
        d->raiseFatalError(d->qxml_handler.content_handler->errorString());
}

extern "C" void handle_processingInstruction(void *ctx, const xmlChar *target, const xmlChar *data)
{
    QtLibxmlReaderPrivate *d = extractCtxt(ctx);
    d->checkEndDtd();

    if (d->qxml_handler.content_handler == 0)
        return;

    if (!d->qxml_handler.content_handler->processingInstruction(mkQStr(d->arg0, target), mkQStr(d->arg1, data)))
        d->raiseFatalError(d->qxml_handler.content_handler->errorString());
}

extern "C" void handle_startElement(void *ctx, const xmlChar *local_name, const xmlChar *prefix,
                                    const xmlChar *uri, int nb_namespaces, const xmlChar **namespaces,
                                    int nb_attributes, int /*nb_defaulted*/, const xmlChar **attributes)
{
    QtLibxmlReaderPrivate *d = extractCtxt(ctx);
    d->checkEndDtd();

    if (d->qxml_handler.content_handler == 0)
        return;

    QtNamespaceList ns_list;
    int i;
    for (i = 0; i < nb_namespaces; ++i) {
        const QString &prefix = mkQStr(d->arg0, namespaces[i*2]);
        const QString &uri = mkQStr(d->arg1, namespaces[i*2 + 1]);

        if (!d->qxml_handler.content_handler->startPrefixMapping(prefix, uri)) {
            d->raiseFatalError(d->qxml_handler.content_handler->errorString());
            return;
        }

        ns_list.append(QtNamespace(prefix, uri));
    }
    d->namespace_stack.push(ns_list);

    QXmlAttributes atts;
    for (i = 0; i < nb_attributes; ++i) {
        const QString &attr_local_name = mkQStr(d->arg0, attributes[5*i]);
        const QString &attr_prefix = mkQStr(d->arg1, attributes[5*i + 1]);
        QString attr_qualified_name;
        if (attr_prefix.isEmpty()) {
            attr_qualified_name = attr_local_name;
        } else {
            attr_qualified_name.reserve(attr_local_name.length() + attr_prefix.length() + 1);
            attr_qualified_name.append(attr_prefix);
            attr_qualified_name.append(':');
            attr_qualified_name.append(attr_local_name);
        }

        const xmlChar *attr_value_start = attributes[5*i + 3];
        const xmlChar *attr_value_end = attributes[5*i + 4];
        const QString &attr_value = mkQStr(d->arg2, attr_value_start, attr_value_end - attr_value_start);

        atts.append(attr_qualified_name, mkQStr(d->arg3, attributes[5*i + 2]),
                    attr_local_name, attr_value);
    }

    const QString &local_name_qstr = mkQStr(d->arg0, local_name);
    const QString &prefix_qstr = mkQStr(d->arg1, prefix);
    QString qualified_name;
    if (prefix_qstr.isEmpty()) {
        qualified_name = local_name_qstr;
    } else {
        qualified_name.reserve(local_name_qstr.length() + prefix_qstr.length() + 1);
        qualified_name.append(prefix_qstr);
        qualified_name.append(':');
        qualified_name.append(local_name_qstr);
    }

    if (!d->qxml_handler.content_handler->startElement(mkQStr(d->arg2, uri), local_name_qstr,
                                                       qualified_name, atts))
        d->raiseFatalError(d->qxml_handler.content_handler->errorString());
}

extern "C" void handle_endElement(void *ctx, const xmlChar *local_name, const xmlChar *prefix,
                                  const xmlChar *uri)
{
    QtLibxmlReaderPrivate *d = extractCtxt(ctx);
    d->checkEndDtd();

    if (d->qxml_handler.content_handler == 0)
        return;

    const QString &local_name_qstr = mkQStr(d->arg0, local_name);
    const QString &prefix_qstr = mkQStr(d->arg1, prefix);
    QString qualified_name;
    if (prefix_qstr.isEmpty()) {
        qualified_name = local_name_qstr;
    } else {
        qualified_name.reserve(local_name_qstr.length() + prefix_qstr.length() + 1);
        qualified_name.append(prefix_qstr);
        qualified_name.append(':');
        qualified_name.append(local_name_qstr);
    }

    if (!d->qxml_handler.content_handler->endElement(mkQStr(d->arg2, uri), local_name_qstr, qualified_name)) {
        d->raiseFatalError(d->qxml_handler.content_handler->errorString());
        return;
    }

    if (!d->namespace_stack.isEmpty()) {
        QtNamespaceList ns_list = d->namespace_stack.pop();
        QtNamespaceList::const_iterator it = ns_list.begin();
        for (; it != ns_list.end(); ++it) {
            if (!d->qxml_handler.content_handler->endPrefixMapping((*it).prefix)) {
                d->raiseFatalError(d->qxml_handler.content_handler->errorString());
                return;
            }
        }
    }
}

/*******************************************************************************
 QXmlDTDHandler callbacks
 *******************************************************************************/

extern "C" void handle_notationDecl(void *ctx, const xmlChar *name, const xmlChar *publicId,
                                    const xmlChar *systemId)
{
    QtLibxmlReaderPrivate *d = extractCtxt(ctx);
    d->checkEndDtd();

    if (d->qxml_handler.dtd_handler == 0)
        return;

    if (!d->qxml_handler.dtd_handler->notationDecl(mkQStr(d->arg0, name), mkQStr(d->arg1, publicId), mkQStr(d->arg2, systemId)))
        d->raiseFatalError(d->qxml_handler.dtd_handler->errorString());
}

extern "C" void handle_unparsedEntityDecl(void *ctx, const xmlChar *name, const xmlChar *publicId,
                                           const xmlChar *systemId, const xmlChar *notationName)
{
    QtLibxmlReaderPrivate *d = extractCtxt(ctx);
    d->checkEndDtd();

    if (d->qxml_handler.dtd_handler == 0)
        return;

    if (!d->qxml_handler.dtd_handler->unparsedEntityDecl(mkQStr(d->arg0, name), mkQStr(d->arg1, publicId),
                                                         mkQStr(d->arg2, systemId), mkQStr(d->arg3, notationName)))
        d->raiseFatalError(d->qxml_handler.dtd_handler->errorString());
}

/*******************************************************************************
 QXmlErrorHandler
 *******************************************************************************/

static QString vaSprintf(const char *fmt, va_list ap)
{
    QByteArray buff;
    buff.resize(500);

    QString result;

    for (;;) {
#if defined(Q_OS_WIN)
        int ret = _vsnprintf(buff.data(), buff.size(), fmt, ap);
#elif defined (Q_OS_FREEBSD)
        int ret = vsnprintf(buff.data(), buff.size(), fmt, ap);
#else
        /*  This is the correct way of doing this (not relying on the value of ap_copy
            after it's passed to vsnprintf), but Windows has no va_copy. */
        va_list ap_copy;
        va_copy(ap_copy, ap);
        int ret = vsnprintf(buff.data(), buff.size(), fmt, ap_copy);
        va_end(ap_copy);
#endif
        if (ret < 0) {
            // -1 means buffer too short, old vsnprintf behavior
            buff.resize(buff.size()*2);
        } else if (ret < (int)buff.size()) {
            result = QString::fromLatin1(buff.data(), ret);
            break;
        } else {
            // ret >= buff.size() means buffer too short, new vsnprintf behavior
            buff.resize(ret + 1);
        }
    }

    if (result.endsWith("\n"))
        result = result.left(result.length() - 1);

    return result;
}

extern "C" void handle_warning(void *ctx, const char *msg, ...)
{
    QtLibxmlReaderPrivate *d = extractCtxt(ctx);

    if (d->qxml_handler.error_handler == 0)
        return;

    va_list ap; va_start(ap, msg);
    QXmlParseException ex(vaSprintf(msg, ap), d->columnNumber(), d->lineNumber());
    va_end(ap);

    if (!d->qxml_handler.error_handler->warning(ex))
        d->raiseFatalError(d->qxml_handler.error_handler->errorString());
}

extern "C" void handle_error(void *ctx, const char *msg, ...)
{
    QtLibxmlReaderPrivate *d = extractCtxt(ctx);

    if (d->qxml_handler.error_handler == 0)
        return;

    va_list ap; va_start(ap, msg);
    QXmlParseException ex(vaSprintf(msg, ap), d->columnNumber(), d->lineNumber());
    va_end(ap);

    if (!d->qxml_handler.error_handler->error(ex))
        d->raiseFatalError(d->qxml_handler.error_handler->errorString());
}

extern "C" void handle_fatalError(void *ctx, const char *msg, ...)
{
    QtLibxmlReaderPrivate *d = extractCtxt(ctx);

    va_list ap; va_start(ap, msg);
    QString msg_str = vaSprintf(msg, ap);
    va_end(ap);

    d->raiseFatalError(msg_str);
}

/*******************************************************************************
 QXmlDeclHandler
 *******************************************************************************/

extern "C" void handle_attributeDecl(void *ctx, const xmlChar *elem, const xmlChar *fullname,
                                        int type, int def, const xmlChar *defaultValue,
                                        xmlEnumerationPtr enumerate)
{
    QtLibxmlReaderPrivate *d = extractCtxt(ctx);
    d->checkEndDtd();

    if (d->libxml_ctxt != 0)
        ::xmlSAX2AttributeDecl(d->libxml_ctxt, elem, fullname, type, def, defaultValue, enumerate);

    if (d->qxml_handler.decl_handler == 0)
        return;

    QString &def_qstr = d->arg2;
    switch (def) {
        case XML_ATTRIBUTE_REQUIRED:
            mkQStr(d->arg2, (const xmlChar*)"#REQUIRED");
            break;
        case XML_ATTRIBUTE_IMPLIED:
            mkQStr(d->arg2, (const xmlChar*)"#IMPLIED");
            break;
        case XML_ATTRIBUTE_FIXED:
            mkQStr(d->arg2, (const xmlChar*)"#FIXED");
            break;
        default:
            mkQStr(d->arg2, (const xmlChar*)"");
            break;
    }

    QString &type_qstr = d->arg3;
    switch (type) {
        case XML_ATTRIBUTE_CDATA:
            mkQStr(d->arg3, (const xmlChar*)"CDATA");
            break;
        case XML_ATTRIBUTE_ID:
            mkQStr(d->arg3, (const xmlChar*)"ID");
            break;
        case XML_ATTRIBUTE_IDREF:
            mkQStr(d->arg3, (const xmlChar*)"IDREF");
            break;
        case XML_ATTRIBUTE_IDREFS:
            mkQStr(d->arg3, (const xmlChar*)"IDREFS");
            break;
        case XML_ATTRIBUTE_ENTITY:
            mkQStr(d->arg3, (const xmlChar*)"ENTITY");
            break;
        case XML_ATTRIBUTE_ENTITIES:
            mkQStr(d->arg3, (const xmlChar*)"ENTITIES");
            break;
        case XML_ATTRIBUTE_NMTOKEN:
            mkQStr(d->arg3, (const xmlChar*)"NMTOKEN");
            break;
        case XML_ATTRIBUTE_NMTOKENS:
            mkQStr(d->arg3, (const xmlChar*)"NMTOKENS");
            break;
        case XML_ATTRIBUTE_ENUMERATION:
            mkQStr(d->arg3, (const xmlChar*)"ENUMERATION");
            break;
        case XML_ATTRIBUTE_NOTATION:
            mkQStr(d->arg3, (const xmlChar*)"NOTATION");
            break;
        default:
            mkQStr(d->arg3, (const xmlChar*)"");
            break;
    }

    if (!d->qxml_handler.decl_handler->attributeDecl(mkQStr(d->arg0, elem),
                                                        mkQStr(d->arg1, fullname),
                                                        type_qstr, def_qstr,
                                                        mkQStr(d->arg4, defaultValue))) {
        d->raiseFatalError(d->qxml_handler.decl_handler->errorString());
        return;
    }

}

static xmlEntity g_dummy_entity = {
    0, XML_ENTITY_DECL, 0,
    0, 0, 0, 0, 0, 0, 0, (xmlChar*)"", 0,
    XML_INTERNAL_PREDEFINED_ENTITY,
    0, 0, 0, 0, 0, 0
};

extern "C" void handle_internalSubset(void *ctx, const xmlChar *name,
                                      const xmlChar *external_id, const xmlChar *system_id)
{
    QtLibxmlReaderPrivate *d = extractCtxt(ctx);
    d->in_dtd = true;

    if (d->libxml_ctxt != 0)
        ::xmlSAX2InternalSubset(d->libxml_ctxt, name, external_id, system_id);

    if (d->qxml_handler.lexical_handler == 0)
        return;

    if (!d->qxml_handler.lexical_handler->startDTD(mkQStr(d->arg0, name), mkQStr(d->arg1, external_id),
                                                    mkQStr(d->arg2, system_id)))
        d->raiseFatalError(d->qxml_handler.lexical_handler->errorString());
}

extern "C" xmlEntityPtr handle_getEntity(void *ctx, const xmlChar *name)
{
    QtLibxmlReaderPrivate *d = extractCtxt(ctx);
    d->checkEndDtd();

    xmlEntity *ent = ::xmlSAX2GetEntity(d->libxml_ctxt, name);
    if (ent == 0)
        return 0;

    if (ent->etype == XML_INTERNAL_PREDEFINED_ENTITY
            || ent->etype == XML_INTERNAL_GENERAL_ENTITY
            || ent->etype == XML_INTERNAL_PARAMETER_ENTITY)
        return ent;

    if (d->libxml_ctxt->inSubset != 0)
        return ent;

    if ((d->libxml_parser_ftrs & XML_PARSE_NOENT) == 0) {
        if (d->qxml_handler.content_handler != 0) {
            if (!d->qxml_handler.content_handler->skippedEntity(mkQStr(d->arg0, name)))
                d->raiseFatalError(d->qxml_handler.content_handler->errorString());
        }
        return &g_dummy_entity;
    }

    return ent;
}

extern "C" xmlEntityPtr handle_getParameterEntity(void *ctx, const xmlChar *name)
{
    QtLibxmlReaderPrivate *d = extractCtxt(ctx);
    d->checkEndDtd();

    return ::xmlSAX2GetParameterEntity(d->libxml_ctxt, name);
}

extern "C" void handle_entityDecl(void *ctx,
                                    const xmlChar *name,
                                    int type,
                                    const xmlChar *public_id,
                                    const xmlChar *system_id,
                                    xmlChar *content)
{
    QtLibxmlReaderPrivate *d = extractCtxt(ctx);
    d->checkEndDtd();

    ::xmlSAX2EntityDecl(d->libxml_ctxt, name, type, public_id, system_id, content);

    if (d->qxml_handler.decl_handler == 0)
    {
        return;
    }

    QString &name_qstr = mkQStr(d->arg0, name);
    if (type == XML_INTERNAL_PARAMETER_ENTITY || type == XML_EXTERNAL_PARAMETER_ENTITY)
        name_qstr.prepend("%");

    if (type == XML_INTERNAL_GENERAL_ENTITY || type == XML_INTERNAL_PARAMETER_ENTITY)
    {
        if (!d->qxml_handler.decl_handler->internalEntityDecl(name_qstr, mkQStr(d->arg1, content))) {
            d->raiseFatalError(d->qxml_handler.decl_handler->errorString());
            return;
        }
    }
    else
    {
        QString s2 = mkQStr(d->arg2, system_id);
        if (!d->qxml_handler.decl_handler->externalEntityDecl(name_qstr, mkQStr(d->arg1, public_id), s2))
        {
            d->raiseFatalError(d->qxml_handler.decl_handler->errorString());
            return;
        }
        //qDebug() << "A:"+mkQStr(d->arg1, public_id);
        //qDebug() << "B:"+mkQStr(d->arg2, system_id);
        //qDebug() << "C:"+name_qstr;
    }
}

/*******************************************************************************
 QXmlLexicalHandler
 *******************************************************************************/

extern "C" void handle_comment(void *ctx, const xmlChar *msg)
{
    QtLibxmlReaderPrivate *d = extractCtxt(ctx);
    d->checkEndDtd();

    if (d->qxml_handler.lexical_handler == 0)
        return;

    if (!d->qxml_handler.lexical_handler->comment(mkQStr(d->arg0, msg)))
        d->raiseFatalError(d->qxml_handler.lexical_handler->errorString());
}

extern "C" void handle_cdataBlock(void *ctx, const xmlChar *value, int len)
{
    QtLibxmlReaderPrivate *d = extractCtxt(ctx);
    d->checkEndDtd();

    if (d->qxml_handler.lexical_handler != 0) {
        if (!d->qxml_handler.lexical_handler->startCDATA())
            d->raiseFatalError(d->qxml_handler.lexical_handler->errorString());
    }

    if (d->qxml_handler.content_handler != 0) {
        if (!d->qxml_handler.content_handler->characters(mkQStr(d->arg0, value, len)))
            d->raiseFatalError(d->qxml_handler.content_handler->errorString());
    }

    if (d->qxml_handler.lexical_handler != 0) {
        if (!d->qxml_handler.lexical_handler->endCDATA())
            d->raiseFatalError(d->qxml_handler.lexical_handler->errorString());
    }
}

/*******************************************************************************
 QtLibxmlReader
 *******************************************************************************/

/*!
    \class QtLibxmlReader
    \brief The QtLibxmlReader class is a SAX2 parser based on libxml2, with a QXmlReader interface.

    \c QtLibxmlReader is a SAX2 parser. Like \c QXmlSimpleReader, it inherits
    \c QXmlReader and therefore Qt's SAX API. Unlike \c QXmlSimpleReader,
    \c QtLibxmlReader uses \c libxml2 to do the actual parsing.

    For an overview of differences between \c QtLibxmlReader and \c QXmlSimpleReader, see
    the \link overview.html overview\endlink.

    For more information on Qt's SAX2 interface, see the documentation for \c QXmlReader and \c QtXmlSimpleReader.
*/

/*!
    Constructs a QtLibxmlReader object.
*/
QtLibxmlReader::QtLibxmlReader()
{
    LIBXML_TEST_VERSION
    htmlDefaultSAXHandlerInit();

    d = new QtLibxmlReaderPrivate;

    memset(&d->libxml_handler, 0, sizeof(d->libxml_handler));
    d->libxml_handler.initialized           = XML_SAX2_MAGIC;
    d->libxml_handler.startDocument         = ::handle_startDocument;
    d->libxml_handler.endDocument           = ::handle_endDocument;
    d->libxml_handler.characters            = ::handle_characters;
    d->libxml_handler.ignorableWhitespace   = ::handle_ignorableWhitespace;
    d->libxml_handler.processingInstruction = ::handle_processingInstruction;
    d->libxml_handler.notationDecl          = ::handle_notationDecl;
    d->libxml_handler.unparsedEntityDecl    = ::handle_unparsedEntityDecl;
    d->libxml_handler.startElementNs        = ::handle_startElement;
    d->libxml_handler.endElementNs          = ::handle_endElement;
    d->libxml_handler.comment               = ::handle_comment;
    d->libxml_handler.warning               = ::handle_warning;
    d->libxml_handler.error                 = ::handle_error;
    d->libxml_handler.fatalError            = ::handle_fatalError;
    d->libxml_handler.setDocumentLocator    = ::handle_setDocumentLocator;
    d->libxml_handler.cdataBlock            = ::handle_cdataBlock;
    d->libxml_handler.attributeDecl         = ::handle_attributeDecl;
    d->libxml_handler.internalSubset        = ::handle_internalSubset;
    d->libxml_handler.getEntity             = ::handle_getEntity;
    d->libxml_handler.getParameterEntity    = ::handle_getParameterEntity;
    d->libxml_handler.entityDecl            = ::handle_entityDecl;

    memset(&d->qxml_handler, 0, sizeof(QtXmlHandler));

    d->libxml_ctxt = 0;
    d->libxml_parser_ftrs = 0;
    d->in_dtd = false;
}

/*!
    Destroys a QtLibxmlReader object.
*/
QtLibxmlReader::~QtLibxmlReader()
{
    d->cleanup();
    delete d;
}

/*!
    If the reader has the feature called \a name, the feature's value
    is returned. If no such feature exists the return value is
    undefined.

    If \a ok is not 0: \a ok  is set to \c TRUE if the reader has the
    feature called \a name; otherwise \a ok is set to \c FALSE.

    \sa setFeature() hasFeature()
*/
bool QtLibxmlReader::feature(const QString &name, bool *ok) const
{
    if (ok != 0)
        *ok = true;

    for (int i = 0; i < g_num_libxml_features; ++i) {
        LibxmlFeature &ftr = g_libxml_feature_list[i];
        if (name == QString::fromLatin1(ftr.name))
            return d->libxml_parser_ftrs & ftr.feature;
    }

    if (ok != 0)
        *ok = false;

    return false;
}

/*!
    Sets the state of the feature \a name to \a value:

    If the feature is not recognized, it is ignored.

    The following features are supported:
    \table
    \header \i Feature \i Notes
    \row \i \e http://qtsoftware.com/xml/features/LIBXML2_NOENT
         \i If this feature is \c TRUE, \c QXmlContentHandler::skippedEntity() is not called for external entity references. Instead, the parser replaces them with their replacement text. \c QtLibxmlReader can load external entities from the local filesystem, or from the network via HTTP or FTP. If this feature is \c FALSE (the default), all external entity references are reported with \c QXmlContentHandler::skippedEntity(). In either case, internal entities are replaced and undefined entities are reported with \c QXmlErrorHandler::error().
    \row \i \e http://qtsoftware.com/xml/features/LIBXML2_RECOVER
         \i If this feature is \c TRUE, the parser continues parsing after \c QXmlErrorHandler::error(). If this feature is \c FALSE (the default), the parser stops after \c QXmlErrorHandler::error().
    \endtable

    \sa feature() hasFeature()
*/
void QtLibxmlReader::setFeature(const QString &name, bool value)
{
    for (int i = 0; i < g_num_libxml_features; ++i) {
        LibxmlFeature &ftr = g_libxml_feature_list[i];
        if (name == QString::fromLatin1(ftr.name)) {
            d->libxml_parser_ftrs = value ? (d->libxml_parser_ftrs | ftr.feature)
                                      : (d->libxml_parser_ftrs & ~ftr.feature);
            return;
        }
    }

    qWarning("qtlibxmlreader: unknown feature \"%s\"", name.toLatin1().constData());
}

/*!
    Returns \c TRUE if the reader has the feature called \a name;
    otherwise returns \c FALSE.

    \sa feature() setFeature()
*/
bool QtLibxmlReader::hasFeature(const QString &name) const
{
    for (int i = 0; i < g_num_libxml_features; ++i) {
        LibxmlFeature &ftr = g_libxml_feature_list[i];
        if (name == QString::fromLatin1(ftr.name))
            return true;
    }

    return false;
}

/*!
    If the reader has the property \a name, this function returns the
    value of the property; otherwise the return value is undefined.

    If \a ok is not 0 and the reader has the \a name property, \a ok
    is set to \c TRUE; otherwise \a ok is set to \c FALSE.

    \sa setProperty() hasProperty()
*/
void *QtLibxmlReader::property(const QString &name, bool *ok) const
{
    Q_UNUSED(name);
    Q_UNUSED(ok);
    return 0;
}

/*!
    Sets the property \a name to \a value. If the reader doesn't have
    the property nothing happens.

    \sa property() hasProperty()
*/
void QtLibxmlReader::setProperty(const QString &name, void *value)
{
    Q_UNUSED(name);
    Q_UNUSED(value);
}


/*!
    Returns \c TRUE if the reader has the property \a name; otherwise
    returns \c FALSE.

    \sa property() setProperty()
*/
bool QtLibxmlReader::hasProperty(const QString &name) const
{
    Q_UNUSED(name);
    return false;
}

/*!
    Does nothing. \c QXmlEntityResolver is not supported. \a resolver is ignored.

    Instead, if the \c NOENT feature is set, \c libxml2 loads external entities from the local filesystem, or from the  network via HTTP or FTP. If the \c NOENT feature is not set, reports all entity references with \c QContentHandler::skippedEntity().

    \sa property() setProperty()
*/
void QtLibxmlReader::setEntityResolver(QXmlEntityResolver *resolver)
{
    Q_UNUSED(resolver);
}

/*!
    Returns 0. \c QXmlEntityResolver is not supported.

    Instead, if the \c NOENT feature is set, \c libxml2 loads external entities from the local filesystem, or from the  network via HTTP or FTP. If the \c NOENT feature is not set, reports all entity references with \c QContentHandler::skippedEntity().

    \sa property() setProperty()
*/
QXmlEntityResolver *QtLibxmlReader::entityResolver() const
{
    return 0;
}

/*!
    Sets the DTD handler to \a handler.

    \sa DTDHandler()
*/
void QtLibxmlReader::setDTDHandler(QXmlDTDHandler *handler)
{
    d->qxml_handler.dtd_handler = handler;
}

/*!
    Returns the DTD handler or 0 if none was set.

    \sa setDTDHandler()
*/
QXmlDTDHandler *QtLibxmlReader::DTDHandler() const
{
    return d->qxml_handler.dtd_handler;
}


/*!
    Sets the content handler to \a handler.

    \sa contentHandler()
*/
void QtLibxmlReader::setContentHandler(QXmlContentHandler *handler)
{
    d->qxml_handler.content_handler = handler;
}


/*!
    Returns the content handler or 0 if none was set.

    \sa setContentHandler()
*/
QXmlContentHandler *QtLibxmlReader::contentHandler() const
{
    return d->qxml_handler.content_handler;
}

/*!
    Sets the error handler to \a handler. Clears the error handler if
    \a handler is 0.

    \sa errorHandler()
*/
void QtLibxmlReader::setErrorHandler(QXmlErrorHandler *handler)
{
    d->qxml_handler.error_handler = handler;
}

/*!
    Returns the error handler or 0 if none is set.

    \sa setErrorHandler()
*/
QXmlErrorHandler *QtLibxmlReader::errorHandler() const
{
    return d->qxml_handler.error_handler;
}

/*!
    Sets the lexical handler to \a handler.

    \sa lexicalHandler()
*/
void QtLibxmlReader::setLexicalHandler(QXmlLexicalHandler *handler)
{
    d->qxml_handler.lexical_handler = handler;
}

/*!
    Returns the lexical handler or 0 if none was set.

    \sa setLexicalHandler()
*/
QXmlLexicalHandler *QtLibxmlReader::lexicalHandler() const
{
    return d->qxml_handler.lexical_handler;
}

/*!
    Sets the declaration handler to \a handler.

    \sa declHandler()
*/
void QtLibxmlReader::setDeclHandler(QXmlDeclHandler *handler)
{
    d->qxml_handler.decl_handler = handler;
}

/*!
    Returns the declaration handler or 0 if none was set.

    \sa setDeclHandler()
*/
QXmlDeclHandler *QtLibxmlReader::declHandler() const
{
    return d->qxml_handler.decl_handler;
}

/*!
    \obsolete
*/
bool QtLibxmlReader::parse(const QXmlInputSource &input)
{
    return parse(&input);
}

/*!
    Reads an XML document from \a input in and parses it. Returns \c FALSE
    if the parsing detects an error; otherwise returns \c TRUE.
*/
bool QtLibxmlReader::parse(const QXmlInputSource *input)
{
    QXmlInputSource *in = const_cast<QXmlInputSource*>(input);

    d->libxml_ctxt = xmlCreateIOParserCtxt(&d->libxml_handler, 0,
                                           readQXmlInputSource,
                                           closeQXmlInputSource,
                                           in, XML_CHAR_ENCODING_NONE);
    if (d->libxml_ctxt == 0)
        return false;

    xmlSwitchEncoding(d->libxml_ctxt, XML_CHAR_ENCODING_UTF16LE);
    xmlCtxtUseOptions(d->libxml_ctxt, d->libxml_parser_ftrs & ~XML_PARSE_NOENT);

    d->libxml_ctxt->_private = d;
    d->libxml_ctxt->myDoc = xmlNewDoc((xmlChar*)"SAX compatibility mode document");

    bool result = xmlParseDocument(d->libxml_ctxt) == 0;
    d->cleanup();
    return result;
}

/*!
    Reads an XML document from \a uri and parses it. \a uri may be a file name, or a HTTP or FTP url. Returns \c FALSE if the parsing detects an error; otherwise returns \c TRUE.

    This function does not use \c QXmlInputSource. Instead, \a uri is passed directly to \c libxml2. This has several advantages:
    \list
    \i \c QXmlInputSource reads the whole document into memory. This function, on the other hand, parses the document in chunks.
    \i \c QXmlInputSource converts the document to UTF-16, which is then converted to UTF-8 by \c libxml2. This function converts directly from the document's encoding to UTF-8.
    \endlist
*/
bool QtLibxmlReader::parse(const QString &uri)
{
    d->libxml_ctxt = xmlCreateFileParserCtxt(uri.toLatin1().constData());
    if (d->libxml_ctxt == 0)
        return false;

    xmlCtxtUseOptions(d->libxml_ctxt, d->libxml_parser_ftrs & ~XML_PARSE_NOENT);

    d->libxml_ctxt->sax = &d->libxml_handler;
    d->libxml_ctxt->_private = d;
//    d->libxml_ctxt->myDoc = xmlNewDoc((xmlChar*)"SAX compatibility mode document");

    bool result = xmlParseDocument(d->libxml_ctxt) == 0;
    d->libxml_ctxt->sax = 0;
    d->cleanup();
    return result;
}

