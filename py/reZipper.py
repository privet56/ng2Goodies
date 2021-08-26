#! python   # shebang, for linux

import time
import os, sys
import argparse
import re
import tempfile
import shutil
import zipfile

class ReZipper:
    def __init__(self):
        pass

    @staticmethod
    def log(s):
        print(s)

    def zip(self, tmpDir, dir):

        fileList = []
        fileSizes = 0
        maxFileSize = 200 * 1000000 # 200 MB
        //TODO: randomize!
        for root, dirs, fns in os.walk(tmpDir):
            for fn in fns:
                fileSize = os.path.getsize(os.path.join(dir, fn))
                if ((fileSizes + fileSize) > maxFileSize):
                    self.makeZipFile(tmpDir, fileList, dir) //TODO: impl
                    fileList = []
                    fileSizes = 0
                else:
                    fileList.extend(fn)
                    fileSizes += fileSize

    def unzipFiles(self, dir, zipFNs):
        tmpDir = tempfile.mkdtemp()

        for zipFN in zipFNs:
        with zipfile.ZipFile(os.path.join(dir, zipFN), 'r') as zipF:    # 'with' -> no need to zipF.close()
            zipF.extractall(tmpDir)

        return tmpDir

    def getZipsInDir(self, dir):
        zipFNs = []
        for (dirpath, dirnames, filenames) in os.walk(dir):
            zipFNs.extend(filenames)
            break
        return zipFNs

    def rezip(self, dir):
        zipFNs = self.getZipsInDir(dir)
        tmpDir = self.unzipFiles(dir, zipFNs)
        self.zip(tmpDir, dir)
        self.removeTempDir(tmpDir)      //TODO: impl # shutil.rmtree(dirpath)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--dir' , type=str,  help='dir containing *.zip files')
    args = parser.parse_args()
    rezipper = ReZipper()
    rezipper.rezip(args.dir)
