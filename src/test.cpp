#include <iostream>
#include <string>
#include "../include/test2.h"
using namespace std;


int cout_calls()
{
    static int cnt = 0;
    return ++ cnt;
}

int main()
{
    
    test1();
    
    cout << __func__<<endl;
    cout <<__FILE__<<endl;
    cout <<__LINE__<<endl;
    cout <<__TIME__<<endl;
    cout <<__DATE__<<endl;
    cin.get();
    cin.get();

    return 0;
}
