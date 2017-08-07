#include "ErrorHandler.h"

using namespace std;


void WriteError(int errorCode, int errorLine, int errorColumn, string errorNumber)
{
    switch(errorCode)
    {
    case FAILOPEN:
        Write("Невозможно открыть файл\n");
        break;
    case NOTSQUERENESS:
        Write("Матрица не прямоугольна\n");
        Write("Проблемная строка: ");
        Write(errorLine);
        Write("\n");
        break;
    case MEMORYERROR:
        Write("Невозможно выделить память\n");
        break;
    case UNCORRECTNUMBER:
        Write("Некорректное число\n");
        Write("Строка: ");
        Write(errorLine + 1);
        Write(" Столбик: ");
        Write(errorColumn + 1);
        Write(" Число: ");
        Write(errorNumber);
        Write("\n");
        break;
    case NUMBEROVERFLOW:
        Write("Переполнение в числе\n");
        Write("Строка: ");
        Write(errorLine + 1);
        Write(" Столбик: ");
        Write(errorColumn + 1);
        Write(" Число: ");
        Write(errorNumber);
        Write("\n");
        break;
    case FEWLINES:
        Write("В файле обнаружено недостаточное количество строк для выполнения расчетов\n");
        break;
    case EMPTYFILE:
        Write("Пустой файл!\n");
        break;
    }
}
