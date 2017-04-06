#ifndef NETWORKACCESSMANAGER_H
#define NETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>
#include <QUrl>
#include "shiwebpage.h"
#include "helpers.h"
#include "shiwebview.h"
#include <QUrl>
#include <QDir>
#include <QSet>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include "quazip/quazip.h"
#include "quazip/quazipfile.h"

class networkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    QString msBase;
    QSet<QuaZip*> mZips;
    networkAccessManager(QNetworkAccessManager *oldManager, QString sUrl, QObject *parent = 0);
    ~networkAccessManager();
    int actualizeZips(QStringList asAbsFNZips);
protected:
    QNetworkReply* createRequest(QNetworkAccessManager::Operation op, const QNetworkRequest &req, QIODevice *device);
};

#endif // NETWORKACCESSMANAGER_H
