#include "LoadMatrix.h"

using namespace std;

void DeleteMatrix(double** matrix, int lines)
{
    for(int i = 0; i < lines;i++)							//������� ������� ������ � ��������� ������ ������� � ����� 5
	{
		delete [] matrix[i];
	}
	delete [] matrix;
}
int CheckNumber(string & str)
{
    bool hadDot = false;                            //����, ��� ����� ��� ���� � �����
    bool hadE = false;                              //����, ��� � ��� ����������� � �����
    //�������� �� ��������� ������ ����
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
    //�������� �� ������������
    double num = strtod(str.c_str(), NULL);
        if(num==HUGE_VAL)
            return 2;

    if(hadE)            //�������� �� ������������ ��� ������� ����������
    {
        int number = 0; //��������� �� �
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
            str[i] = ',';                             //� ������� ������ ������������ ������� � ������
            if(i == 0) //���� ����� ����� � ����� ������, �� �������� ���� ����� ������
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
			fin >> s;											//��������� �� ������ ����� � ������� ��� � ��������� ���
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
        return error; //������
    return 0;

}

void InputFilename(string & filename)
{
    Write("������� �������� �����:\n");
    filename = Enter();
}

bool OpenFile(ifstream & fin, string filename)
{
    fin.open(filename.c_str());										//���� ���� �� ������ �� ��������� ������ ������� � ����� 1
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
    string s;												//������� ������
    int countStr = 0;
    int countColumn;
    lines = 0;
    columns = 1;
	while (!fin.eof())										//���� �� ����� �����
	{
		getline(fin,s);										//������ ��� ���������
		if (s == "") continue;								//������ �������� �� ������ ������
		bool allSpace = true;
		for(int i = 0; i < s.length(); i++)
        {
            if(s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
            {
                allSpace = false;
                break;
            }
        }
        if (allSpace) continue;                             //������ �������� �� ������ ������
		countStr++;										    //������� �����
		countColumn = 1;									//������� ��������

        //���� ������ ����� (� ������ ���� ������� ���������� � ��������
        int start = 0;
        while(s[start] == ' ')
        {
            start++;
        }

        //����� ���������� ����� (����� ������� ����� ��������� ����� ���������� ����� �� �����������
        int end = 0;
        for(int j = start; j < s.length(); j++)
        {
            if(s[j] != ' ' && s[j] != '\n' && s[j] != '\t')
                end = j;
        }
        if (countStr==1)									//��������� ���������� �������� � ������ �������� ������ � ������� � columns
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
      //�������� �� ���������������
		if (columns != countColumn)										//���������, ����� ����� �������� ����� ���������
		{
            columns = 0;
            errorLine = lines+1;
            return NOTSQUERENESS;
		}
		lines = lines + 1;											//lines - ������� �������� ����� �����, �.�. �������� ����� �������

	}
	if(lines == 0 && columns == 0)
        return EMPTYFILE;
	return 0;
}
