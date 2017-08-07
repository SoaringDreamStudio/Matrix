#include "LoadMatrix.h"

using namespace std;

void DeleteMatrix(double** matrix, int lines)
{
    for(int i = 0; i < lines;i++)							//Поэтому очищаем память и завершаем работу функции с кодом 5
	{
		delete [] matrix[i];
	}
	delete [] matrix;
}
int CheckNumber(string & str)
{
    bool hadDot = false;                            //Флаг, что точка уже была в числе
    bool hadE = false;                              //флаг, что е уже встречалось в числе
    //проверка на отсутсвие лишних букв
    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] == '1'||
           str[i] == '2'||
           str[i] == '3'||
           str[i] == '4'||
           str[i] == '5'||
           str[i] == '6'||
           str[i] == '7'||
           str[i] == '8'||
           str[i] == '9'||
           str[i] == '0'||
           str[i] == '.'||
           str[i] == ','||
           str[i] == ' '||
           str[i] == '\t'||
           str[i] == '\n')
        {
            continue;
        }
        else if(!hadDot && (str[i] == '.' || str[i] == ','))
        {
            hadDot = true;
        }
        else if(hadDot && (str[i] == '.' || str[i] == ','))
        {
            return UNCORRECTNUMBER;
        }
        else if(str[i] == '-')
        {
            if(i != 0)
                return UNCORRECTNUMBER;
        }
        else if(str[i] == 'e' || str[i] == 'E')
        {
            if(!hadE)
                hadE = true;
            else
                return UNCORRECTNUMBER;
        }
        else
            return UNCORRECTNUMBER;
    }
    //проверка на переполнение
    double num = strtod(str.c_str(), NULL);
        if(num==HUGE_VAL)
            return 2;

    if(hadE)            //Проверка на переполнение при наличии экспоненты
    {
        int number = 0; //указатель на Е
        while(number < str.length())
        {
            if(str[number] == 'e' || str[number] == 'E')
                break;
            number++;
        }
        string exponent;
        for(int i = number; i < str.length(); i++)
            exponent.push_back(str[i]);
        if(atoi(exponent.c_str()) > 21)
            return NUMBEROVERFLOW;
    }
    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] == '.' || str[i] == ',')
        {
            str[i] = ',';                             //в русской локали используется запятая в числах
            if(i == 0) //Если точка стоит в самом начале, то добавить ноль перед точкой
            {
                str.insert(0,1,'0');

                i++;
            }

        }
    }
    return 0;
}

int LoadMatrixFromFile(string filename, double** & matrix, int & lines, int & columns, int & errorLine, int & errorColumn, string & errorNumber)
{
    int error = CalculateColumnsAndLines(lines, columns,  filename, errorLine);
    if(error != 0)
        return error;

    ifstream fin;
    if(OpenFile(fin, filename))
    {
        lines = 0;
        columns = 0;
        errorLine = -1;
        return FAILOPEN;
    }

    matrix = new(nothrow) double*[lines];
    if(matrix == NULL)
    {
        delete [] matrix;
        return MEMORYERROR;
    }
    for(int i = 0; i < lines; i++)
    {
        matrix[i]=new(nothrow) double[columns];
        if(matrix[i] == NULL)
        {
            DeleteMatrix(matrix, lines);
            return MEMORYERROR;
        }
    }

    for(int i = 0; i < lines; i++)
		for(int j = 0; j < columns; j++)
		{
			string s;
			fin >> s;											//Считываем по каждое число и заносим его в строковой тип
            error = CheckNumber(s);
            if(error > 0)
            {
                lines = 0;
                columns = 0;
                errorLine = i;
                errorColumn = j;
                errorNumber = s;
                DeleteMatrix(matrix, lines);
                fin.close();
                return error;
            }

            double count = atof(s.c_str());
            matrix[i][j] = count;
		}
	fin.close();
	return 0;
}
int CalculateColumnsAndLines(int & lines, int & columns, string filename, int & errorLine)
{
    ifstream fin;
    lines = 0;
    columns = 1;
    if(OpenFile(fin, filename))
    {
        columns = 0;
        return FAILOPEN;
    }
    int error = CalculateCAndLFromFile(fin, lines, columns, errorLine);
    CloseFile(fin);
    if(error)
        return error; //ошибка
    return 0;

}

void InputFilename(string & filename)
{
    Write("Введите название файла:\n");
    filename = Enter();
}

bool OpenFile(ifstream & fin, string filename)
{
    fin.open(filename.c_str());										//Если файл не открыт то завершаем работу функции с кодом 1
	if (!fin.is_open())
		return 1;
    return 0;
}
void CloseFile(ifstream & fin)
{
	fin.close();
}

int CalculateCAndLFromFile(ifstream & fin, int & lines, int & columns, int & errorLine)
{
    string s;												//рабочая строка
    int countStr = 0;
    int countColumn;
    lines = 0;
    columns = 1;
	while (!fin.eof())										//Цикл по всему файлу
	{
		getline(fin,s);										//Читаем его построчно
		if (s == "") continue;								//Первая проверка на пустую строку
		bool allSpace = true;
		for(int i = 0; i < s.length(); i++)
        {
            if(s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
            {
                allSpace = false;
                break;
            }
        }
        if (allSpace) continue;                             //Вторая проверка на пустую строку
		countStr++;										    //Счетчик строк
		countColumn = 1;									//Счетчик столбцов

        //ищем первое число (в случае если строчка начинается с пробелов
        int start = 0;
        while(s[start] == ' ')
        {
            start++;
        }

        //поиск последнего числа (чтобы пробелы после последней цифры последнего числа не учитывались
        int end = 0;
        for(int j = start; j < s.length(); j++)
        {
            if(s[j] != ' ' && s[j] != '\n' && s[j] != '\t')
                end = j;
        }
        if (countStr==1)									//Посчитаем количество столбцов в первой непустой строке и запишем в columns
			for(int j = start; j <= end; j++)
			{
				if (s[j] == ' ' && s[j-1] != ' ' && s[j-1] != '\t')
					columns = columns + 1;
			}

        for(int j = start; j <= end; j++)
        {
            if (s[j] == ' ' && s[j-1] != ' ' && s[j-1] != '\t')
                countColumn++;
        }
      //проверки на прямоугольность
		if (columns != countColumn)										//Проверяем, чтобы число столбцов везде совпадало
		{
            columns = 0;
            errorLine = lines+1;
            return NOTSQUERENESS;
		}
		lines = lines + 1;											//lines - счетчик непустых строк файла, т.е. значащих строк матрицы

	}
	if(lines == 0 && columns == 0)
        return EMPTYFILE;
	return 0;
}
