#ifndef NETWORKREPLY_H
#define NETWORKREPLY_H

#include <QNetworkReply>
#include <QUrl>
#include <QSet>
#include "shiwebpage.h"
#include "helpers.h"
#include "shiwebview.h"
#include "quazip/quazip.h"
#include "quazip/quazipfile.h"

class networkReply : public QNetworkReply
{
    Q_OBJECT
public:
    void dorequest(const QNetworkRequest &req, const QNetworkAccessManager::Operation op, QSet<QuaZip*> *pZips, QString sBase);
    networkReply(QObject *parent, const QNetworkRequest &req, const QNetworkAccessManager::Operation op, QSet<QuaZip*> *pZips, QString sBase);
    networkReply(QObject *parent);
    void networkReply::abort();
    qint64 bytesAvailable() const;
    bool isSequential() const;
    qint64 readData(char* pData, qint64 lMaxSize);
    QString getRelFN(QString sBase, QString sAbsFN);

protected:
    QByteArray m_content;
    qint64 m_lOffset;
    qint64 m_lSize;

signals:

public slots:

};

#endif // NETWORKREPLY_H
