#include <iostream>
#include <vector>

using namespace std;
int main(){
    vector<int> tv;
    vector<int>::iterator itor;
    for(int i =1 ; i<= 10; i++){
        tv.push_back(i);
        cout<<"the number of element in vector is:"
            <<tv.size()
            <<" and capacity is :"
            <<tv.capacity()<<endl;
    }
    itor = tv.end();
    //tv.insert(itor,9, 99);
    for(int el : tv){
        cout << el<<endl;
    }
    for(int i = 0; i< 10 ; i++){
        tv.pop_back();
        cout<<"the size of vector is :"<<tv.size()<<"and capacity is :"<<tv.capacity()<<endl;
    }
    cout<<tv.capacity()<<endl;
    cin.get();
    return 0;
}