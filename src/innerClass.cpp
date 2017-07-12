#include <iostream>
#include <string>
using namespace std;

class Outer{
        class Inner{
    public:
        int m_inner=12;
        void printI(){
            cout<<"can I reach Outer "<<m_outer<<endl;
        };
    };
public:
    Outer(int m) : m_outer(m) {outerstr = "this is outer str\n";};
    void printO() {
        cout<<outerstr;
        cout<<"can I reach inner "<<inner.m_inner<<endl;
        inner.printI();
    };
    Inner inner;
    int m_outer;
private:
    string outerstr;

};
int main(){
    Outer to(86);
    to.printO();
    while(1);
    return 0;
}



