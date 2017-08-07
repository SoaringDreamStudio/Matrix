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

//Обработка готовой матрицы
int workingWithMatrix(double** & matrix1, double** & matrix2, int lines,int columns, int* & mass1, int & mass1count);      //группа функций, связанных с обработкой загруженной матрицы
//вывод данных
int format_cout(double **X,int N,int M);
void variantOutput1(int mass1count, int* mass1);    //Вывод задания варианта
void variantOutput2(double **X,int N,int M);           //Вывод задания варианта

//обработка
int variant1(double** X,int N,int M, int & mass1count, int * & mass1);                  //Определяет количество нужных столбиков
int variant2(double** X,int N,int M, int mass1count, int * & mass1);
                                                    //Меняет столбики в исходной матрице

//вспомогательные функции
double middleAriphmetic(double* mass, int count); //Среднее арифметическое из строчки int
int lenAfterDot(const double& x);                  //Определяет количество цифр после точки
int countLen(const double& x);                     //Определяет количество цифр в числе
string doubleToStr(const double& x);

int CopyMatrix(double** matrix1, double** & matrix2, int lines,int columns);

int PrintResult(double** matrix1, double** matrix2, int lines,int columns, int* mass1, int mass1count);


