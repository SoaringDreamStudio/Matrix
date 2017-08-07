#include "ConsoleInOut.h"

using namespace std;

void Write(string i)
{
    cout << i;
}
void Write(int i)
{
    cout << i;
}
void Write(double i)
{
    cout << i;
}

string Enter()
{
    string s;
    getline(cin, s);
    return s;
}
