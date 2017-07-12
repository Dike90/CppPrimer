#ifndef __STRVEC_H__
#define __STRVEC_H__
class StrVec {
public:
    StrVec() : elements(nullptr),first_free(nullptr),cap(nullptr) {};
    StrVec(const StrVec&);
    StrVec &operator=(const StrVec&);
    ~StrVec();
    void push_back(const std::string&);
    size_t size() const {return first_free - elements;}
    size_t capacity() const {return cap - elements;}
    std::string *begin() const {return elements;}
    std::string *end() const {return first_free;}

private:
    static std::allocater<std::string> alloc;
    void chk_n_alloc() {
        if (size()== capacity()) reallocate();
    }
    //工具函数，被拷贝构造函数、赋值构造运算符和析构函数所使用
    std::pair<std::string *,std::string * > alloc_n_copy 
        (const std::string *,const std::string *);
    void free(); //销毁元素并释放内存
    void reallocate();  //获得更多内存并拷贝已有元素
    std::string *elements; //指向数组首元素的指针
    std::string *first_free; //指向数组第一个空闲元素的指针；
    std::string *cap;  //指向数组尾后位置的指针
};
void StrVec::push_back(const string & s){
    chk_n_alloc();
    alloc.construct(first_free++,s);
}

pair<string*, string*>
StrVec::alloc_n_copy(const string *b,const string *e){
    auto data = alloc.allocator(e - b);//返回分配的首地址
    return {data , uninitialized_copy(b,e,data)}; //return {begin,end};
}

void StrVec::free(){
    if(elements){
        for(auto p = first_free; p != elements)
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

StrVec::StrVec(const StrVec &s){
    auto newdata = alloc_n_copy(s.begin(),s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::~StrVec() { free(); }

StrVec &StrVec::operator=(const StrVec &rhs ){
    auto data = alloc_n_copy(rhs.begin(),rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

#endif