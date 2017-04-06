#ifndef QMSOFFICE_H
#define QMSOFFICE_H

#include <QObject>
#include <QAxObject>
#include "../../../../_Projekt.lfd/shi/IPTools/qt/helpers.h"


//.PRO: CONFIG += qaxcontainer


class qmsoffice : public QObject
{
    Q_OBJECT
public:
    explicit qmsoffice(QObject *parent = 0, helpers* helper=0);
    helpers* m_phelper;
    void log(QString s, int iLogLevel = LOG_ERR);
    bool openAsNew(QString sAbsFNhtml, QString sAbsFNdot);

protected:
    QAxObject* querySubObject(QAxObject* pO, QString sSubObject);
    void embedpics(QAxObject* pNewDoc, QAxObject* pNewDocContent);
    int embedpics(QAxObject* pDoc, QAxObject* pContentWithPics, QAxObject* pDocContent);

signals:

public slots:
    void SlotComException(int i, const QString& s1, const QString& s2, const QString& s3);

};

#endif // QMSOFFICE_H
