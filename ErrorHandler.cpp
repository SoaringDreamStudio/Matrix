#include "ErrorHandler.h"

using namespace std;


void WriteError(int errorCode, int errorLine, int errorColumn, string errorNumber)
{
    switch(errorCode)
    {
    case FAILOPEN:
        Write("���������� ������� ����\n");
        break;
    case NOTSQUERENESS:
        Write("������� �� ������������\n");
        Write("���������� ������: ");
        Write(errorLine);
        Write("\n");
        break;
    case MEMORYERROR:
        Write("���������� �������� ������\n");
        break;
    case UNCORRECTNUMBER:
        Write("������������ �����\n");
        Write("������: ");
        Write(errorLine + 1);
        Write(" �������: ");
        Write(errorColumn + 1);
        Write(" �����: ");
        Write(errorNumber);
        Write("\n");
        break;
    case NUMBEROVERFLOW:
        Write("������������ � �����\n");
        Write("������: ");
        Write(errorLine + 1);
        Write(" �������: ");
        Write(errorColumn + 1);
        Write(" �����: ");
        Write(errorNumber);
        Write("\n");
        break;
    case FEWLINES:
        Write("� ����� ���������� ������������� ���������� ����� ��� ���������� ��������\n");
        break;
    case EMPTYFILE:
        Write("������ ����!\n");
        break;
    }
}
