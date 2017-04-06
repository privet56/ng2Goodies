#ifndef HELPERS_H
#define HELPERS_H

#include <QObject>
#include <QtGui/QApplication>
#include <QObject>

#define LOG_ERR 1
#define LOG_WRN 2
#define LOG_INF 3

class helpers : public QObject
{
    Q_OBJECT
public:
    QApplication* m_pApp;
    QObject* m_pLogTarget;

    helpers(QObject *parent, QApplication* pApp,QObject* pLogTarget);

    bool emptydir(QString sDir);
    static bool emptydir(QString sDir, QApplication* pApp, QObject* pLogTarget);
    static int emptydir(QString sDir, QApplication* pApp, QObject* pLogTarget, QString sPattern, bool bRecursive);

    bool copydir(QString sFrom,QString sTo,QString sPattern, bool bWarnIfNotFound);
    static bool copydir(QString sFrom,QString sTo,QString sPattern, bool bWarnIfNotFound, QApplication* pApp, QObject* pLogTarget);
    static bool copydirifdifferent(QString sFrom,QString sTo,QString sPattern, bool bWarnIfNotFound, QApplication* pApp, QObject* pLogTarget);

    static QString makeAbsFN(QString sBase, QString sAppend);

    bool copydir(QString sFr, QString sTo);
    static bool copydir(QString sFr, QString sTo, QApplication* pApp, QObject* pLogTarget);
    static bool copydirifdifferent(QString sFr, QString sTo, QApplication* pApp, QObject* pLogTarget);

    QStringList GetFilesFromDir(QString sDir,QString sPattern, bool bWarnIfNotFound);
    static QStringList GetFilesFromDir(QString sDir,QString sPattern, bool bWarnIfNotFound, QApplication* pApp, QObject* pLogTarget);

    void log(QString s, int iLevel, bool bWithDate=true);
    static void log(QString s, int iLevel, QApplication* pApp, QObject* pLogTarget, bool bWithDate=true);

    QString getarg(QString sEntryName);
    static QString getarg(QString sEntryName, QApplication* pApp, QObject* pLogTarget);

    QString GetCFG(QString sEntryName, QString sDefault="", QString sSection="CFG", QString sFN="");
    static QString GetCFG(QString sEntryName, QApplication* pApp, QObject* pLogTarget, QString sDefault="", QString sSection="CFG", QString sFN="");
    static bool GetCFG_bool(QString sEntryName, QApplication* pApp, QObject* pLogTarget, QString sDefault="", QString sSection="CFG", QString sFN="", bool bDefault=false);
    static int GetCFG_int(QString sEntryName, QApplication* pApp, QObject* pLogTarget, QString sDefault="", QString sSection="CFG", QString sFN="", int iDefault=0);
    static void SetCFG(QString sEntryName, QString sEntryValue, QApplication* pApp, QObject* pLogTarget, QString sSection="CFG", QString sFN="");

    static QString str_removeright(QString s, QString srem);
    static bool str_isempty(QString s, bool bTrim);
    static QString str_xmalstr(QString s, int ix);

    static QString GetFileContent(QString sAbsFN, bool bWarnIfEmpty, QApplication* pApp, QObject* pLogTarget);
    static bool WriteFileContent(QString sAbsFN, QString sFC, bool bWarnOnError, QApplication* pApp, QObject* pLogTarget);
    static bool AppendFileContent(QString sAbsFN, QString sFC, bool bWarnOnError, QApplication* pApp, QObject* pLogTarget);

    static QString f_getPath(QString sFN);
    static QString f_getFileName(QString sFN, bool bWithExt);
    static QString f_replaceext(QString sFN, QString sNewExt);
    static QString f_getext(QString sFN);
    static QString f_replaceplaceholders(QString s);

    static void qWait(int ms);

    static QString str_FormatFromHtmlEntities(QString s, QString sProtect="");
    static QString str_FormatToHtmlEntities(QString s, QString sProtect="");

    static QString t_elapsed(int iElapsedMSecs);

    QString getUrlFromCFG(QString sCfgEntryName);
    static bool f_remove(QString sAbsFN);
    static bool mkdirfull(QString sDir);
};

class emitter : public QObject
{
    Q_OBJECT
public:
    emitter(QObject* parent);
    void emitlog(QString s, int iLevel, QApplication* pApp, QObject* pLogTarget, bool bWithDate);
signals:
    void log(QString s, int iLevel, QApplication* pApp, bool bWithDate);
};


#ifdef UNICODE
#define QStringToTCHAR(x)     (wchar_t*) x.utf16()
#define PQStringToTCHAR(x)    (wchar_t*) x->utf16()
#define TCHARToQString(x)     QString::fromUtf16((x))
#define TCHARToQStringN(x,y)  QString::fromUtf16((x),(y))
#else
#define QStringToTCHAR(x)     x.toLocal8Bit().constData()
#define PQStringToTCHAR(x)    x->toLocal8Bit().constData()
#define TCHARToQString(x)     QString::fromLocal8Bit((x))
#define TCHARToQStringN(x,y)  QString::fromLocal8Bit((x),(y))
#endif


#endif // HELPERS_H
