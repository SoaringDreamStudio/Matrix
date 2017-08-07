#pragma once
#include "ConsoleInOut.h"
#include <fstream>
#include <cstdlib>

#define FAILOPEN 10000
#define NOTSQUERENESS 10100
#define MEMORYERROR 10200
#define UNCORRECTNUMBER 10300
#define NUMBEROVERFLOW 10400
#define FEWLINES 10500
#define EMPTYFILE 10600

using namespace std;


void InputFilename(string & filename);

bool OpenFile(ifstream & fin, string filename);
void CloseFile(ifstream & fin);
int CalculateCAndLFromFile(ifstream & fin, int & N, int & M, int & errorLine);
int CalculateColumnsAndLines(int & columns, int & lines, string filename, int & errorLine);
int LoadMatrixFromFile(string filename, double ** & X, int & N, int & M, int & errorLine, int & errorColumn, string & errorNumber);
int CheckNumber(string & str);

void DeleteMatrix(double** X, int N);

