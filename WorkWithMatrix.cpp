#include "WorkWithMatrix.h"

using namespace std;

int workingWithMatrix(double** & matrix1, double** & matrix2, int lines,int columns, int* & mass1, int & mass1count)
{
    int error = CopyMatrix(matrix1, matrix2, lines, columns);
    if(error)
        return error;
    error = variant1(matrix2, lines, columns, mass1count, mass1);
    if(error)
        return error;

    error = variant2(matrix2, lines, columns, mass1count, mass1);
    if(error)
        return error;

    return 0;
}

int PrintResult(double** matrix1, double** matrix2, int lines,int columns, int* mass1, int mass1count)
{
    Write("\nИсходная матрица: \n");
    if(format_cout(matrix1,lines,columns))
    {
        DeleteMatrix(matrix1, lines);
        return MEMORYERROR;
    }
    variantOutput1(mass1count, mass1);
    variantOutput2(matrix2,lines,columns);

    return 0;
}

int CopyMatrix(double** matrix1, double** & matrix2, int lines,int columns)
{
    matrix2 = new(nothrow) double*[lines];
    if(matrix2 == NULL)
    {
        delete [] matrix2;
        return MEMORYERROR;
    }
    for(int i = 0; i < lines; i++)
    {
        matrix2[i]=new(nothrow) double[columns];
        if(matrix2[i] == NULL)
        {
            DeleteMatrix(matrix2, lines);
            return MEMORYERROR;
        }

    }
    for(int i = 0; i < lines; i++)
        for(int j = 0; j < columns; j++)
            matrix2[i][j] = matrix1[i][j];
    return 0;
}
int format_cout(double **matrix,int lines,int columns)
{

    int* max_len = new(nothrow) int[columns];
    if(max_len == NULL)
    {
        delete max_len;
        return MEMORYERROR;
    }

    int* maxLenAfterDot = new(nothrow) int[columns];
    if(maxLenAfterDot == NULL)
    {
        delete maxLenAfterDot;
        return MEMORYERROR;
    }


	for(int i = 0; i < lines; i++)
        for(int j = 0; j < columns; j++)
        {
            if(countLen( matrix[i][j] ) > max_len[j])
                max_len[j] = countLen( matrix[i][j] );
            ////////////////////////////////
            if(lenAfterDot( matrix[i][j] ) > maxLenAfterDot[j])
                maxLenAfterDot[j] = lenAfterDot( matrix[i][j] );
        }

	for(int i = 0; i < lines; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            cout << fixed << setprecision(maxLenAfterDot[j]) << setw(max_len[j]+1) << double(*(matrix[i]+j)) << " ";
        }
        cout << endl;
    }

    cout << endl;
    delete [] max_len;
    delete [] maxLenAfterDot;
    return 0;
}

double middleAriphmetic(double* mass, int count)
{
    double summ = 0;
    for(int i = 0; i < count; i++)
    {
        summ += mass[i];
    }
    return summ/count;
}



int variant1(double** matrix,int lines,int columns, int & mass1count, int* & mass1)                  //Определяет количество нужных столбиков
{
    if(lines > 1)
    {
        mass1count = 0;
        for(int i = 0; i < columns; i++) //количество столбцов
        {
            if(matrix[1][i] < matrix[0][i])
            {
                mass1count++;
            }
        }
        mass1 = new(nothrow) int[mass1count];
        if(mass1 == NULL)
        {
            delete [] mass1;
            return MEMORYERROR;
        }


        int active = 0;
        for(int i = 0; i < columns; i++) //kolvo stolb
        {
            if(matrix[1][i] < matrix[0][i])
            {
                mass1[active] = i;
                active++;
            }
        }
        return 0;
    }
    else
    {
        DeleteMatrix(matrix, lines);
        return FEWLINES; //ошибка, что недостаточно строк для расчетов
    }


}


int variant2(double** matrix,int lines,int columns, int mass1count, int* & mass1)
                                                    //Меняет столбики в исходной матрице
{
    for(int i = 0; i < mass1count; i++)
    {
        double * tmpMatrix = new(nothrow) double[lines];                        //Создаем столбец

        if(tmpMatrix == NULL)
        {
            delete [] tmpMatrix;
            return MEMORYERROR;
        }


        for(int j = 0; j < lines; j++)
        {
            tmpMatrix[j] = matrix[j][mass1[i]];
        }

        matrix[0][mass1[i]] = middleAriphmetic(tmpMatrix, lines);
        for(int j = 1; j < lines; j++)
        {
            matrix[j][mass1[i]] = matrix[0][mass1[i]];
        }
    }
    return 0;
}

void variantOutput1(int mass1count, int* mass1)    //Вывод задания варианта
{
    Write("В следующих столбиках второй элемент меньше первого: \n   ");
    if(mass1count)
    {
        for(int i = 0; i < mass1count; i++)
        {
            Write((*(mass1 + i)) + 1);                //Адресная арифметика
            if(i != mass1count-1)
                Write(", ");
        }
    }
    else
        Write("Подходящие столбики не найдены.");

    Write("\n\n");
}

void variantOutput2(double **matrix,int lines,int columns)           //Вывод задания варианта
{
    Write("Обновленная матрица: \n");
    format_cout(matrix,lines,columns);
}


int lenAfterDot(const double& x)                  //Определяет количество цифр после точки
{
    double smallX = floor(x);
    double newX = x - smallX;
    if(newX == 0)
    {
        return 0;
    }
    string tmp = doubleToStr(newX);
    return tmp.length()-2;
}

int countLen(const double& x)                     //Определяет количество цифр в числе
{
    string tmp = doubleToStr(x);
        return tmp.length();
}

string doubleToStr(const double& x)
{
    ostringstream strs;
    int z = lenAfterDot(x);
    if(z == 0)                                      //костыль от бага с отображением кучи нулей после запятой при z = 0
        strs << fixed << setprecision( 0 ) << x;
    else
        strs << fixed << setprecision( z ) << x;
    string str = strs.str();
    return str;
}
