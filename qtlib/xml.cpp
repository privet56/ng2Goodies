#include "xml.h"

xml::xml(QString sAbsFN)
{
    this->msAbsFN = sAbsFN;
}

QString xml::GetRootEle(QString s)
{
    int iS = s.lastIndexOf('/');
    int iK = s.lastIndexOf('>');
    QString sTag = s.mid(iS+1, iK-(iS+1));
    return sTag;
}

QString xml::getTagAttribs(QDomElement e)
{
    QDomNamedNodeMap ns = e.attributes();
    QString s = "";
    int is = ns.count();
    for(int i=0; i < is; i++)
    {
        QDomNode a = ns.item(i);
        s += ((i==0 ? "" : ",") + a.nodeName() + "=" + a.nodeValue());
    }
    return s;
}

void xml::GetEles(QDomElement e, QSet<QString>* pTagnames, QList<QDomElement> *pEles, helpers* phelper)
{
    if(pTagnames->contains(e.tagName()))
    {
        pEles->append(e);
        //phelper->log("GetEles:FOUND", LOG_ERR, phelper->m_pApp, phelper->m_pLogTarget, false);
        return;
    }
    //phelper->log("GetEles:NOT-FOUND:'"+e.tagName()+"'", LOG_ERR, phelper->m_pApp, phelper->m_pLogTarget, false);
    QDomElement ce = e.firstChildElement();
    while(!ce.isNull())
    {
        xml::GetEles(ce, pTagnames, pEles, phelper);
        ce = ce.nextSiblingElement();
    }
}
