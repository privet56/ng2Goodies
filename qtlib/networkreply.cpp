#include "networkreply.h"
#include <QDebug>
#include <QFile>

networkReply::networkReply(QObject *parent) : QNetworkReply(parent)
{
    m_lSize = 0;
}

networkReply::networkReply(QObject *parent, const QNetworkRequest &req, const QNetworkAccessManager::Operation op, QSet<QuaZip*> *pZips, QString sBase) : QNetworkReply(parent)
{
    //m_content.reserve(1024*10);
    dorequest(req, op, pZips, sBase);
}
void networkReply::dorequest(const QNetworkRequest &req, const QNetworkAccessManager::Operation op, QSet<QuaZip*> *pZips, QString sBase)
{
    m_lSize = 0;
    setRequest(req);
    setUrl(req.url());
    setOperation(op);

    QNetworkReply::open(QIODevice::ReadOnly | QIODevice::Unbuffered);

    QString sAbsFN  = req.url().toString().replace("file:///","").replace("file://","\\\\").replace('\\','/').replace('ß','_');
    QFileInfo fi(sAbsFN);
    QString sExt    = fi.extension().lower();               //helpers::f_getext(sFN).lower();
#ifdef NETWORKREPLY_CHECKF
    QString sFN     = fi.baseName()+"."+fi.extension();     //helpers::f_getFileName(sAbsFN, true);
    QFile f(sAbsFN);
    if(f.exists())
    {
        if(!f.open(QFile::ReadOnly))
        {
            helpers::log("networkReply:fopen:"+f.fileName(),LOG_ERR, qApp, 0);
        }
        else
        {
            m_content = f.readAll();
            f.close();
        }
    }
    else
#endif
    {
        QString sRelFN = getRelFN(sBase, sAbsFN);
        QuaZip* pZipFirst = 0;
        bool bFound = false;

        foreach (QuaZip* pZip, *pZips)
        {
            if(!pZipFirst) pZipFirst = pZip;
#ifdef V1
            //if(!pZip->setCurrentFile(sRelFN) && !pZip->setCurrentFile(sRelFN.replace("96dpi/","96 dpi/")))
            if(!pZip->setCurrentFile(sRelFN))
            {
                //helpers::log("zip.setCurrentFile:'"+sRelFN+"'",LOG_ERR, qApp, 0);
                continue;
            }
            QuaZipFile file(pZip);
            file.open(QIODevice::ReadOnly);
            char c;
            while (file.getChar(&c)) m_content.append(c);
#else
            QTime now = QTime::currentTime();
            if(!pZip->setCurrentFile(sRelFN,QuaZip::csSensitive))
            {
                //helpers::log("zip.setCurrentFile:'"+sRelFN+"'",LOG_ERR, qApp, 0);
                continue;
            }
            static int __iUnZippedFile=0;
            QuaZipFile file(pZip);
            m_content.reserve(file.usize()+3);
            file.open(QIODevice::ReadOnly);
            m_content = file.readAll();
            if((__iUnZippedFile++ % 100) == 0)
            {
                qDebug() << "Unzip time: " << now.elapsed() << " ms";    //normally 140 - 160 ms
                //QCoreApplication::processEvents(QEventLoop::AllEvents, 0);
            }
#endif
            bFound = true;
            file.close();
            break;
        }
        if(!bFound)
        {
            static bool __bLogged = false;
            if(pZipFirst && !__bLogged)
            {
                __bLogged = true;
                pZipFirst->goToFirstFile();
                while(pZipFirst->goToNextFile())
                {
                    QuaZipFileInfo info;
                    pZipFirst->getCurrentFileInfo(&info);
                    if((info.name.indexOf("96") > -1) && (info.name.indexOf("qds") > -1))
                    {
                        helpers::log("networkReply:networkReply:firstInZIPfile:'"+info.name+"'",LOG_ERR, qApp, 0);
                        break;
                    }
                }
                helpers::log("networkReply:networkReply:fnf:'"+sRelFN+"'",LOG_ERR, qApp, 0);
            }
        }

        //helpers::log("zip.unzipped('"+sFN+"')(size:"+QString::number(m_content.size())+"):"+qApp->applicationDirPath()+QDir::separator()+"pics.zip",LOG_INF, qApp, 0);
    }

    m_lOffset = 0;
    m_lSize   = m_content.size();

    if(sExt == "png")                           setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
    else if((sExt == "bmp"))                    setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/bmp"));
    else if((sExt == "gif"))                    setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/gif"));
    else if((sExt == "jpg")||(sExt == "jpeg"))  setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    else if((sExt == "ini")||(sExt == "cfg"))   setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    else if((sExt == "js" ))                    setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/javascript"));
    else if((sExt == "css"))                    setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/css"));
    else
    {
        setHeader(QNetworkRequest::ContentTypeHeader, "binary/octet");//setHeader( QNetworkRequest::ContentTypeHeader, "text/html" );
    }

    setHeader(QNetworkRequest::ContentLengthHeader, QVariant(m_lSize));
    Qt::ConnectionType type = Qt::QueuedConnection;
    //Qt::ConnectionType type = Qt::DirectConnection;
    QMetaObject::invokeMethod(this, "metaDataChanged"   ,type);
    QMetaObject::invokeMethod(this, "downloadProgress"  ,type, Q_ARG(qint64, m_lSize), Q_ARG(qint64, m_lSize));
    QMetaObject::invokeMethod(this, "readyRead"         ,type);
    QMetaObject::invokeMethod(this, "finished"          ,type);
}

QString networkReply::getRelFN(QString sBase, QString sAbsFN)
{
    QString sbase(sBase.replace( '\\','/'));  sbase.toLower().replace( '\\','/');
    QString sabsfn(sAbsFN.replace('\\','/')); sabsfn.toLower().replace('\\','/');
    if(!sbase.endsWith('/'))
        sbase += '/';
    if(!sabsfn.startsWith(sbase))
    {
        sbase = QFileInfo(sbase).canonicalFilePath();
        if(!sbase.endsWith('/'))sbase += '/';
        sbase.replace( '\\','/');
        sbase.toLower().replace( '\\','/');
    }
    if(!sabsfn.startsWith(sbase))
    {
        helpers::log("networkReply:networkReply:!rel:'"+sabsfn+"'\n\tbase:'"+sbase+"'",LOG_ERR, qApp, 0);
        return sAbsFN;
    }
    return sAbsFN.midRef(sbase.length()).toString();
}

void networkReply::abort()
{
    QNetworkReply::close();
}
qint64 networkReply::bytesAvailable() const
{
    return m_lSize - m_lOffset;
}
bool networkReply::isSequential() const
{
    return false;
    return true;
}
qint64 networkReply::readData(char* pData, qint64 lMaxSize)
{
    if (m_lOffset >= m_lSize)
    {
        return -1;
    }
    qint64 lCount = qMin(lMaxSize, m_lSize - m_lOffset);
    memcpy(pData, m_content.constData() + m_lOffset, lCount);
    m_lOffset += lCount;
    return lCount;
}
