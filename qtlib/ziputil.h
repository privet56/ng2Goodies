#ifndef ZIPUTIL_H
#define ZIPUTIL_H

#include <QObject>
#include <QUrl>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include "helpers.h"
#include "quazip/quazip.h"
#include "quazip/quazipfile.h"

class ziputil : public QObject
{
    Q_OBJECT
public:
    explicit ziputil(QObject *parent = 0);

public:
    static int zipdir(QString sDir, QString sZip, helpers *phelpers);
    static int zipdir(QString sDir, QString sDirRoot, QuaZip* pZip, helpers *phelpers);

signals:

public slots:

};

#endif // ZIPUTIL_H
