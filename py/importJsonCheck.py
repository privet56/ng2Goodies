#!/usr/bin/env python
# call: .\importJsonCheck.py ./my.json > out.log

import sys
import json
from datetime import datetime
from collections.abc import Iterable   # import directly from collections for Python < 3.3

######## CHECK FUNCTIONS START ########

def _checkEmployment(employment, employmentIds, path):
    sentry = employment['entry']
    entry = int(sentry)
    entry /= 1000 #  the timestamp may be in milliseconds
    dentry = datetime.fromtimestamp(entry)  # or dentry = datetime.utcfromtimestamp(entry)
    # print("employmentId: " + employment['id'] + " entry: " + str(dentry))
    employmentIds[employment['id']] = employment

def _checkWorkingTime(workingTime, employmentIds, path):
    if workingTime:
        weeklyHours = workingTime['weeklyHours']
        if weeklyHours > 99:
            print("ERROR: weeklyHours: " + str(weeklyHours))

def _checkJobTenureUpdates(jobTenureUpdates, employmentIds, path):
    hasEmployment = jobTenureUpdates in employmentIds
    if not hasEmployment:
        print("ERROR: " + str(hasEmployment))

######## CHECK FUNCTIONS END   ########

def isJsonObject(i):
    try:
        for _, _ in i.items():
            return True
    except:
        return False
    else:
        return True

def checkJsonObject(o, employmentIds, path):

    if not isJsonObject(o):                 # = o is no iterable object (can be array, int, string, ...)
        if isinstance(o, list):             # = o is a list
            for ele in o:
                checkJsonObject(ele, employmentIds, path)
        return

    for key, val in o.items():

        if key == 'employment':
            _checkEmployment(val, employmentIds, path)
        if key == 'workingTime':
            _checkWorkingTime(val, employmentIds, path)
        if path.find(".result.payload.employment.JobTenure.updates") == 0 and key == "id":
            _checkJobTenureUpdates(val, employmentIds, path)

        checkJsonObject(val, employmentIds, path + "." + key)

with open(sys.argv[1]) as f:
    data = json.load(f)
    employmentIds = {}
    checkJsonObject(data, employmentIds, "")
    print("FINISHED. employmentIds# = " + str(len(employmentIds)))
