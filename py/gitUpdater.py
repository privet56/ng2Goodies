#! python   # shebang, for linux

import time
import os, sys
import argparse
import re

# pip install gitpython
from git import Repo
import git

class GitUpdater:
    def __init__(self):
        pass

    @staticmethod
    def log(s):
        print(s)

    #        GitLab & SSH Key prerequisite: a key **WITHOUT** passphrase and an ssh config:
    #
    #        Append your target GIT server to the list of authorized hosts:
    #        into c:\Users\{username}\.ssh\known_hosts (otherwise 'Host key verification failed')
    #
    #       and fill
    #        c:\Users\{username}\.ssh\config  ->
    #
    #       Host *
    #           AddKeysToAgent yes
    #           UseKeychain yes
    #           IdentityFile ~/.ssh/id_ed25519
    #

    def checkPrerequisites(self, dir):
        userName = os.getlogin()
        sshConfigFN = os.path.join('c:\\', 'Users', userName, '.ssh','config')    # c:\Users\{username}\.ssh\config
        if(not os.path.isfile(sshConfigFN)):
            GitUpdater.log("checkPrerequisites WRN: fnf{}".format(sshConfigFN))
            return False
        sshConfigFC = ''.join(open(sshConfigFN, 'r').readlines())
        if(not re.search(r"^Host\s", sshConfigFC, re.MULTILINE)):
            GitUpdater.log("checkPrerequisites WRN: no Host in {}".format(sshConfigFN)+"\n--------\n"+sshConfigFC+"\n--------")
            return False
        if(not re.search(r"^\s+AddKeysToAgent\s+yes$", sshConfigFC, re.MULTILINE)):
            GitUpdater.log("checkPrerequisites WRN: no AddKeysToAgent=yes in {}".format(sshConfigFN)+"\n--------\n"+sshConfigFC+"\n--------")
            return False
        if(not re.search(r"^\s+IdentityFile\s+", sshConfigFC, re.MULTILINE)):
            GitUpdater.log("checkPrerequisites WRN: no IdentityFile in {}".format(sshConfigFN)+"\n--------\n"+sshConfigFC+"\n--------")
            return False

        return True

    def gitUpdate(self, dir):

        if(not self.checkPrerequisites(dir)):
            return False

        updatedDirCount = 0
        for subdir, dirs, _ in os.walk(dir):
            for aSubDir in dirs:
                if aSubDir.startswith("."):
                    continue    # skip dirs starting with .
                if(not self.updateGitDir(os.path.join(subdir, aSubDir))):
                    return False
                updatedDirCount = updatedDirCount + 1

                if (updatedDirCount % 10) == 0:
                    # bitbucket tries to prevent DDOS -> we have to wait
                    GitUpdater.log("updateGitDir INF: waiting a little bit... " + time.strftime("%H:%M:%S"))
                    time.sleep(11) # Sleep for 11 seconds
                    GitUpdater.log("updateGitDir INF: waited a little bit " + time.strftime("%H:%M:%S"))

            break   #prevent decending into subfolders

        GitUpdater.log("updateGitDir INF: updated repos: {}".format(updatedDirCount)+"   in "+dir)
        return True

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

