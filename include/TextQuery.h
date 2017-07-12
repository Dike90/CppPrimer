#ifndef __TEXTQUERY__
#define __TEXTQUERY__

#include <vector>
#include <map>
#include <set>
#include <memory>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;
using line_no = vector<string>::size_type; //每个单词出现位置的行号
class QueryResult{
    //using namespace std;
    friend ostream& print(ostream&, const QueryResult&);
public:
    QueryResult(string s, shared_ptr<set<line_no>> p , shared_ptr<vector<string>> f): sought(s),lines(p),file(f){};
private:
    string sought;//查询单词
    shared_ptr<set<line_no>> lines;//出现的行号
    shared_ptr<vector<string>> file;//输入文本

};
class TextQuery{
    
public:
    
    TextQuery(ifstream&);
    QueryResult query(const string&) const;
private:
    shared_ptr<vector<string>> file; //输入文件
    //每个单词和它所在行号的映射
    map<string,shared_ptr<set<line_no>>> wm;
};

TextQuery::TextQuery(ifstream &is) : file(new vector<string>){
    string text;
    //逐行读取文件
    while(getline(is,text)){
        file->push_back(text); //保存文本行
        int n = file->size() - 1;//计算当前行号
        istringstream line(text); //将行文本分解成单词
        string word;
        while(line>>word){
            auto &lines = wm[word]; //lines是shared_ptr<set<line_no>>的类型的引用
            if(!lines) //map wm中没有这个单词就分配一个新的set给这个单词
                lines.reset(new set<line_no>);
            lines->insert(n); //wm中有这个单词就把该单词的当前行号加入set中
        }
    }
}

QueryResult TextQuery::query(const string &sought) const {
    //如果没有找到sought，我们返回一个指向此set的指针
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto loc = wm.find(sought);
    if( loc==wm.end())
        return QueryResult(sought,nodata,file);
    else
        return QueryResult(sought,loc->second,file);
}



ostream &print(ostream &os, const QueryResult &qr){
    os<<qr.sought<<" occurs "<<qr.lines->size()<<" "
        <<(qr.lines->size()<=1?"time":"times")<<endl;
    for(auto num : *qr.lines){
        os<<"\t(line "<<num + 1 <<") "<<*(qr.file->begin() + num )<<endl;
    }
    return os;
}


#endif