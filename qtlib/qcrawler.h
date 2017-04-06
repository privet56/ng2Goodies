#ifndef QCRAWLER_H
#define QCRAWLER_H

#include <QObject>
#include <QUrl>
#include <QSet>
#include <QWebFrame>
#include "helpers.h"
#include "shiwebview.h"

class qcrawler : public QObject
{
Q_OBJECT
public:
    explicit qcrawler(QObject *parent, QUrl url, helpers* phelper, int iCrawlTilRecDepth, bool bWithParams, bool bFollowExternalLinks);
    void crawl(QUrl url, int iRecDepth, int iCrawlTilRecDepth, bool bWithParams, bool bFollowExternalLinks, QString sUrlVerweisender);
    void crawl(QWebFrame* pFr, QSet<QString> &rels, helpers* phelper, int iCrawlTilRecDepth, bool bWithParams, bool bFollowExternalLinks);
    void crawl(QWebFrame* pFr, QWebElement e , QSet<QString> &rels, helpers* phelper, int iCrawlTilRecDepth, bool bWithParams, bool bFollowExternalLinks);
    void crawlele(QWebFrame* pFr, QWebElement e , QSet<QString> &rels, helpers* phelper, int iCrawlTilRecDepth, bool bWithParams, bool bFollowExternalLinks);

    bool docType2Crawl(QString sUrl);
    bool isExternal(QWebFrame* pFr, QString sUrl);
    QString extractHostMain(QString sHost);

public:
    QUrl m_uRoot;
    QSet<QString> m_rels;
    QSet<QString> m_visitedUrls;
    SHIWebView m_webview;
    helpers* m_phelper;

signals:

public slots:

};

#endif // QCRAWLER_H
