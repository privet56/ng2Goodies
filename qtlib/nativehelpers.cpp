#include <QSettings>
#include <QFileDialog>
#include "nativehelpers.h"
#include "httpcomm.h"
#ifdef Q_WS_WIN
  #include "windows.h"
#endif

nativehelpers::nativehelpers(QObject *parent, helpers* helper) : QObject(parent)
{
    this->m_phelpers = helper;
}

bool nativehelpers::shellExecute(QString sAbsFN)
{
    sAbsFN = replacepeholders(sAbsFN);
    bool bUrlOK = false;

#ifdef Q_WS_WIN
    sAbsFN = sAbsFN.remove("file:///");
    sAbsFN.replace('/','\\');
    QString sOpen = "open";
    QString sEmpty = "";
    if((sAbsFN.indexOf(' ') > -1)&&(sAbsFN.indexOf('-') > -1)&&(sAbsFN.indexOf('=') > -1))
        bUrlOK = ::WinExec(sAbsFN, SW_SHOW) > 31;
    else
        bUrlOK = ((long)::ShellExecute(0, (const wchar_t*)sOpen.constData(), (const wchar_t*)sAbsFN.constData(), (const wchar_t*)sEmpty.constData(), (const wchar_t*)sEmpty.constData(), SW_SHOW)) > 32;
    if(m_phelpers)m_phelpers->log(QString(bUrlOK ? "":"!")+"shell:"+sAbsFN, bUrlOK ? LOG_INF:LOG_WRN, true);
#else
    bUrlOK = QDesktopServices::openUrl(QUrl(sAbsFN));
#endif
    return bUrlOK;
}
QString nativehelpers::getFC(QString sFN)
{
    sFN = replacepeholders(sFN);
    sFN.remove("file:///", Qt::CaseInsensitive).replace("file://","\\\\");
    QString sre = helpers::GetFileContent(sFN, true, qApp, 0);
    return sre;
}
bool nativehelpers::setFC(QString sFN, QString sFC)
{
    sFN = replacepeholders(sFN);
    sFN.remove("file:///", Qt::CaseInsensitive).replace("file://","\\\\");
    return helpers::WriteFileContent(sFN, sFC, true, qApp, 0);
}
QString nativehelpers::getCFG(QString sCfgEntryName)
{
    if(helpers::str_isempty(sCfgEntryName, true))
    {
        //arguments().at(0) is the program name
        if (qApp->arguments().size() > 1)
            return qApp->arguments().at(1);
        return "";
    }

    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
    QString s = settings.value(sCfgEntryName).toString();
    if(!helpers::str_isempty(s, true))return s;

    return helpers::GetCFG(sCfgEntryName, qApp, 0);
}
bool nativehelpers::setCFG(QString sCfgEntryName, QString sValue)
{
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue(sCfgEntryName, sValue);
    return true;
}
QString nativehelpers::getSaveFileName(QString sPattern)
{
    return QFileDialog::getSaveFileName(0, tr("Datei speichern unter"),"",tr(sPattern));
}
QString nativehelpers::getOpenFileName(QString sPattern)
{
    //sPattern = "bla 2.0 Dateien (*.bla2);;bla 1.x Dateien (*.bla1)";
    return QFileDialog::getOpenFileName(0, tr("Datei öffnen"),"",tr(sPattern));
}
bool nativehelpers::log(QString s)
{
    if(m_phelpers)m_phelpers->log(s, LOG_WRN, false);
    return true;
}
void nativehelpers::doQuit()
{
    qApp->closeAllWindows();
}
bool nativehelpers::_access(QString sAbsFN)
{
    sAbsFN = replacepeholders(sAbsFN);
    return QFile::exists(sAbsFN);
}
bool nativehelpers::copy(QString sAbsFNFrom,QString sAbsFNTo, bool bMakeReadOnly)
{
    sAbsFNFrom=replacepeholders(sAbsFNFrom);
    sAbsFNTo = replacepeholders(sAbsFNTo);
    //ff a file with the name newName already exists, copy() returns false
    if(!QFile::copy(sAbsFNFrom, sAbsFNTo))
    {
        return false;
    }

    if(bMakeReadOnly)
    {
        if(!QFile::setPermissions(sAbsFNTo,QFile::ReadOwner|QFile::ReadUser|QFile::ReadGroup|QFile::ReadOther))
            if(m_phelpers)m_phelpers->log("copy:!setPermissions:"+sAbsFNTo, LOG_ERR, true);
    }
    return true;
}
QString nativehelpers::replacepeholders(QString s)
{
    s = helpers::f_replaceplaceholders(s);
    s.replace("file:///", "");
    s.replace("file://", "\\\\");
    return s;
}
bool nativehelpers::doDelete(QString sAbsFN)
{
    sAbsFN = replacepeholders(sAbsFN);
    if(QFile::remove(sAbsFN))
        return true;

    if(!QFile::setPermissions(sAbsFN,QFile::permissions(sAbsFN)|QFile::ReadOwner|QFile::ReadUser|QFile::ReadGroup|QFile::ReadOther|QFile::WriteOwner|QFile::WriteUser|QFile::WriteGroup|QFile::WriteOther))
        if(m_phelpers)m_phelpers->log("doDelete:!setPermissions:"+sAbsFN, LOG_ERR, true);

    return QFile::remove(sAbsFN);
}
qint64 nativehelpers::getFileDate(QString sAbsFN)
{
    sAbsFN = replacepeholders(sAbsFN);
    qint64 ms = 0;
    if(sAbsFN.startsWith("http"))
    {
        QTime t;
        t.start();
        httpcomm c(this,QUrl(sAbsFN), m_phelpers);
        QByteArray bytes = c.head(QUrl(sAbsFN), QNetworkRequest::LastModifiedHeader);
        QString sLastMod(bytes);
        QDateTime dt = QDateTime::fromString(sLastMod, Qt::ISODate);
        if (dt.isNull() || !dt.isValid())
            dt = QDateTime::fromString(sLastMod);
        if (dt.isNull() || !dt.isValid())
        {
            if(m_phelpers)m_phelpers->log("getFileDate: !VALID:"+sLastMod+" URL:"+sAbsFN, LOG_ERR, qApp, 0, true);
            return 0;
        }
        qint64 ms = dt.toMSecsSinceEpoch();//uint sec  = dt.toTime_t();

        {
            QDateTime dt1(QDateTime::currentDateTime());
            QDateTime dt2(QDateTime::currentDateTime());
            dt1 = dt1.addYears(-33);
            dt2 = dt2.addYears(33);
            if(dt > dt2)
            {
                if(m_phelpers)m_phelpers->log("getFileDate: wrong(toobig):"+sLastMod+" ", LOG_ERR, qApp, 0, true);
            }
            if(dt < dt1)
            {
                if(m_phelpers)m_phelpers->log("getFileDate: wrong(toosmall):"+sLastMod+" = "+dt.toString("dd.MM.yyyy")+" < dt1:"+dt1.toString("dd.MM.yyyy"), LOG_ERR, qApp, 0, true);
            }

            QDateTime dtre = QDateTime::fromMSecsSinceEpoch(ms);
            //if(m_phelpers)m_phelpers->log("getFileDate:"+sLastMod+" = "+QString::number((long)ms)+"ms = "+QString::number(dt.toTime_t())+"sec = "+dtre.toString("dd.MM.yyyy")+" \t elapsedTime:"+helpers::t_elapsed(t.elapsed()), LOG_INF, qApp, 0, true);
            return ms;
        }
    }
    else
    {
        QFileInfo f(sAbsFN);
        if(!f.exists())
        {
            if(m_phelpers)m_phelpers->log("getFileDate:fnf:"+sAbsFN, LOG_WRN, qApp, 0, true);
            return 0;
        }
        QDateTime dt = f.lastModified();
        ms = dt.toMSecsSinceEpoch();
    }
    return ms;
}
bool nativehelpers::isWritable(QString sAbsFN)
{
    sAbsFN = replacepeholders(sAbsFN);
    QFileInfo f(sAbsFN);
    if(!f.exists())return true;
    return f.isWritable();          //TODO: test on Win7+ProgramFiles
    //if(QFile::permissions(sAbsFN) & QFile::WriteUser)return true;return false;
}
bool nativehelpers::makeReadOnly(QString sAbsFN, bool bReadOnly)
{
    sAbsFN = replacepeholders(sAbsFN);

    if(bReadOnly)
    {
        if(!QFile::setPermissions(sAbsFN,QFile::ReadOwner|QFile::ReadUser|QFile::ReadGroup|QFile::ReadOther))
        {
            if(m_phelpers)m_phelpers->log("makeReadOnly:!setPermissions:"+sAbsFN, LOG_ERR, true);
            return false;
        }
        return true;
    }
    else
    {
        if(!QFile::setPermissions(sAbsFN,QFile::permissions(sAbsFN)|QFile::ReadOwner|QFile::ReadUser|QFile::ReadGroup|QFile::ReadOther|QFile::WriteOwner|QFile::WriteUser|QFile::WriteGroup|QFile::WriteOther))
        {
            if(m_phelpers)m_phelpers->log("makeReadOnly:!setPermissions:"+sAbsFN, LOG_ERR, true);
            return false;
        }
        return true;
    }
}
