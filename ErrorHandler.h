#pragma once
#include "ConsoleInOut.h"

#define FAILOPEN 10000
#define NOTSQUERENESS 10100
#define MEMORYERROR 10200
#define UNCORRECTNUMBER 10300
#define NUMBEROVERFLOW 10400
#define FEWLINES 10500
#define EMPTYFILE 10600

using namespace std;

void WriteError(int errorCode, int line = 0, int column = 0, string str = "");
