#include <iomanip>
#include "WorkWithMatrix.h"
#include "LoadMatrix.h"
#include "ErrorHandler.h"

#define FAILOPEN 10000
#define NOTSQUERENESS 10100
#define MEMORYERROR 10200
#define UNCORRECTNUMBER 10300
#define NUMBEROVERFLOW 10400
#define FEWLINES 10500
#define EMPTYFILE 10600

using namespace std;

bool TryAgain();

int main()
{
    setlocale(LC_ALL, "rus");

    //инициализация необходимых переменных
    string filename;
    int error = -1;
    int columns = 0;
    int lines = 0;
    int errorLine = 0;
    int errorColumn = 0;
    string errorNumber;
    double **Matrix;
    int mass1count;
    int* mass1;
    double** matrix2;


    while(error != 0)
    {
        switch(error)
        {
        case -1:
            InputFilename(filename);

            //для тестирования
            //filename = "123.txt";

            error = LoadMatrixFromFile(filename, Matrix, lines, columns, errorLine, errorColumn, errorNumber);
            if(error != 0)
                break;

            error = workingWithMatrix(Matrix, matrix2, lines, columns, mass1, mass1count);
            if(error != 0)
                break;

            error = PrintResult(Matrix, matrix2, lines, columns, mass1, mass1count);
            if(error != 0)
                break;
            if(TryAgain())
                error = -1;
            else
                error = 0;

            break;
        case FAILOPEN:
            WriteError(error);
            error = -1;
            break;
        case NOTSQUERENESS:
            WriteError(error, errorLine);
            error = -1;
            break;
        case MEMORYERROR:
            WriteError(error);
            error = -1;
            break;
        case UNCORRECTNUMBER:
            WriteError(error, errorLine, errorColumn, errorNumber);
            error = -1;
            break;
        case NUMBEROVERFLOW:
            WriteError(error, errorLine, errorColumn, errorNumber);
            error = -1;
            break;
        case FEWLINES:
            WriteError(error);
            error = -1;
            break;
        case EMPTYFILE:
            WriteError(error);
            error = -1;
            break;
        }

    }



    return 0;
}


bool TryAgain()
{
    while(true)
    {
        Write("\nЖелаете выполнить расчеты еще раз (впишите 1,если да или 0, если нет)?\n");
        string enter = Enter();
        if(enter == "1")
            return true;
        else if(enter == "0")
            return false;
        else
        {
            Write("Некорректный ввод, попробуйте еще раз.\n");
            continue;
        }
    }
}
