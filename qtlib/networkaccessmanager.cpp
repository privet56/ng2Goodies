#include "networkaccessmanager.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkProxy>
#include <QThread>
#include "networkReply.h"
#include "helpers.h"

networkAccessManager::networkAccessManager(QNetworkAccessManager *oldManager, QString sUrl, QObject *parent /*= 0*/) : QNetworkAccessManager(parent)
{
    setCache(oldManager->cache());
    setCookieJar(oldManager->cookieJar());
    setProxy(oldManager->proxy());
    setProxyFactory(oldManager->proxyFactory());

    msBase = helpers::f_getPath(sUrl.replace("file:///","").replace("file://","\\\\"));
    QStringList asDDBs = helpers::GetFilesFromDir(msBase, "*.ddb", true, qApp, 0);
    if(asDDBs.length() < 1) helpers::log("networkAccessManager:constr:!zip:'"+msBase+"'",LOG_WRN, qApp, 0, false);
    //else                  helpers::log("networkAccessManager:constr:zips("+QString::number(asDDBs.length())+"): indir:'"+msBase+"'",LOG_INF, qApp, 0, false);
    for(int i=0;i<asDDBs.length();i++)
    {
        QuaZip* pZip = new QuaZip(helpers::makeAbsFN(msBase, asDDBs.at(i)));
        if(!pZip->open(QuaZip::mdUnzip))
        {
            helpers::log("networkAccessManager:networkAccessManager:!zip:"+helpers::makeAbsFN(msBase, asDDBs.at(i)),LOG_ERR, qApp, 0, false);
            continue;
        }
        this->mZips.insert(pZip);
    }
}

int networkAccessManager::actualizeZips(QStringList asAbsFNZips)
{
    int iActualizedZips=0;
    for(int i=0;i<asAbsFNZips.size();i++)
    {
        QString sAbsFNZipWithTilde(asAbsFNZips.at(i));
        {
            QFileInfo f(sAbsFNZipWithTilde);sAbsFNZipWithTilde = f.canonicalFilePath().trimmed().lower().replace('\\','/');
        }

        bool bFound = false;
        QString sAllZIPFNs;
        foreach (QuaZip* pZip, this->mZips)
        {
            QString sAbsFNZip(pZip->getZipName());
            {
                QFileInfo f(sAbsFNZip);sAbsFNZip = f.canonicalFilePath().trimmed().lower().replace('\\','/');
            }
            sAllZIPFNs += ";"+sAbsFNZip;
            QString s(sAbsFNZipWithTilde);
            s = s.replace(sAbsFNZip,"").replace('~',' ').trimmed();
            if(s == "")
            {
                bFound = true;
                pZip->close();

                {
                    QString sAbsFNZipBAK = sAbsFNZip + ".bak";
                    while(QFile::exists(sAbsFNZipBAK))sAbsFNZipBAK += ".bak";
                    if(!QFile::rename(sAbsFNZip, sAbsFNZipBAK))
                        helpers::log("networkAccessManager:actualizeZips:!rename:"+sAbsFNZip+"->"+sAbsFNZipBAK,LOG_ERR, qApp, 0, false);
                }

                if(!QFile::rename(sAbsFNZipWithTilde, sAbsFNZip))
                    helpers::log("networkAccessManager:actualizeZips:!rename:"+sAbsFNZipWithTilde+"->"+sAbsFNZip,LOG_ERR, qApp, 0, false);
                if(!pZip->open(QuaZip::mdUnzip))
                    helpers::log("networkAccessManager:actualizeZips:!open:"+sAbsFNZipWithTilde+"->"+sAbsFNZip,LOG_ERR, qApp, 0, false);
                else
                    iActualizedZips++;
            }
        }
        if(!bFound)
        {
            helpers::log("networkAccessManager:actualizeZips:ZIPNF:"+sAbsFNZipWithTilde+"\nALLZIPS:"+sAllZIPFNs,LOG_ERR, qApp, 0, false);
        }
    }
    return iActualizedZips;
}

QNetworkReply* networkAccessManager::createRequest(QNetworkAccessManager::Operation op, const QNetworkRequest &req, QIODevice *device)
{
    if (op == QNetworkAccessManager::GetOperation)
    {
        QString sUrl = req.url().toString().replace("file:///","").replace("file://","\\\\");
        if((req.url().scheme() == "file") && !QFile::exists(sUrl))
        {
            //helpers::log("networkAccessManager:networkAccessManager:fnf:"+sUrl+"\n\turl:"+req.url().toString(),LOG_ERR, qApp, 0, false);
            //QString sUrl = req.url().toString().replace("file:///","");
            //helpers::log(QString("networkAccessManager:createRequest:")+req.url().scheme()+" ==> "+sUrl,LOG_INF, qApp, 0, true);
            //QThread* t = new QThread();
            //nr->moveToThread(t);
            //SHIWebView* p = (SHIWebView*)this->parent();
            //if(p)p->update();

            networkReply* nr = new networkReply(0, req, op, &this->mZips, msBase);
            /*
            static networkReply* nr = 0;
            if(!nr)
                nr = new networkReply(this);
            nr->dorequest(req, op, &(this->mZips), msBase);
            */
            nr->deleteLater();
            return nr;
        }
    }
    // defer to default
    return QNetworkAccessManager::createRequest(op, req, device);
}
networkAccessManager::~networkAccessManager()
{
    foreach (QuaZip* pZip, this->mZips)
    {
        if(pZip)pZip->close();
    }
    this->mZips.empty();
}
