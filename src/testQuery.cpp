#include <iostream>
#include <fstream>
#include "../include/TextQuery.h"

using namespace std;
int main(){
    ifstream readfile("tale.txt");
    if(!readfile.is_open()){
        cout<<"file can't open"<<endl;
    }
    TextQuery myquery(readfile);
    print(cout,myquery.query("word"));

    while(1);
    return 0;
}