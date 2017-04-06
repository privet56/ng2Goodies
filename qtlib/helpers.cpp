#include "helpers.h"
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QFSFileEngine>
#include <QSettings>
#include <QTimer>
#include <QProcess>
#include <QDateTime>
#include <QMessageBox>
#include <QDesktopServices>
#ifdef Q_WS_WIN
#include "windows.h"
#include "shlobj.h" //SHGetSpecialFolderPath
#endif

emitter::emitter(QObject* parent) : QObject(parent)
{

}
void emitter::emitlog(QString s, int iLevel, QApplication* pApp, QObject* pLogTarget, bool bWithDate)
{
    connect(this,SIGNAL(log(QString,int,QApplication*,bool)),pLogTarget,SLOT(log(QString,int,QApplication*,bool)));
    emit log(s,iLevel,pApp,bWithDate);
}

helpers::helpers(QObject *parent, QApplication* pApp, QObject* pLogTarget) : QObject(parent)
{
    m_pApp = pApp;
    m_pLogTarget = pLogTarget;
}

void helpers::log(QString s, int iLevel, QApplication* pApp, QObject* pLogTarget, bool bWithDate/*=true*/)
{
    QString sLevel("ERR");
    {
        if(iLevel == LOG_INF)       sLevel = "INF";
        else if(iLevel == LOG_WRN)  sLevel = "WRN";
        qDebug() << sLevel+":"+s;
    }

    if (pLogTarget != 0)
    {
#ifndef USE_EMITTER
        emitter e(0);
        e.emitlog(s, iLevel, pApp, pLogTarget, bWithDate);
#else
        QMetaObject::invokeMethod(pLogTarget, "log", Qt::AutoConnection, /*Q_RETURN_ARG(...),*/ Q_ARG(QString, s), Q_ARG(int, iLevel), Q_ARG(QApplication*, pApp), Q_ARG(bool,bWithDate));
#endif
        //pLogTarget->log(s, iLevel, pApp, bWithDate);
    }
    if(!pApp)return;

    QString sDate = bWithDate ? QDateTime::currentDateTime().toString("yyyy:MM:dd hh:mm:ss.zzz:") : "";

    static bool bDebug = false;
    static bool bDebugDeterminated = false;

    if(!bDebugDeterminated)
    {
        bDebugDeterminated = true;
        bDebug = (GetCFG("debug", pApp, pLogTarget) == "1");
    }
    if(bDebug)
    {
#ifdef Q_WS_WIN
        static QString sLogFN = pApp->applicationFilePath().left(pApp->applicationFilePath().length()-3)+"log";
#else
        static QString sLogFN = pApp->applicationFilePath()+".log";
#endif
        static bool bLogFNChecked = false;
        if(!bLogFNChecked)
        {
            bLogFNChecked = true;
            static QString sCFG = helpers::getarg("cfg", pApp, pLogTarget);
            if(QFile::exists(sCFG))
            {
                sLogFN = helpers::f_replaceext(sCFG,"log");
            }
        }

        FILE *fp = fopen(sLogFN.toAscii(), "a+"/*append*/);
        if(!fp)
        {
            sLogFN = QDir::tempPath()+"/.log";
            fp = fopen(sLogFN.toAscii(), "a+"/*append*/);
            if(!fp)
                return;
        }
        //fputs(QString(sDate+(bWithDate ? " " : "")+sLevel+" "+s+"\n").toAscii(),fp);
        fputs(QString(sDate+" "+sLevel+" "+s+"\n").toAscii(),fp);
        fclose(fp);
    }
}
void helpers::log(QString s, int iLevel, bool bWithDate/*=true*/)
{
    log(s, iLevel, m_pApp, m_pLogTarget, bWithDate);
}

bool helpers::copydir(QString sFr, QString sTo)
{
    return copydir(sFr, sTo, m_pApp, m_pLogTarget);
}
bool helpers::copydir(QString sFr, QString sTo, QApplication* pApp, QObject* pLogTarget)
{
    QDir src(sFr);
    QDir dst(sTo);
    QFileInfoList contents = src.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (QFileInfo fileInfo, contents)
    {
        QString fileName = fileInfo.fileName();
        QString srcFilePath = src.absoluteFilePath(fileName);
        QString dstFilePath = dst.absoluteFilePath(fileName);
        if (fileInfo.isDir())
        {
            QString sdstsubdir = makeAbsFN(sTo,fileName);
            QDir dstsubdir(sdstsubdir);
            if(!dstsubdir.exists() && !dst.mkdir(fileName))
            {
                log("copydir:!mkdir:"+makeAbsFN(sTo,fileName),LOG_ERR, pApp, pLogTarget);
                return false;
            }
            if(!copydir(srcFilePath, dstFilePath, pApp, pLogTarget))
                return false;
        }
        else if (fileInfo.isFile())
        {
            QFile::remove(dstFilePath+"____");
            QFile::rename(dstFilePath,dstFilePath+"____");
            if (!QFile::copy(srcFilePath, dstFilePath))
            {
                QFile::rename(dstFilePath+"____",dstFilePath);
                log("copydir:!copy:"+srcFilePath+"\n\tTO:"+dstFilePath,LOG_ERR, pApp, pLogTarget);
                return false;
            }
            QFile::remove(dstFilePath+"____");
            /*  //returns false if target exists
            if (!QFile::copy(srcFilePath, dstFilePath))
            {
                return false;
            }
            */
        }
        else
        {
            log("copydir:unexpected:"+srcFilePath,LOG_WRN, pApp, pLogTarget);
        }
    }
    return true;
}
bool helpers::copydirifdifferent(QString sFr, QString sTo, QApplication* pApp, QObject* pLogTarget)
{
    QDir src(sFr);
    QDir dst(sTo);
    QFileInfoList contents = src.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (QFileInfo fileInfo, contents)
    {
        QString fileName = fileInfo.fileName();
        QString srcFilePath = src.absoluteFilePath(fileName);
        QString dstFilePath = dst.absoluteFilePath(fileName);
        if (fileInfo.isDir())
        {
            QString sdstsubdir = makeAbsFN(sTo,fileName);
            QDir dstsubdir(sdstsubdir);
            if(!dstsubdir.exists() && !dst.mkdir(fileName))
            {
                log("copydirifdifferent:!mkdir:"+makeAbsFN(sTo,fileName),LOG_ERR, pApp, pLogTarget);
                return false;
            }
            if(!copydirifdifferent(srcFilePath, dstFilePath, pApp, pLogTarget))
                return false;
        }
        else if (fileInfo.isFile())
        {
            if(QFile::exists(dstFilePath))
            {
                QFileInfo fdstFilePath(dstFilePath);
                if(fdstFilePath.lastModified() == fileInfo.lastModified())
                {
                    continue;
                }
            }

            QFile::remove(dstFilePath+"____");
            QFile::rename(dstFilePath,dstFilePath+"____");
            if (!QFile::copy(srcFilePath, dstFilePath))
            {
                QFile::rename(dstFilePath+"____",dstFilePath);
                log("copydirifdifferent:!copy:"+srcFilePath+"\n\tTO:"+dstFilePath,LOG_ERR, pApp, pLogTarget);
                return false;
            }
            QFile::remove(dstFilePath+"____");
            /*  //returns false if target exists
            if (!QFile::copy(srcFilePath, dstFilePath))
            {
                return false;
            }
            */
        }
        else
        {
            log("copydirifdifferent:unexpected:"+srcFilePath,LOG_WRN, pApp, pLogTarget);
        }
    }
    return true;
}

bool helpers::emptydir(QString sDir)
{
    return emptydir(sDir, m_pApp, m_pLogTarget);
}
bool helpers::emptydir(QString sDir, QApplication* pApp, QObject* pLogTarget)
{
    QDir src(sDir);
    QFileInfoList contents = src.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (QFileInfo fileInfo, contents)
    {
        QString fileName = fileInfo.fileName();
        QString srcFilePath = src.absoluteFilePath(fileName);
        if (fileInfo.isDir())
        {
            QDir dstsubdir(srcFilePath);
            emptydir(srcFilePath, pApp, pLogTarget);
            if(!src.rmdir(fileName))
                log("emptydir:!dir.rmdir("+fileName+"):in:'"+sDir+"'",LOG_ERR, pApp, pLogTarget);
        }
        else if (fileInfo.isFile())
        {
            if(!QFile::remove(srcFilePath))
                log("emptydir:!file.remove:"+srcFilePath,LOG_ERR, pApp, pLogTarget);
        }
        else
        {
            log("emptydir:unexpected:"+srcFilePath,LOG_WRN, pApp, pLogTarget);
        }
    }
    return true;
}
int helpers::emptydir(QString sDir, QApplication* pApp, QObject* pLogTarget, QString sPattern, bool bRecursive)
{
    QDir d(sDir);
    d.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    QStringList filters;
    filters << sPattern.split(' ');
    d.setNameFilters(filters);
    QStringList fs = d.entryList();

    int iRE = 0;

    for(int i=0; i < fs.length(); i++)
    {
        QString sFN(makeAbsFN(sDir,fs.at(i)));
        QFileInfo f(sFN);
        if(f.isDir())
        {
            if(bRecursive) iRE += emptydir(sFN, pApp, pLogTarget, sPattern, bRecursive);
        }
        else if(f.isFile())
        {
            if(!QFile::remove(sFN))
                log("emptydir:!file.remove:"+sFN,LOG_ERR, pApp, pLogTarget);
            else
                iRE++;
        }
        else
        {
            log("emptydir:unexpected:"+sFN,LOG_WRN, pApp, pLogTarget);
        }
    }

    return iRE;
}
QString helpers::getarg(QString sEntryName)
{
    return getarg(sEntryName, m_pApp, m_pLogTarget);
}
QString helpers::getarg(QString sEntryName, QApplication* pApp, QObject* pLogTarget)
{
    if(!pApp)return "";
    sEntryName = sEntryName.trimmed().toLower();

    for(int i=0; i < pApp->argc(); i++)
    {
        QString sarg(pApp->argv()[i]);
        sarg = sarg.trimmed();
        int iE = sarg.indexOf('=');
        if (iE > 0)
        {
            QString sargname(sarg.left(iE).trimmed());
            bool bE = (sargname.compare(sEntryName, Qt::CaseInsensitive) == 0);
            bool bE_ = (bE || (sargname.compare("-"+sEntryName, Qt::CaseInsensitive) == 0));
            if(bE || bE_)
            {
                QString sargval(sarg.midRef(iE+1).toString());
                if(sargval.startsWith('"') && sargval.endsWith('"'))
                {
                    sargval = sargval.left(sargval.size()-1);
                    sargval = sargval.midRef(1).toString();
                }
                return sargval;
            }
        }
    }
    return "";
}

bool helpers::GetCFG_bool(QString sEntryName, QApplication* pApp, QObject* pLogTarget, QString sDefault/*=""*/, QString sSection/*="CFG"*/, QString sFN/*=""*/, bool bDefault/*=false*/)
{
    QString sEntryVal = GetCFG(sEntryName, pApp, pLogTarget, sDefault, sSection, sFN).toLower().trimmed();

    if(helpers::str_isempty(sEntryVal, true))
        return bDefault;

    if((sEntryVal == "1")||(sEntryVal == "true") ||(sEntryVal == "yes")||(sEntryVal == "ja"))
        return true;
    if((sEntryVal == "0")||(sEntryVal == "false")||(sEntryVal == "not")||(sEntryVal == "no")||(sEntryVal == "nein"))
        return false;

    log("GetCFG_bool:unknown.cfgentry:'"+sEntryVal+"'",LOG_WRN, pApp, pLogTarget);
    return bDefault;
}
int helpers::GetCFG_int(QString sEntryName, QApplication* pApp, QObject* pLogTarget, QString sDefault/*=""*/, QString sSection/*="CFG"*/, QString sFN/*=""*/, int iDefault/*=0*/)
{
    QString sEntryVal = GetCFG(sEntryName, pApp, pLogTarget, sDefault, sSection, sFN).toLower().trimmed();

    if(helpers::str_isempty(sEntryVal, true))
        return iDefault;
    bool bok = false;
    int iRe = sEntryVal.toInt(&bok);
    if(!bok)return iDefault;
    return iRe;
}

QString helpers::GetCFG(QString sEntryName, QString sDefault/*=""*/, QString sSection/*="CFG"*/, QString sFN/*=""*/)
{
    return GetCFG(sEntryName, m_pApp, m_pLogTarget, sDefault, sSection, sFN);
}
QString helpers::GetCFG(QString sEntryName, QApplication* pApp, QObject* pLogTarget, QString sDefault/*=""*/, QString sSection/*="CFG"*/, QString sFN/*=""*/)
{
    QString sValue = "";
    if(sFN.isEmpty())
    {
        if((sSection == "CFG") && (sFN.isNull() || sFN.isEmpty()))
        {
             sValue = getarg(sEntryName, pApp, pLogTarget);
        }

        if((sValue.isNull() || sValue.isEmpty()) && (pApp != 0) && (pApp->arguments().length() > 1) && QFile::exists(pApp->arguments().at(1)) && pApp->arguments().at(1).endsWith(".cfg", Qt::CaseInsensitive))
        {
            sFN = pApp->arguments().at(1);
        }
        else if((sValue.isNull() || sValue.isEmpty()) && (QFile::exists(getarg("cfg", pApp, pLogTarget))))
        {
            sFN = getarg("cfg", pApp, pLogTarget);
        }
        else if(!sValue.isNull() && !sValue.isEmpty())
        {
            //value already determinated...
        }
        else if(pApp != 0)
        {
            //QLibraryInfo::location(QLibraryInfo::BinariesPath)
            //log("appdirpath:"+m_pApp->applicationDirPath(),LOG_INF);    //dir of exe
            //log("appname::::"+m_pApp->applicationName(),LOG_INF);       //empty
            //log("appfilepth:"+m_pApp->applicationFilePath(),LOG_INF);   //dir+fn of exe
#ifdef Q_WS_WIN
            sFN = pApp->applicationFilePath().left(pApp->applicationFilePath().length()-3)+"cfg";
#else
  #ifdef Q_WS_MAC
            sFN = pApp->applicationDirPath()+"/../../../"+helpers::f_getFileName(pApp->applicationFilePath(), false)+".cfg";
  #else
            sFN = pApp->applicationFilePath()+".cfg";
  #endif
#endif
        }
    }

    static QString sBaseDir;
    if(sBaseDir.isNull() || sBaseDir.isEmpty())
    {
        sBaseDir = "%%%";
        sBaseDir = GetCFG("basedir", pApp, pLogTarget);
    }

    if(!QFile::exists(sFN) && (sValue.isNull() || sValue.isEmpty()))
    {
        log("logfn:fnf:'"+sFN+"'",LOG_WRN, pApp, pLogTarget);
        sDefault.replace("%BASEDIR%", sBaseDir);
#ifdef Q_WS_MAC
        sDefault.replace("%CURRENTDIR%", pApp->applicationDirPath()+"/../../..");
#else
        sDefault.replace("%CURRENTDIR%", pApp->applicationDirPath().replace('\\','/'));
#endif
        sDefault.replace("%20%20", " ");
        return sDefault;
    }

    if (sValue.isNull() || sValue.isEmpty())
    {
        sValue = QSettings(sFN, QSettings::IniFormat, 0).value((sSection+"/"+sEntryName), sDefault).toString();
        //if(sEntryName == "url")QMessageBox::critical(0,sFN,(sSection+"/"+sEntryName)+"\nsValue:"+sValue,1,0,0);
    }

    if (sValue.isNull() || sValue.isEmpty())
        sValue = sDefault;

    if(sValue.indexOf('%') > -1)
    {
        sValue.replace("%BASEDIR%", sBaseDir);
#ifdef Q_WS_MAC
        sValue.replace("%CURRENTDIR%", pApp->applicationDirPath()+"/../../..");
#else
        sValue.replace("%CURRENTDIR%", pApp->applicationDirPath().replace('\\','/'));
#endif
        sValue.replace("%20%20", " ");
    }
    return sValue;
    //QSettings stt(sFN, QSettings::IniFormat, this);
    //return stt.value((sSection+"/"+sEntryName), sDefault).toString();
}
QString helpers::makeAbsFN(QString sBase, QString sAppend)
{
    sBase   = sBase.replace('\\'  , QDir::separator()).trimmed();
    sBase   = sBase.replace('/'   , QDir::separator());
    sAppend = sAppend.replace('\\', QDir::separator()).trimmed();
    sAppend = sAppend.replace('/' , QDir::separator());

    if(sAppend.isNull() || sAppend.isEmpty())   return sBase;
    if(sBase.isNull() || sBase.isEmpty())       return sAppend;

    if((sAppend.length() > 1) && ((sAppend.at(1) == ':') || sAppend.startsWith(QString(QDir::separator())+QDir::separator())))
    {
        return sAppend;
    }
    bool bBase = sBase.endsWith(QDir::separator());
    bool bAppd = sAppend.startsWith(QDir::separator());
    if(bBase && bAppd)
    {
        return sBase.left(sBase.length()-1) + sAppend;
    }
    if(bBase || bAppd)
    {
        return sBase + sAppend;
    }
    return sBase +QDir::separator()+ sAppend;
}

QStringList helpers::GetFilesFromDir(QString sDir,QString sPattern, bool bWarnIfNotFound)
{
    return GetFilesFromDir(sDir, sPattern, bWarnIfNotFound, m_pApp, m_pLogTarget);
}
QStringList helpers::GetFilesFromDir(QString sDir,QString sPattern, bool bWarnIfNotFound, QApplication* pApp, QObject* pLogTarget)
{
    QDir d(sDir);
    if(!d.exists())
    {
        log("getfilesfromdir:dirnf:"+sDir, LOG_ERR, pApp, pLogTarget);
        return QStringList();
    }
    d.setFilter(QDir::Files);
    QStringList filters;
    filters << sPattern;
    d.setNameFilters(filters);
    QStringList fs = d.entryList();
    if(bWarnIfNotFound && fs.isEmpty())
        log("getfilesfromdir:!fnf4pattern:"+sPattern+"  indir:"+sDir, LOG_WRN, pApp, pLogTarget);
    return fs;
}
bool helpers::copydir(QString sFrom,QString sTo,QString sPattern, bool bWarnIfNotFound)
{
    return copydir(sFrom, sTo, sPattern, bWarnIfNotFound, m_pApp, m_pLogTarget);
}
bool helpers::copydir(QString sFrom,QString sTo,QString sPattern, bool bWarnIfNotFound, QApplication* pApp, QObject* pLogTarget)
{
    QDir dfrom(sFrom);
    QDir dto(sTo);
    if(!dfrom.exists())
    {
        log("copydir(p):dirnf:"+sFrom, LOG_ERR, pApp, pLogTarget);
        return false;
    }
    if(!dto.exists() && !dto.mkpath(sTo))
    {
        log("copydir(p):!mkpath:"+sTo, LOG_ERR, pApp, pLogTarget);
        return false;
    }

    dfrom.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    QStringList filters;
    filters << sPattern.split(' ');
    dfrom.setNameFilters(filters);
    QStringList fs = dfrom.entryList();
    if(bWarnIfNotFound && fs.isEmpty())
        log("copydir(p):!fnf4pattern:'"+sPattern+"'  indir:"+sFrom, LOG_WRN, pApp, pLogTarget);
    for(int i=0; i < fs.length(); i++)
    {
        QString sFNFrom(makeAbsFN(sFrom,fs.at(i)));
        QString sFNTo(makeAbsFN(sTo,fs.at(i)));
        QFileInfo f(sFNFrom);
        if(f.isDir())
        {
            QDir subdirto(sFNTo);
            if(!subdirto.exists(sFNTo) && !subdirto.mkpath(sFNTo))
            {
                log("copydir(p):!mkpath:"+sFNTo, LOG_ERR, pApp, pLogTarget);
                return false;
            }
            if(!copydir(sFNFrom, sFNTo, sPattern, bWarnIfNotFound, pApp, pLogTarget))
                return false;
        }
        else
        {
            QFile::remove(sFNTo+"____");
            QFile::rename(sFNTo,sFNTo+"____");
#ifdef Q_WS_WIN
            if (!QFile::copy(sFNFrom, sFNTo) && !::CopyFile((const wchar_t*)sFNFrom.constData(), (const wchar_t*)sFNTo.constData(), false))
#else
            if (!QFile::copy(sFNFrom, sFNTo))
#endif
            {
#ifdef Q_WS_WIN
                LPVOID lpMsgBuf;
                FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS,NULL,GetLastError(),0, /* Default language */(LPTSTR) &lpMsgBuf,0,NULL);
                QString sE((char*)lpMsgBuf);
                LocalFree(lpMsgBuf);
                log("copydir(p):!copy:"+sFNFrom+"\n\tTO:"+sFNTo+"\n\tsE:"+sE,LOG_ERR, pApp, pLogTarget);
#else
                log("copydir(p):!copy:"+sFNFrom+"\n\tTO:"+sFNTo,LOG_ERR, pApp, pLogTarget);
#endif
                QFile::rename(sFNTo+"____",sFNTo);
                return false;
            }
            QFile::remove(sFNTo+"____");
        }
    }
    return true;
}
bool helpers::copydirifdifferent(QString sFrom,QString sTo,QString sPattern, bool bWarnIfNotFound, QApplication* pApp, QObject* pLogTarget)
{
    QDir dfrom(sFrom);
    QDir dto(sTo);
    if(!dfrom.exists())
    {
        log("copydirifdifferent(p):dirnf:"+sFrom, LOG_ERR, pApp, pLogTarget);
        return false;
    }
    if(!dto.exists() && !dto.mkpath(sTo))
    {
        log("copydirifdifferent(p):!mkpath:"+sTo, LOG_ERR, pApp, pLogTarget);
        return false;
    }

    dfrom.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    QStringList filters;
    filters << sPattern.split(' ');
    dfrom.setNameFilters(filters);
    QStringList fs = dfrom.entryList();
    if(bWarnIfNotFound && fs.isEmpty())
    {
        log("copydirifdifferent(p):!fnf4pattern:'"+sPattern+"'  indir:"+sFrom, LOG_WRN, pApp, pLogTarget);
    }
    for(int i=0; i < fs.length(); i++)
    {
        QString sFNFrom(makeAbsFN(sFrom,fs.at(i)));
        QString sFNTo(makeAbsFN(sTo,fs.at(i)));
        QFileInfo f(sFNFrom);
        if(f.isDir())
        {
            QDir subdirto(sFNTo);
            if(!subdirto.exists(sFNTo) && !subdirto.mkpath(sFNTo))
            {
                log("copydirifdifferent(p):!mkpath:"+sFNTo, LOG_ERR, pApp, pLogTarget);
                return false;
            }
            if(!copydirifdifferent(sFNFrom, sFNTo, sPattern, bWarnIfNotFound, pApp, pLogTarget))
            {
                return false;
            }
        }
        else
        {
            if(QFile::exists(sFNTo))
            {
                QFileInfo fdstFilePath(sFNTo);
                QFileInfo fsrcFilePath(sFNFrom);
                if(fdstFilePath.lastModified() == fsrcFilePath.lastModified())
                {
                    continue;
                }
            }

            QFile::remove(sFNTo+"____");
            QFile::rename(sFNTo,sFNTo+"____");
#ifdef Q_WS_WIN
            if (!QFile::copy(sFNFrom, sFNTo) && !::CopyFile((const wchar_t*)sFNFrom.constData(), (const wchar_t*)sFNTo.constData(), false))
#else
            if (!QFile::copy(sFNFrom, sFNTo))
#endif
            {
#ifdef Q_WS_WIN
                LPVOID lpMsgBuf;
                FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS,NULL,GetLastError(),0, /* Default language */(LPTSTR) &lpMsgBuf,0,NULL);
                QString sE((char*)lpMsgBuf);
                LocalFree(lpMsgBuf);
                log("copydir(p):!copy:"+sFNFrom+"\n\tTO:"+sFNTo+"\n\tsE:"+sE,LOG_ERR, pApp, pLogTarget);
#else
                log("copydir(p):!copy:"+sFNFrom+"\n\tTO:"+sFNTo,LOG_ERR, pApp, pLogTarget);
#endif
                QFile::rename(sFNTo+"____",sFNTo);
                return false;
            }
            QFile::remove(sFNTo+"____");
        }
    }
    return true;
}

QString helpers::str_removeright(QString s, QString srem)
{
    int i = s.indexOf(srem);
    if( i < 0)return s;
    return s.left(i);
}
bool helpers::str_isempty(QString s, bool bTrim)
{
    if(s.isNull() || s.isEmpty())return true;
    if(!bTrim)return false;
    s = s.trimmed();
    if(s.isNull() || s.isEmpty())return true;
    return false;
}
QString helpers::GetFileContent(QString sAbsFN, bool bWarnIfEmpty, QApplication* pApp, QObject* pLogTarget)
{
    QFile f(sAbsFN);
    if(!f.exists())
    {
        if(bWarnIfEmpty)log("GetFileContent:fnf:"+sAbsFN,LOG_ERR, pApp, pLogTarget);
        return "";
    }
    if(!f.open(QFile::ReadOnly))
    {
        if(bWarnIfEmpty)log("GetFileContent:!open:"+sAbsFN,LOG_ERR, pApp, pLogTarget);
        return "";
    }
    QByteArray buff = f.readAll();
    f.close();
    QString sFC(buff);
    if(helpers::str_isempty(sFC, false))
    {
        if(bWarnIfEmpty)log("GetFileContent:!empty:"+sAbsFN,LOG_ERR, pApp, pLogTarget);
        return "";
    }
    return sFC;
}
bool helpers::WriteFileContent(QString sAbsFN, QString sFC, bool bWarnOnError, QApplication* pApp, QObject* pLogTarget)
{
    if(QFile::exists(sAbsFN))QFile::remove(sAbsFN);
    QFile f(sAbsFN);
    if(!f.open(QFile::WriteOnly | QIODevice::Truncate))
    {
        if(bWarnOnError)log("WriteFileContent:!open:"+sAbsFN,LOG_ERR, pApp, pLogTarget);
        return false;
    }
    QByteArray baFC = sFC.toAscii();
    qint64 i2Write = baFC.length();
    qint64 iWritten= f.write(baFC);

    if(iWritten != i2Write)
    {
        if(bWarnOnError)log("WriteFileContent:!write("+QString::number(iWritten)+" != "+QString::number(i2Write)+"):"+sAbsFN,LOG_ERR, pApp, pLogTarget);
    }

    f.close();
    return true;
}
bool helpers::AppendFileContent(QString sAbsFN, QString sFC, bool bWarnOnError, QApplication* pApp, QObject* pLogTarget)
{
    QFile f(sAbsFN);
    if(!f.open(QFile::WriteOnly | QIODevice::Append))
    {
        if(bWarnOnError)log("appendFileContent:!open:"+sAbsFN,LOG_ERR, pApp, pLogTarget);
        return false;
    }
    QByteArray baFC = sFC.toAscii();
    qint64 i2Write = baFC.length();
    qint64 iWritten= f.write(baFC);

    if(iWritten != i2Write)
    {
        if(bWarnOnError)log("appendFileContent:!write("+QString::number(iWritten)+" != "+QString::number(i2Write)+"):"+sAbsFN,LOG_ERR, pApp, pLogTarget);
    }

    f.close();
    return true;
}
QString helpers::f_getPath(QString sFN)
{
    sFN = sFN.replace("/", QDir::separator());
    sFN = sFN.replace("\\",QDir::separator());
    int iLastSlash = sFN.lastIndexOf(QDir::separator());
    if (iLastSlash < 0)
        return "";
    return sFN.left(iLastSlash);
}
QString helpers::f_getFileName(QString sFN, bool bWithExt)
{
    sFN = sFN.replace("/", QDir::separator());
    sFN = sFN.replace("\\",QDir::separator());
    int iLastSlash = sFN.lastIndexOf(QDir::separator());
    if (iLastSlash < 0)
        return sFN;
    sFN = sFN.mid(iLastSlash+1);
    if(bWithExt)return sFN;
    int iLastDot = sFN.lastIndexOf('.');
    if (iLastDot < 1)
        return sFN;
    return sFN.left(iLastDot);
}
QString helpers::f_replaceext(QString sFN, QString sNewExt)
{
    QString sPath = f_getPath(sFN);
    QString sName = f_getFileName(sFN, false);

    if(sNewExt.isNull() || sNewExt.isEmpty())
        return sPath + QDir::separator() + sName;
    return sPath + QDir::separator() + sName + "." + sNewExt;
}
QString helpers::f_getext(QString sFN)
{
    QString sName = f_getFileName(sFN, true);
    int iLastDot = sName.lastIndexOf('.');
    if (iLastDot < 1)
        return "";
    return sName.mid(iLastDot+1);
}
void helpers::qWait(int ms)
{
    Q_ASSERT(QCoreApplication::instance());

    QTime dieTime = QTime::currentTime().addSecs(ms);
    while(QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
}
QString helpers::str_FormatToHtmlEntities(QString s, QString sProtect /*=""*/)
{
        QChar c;
        QString _sEntity((""));
        for(int i=0; i<s.length(); i++)
        {
                c = s.at(i);
                if(c == 'ä')		_sEntity = ("&auml;");
                else if(c == 'Ä')	_sEntity = ("&Auml;");
                else if(c == 'ö')	_sEntity = ("&ouml;");
                else if(c == 'Ö')	_sEntity = ("&Ouml;");
                else if(c == 'ü')	_sEntity = ("&uuml;");
                else if(c == 'Ü')	_sEntity = ("&Uuml;");
                else if(c == 'ß')	_sEntity = ("&szlig;");
                else if(c == '&')	_sEntity = ("&amp;");
                else if(c == '<')	_sEntity = ("&lt;");
                else if(c == '>')	_sEntity = ("&gt;");
                else if(c == '"')	_sEntity = ("&quot;");
                else if(c == '®')	_sEntity = ("&reg;");
                else if(c == '©')	_sEntity = ("&copy;");
                else if(c == '§')	_sEntity = ("&sect;");
                else if(c == '°')	_sEntity = ("&deg;");
                else if(c == '±')	_sEntity = ("&plusmn;");
                else if(c == '²')	_sEntity = ("&sup2;");
                else if(c == '³')	_sEntity = ("&sup3;");

                int _nEntLen = _sEntity.length();
                if (_nEntLen)
                {
                        s.remove(i,1);
                        s.insert(i, _sEntity);
                        i += _nEntLen-1;
                        _sEntity = "";
                }
        }
        return s;
}
QString helpers::str_FormatFromHtmlEntities(QString s, QString sProtect /*=""*/)
{
    int	_nChar;
    QString _sChar;
    QString _s;
    int i = s.indexOf('&');

    while(i >= 0)
    {
            int _nLenTotal = s.length();

            //Handle numeric entities
            if(i < _nLenTotal && s.operator[](i+1) == '#')
            {
                    //Get num value
                    _s.clear();
                    _nChar	= 0;

                    try
                    {
                            //if(this->Mid(i+3, 1) == (";"))
                            if(s.at(i+3)	== ';')
                                    _s = s.mid(i+2, 1);
                            else if(s.at(i+4)	== ';')
                                    _s = s.mid(i+2, 2);
                            else if(s.at(i+5)	== ';')
                                    _s = s.mid(i+2, 3);
                            else if(s.at(i+6)	== ';')
                                    _s = s.mid(i+2, 4);
                            else if(s.at(i+7)	== ';')
                                    _s = s.mid(i+2, 5);
                            else if(s.at(i+8)	== ';')
                                    _s = s.mid(i+2, 6);
                    }
                    catch(...)
                    {
                            _s.clear();
                            _nChar	= 0;
                    }

                    if(!_s.isEmpty())
                    {
                            //try hexadecimal
                            if(_s.length() > 2)
                            {
                                    if(((_s[0] == 'x') || (_s[0] == 'X')) && ((_s[1] >= '0') && (_s[1] <= 'f')))	//'f' > 'F'
                                    {
                                            char *stopstring;
                                            _nChar = strtol((const char*)QString("0"+_s).constData(), &stopstring, 0);
                                            if((_nChar == LONG_MAX) || (_nChar == LONG_MIN) || (_nChar == 0))
                                            {
                                                    //convert !ok
                                                    _nChar = 0;
                                                    _sChar.clear();
                                            }
                                            else
                                            {
                                                    _sChar = QString((char)_nChar);
                                            }
                                    }
                                    else if((_s[0] == '0') && ((_s[1] == 'x') || (_s[1] == 'X')))
                                    {
                                            char *stopstring;
                                            _nChar = strtol((const char*)QString("0"+_s).constData(), &stopstring, 0);
                                            if((_nChar == LONG_MAX) || (_nChar == LONG_MIN) || (_nChar == 0))
                                            {
                                                    //convert !ok
                                                    _nChar = 0;
                                                    _sChar.clear();
                                            }
                                            else
                                            {
                                                    _sChar = QString((char)_nChar);
                                            }
                                    }
                                    else
                                    {
                                            //AfxMessageBox("WRN:unknown:"+_s);
                                    }
                            }

                            //try decimal
                            if(_nChar == 0)
                            {
                                    _nChar = _s.toInt();
                                    _sChar = QString((char)_nChar);
                            }
                            if(_nChar > 255)
                            {
                                    //Translate some
                                    if(_nChar == 8217)		_sChar = ("´");
                                    else if(_nChar == 8364)	_sChar = ("€"); //Euro
                                    else if(_nChar == 8194)	_sChar = (" ");
                                    else if(_nChar == 8195)	_sChar = (" ");
                                    else if(_nChar == 8201)	_sChar = (" ");
                                    else if(_nChar == 8211)	_sChar = ("-");
                                    else if(_nChar == 8212)	_sChar = ("-");
                                    else if(_nChar == 8216)	_sChar = ("'");
                                    else if(_nChar == 8217)	_sChar = ("'");
                                    else if(_nChar == 8218)	_sChar = ("'");
                                    else if(_nChar == 8220)	_sChar = ("\"");
                                    else if(_nChar == 8221)	_sChar = ("\"");
                                    else if(_nChar == 8222)	_sChar = ("\"");
                                    else if(_nChar == 8230)	_sChar = ("...");
                                    else if(_nChar == 8240)	_sChar = ("o/oo");
                                    else if(_nChar == 8249)	_sChar = ("<");
                                    else if(_nChar == 8250)	_sChar = (">");
                                    else if(_nChar == 8482)	_sChar = ("(TM)");
                                    else if(_nChar == 8722)	_sChar = ("-");
                                    else if(_nChar == 8594)	_sChar = ("->");
                                    else			_nChar = 0;
                            }
                    }
                    if(_nChar != 0)
                    {
                            bool _bReplace = true;
                            for(int ii=0; ii<_sChar.length(); ii++)
                            {
                                    if(sProtect.indexOf(_sChar[ii]) >= 0)
                                    {
                                            _bReplace = false;
                                            break;
                                    }
                            }
                            if(_bReplace)
                            {
                                    s.operator=(s.left(i)				  +
                                                                    _sChar						  +
                                                                    s.mid(i+_s.length()+3) 	);
                            }
                    }
            }
            else	//if ! (i < _nLenTotal && this->operator[](i+1) == '#')
            {
                    int _nLen;
                    _s.clear();

                    try
                    {
                            if(s.at(i+3)	== ';')
                                    _s = s.mid(i+1, 2);
                            else if(s.at(i+4)	== ';')
                                    _s = s.mid(i+1, 3);
                            else if(s.at(i+5)	== ';')
                                    _s = s.mid(i+1, 4);
                            else if(s.at(i+6)	== ';')
                                    _s = s.mid(i+1, 5);
                            else if(s.at(i+7)	== ';')
                                    _s = s.mid(i+1, 6);
                    }
                    catch(...)
                    {
                            _s.clear();
                    }

                    _nLen = _s.length();

                    if(_nLen > 0)
                    {
                            _sChar.clear();

                            if(_nLen == 2)
                            {
                                    if(_s == ("lt"))      _sChar = ("<");
                                    else if(_s == ("gt")) _sChar = (">");
                            }
                            else if(_nLen == 3)
                            {
                                    if(_s == ("amp"))	   _sChar = ("&");
                                    else if(_s == ("reg")) _sChar = ("®");
                                    else if(_s == ("deg")) _sChar = ("°");
                                    else if(_s == ("eth")) _sChar = ("-");
                            }
                            else if(_nLen == 4)
                            {
                                    if(_s == ("nbsp"))      _sChar = (" ");
                                    else if(_s == ("auml")) _sChar = ("ä");
                                    else if(_s == ("Auml")) _sChar = ("Ä");
                                    else if(_s == ("ouml")) _sChar = ("ö");
                                    else if(_s == ("Ouml")) _sChar = ("Ö");
                                    else if(_s == ("uuml")) _sChar = ("ü");
                                    else if(_s == ("Uuml")) _sChar = ("Ü");
                                    else if(_s == ("quot")) _sChar = ("\"");
                                    else if(_s == ("copy")) _sChar = ("©");
                                    else if(_s == ("para")) _sChar = ("§");
                                    else if(_s == ("sect")) _sChar = ("§");
                                    else if(_s == ("sup2")) _sChar = ("²");
                                    else if(_s == ("sup3")) _sChar = ("³");
                                    else if(_s == ("euro")) _sChar = ("€");
                                    else if(_s == ("Euml")) _sChar = ("Ë");
                                    else if(_s == ("Iuml")) _sChar = ("Ï");
                                    else if(_s == ("euml")) _sChar = ("ë");
                                    else if(_s == ("iuml")) _sChar = ("ï");
                                    else if(_s == ("yuml")) _sChar = ("ý");
                                    else if(_s == ("emsp")) _sChar = (" ");
                                    else if(_s == ("ensp")) _sChar = (" ");
                                    else if(_s == ("rarr")) _sChar = ("->");
                            }
                            else if(_nLen == 5)
                            {
                                    if(_s == ("szlig"))      _sChar = ("ß");
                                    else if(_s == ("trade")) _sChar = ("®");
                                    else if(_s == ("ndash")) _sChar = ("-");
                                    else if(_s == ("mdash")) _sChar = ("-");
                                    else if(_s == ("laquo")) _sChar = ("«");
                                    else if(_s == ("raquo")) _sChar = ("»");
                                    else if(_s == ("lsquo")) _sChar = ("'");
                                    else if(_s == ("rsquo")) _sChar = ("'");
                                    else if(_s == ("sbquo")) _sChar = ("'");
                                    else if(_s == ("ldquo")) _sChar = ("\"");
                                    else if(_s == ("rdquo")) _sChar = ("\"");
                                    else if(_s == ("bdquo")) _sChar = ("\"");
                                    else if(_s == ("Acirc")) _sChar = ("Â");
                                    else if(_s == ("Aring")) _sChar = ("Å");
                                    else if(_s == ("Ecirc")) _sChar = ("Ê");
                                    else if(_s == ("Icirc")) _sChar = ("Î");
                                    else if(_s == ("Ocirc")) _sChar = ("Ô");
                                    else if(_s == ("Ucirc")) _sChar = ("Û");
                                    else if(_s == ("acirc")) _sChar = ("â");
                                    else if(_s == ("aring")) _sChar = ("å");
                                    else if(_s == ("ecirc")) _sChar = ("ê");
                                    else if(_s == ("icirc")) _sChar = ("î");
                                    else if(_s == ("ucirc")) _sChar = ("û");
                                    else if(_s == ("ocirc")) _sChar = ("ô");
                                    else if(_s == ("trade")) _sChar = ("(TM)");
                                    else if(_s == ("minus")) _sChar = ("-");
                            }
                            else if(_nLen == 6)
                            {
                                    if(_s == ("plusmn"))      _sChar = ("±");
                                    else if(_s == ("Agrave")) _sChar = ("À");
                                    else if(_s == ("Aacute")) _sChar = ("Á");
                                    else if(_s == ("Atilde")) _sChar = ("Ã");
                                    else if(_s == ("Ccedil")) _sChar = ("Ç");
                                    else if(_s == ("Egrave")) _sChar = ("È");
                                    else if(_s == ("Eacute")) _sChar = ("É");
                                    else if(_s == ("Igrave")) _sChar = ("Ì");
                                    else if(_s == ("Iacute")) _sChar = ("Í");
                                    else if(_s == ("Ntilde")) _sChar = ("Ñ");
                                    else if(_s == ("Ograve")) _sChar = ("Ò");
                                    else if(_s == ("Oacute")) _sChar = ("Ó");
                                    else if(_s == ("Otilde")) _sChar = ("Õ");
                                    else if(_s == ("Ugrave")) _sChar = ("Ù");
                                    else if(_s == ("Uacute")) _sChar = ("Ú");
                                    else if(_s == ("Yacute")) _sChar = ("Ý");
                                    else if(_s == ("agrave")) _sChar = ("à");
                                    else if(_s == ("aacute")) _sChar = ("á");
                                    else if(_s == ("atilde")) _sChar = ("ã");
                                    else if(_s == ("ccedil")) _sChar = ("ç");
                                    else if(_s == ("egrave")) _sChar = ("è");
                                    else if(_s == ("eacute")) _sChar = ("é");
                                    else if(_s == ("igrave")) _sChar = ("ì");
                                    else if(_s == ("iacute")) _sChar = ("í");
                                    else if(_s == ("ntilde")) _sChar = ("ñ");
                                    else if(_s == ("ograve")) _sChar = ("ò");
                                    else if(_s == ("oacute")) _sChar = ("ó");
                                    else if(_s == ("yacute")) _sChar = ("ü");
                                    else if(_s == ("uacute")) _sChar = ("ú");
                                    else if(_s == ("otilde")) _sChar = ("õ");
                                    else if(_s == ("ugrave")) _sChar = ("ù");
                                    else if(_s == ("thinsp")) _sChar = (" ");
                                    else if(_s == ("rdquor")) _sChar = ("\"");
                                    else if(_s == ("ldquor")) _sChar = ("\"");
                                    else if(_s == ("lsaquo")) _sChar = ("<");
                                    else if(_s == ("rsaquo")) _sChar = (">");
                                    else if(_s == ("emsp14")) _sChar = (" ");
                                    else if(_s == ("hellip")) _sChar = ("...");
                                    else if(_s == ("permil")) _sChar = ("o/oo");
                            }

                            if(!_sChar.isEmpty())
                            {
                                    bool _bReplace = true;
                                    for(int ii=0; ii<_sChar.length(); ii++)
                                    {
                                            if(sProtect.indexOf(_sChar[ii]) >= 0)
                                            {
                                                    _bReplace = false;
                                                    break;
                                            }
                                    }
                                    if(_bReplace)
                                    {
                                            s.operator=(s.left(i)				  +
                                                                            _sChar						  +
                                                                            s.mid(i+_nLen+2) 	);
                                    }
                            }
                    }
            }

            //Find next
            i = s.indexOf('&', i+1);
    }
    return s;
}
QString helpers::t_elapsed(int iElapsedMSecs)
{
    int iHours=iElapsedMSecs / (1000*60*60);    iElapsedMSecs%=1000*60*60;
    int iMins =iElapsedMSecs / (1000*60);       iElapsedMSecs%=1000*60;
    int iSecs =iElapsedMSecs / (1000);          iElapsedMSecs%=1000;

    QString s;
    bool d=false;
    if(iHours)
        s+=QString::number(iHours) + " hours ", d=true;
    if(iMins || d)
        s+=QString::number(iMins) +" min ", d=true;
    if(iSecs || d)
        s+=QString::number(iSecs) +" secs ";
    s+=QString::number(iElapsedMSecs)+" msecs";
    return s;

    /*
    int iHours=0;
    int iMins =0;
    int iSecs =0;

    while(iElapsedMSecs >= (1000*60*60))
    {
        iElapsedMSecs -= (1000*60*60);
        iHours++;
    }
    while(iElapsedMSecs >= (1000*60))
    {
        iElapsedMSecs -= (1000*60);
        iMins++;
    }
    while(iElapsedMSecs >= (1000))
    {
        iElapsedMSecs -= (1000);
        iSecs++;
    }

    if(iHours > 0)
    {
        return  QString::number(iHours) + " hours " + QString::number(iMins) +" min " + QString::number(iSecs) +" secs " + QString::number(iElapsedMSecs)+" msecs";
    }
    if(iMins > 0)
    {
        return  QString::number(iMins) +" min " + QString::number(iSecs) +" secs " + QString::number(iElapsedMSecs)+" msecs";
    }
    if(iSecs > 0)
    {
        return  QString::number(iSecs) +" secs " + QString::number(iElapsedMSecs)+" msecs";
    }
    return  QString::number(iElapsedMSecs)+" msecs";
    */
}
QString helpers::str_xmalstr(QString s, int ix)
{
    QString sRe="";
    for(int i=0; i < ix; i++)
        sRe += s;
    return sRe;
}

void helpers::SetCFG(QString sEntryName, QString sEntryValue, QApplication* pApp, QObject* pLogTarget, QString sSection/*="CFG"*/, QString sFN/*=""*/)
{
    if(helpers::str_isempty(sFN, true))
    {
        sFN = helpers::getarg("cfg", pApp, pLogTarget);
        if(helpers::str_isempty(sFN, true))
        {
#ifdef Q_WS_WIN
            sFN = pApp->applicationFilePath().left(pApp->applicationFilePath().length()-3)+"cfg";
#else
            sFN = pApp->applicationFilePath()+".cfg";
#endif
        }
    }

    QSettings(sFN, QSettings::IniFormat, 0).setValue(sSection+"/"+sEntryName, sEntryValue);
}
QString helpers::f_replaceplaceholders(QString s)
{
    if(s.indexOf('%') < 0)return s;

    //%MYFILES%,%TEMP%,%TMP%,%*APPDATA*%,%CURRENTDIR%(=AppDir)

    static QString sMYFILES    = QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation);//QDir::homePath();
/*#ifdef Q_WS_WIN
    static bool bMYFILES = false;
    if(!bMYFILES)
    {   bMYFILES = true;
        QSettings register("HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders", QSettings::NativeFormat);
        QString allUserDesktop( register.value("Common Desktop").toString());
    }
#endif*/
    static QString sCURRENTDIR          = qApp->applicationDirPath();
    static QString sTEMP                = QDir::tempPath();
    static QString sPERSONAL_APPDATA    = QString(qgetenv("APPDATA"));
    static QString sCOMMON_APPDATA      = QString::null;
    static QString sAPP_PERSONAL_APPDATA= QString::null;
    static QString sAPP_COMMON_APPDATA  = QString::null;

    if(sPERSONAL_APPDATA.isNull())
    {
#ifdef Q_WS_WIN
        TCHAR lpBuffer[_MAX_PATH];      //CSIDL_* list -> see: http://msdn.microsoft.com/en-us/library/ms954149.aspx
        /*int ret = */SHGetSpecialFolderPath(NULL, lpBuffer, CSIDL_APPDATA, 0);
        sPERSONAL_APPDATA = QString::fromUtf16(lpBuffer);
#else
        sPERSONAL_APPDATA = QDir::homePath();
#endif
    }
    if(sCOMMON_APPDATA.isNull())
    {
#ifdef Q_WS_WIN
        TCHAR lpBuffer[_MAX_PATH];
        /*int ret = */SHGetSpecialFolderPath(NULL, lpBuffer, CSIDL_COMMON_APPDATA, 0);
        sCOMMON_APPDATA = QString::fromUtf16(lpBuffer);
#else
        sCOMMON_APPDATA = QDir::homePath();
#endif
        sAPP_COMMON_APPDATA = sCOMMON_APPDATA   + QDir::separator() + QCoreApplication::organizationName() + QDir::separator() + QCoreApplication::applicationName();
        helpers::mkdirfull(sAPP_COMMON_APPDATA);

        sAPP_PERSONAL_APPDATA = sPERSONAL_APPDATA+QDir::separator() + QCoreApplication::organizationName() + QDir::separator() + QCoreApplication::applicationName();
        helpers::mkdirfull(sAPP_PERSONAL_APPDATA);
    }

    s = s.replace("%MYFILES%"       ,sMYFILES);
    s = s.replace("%TEMP%"          ,sTEMP);
    s = s.replace("%TMP%"           ,sTEMP);
    s = s.replace("%CURRENTDIR%"    ,sCURRENTDIR);

    s = s.replace("%APPDATA%"               ,sPERSONAL_APPDATA);
    s = s.replace("%PERSONAL_APPDATA%"      ,sPERSONAL_APPDATA);
    s = s.replace("%COMMON_APPDATA%"        ,sCOMMON_APPDATA);
    s = s.replace("%APP_PERSONAL_APPDATA%"  ,sAPP_PERSONAL_APPDATA);
    s = s.replace("%APP_COMMON_APPDATA%"    ,sAPP_COMMON_APPDATA);

    return s;
}
QString helpers::getUrlFromCFG(QString sCfgEntryName)
{
    QString sUrl        = GetCFG(sCfgEntryName, m_pApp, m_pLogTarget, "about:blank");
    QString sCURRENTDIR = GetCFG("", m_pApp, m_pLogTarget, "%CURRENTDIR%");
    QString sCURRENTURL = "";

    if (sCURRENTDIR.startsWith("\\\\") || sCURRENTDIR.startsWith("//"))
        sCURRENTURL = "file:"+sCURRENTDIR.replace('\\','/');
    else
        sCURRENTURL = "file:///"+sCURRENTDIR.replace('\\','/');

    sUrl.replace("%CURRENTURL%",sCURRENTURL);

    return sUrl;
}

bool helpers::mkdirfull(QString sDir)
{
    QDir d(sDir);
    return d.mkpath(sDir);
}

bool helpers::f_remove(QString sAbsFN)
{
    QFile f(sAbsFN);
    if(!f.exists())return true;
    if(f.remove() )return true;
    f.setPermissions(f.permissions()|QFile::ReadOwner|QFile::ReadUser|QFile::ReadGroup|QFile::ReadOther|QFile::WriteOwner|QFile::WriteUser|QFile::WriteGroup|QFile::WriteOther);
    return f.remove();
}
