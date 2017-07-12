#include <iostream>
#include <map>
#include <string>
#include <utility>
using namespace std;
int main(){
    map<string,int> mymap;
    mymap["li"]= 1234435;
    mymap["dfdf"]=3958234;
    mymap["dk"]=12312121;
    mymap["cmx"]=320489324;
    for(pair<string,int> el : mymap){
        cout<<el.first<<":"<<el.second<<endl;
    }
    cin.get();
    return 0;
}