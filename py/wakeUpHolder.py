#! python   # shebang, for linux

import time
import os, sys
import argparse

import pyautogui                # pip install pyautogui
import win32api, win32con       # pip install pypiwin32

pyautogui.FAILSAFE = False      # disables the fail-safe

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
        win32Api = True
        loopDone = 0
        lastUserMouseMoveAtLoop = 0

        try:
            while True:
                time.sleep(sleepInterval)

                loopsSinceLastUserMouseMove = loopDone - lastUserMouseMoveAtLoop
                lastUserMouseMoveSec = loopsSinceLastUserMouseMove * sleepInterval
                lastUserMouseMove = " lastUserMouseMove:"+str(lastUserMouseMoveSec).rjust(4)+"sec" if loopDone > 0 else ""

                positionStr = 'x:' + str(x).rjust(4) + ' y:' + str(y).rjust(4) + " loopDone:"+str(loopDone).rjust(4) + " ("+str(loopDone*sleepInterval).rjust(4)+"sec), win32Api:"+str(win32Api).rjust(5) + lastUserMouseMove

                if (x != pyautogui.position().x) or (y != pyautogui.position().y):
                    positionStr += ' manually moved: -> nothing to do!'
                    lastUserMouseMoveAtLoop = loopDone
                else:
                    positionStr += ' mouse not moved -> move mouse!'
                    if win32Api:
                        newPos =(x + (10 if left else -10), y)
                        win32api.SetCursorPos(newPos)
                        win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,x,y,0,0)
                        win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,x,y,0,0)
                    else:
                        pyautogui.moveRel(10 if left else -10, 0, duration=0.25)

                WakeUpHolder.log(positionStr)
                x, y = pyautogui.position()
                left = not left
                win32Api = not win32Api
                loopDone = loopDone + 1

        except KeyboardInterrupt:
            WakeUpHolder.log('\nDone.')

    def doWakeUpHolderWithAutoGui(self, sleepInterval):
        x, y = pyautogui.position()
        left = True

        try:
            while True:
                time.sleep(sleepInterval)

                positionStr = 'X: ' + str(x).rjust(4) + ' Y: ' + str(y).rjust(4)

                if (x != pyautogui.position().x) or (y != pyautogui.position().y):
                    positionStr += ' ... manually moved... -> nothing to do!'
                else:
                    positionStr += ' ... mouse not moved... -> move it!'
                    pyautogui.moveRel(10 if left else -10, 0, duration=0.25)

                WakeUpHolder.log(positionStr)
                x, y = pyautogui.position()
                left = not left

        except KeyboardInterrupt:
            WakeUpHolder.log('\nDone.')

    def doWakeUpHolderWithWinApi(self, sleepInterval):
        x, y = win32api.GetCursorPos()
        left = True

        try:
            while True:
                time.sleep(sleepInterval)

                positionStr = 'X: ' + str(x).rjust(4) + ' Y: ' + str(y).rjust(4)

                if (x != win32api.GetCursorPos()[0]) or (y != win32api.GetCursorPos()[1]):
                    positionStr += ' ... manually moved... -> nothing to do!'
                else:
                    positionStr += ' ... mouse not moved... -> move it!'
                    newPos =(x + (10 if left else -10), y)
                    win32api.SetCursorPos(newPos)

                WakeUpHolder.log(positionStr)
                x, y = win32api.GetCursorPos()
                left = not left

        except KeyboardInterrupt:
            WakeUpHolder.log('\nDone.')


    @staticmethod
    def log(s):
        print(s)

# call: python ./wakeUpHolder.py --sleep 3
if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--sleep' , type=int, default=30,  help='sleep interval in seconds')
    args = parser.parse_args()
    wakeUpHolder = WakeUpHolder()
    WakeUpHolder.log("starting wakeUpHolder with sleepInterval: "+str(args.sleep))
    wakeUpHolder.doWakeUpHolder(args.sleep)
