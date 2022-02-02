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

def _checkEmployeeCalendarUpdates(employeeCalendar, employmentIds, calendarCharacteristicIds, path):
    scope = employeeCalendar['scope']
    if not scope or len(scope) < 1 or scope.isspace():
        print("ERROR: scope: " + str(employeeCalendar))

    calendarCharacteristicId = employeeCalendar['calendarCharacteristic']['id']
    hasCalendarCharacteristic = calendarCharacteristicId in calendarCharacteristicIds
    if not hasCalendarCharacteristic:
        print("ERROR: calendarCharacteristicId: " + calendarCharacteristicId + " !hasCalendarCharacteristic" + str(hasCalendarCharacteristic) + " employeeCalendar: " + str(employeeCalendar))

def _checkVacationRequestUpdates(employeeCalendar, employmentIds, calendarCharacteristicIds, path):
    scope = employeeCalendar['scope']
    if not scope or len(scope) < 1 or scope.isspace():
        print("ERROR: scope: " + str(employeeCalendar))

    calendarCharacteristicId = employeeCalendar['calendarCharacteristic']['id']
    hasCalendarCharacteristic = calendarCharacteristicId in calendarCharacteristicIds
    if not hasCalendarCharacteristic:
        print("ERROR: calendarCharacteristicId: " + calendarCharacteristicId + " !hasCalendarCharacteristic" + str(hasCalendarCharacteristic) + " employeeCalendar: " + str(employeeCalendar))

def _checkCalendarCharacteristicUpdates(calendarCharacteristic, employmentIds, calendarCharacteristicIds, path):
    scope = calendarCharacteristic['scope']
    if not scope or len(scope) < 1 or scope.isspace():
        print("ERROR: scope: " + str(calendarCharacteristic))

    calendarCharacteristicIds[calendarCharacteristic['id']] = calendarCharacteristic

def _checkJobTenureUpdates(jobTenureUpdatesId, employmentIds, path):
    hasEmployment = jobTenureUpdatesId in employmentIds
    if not hasEmployment:
        print("ERROR: " + jobTenureUpdatesId + " !hasEmployment" + str(hasEmployment))

######## CHECK FUNCTIONS END   ########

def isJsonObject(i):
    try:
        for _, _ in i.items():
            return True
    except:
        return False
    else:
        return True

def checkJsonObject(o, employmentIds, calendarCharacteristicIds, path):

    if not isJsonObject(o):                 # = o is no iterable object (can be array, int, string, ...)
        if isinstance(o, list):             # = o is a list
            for ele in o:

                if path.find(".result.payload.employee.calendar.EmployeeCalendar.updates") == 0:
                    _checkEmployeeCalendarUpdates(ele, employmentIds, calendarCharacteristicIds, path)
                if path.find(".result.payload.employee.calendar.VacationRequest.updates") == 0:
                    _checkVacationRequestUpdates(ele, employmentIds, calendarCharacteristicIds, path)
                if path.find(".result.payload.organization.CalendarCharacteristic.updates") == 0:
                    _checkCalendarCharacteristicUpdates(ele, employmentIds, calendarCharacteristicIds, path)

                checkJsonObject(ele, employmentIds, calendarCharacteristicIds, path)
        return

    for key, val in o.items():

        if key == 'employment':
            _checkEmployment(val, employmentIds, path)
        if key == 'workingTime':
            _checkWorkingTime(val, employmentIds, path)
        if path.find(".result.payload.employment.JobTenure.updates") == 0 and key == "id":
            _checkJobTenureUpdates(val, employmentIds, path)

        checkJsonObject(val, employmentIds, calendarCharacteristicIds, path + "." + key)

with open(sys.argv[1]) as f:
    data = json.load(f)
    employmentIds = {}
    calendarCharacteristicIds = {}
    checkJsonObject(data, employmentIds, calendarCharacteristicIds, "")
    print("FINISHED. employmentIds# = " + str(len(employmentIds)))
