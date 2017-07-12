#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

map<string,string> buildMap(ifstream &map_file){
    map<string,string> trans_map;  //保存转换关系
    string key;                    //要转换的字符
    string value;                   //转换后的字符
    //读取第一个字符串存入key中，剩余的部分存入value中(包含第一个字符串剩下的空格)
    while (map_file >> key && getline(map_file,value))
        if (value.size() >1)        //检查是否存在转换规则
            trans_map[key] = value.substr(1); //跳过开头的空格
        else
            throw runtime_error("no value for" + key);
    return trans_map;
}
const string& transform(const string &s, const map<string,string> &m){
    auto map_it = m.find(s);
    if (map_it != m.cend())
        return map_it->second;
    else
        return s;
} 

void word_transform( ifstream &map_file, ifstream &input){
    auto trans_map = buildMap(map_file);//保存转换规则
    string text;                        //保存输入的每一行
    while( getline(input, text)){       //读取每一行
        istringstream stream(text);     
        string word;                
        bool firstword = true;          //控制是否打印空格  
        while( stream >> word){
            if (firstword) firstword = false; 
            else cout<<" ";             //单词间打印一个空格
            cout << transform(word,trans_map);  //打印转换后的字符
        }
        cout<<endl;
    }
}

int main(){
    ifstream trans_rule("transrule.txt");
    ifstream to_be_transed("tobetransed.txt");
    word_transform(trans_rule,to_be_transed);

    while(1);
    return 0;
}