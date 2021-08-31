#! python   # shebang, for linux

import time
import os, sys
import argparse
import re
import tempfile
import shutil
import zipfile
import random

# //TODO: refactor to 3 classes: Zipper, UnZipper, ReZipper

class ReZipper:
    prefix = ''

    def __init__(self, prefix):
        self.prefix = prefix

    @staticmethod
    def log(s):
        print(s)

    def removeTempDir(self, tmpDir):
        # shutil.rmtree(dirpath)
        ReZipper.log("WRN: removeTempDir: DO: " + tmpDir)

    def makeZipFile(self, tmpDir, fileList, outDir, createdZips):

        if (len(fileList) < 1):
            ReZipper.log("ERR: makeZipFile: !fileList for " + str(createdZips))

        with zipfile.ZipFile(os.path.join(outDir, self.prefix + '.' + format(createdZips, '02d') + '.zip'), 'w') as zipObj: # 'with' -> no need to zipF.close()
            for fn in fileList:
                absFN = os.path.join(tmpDir, fn)
                if not os.path.isfile(absFN):
                    ReZipper.log("ERR: makeZipFile: fnf(createdZips:" + str(createdZips) + ") #fileList:" + str(len(fileList)) + ") "+ absFN)
                    return False
                else:
                    zipObj.write(absFN, fn)

        return True

    def zip(self, tmpDir, outDir):

        createdZips = 0
        fileList = []
        fileSizes = 0
        maxFileSize = 200 * 1000000 # 200 MB

        allFiles = []
        for root, dirs, fns in os.walk(tmpDir):
            allFiles.extend(fns)
            break

        random.shuffle(allFiles)

        for fn in allFiles:
            fileSize = os.path.getsize(os.path.join(tmpDir, fn))

            if (fileSize < 1):
                ReZipper.log("ERR: zip: !fileSize for " + os.path.join(tmpDir, fn))

            if ((fileSizes + fileSize) > maxFileSize):
                if(not self.makeZipFile(tmpDir=tmpDir, fileList=fileList, outDir=outDir, createdZips=createdZips)):
                    ReZipper.log("ERR: zip: !makeZipFile("+tmpDir+", " + outDir + ", " + str(createdZips) + ") for " + str(len(fileList)) + "/" + str(len(allFiles)))
                    ReZipper.log("ERR: zip: !makeZipFile: fileList:" + ' '.join(fileList))
                    ReZipper.log("ERR: zip: !makeZipFile: allFiles:" + ' '.join(allFiles))
                    return createdZips
                else:
                    # ReZipper.log("INF: zip: OK makeZipFile("+tmpDir+", " + outDir + ", " + str(createdZips) + ") fileSizes: " + str(fileSizes) + " for " + str(len(fileList)) + "/" + str(len(allFiles)))
                    pass

                fileList = []
                fileSizes = 0
                createdZips = createdZips + 1
            else:
                fileList.append(fn)
                fileSizes += fileSize

        return createdZips

    def unzipFiles(self, dir, zipFNs):
        tmpDir = tempfile.mkdtemp()

        for zipFN in zipFNs:
            with zipfile.ZipFile(os.path.join(dir, zipFN), 'r') as zipF:    # 'with' -> no need to zipF.close()
                # //TODO: what if target file in tmpDir already exists?
                zipF.extractall(tmpDir)

        return tmpDir

    def getZipsInDir(self, dir):
        zipFNs = []
        for (dirpath, dirnames, filenames) in os.walk(dir):
            # //TODO: get only *.zip's
            zipFNs.extend(filenames)
            break

        if (len(zipFNs) < 1):
            ReZipper.log("ERR: zip: !getZipsInDir for " + dir)

        return zipFNs

    def rezip(self, dir):
        zipFNs = self.getZipsInDir(dir)
        tmpDir = self.unzipFiles(dir, zipFNs)
        createdZips = self.zip(tmpDir=tmpDir, outDir=dir)
        self.removeTempDir(tmpDir)
        return createdZips


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--prefix' , type=str,  help='prefix for the created zip files', required=True)
    parser.add_argument('--dir' , type=str,  help='dir containing *.zip files', required=True)
    args = parser.parse_args()
    rezipper = ReZipper(args.prefix)
    createdZips = rezipper.rezip(args.dir)

    ReZipper.log("FINISH. created " + str(createdZips) + " ZIPs from " + args.dir)
