#include <iostream>
using namespace std;
int main(){
    auto f = [] { return "test lambda";};
    cout << f() <<endl;
    cin.get();
    return 0;
}