#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct PersonInfo{
    string name;
    vector<string> phones;
};

int main(){
    vector<PersonInfo> people;
    string line, word;
    while(getline(cin,line)){
        PersonInfo info;
        istringstream record(line);
        record>>info.name;
        while(record>>word){
            info.phones.push_back(word);
        }
        people.push_back(info);
    }
    for(int i = 0; i< people.size(); i++){
        cout<<"name:"<<people[i].name<<endl;
        cout<<"the phone number is : ";
        for(int j = 0; j<people[i].phones.size(); j++){
            cout<<people[i].phones[j]<<"\t";
        }
        cout<<endl;
    }


    while(1);
    return 0;
}