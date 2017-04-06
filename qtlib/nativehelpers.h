#ifndef NATIVEHELPERS_H
#define NATIVEHELPERS_H

#include <QObject>
#include <QDomDocument>
#include <QDomElement>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QFile>
#include <QtCore/QTime>
#include "helpers.h"

class nativehelpers : public QObject
{
    Q_OBJECT
public:
    nativehelpers(QObject *parent, helpers* helper=0);
    helpers* m_phelpers;

public slots:
    bool shellExecute(QString sAbsFN);
    QString getFC(QString sFN);
    bool setFC(QString sFN, QString sFC);
    QString getCFG(QString sCfgEntryName);
    bool setCFG(QString sCfgEntryName, QString sValue);
    QString getSaveFileName(QString sPattern);
    QString getOpenFileName(QString sPattern);
    bool log(QString s);
    void doQuit();
    bool _access(QString sAbsFN);
    bool copy(QString sAbsFNFrom,QString sAbsFNTo, bool bMakeReadOnly);
    QString replacepeholders(QString s);
    bool doDelete(QString sAbsFN);
    qint64 getFileDate(QString sAbsFN);
    bool isWritable(QString sAbsFN);
    bool makeReadOnly(QString sAbsFN, bool bReadOnly);
};

#endif // NATIVEHELPERS_H
