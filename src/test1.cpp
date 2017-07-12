#include <iostream>
using namespace std;

int main(){
    const char str1[] = "abc";
    const char str2[] = "abc";
    const char *p1 = "abc";
    const char *p2 = "abc";

    if(str1==str2)
        cout<<"str1==str2"<<endl;
    if(p1 == p2)
        cout<<"p1==p2"<<endl;
    cout<<&str1<<endl;
    cout<<&str2<<endl;
    cout<<&p1<<endl;
    cout<<&p2<<endl;

    while(1);
    return 0;
}