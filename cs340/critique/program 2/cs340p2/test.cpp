#include <stdlib.h>
#include <iostream>
using namespace std;

void f1(int * number[])
{
    number[0] = number[0] + 1;
};

int main()
{
    int x; 
    cin >> x;
    int number[2];
    number[0] = x;
    
    f1(number);
    
    cout << number[0] << endl;
    
    system("PAUSE");
    
    return 0;
    
}
