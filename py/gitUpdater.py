#! python   # shebang, for linux

import time
import os, sys
import argparse

# pip install gitpython
from git import Repo
import git

class GitUpdater:
    def __init__(self):
        pass

    @staticmethod
    def log(s):
        print(s)

    def gitUpdate(self, dir):
        for subdir, dirs, _ in os.walk(dir):
            print("subdir:"+subdir)
            for aSubDir in dirs:
                self.updateGitDir(os.path.join(subdir, aSubDir))
            break   #prevent decending into subfolders

    def updateGitDir(self, dir):
        repo = Repo(dir)
        if repo.bare:
            GitUpdater.log("updateGitDir ERR: Could not load repo at '{}'".format(dir))
            return False
        
        # git = repo.git
        # r = remote.pull()   # IterableInfo = pull(refspec=None, progress=None, **kwargs)

        # does not support git pull with passphrase!
        g = git.cmd.Git(dir)
        msg = g.pull()
        GitUpdater.log("updateGitDir INF: updated("+msg+") repo at '{}'".format(dir))
        return True


# call: python ./gitUpdater.py --dir c:/Entwicklung/workspace.git
if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--dir' , type=str,  help='dir having subdirs which are local git repos')
    args = parser.parse_args()
    gitUpdater = GitUpdater()
    gitUpdater.gitUpdate(args.dir)
