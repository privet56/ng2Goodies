#ifndef XML_H
#define XML_H

#include <QObject>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QSet>
#include <QDir>
#include <QFSFileEngine>
#include <QSettings>
#include <QTimer>
#include <QProcess>
#include <QDateTime>
#include <QMessageBox>
#include <QRegExp>
#include "helpers.h"

class xml : public QObject
{
    Q_OBJECT
public:
    xml(QString sAbsFN);
    QString msAbsFN;

    static QString GetRootEle(QString s);
    static QString getTagAttribs(QDomElement e);
    static void GetEles(QDomElement e, QSet<QString>* pTagnames, QList<QDomElement> *pEles, helpers* phelper);
};

#endif // XML_H
