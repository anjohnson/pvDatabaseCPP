/*
 * Copyright information and license terms for this software can be
 * found in the file LICENSE that is included with the distribution
 */

/**
 * @author mrk
 * @date 2013.07.24
 */


/* Author: Marty Kraimer */
#include <epicsThread.h>
#include <iocsh.h>
#include <pv/standardField.h>
#include <pv/standardPVField.h>
#include <pv/timeStamp.h>
#include <pv/pvTimeStamp.h>
#include <pv/alarm.h>
#include <pv/pvAlarm.h>
#include <pv/pvDatabase.h>

// The following must be the last include for code pvDatabase uses
#include <epicsExport.h>
#define epicsExportSharedSymbols
#include "pv/removeRecord.h"

using namespace epics::pvData;
using namespace epics::pvAccess;
using namespace epics::pvDatabase;
using namespace std;

static const iocshArg testArg0 = { "recordName", iocshArgString };
static const iocshArg *testArgs[] = {
    &testArg0};

static const iocshFuncDef removeRecordFuncDef = {"removeRecordCreate", 1,testArgs};

static void removeRecordCallFunc(const iocshArgBuf *args)
{
    cerr << "DEPRECATED use pvdbcrRemoveRecord instead\n";
    char *recordName = args[0].sval;
    if(!recordName) {
        throw std::runtime_error("removeRecordCreate invalid number of arguments");
    }
    RemoveRecordPtr record = RemoveRecord::create(recordName);
    bool result = PVDatabase::getMaster()->addRecord(record);
    if(!result) cout << "recordname" << " not added" << endl;
}

static void removeRecordRegister(void)
{
    static int firstTime = 1;
    if (firstTime) {
        firstTime = 0;
        iocshRegister(&removeRecordFuncDef, removeRecordCallFunc);
    }
}

extern "C" {
    epicsExportRegistrar(removeRecordRegister);
}
