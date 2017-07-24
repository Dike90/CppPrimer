#ifndef __QUERY_H__
#define __QUERY_H__

#include<string>
#include"TextQuery.h"
//这是一个抽象基类，具体的查询类型从中派生，所有成员都是private的
class Query_base {
    friend class Query;
protected:
    //using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;
private:
    //eval返回与当前Query匹配的QueryResult
    virtual QueryResult eval(const TextQuery&) const = 0;
    //rep是表示查询的一个string
    virtual std::string rep() const = 0;
};
//这是一个管理Query_base继承体系的接口类
class Query {
    //这些运算需要访问接受shared_ptr的构造函数，而该函数是私有的
    friend Query operator~(const Query &);
    friend Query operator|(const Query &, const Query);
    friend Query operator&(const Query &, const Query);
public:
    //构造一个新的WordQuery
    Query(const std::string&);
    //接口函数：调用对应的Query_base操作
    QueryResult eval(const TextQuery &t) const { return q->eval(t);}
    std::string rep() const { return q->rep();}
private:
    Query(std::shared_ptr<Query_base> query) : q(query) {}
    std::shared_ptr<Query_base> q;

};
inline Query::Query(const std::string &s) : q(new WordQuery(s)) {}
class WordQuery: public Query_base {
    friend class Query; //Query使用WordQuery构造函数
    WordQuery(const std::string &s) : query_word(s) {}
    //具体的类：WordQuery将定义所有继承而来的纯虚函数
    QueryResult eval(const TextQuery &t) const { return t.query(query_word);}
    std::string rep() const { return query_word;}
    std::string query_word; //要查找的单词
};

class NotQuery : public Query_base {
    friend Query operator~(const Query &);
    NotQuery(const Query &q) : query(q) {}
    std::string rep() const { return "~(" + query.rep() + ")";}
    QueryResult eval(const TextQuery&) const;
    Query query;
};
inline Query operator~(const Query &operand){
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

#endif
