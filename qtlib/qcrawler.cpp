#include "qcrawler.h"
#include <QDebug>

//#define DOWNLOAD_TEST 1

qcrawler::qcrawler(QObject *parent, QUrl url, helpers* phelper, int iCrawlTilRecDepth, bool bWithParams, bool bFollowExternalLinks) : QObject(parent), m_webview(0)
{
    m_phelper   = phelper;
    m_uRoot     = url;
    m_rels.insert(url.toString());
    m_webview.setSilent(true);
    crawl(url, 0, iCrawlTilRecDepth, bWithParams, bFollowExternalLinks, "");
}

bool qcrawler::docType2Crawl(QString sUrl)
{
    static QSet<QString> __seHtml;
    static QSet<QString> __seNotHtml;
    if( __seHtml.size() < 1)
    {
        __seHtml.insert("htm");
        __seHtml.insert("xml");
        __seHtml.insert("rdf");
        __seHtml.insert("rss");
        __seHtml.insert("html");
        __seHtml.insert("xhtml");
        __seHtml.insert("php");
        __seHtml.insert("php3");
        __seHtml.insert("jsp");
        __seHtml.insert("jsf");
        __seHtml.insert("asp");
        __seHtml.insert("aspx");
        __seHtml.insert("cgi");
        __seHtml.insert("pl");

        __seNotHtml.insert("gif");
        __seNotHtml.insert("tif");
        __seNotHtml.insert("tiff");
        __seNotHtml.insert("jpe");
        __seNotHtml.insert("jpg");
        __seNotHtml.insert("jpeg");
        __seNotHtml.insert("bmp");
        __seNotHtml.insert("ico");
        __seNotHtml.insert("svg");
        __seNotHtml.insert("js");
        __seNotHtml.insert("css");
        __seNotHtml.insert("pdf");
        __seNotHtml.insert("doc");
        __seNotHtml.insert("docx");
        __seNotHtml.insert("txt");
        __seNotHtml.insert("xls");
        __seNotHtml.insert("ppt");
        __seNotHtml.insert("cpp");
        __seNotHtml.insert("h");
        __seNotHtml.insert("swf");
        __seNotHtml.insert("png");
        __seNotHtml.insert("avi");
        __seNotHtml.insert("wmv");
        __seNotHtml.insert("wma");
        __seNotHtml.insert("mpg");
        __seNotHtml.insert("mpe");
        __seNotHtml.insert("mp3");
        __seNotHtml.insert("mid");
        __seNotHtml.insert("mpeg");
        __seNotHtml.insert("flv");
        __seNotHtml.insert("rm");
        __seNotHtml.insert("zip");
        __seNotHtml.insert("gz");
        __seNotHtml.insert("rar");
    }
    QString sExt = helpers::f_getext(helpers::str_removeright(helpers::str_removeright(sUrl,"#"),"?")).trimmed().toLower();

    if(helpers::str_isempty(sExt, true))return true;
    if(__seHtml.contains(sExt))         return true;
    if(__seNotHtml.contains(sExt))      return false;

    if((sExt.indexOf('%') > -1) || (sExt.indexOf(',') > -1) || (sExt.indexOf(';') > -1) || (sExt.indexOf('=') > -1))
        return true;

    //qDebug() << "ext2crawl? '"+sExt+"' url:"+sUrl;

    return true;
}

void qcrawler::crawl(QUrl url, int iRecDepth, int iCrawlTilRecDepth, bool bWithParams, bool bFollowExternalLinks, QString sUrlVerweisender)
{
    {
        QString sUrl = url.toString();
        if( !bWithParams)
            sUrl = helpers::str_removeright(sUrl,"?");

        if(m_visitedUrls.contains(sUrl))
            return;
        m_visitedUrls.insert(sUrl);
#ifndef DOWNLOAD_TEST
        if(!docType2Crawl(sUrl))
        {
            this->m_rels.insert(sUrl);
            return;
        }
#endif
    }

    QMap<QWebFrame*,QWebFrame*> frs;
    bool bOK = false;
    QWebFrame* pMainFr = m_webview.loadAndWaitTilFinish(url.toString(), &bOK);
    if(!bOK)
    {
        m_phelper->log("qcrawler:crawl !load:'"+url.toString()+(helpers::str_isempty(sUrlVerweisender, true) ? "" : "\n  sUrlVerweisender:"+sUrlVerweisender),LOG_WRN);
        return;
    }
    m_webview.getallframes(pMainFr, frs);
    {
        QMap<QString, QSet<QString>*> mrels;
        {
            QMap<QWebFrame*, QWebFrame*>::const_iterator i = frs.constBegin();

            while(i != frs.constEnd())
            {
                QWebFrame* fr = i.key();
                QSet<QString>* pRels = new QSet<QString>();
                ++i;
#ifdef DOWNLOAD_TEST
                    QWebPage* p = fr->page();
                    if(p && p->inherits("SHIWebPage"))
                    {
                        SHIWebPage* pp = (SHIWebPage*)p;
                        QString sFN = helpers::f_getFileName(fr->url().toString(), true);
                        if(helpers::str_isempty(sFN, true))
                            sFN = "index";
                        QString sAbsFN = "c:\\temp\\_hu_\\"+sFN;
                        if(QFile::exists(sAbsFN))QFile::remove(sAbsFN);
                        QFile f(sAbsFN);
                        f.open(QFile::WriteOnly | QIODevice::Truncate);
                        f.write(???);
                        f.close();
                    }
#endif
                crawl(fr, *pRels, m_phelper, iCrawlTilRecDepth, bWithParams, bFollowExternalLinks);

                if(mrels.contains(fr->url().toString()))
                    mrels[fr->url().toString()]->operator +=(*pRels);
                else
                    mrels[fr->url().toString()] = pRels;
            }
        }
        {
            QMap<QString, QSet<QString>*>::const_iterator i = mrels.constBegin();
            while (i != mrels.constEnd())
            {
                QString sUrl = i.key();
                QSet<QString>* rels = i.value();
                ++i;
                if(iRecDepth < iCrawlTilRecDepth)
                {
                    foreach(QString sRef, *rels)
                    {
                        if(!this->m_rels.contains(sRef))
                        {
                            crawl(QUrl(sRef),iRecDepth+1, iCrawlTilRecDepth, bWithParams, bFollowExternalLinks, sUrl);
                        }
                    }
                }
                this->m_rels += *rels;
            }
        }
    }
}

QString qcrawler::extractHostMain(QString sHost)
{
    QStringList asHost = sHost.split('.');

    if(asHost.size() < 2)   return sHost.trimmed().toLower();
    if(asHost.size() == 2)  return asHost.at(0).trimmed().toLower();

    return asHost.at(asHost.size()-2).trimmed().toLower();
}

bool qcrawler::isExternal(QWebFrame* pFr, QString sUrl)
{
    QString sHost1 = extractHostMain(pFr->url().host());
    QString sHost2 = extractHostMain(QUrl(sUrl).host());

    return (sHost1 != sHost2);
}

void qcrawler::crawlele(QWebFrame* pFr, QWebElement e, QSet<QString> &rels, helpers* phelper, int iCrawlTilRecDepth, bool bWithParams, bool bFollowExternalLinks)
{
    QSet<QString> erels;
    erels.insert(e.attribute("src"));
    erels.insert(e.attribute("href"));

    foreach (QString sUrl, erels)
    {
        if(helpers::str_isempty(sUrl, true))continue;
        sUrl.trimmed();
        if(sUrl.indexOf('#') == 0)          continue;
        if(sUrl.indexOf("javascript:") == 0)continue;
        if(sUrl.indexOf("mailto:") == 0)    continue;
        if((sUrl.indexOf('(') > 0) && (sUrl.indexOf(')') > sUrl.indexOf('(')))continue;

        sUrl = helpers::str_removeright(sUrl,"#");
        QUrl u(sUrl);
        if(!u.isValid())
        {
            phelper->log("qcrawler:crawl !valid:'"+sUrl+"' inpage:"+pFr->url().toString(),LOG_WRN);
            continue;
        }

        if( !bWithParams)
            sUrl = helpers::str_removeright(sUrl,"?");
        sUrl = helpers::str_removeright(sUrl,"#");

        if( u.isRelative())
        {
            sUrl = QUrl(pFr->url().toString()).resolved(u).toString();
        }
        else
        {
            if(!bFollowExternalLinks && isExternal(pFr, sUrl))
            {
                continue;
            }
        }
        rels.insert(sUrl);
    }
}
void qcrawler::crawl(QWebFrame* pFr, QWebElement e, QSet<QString> &rels, helpers* phelper, int iCrawlTilRecDepth, bool bWithParams, bool bFollowExternalLinks)
{
    if(e.isNull())return;
    crawlele(pFr, e, rels, phelper, iCrawlTilRecDepth, bWithParams, bFollowExternalLinks);

    QWebElement c = e.firstChild();
    if(e.isNull())return;

    do
    {
        crawlele(pFr, c, rels, phelper, iCrawlTilRecDepth, bWithParams, bFollowExternalLinks);
        crawl(pFr, c, rels, phelper, iCrawlTilRecDepth, bWithParams, bFollowExternalLinks);
        c = c.nextSibling();
    }
    while(!c.isNull());
}
void qcrawler::crawl(QWebFrame* pFr, QSet<QString> &rels, helpers* phelper, int iCrawlTilRecDepth, bool bWithParams, bool bFollowExternalLinks)
{
    {
        QString sUrl = helpers::str_removeright(pFr->url().toString(),"#");
        if(!bWithParams)
            sUrl = helpers::str_removeright(pFr->url().toString(),"?");

        rels.insert(sUrl);
    }
    QWebElement e = pFr->documentElement();

    if(e.isNull())
    {
        phelper->log("qcrawler:crawl !documentele:"+pFr->url().toString(),LOG_WRN);
        return;
    }

    crawl(pFr, e, rels, phelper, iCrawlTilRecDepth, bWithParams, bFollowExternalLinks);
}
