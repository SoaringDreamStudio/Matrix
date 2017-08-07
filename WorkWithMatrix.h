#pragma once
#include "ConsoleInOut.h"
#include <iostream>
#include <new>
#include <sstream>
#include <iomanip>
#include <math.h>
#include "LoadMatrix.h"

#define FAILOPEN 10000
#define NOTSQUERENESS 10100
#define MEMORYERROR 10200
#define UNCORRECTNUMBER 10300
#define NUMBEROVERFLOW 10400
#define FEWLINES 10500
#define EMPTYFILE 10600


using namespace std;

//��������� ������� �������
int workingWithMatrix(double** & matrix1, double** & matrix2, int lines,int columns, int* & mass1, int & mass1count);      //������ �������, ��������� � ���������� ����������� �������
//����� ������
int format_cout(double **X,int N,int M);
void variantOutput1(int mass1count, int* mass1);    //����� ������� ��������
void variantOutput2(double **X,int N,int M);           //����� ������� ��������

//���������
int variant1(double** X,int N,int M, int & mass1count, int * & mass1);                  //���������� ���������� ������ ���������
int variant2(double** X,int N,int M, int mass1count, int * & mass1);
                                                    //������ �������� � �������� �������

//��������������� �������
double middleAriphmetic(double* mass, int count); //������� �������������� �� ������� int
int lenAfterDot(const double& x);                  //���������� ���������� ���� ����� �����
int countLen(const double& x);                     //���������� ���������� ���� � �����
string doubleToStr(const double& x);

int CopyMatrix(double** matrix1, double** & matrix2, int lines,int columns);

int PrintResult(double** matrix1, double** matrix2, int lines,int columns, int* mass1, int mass1count);


