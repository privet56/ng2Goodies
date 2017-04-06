#include "ziputil.h"

ziputil::ziputil(QObject *parent) : QObject(parent)
{
}
int ziputil::zipdir(QString sDirRoot, QString sDir, QuaZip* pZip, helpers *phelpers)
{
    QFile inFile;
    QDir dir(sDir);
    const QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    QFileInfo fi;
    int iFilesFound = 0;

    for (int l = 0; l < list.size(); l++)
    {
        fi = list.at(l);
        if (fi.isDir())
        {
            iFilesFound += zipdir(sDirRoot, helpers::makeAbsFN(sDir,fi.fileName()), pZip, phelpers);
        }
        else
        {
            QString sAbsFN = helpers::makeAbsFN(sDir,fi.fileName());
            {
                QString szipfn = pZip->getZipName().replace('\\','/');
                QString sabsfn = sAbsFN.replace('\\','/');
                szipfn.toLower().replace('\\','/');
                sabsfn.toLower().replace('\\','/');
                if(sabsfn == szipfn)
                    continue;
            }
            inFile.setFileName(sAbsFN);
            if(!inFile.open(QIODevice::ReadOnly))
            {
                if(phelpers)phelpers->log("ziputil:zipdir:2:inFile.open():"+QString(inFile.errorString().toLocal8Bit().constData()),LOG_ERR);
                break;
            }
            QString sFN = fi.fileName();
            if(sDirRoot.length() < sDir.length())
                sFN = sDir.midRef(sDirRoot.length()+1).toString() + "/" + fi.fileName();
            sFN = sFN.replace('\\','/');

            QuaZipFile outFile(pZip);
            if(!outFile.open(QIODevice::WriteOnly, QuaZipNewInfo(sFN)))
            {
                if(phelpers)phelpers->log("ziputil:zipdir:3:outFile.open():"+QString::number(outFile.getZipError()),LOG_ERR);
                break;
            }
            char c;
            while(inFile.getChar(&c)&&outFile.putChar(c));
            if(outFile.getZipError()!=UNZ_OK)
            {
                if(phelpers)phelpers->log("ziputil:zipdir:4:outFile.putChar():"+QString::number(outFile.getZipError()),LOG_ERR);
                break;
            }
            outFile.close();
            if(outFile.getZipError()!=UNZ_OK)
            {
                if(phelpers)phelpers->log("ziputil:zipdir:4:outFile.close():"+QString::number(outFile.getZipError()),LOG_ERR);
                break;
            }
            inFile.close();
            iFilesFound++;
        }
    }
    return iFilesFound;
}

int ziputil::zipdir(QString sDir, QString sZip, helpers *phelpers)
{
    QuaZip zip(sZip);
    if(!zip.open(QuaZip::mdCreate))
    {
        if(phelpers)phelpers->log("ziputil:zipdir:!zipCreate:"+sZip, LOG_ERR);
        return 0;
    }

    int iFilesFound = zipdir(sDir, sDir, &zip, phelpers);

    zip.close();
    if(zip.getZipError()!=0)
    {
        if(phelpers)phelpers->log("ziputil:zipdir:5:zip.close():"+QString::number(zip.getZipError()),LOG_ERR);
    }
    return iFilesFound;
}
