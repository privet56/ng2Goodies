#! python   # shebang, for linux

import time
import os, sys
import argparse

import pyautogui    # pip install pyautogui

#Issue:
# Command "python setup.py egg_info" failed with error code 1 in c:\temp\pip-install-lamdpy\pygetwindow\
#Solution:
# 1. use python 3.x
# 2. python -m pip install --upgrade pip
# 3. pip install --upgrade setuptools
# 4. pip install pyautogui

class WakeUpHolder:
    def __init__(self):
        pass
    def doWakeUpHolder(self, sleepInterval):
        x, y = pyautogui.position()
        left = True

        try:
            while True:
                time.sleep(sleepInterval)

                if (x != pyautogui.position().x) or (y != pyautogui.position().y):
                    positionStr = 'X: ' + str(x).rjust(4) + ' Y: ' + str(y).rjust(4) + ' ... manually moved... -> nothing to do!'
                else:
                    positionStr = 'X: ' + str(x).rjust(4) + ' Y: ' + str(y).rjust(4) + ' ... mouse not moved... -> move it!'
                    pyautogui.moveRel(10 if left else -10, 0, duration=0.25)

                WakeUpHolder.log(positionStr)
                x, y = pyautogui.position()
                left = not left

        except KeyboardInterrupt:
            WakeUpHolder.log('\nDone.')

    @staticmethod
    def log(s):
        print(s)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--sleep' , type=int, default=30,  help='sleep interval in seconds')
    args = parser.parse_args()
    wakeUpHolder = WakeUpHolder()
    WakeUpHolder.log("starting wakeUpHolder with sleepInterval: "+str(args.sleep))
    wakeUpHolder.doWakeUpHolder(args.sleep)
