#ifndef __STRVEC_H__
#define __STRVEC_H__
class StrVec {
public:
    StrVec() : elements(nullptr),first_free(nullptr),cap(nullptr) {};
    StrVec(const StrVec&); //拷贝赋值函数
    StrVec(StrVec &&) noexcept; //移动赋值函数
    StrVec &operator=(const StrVec&); //拷贝赋值运算符
    StrVec &operator=(StrVec&&) noexcept; //移动赋值运算符
    StrVec &operator=(std::initializer_list<std::string>);
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
    return {data , uninitialized_copy(b,e,data)}; // 从[b,e)拷贝到data所指空间,返回一个尾后迭代器
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

StrVec::StrVec(StrVec &&s) noexcept // 移动操作不应抛出任何异常
//成员初始化器接管s中的资源
    : elements(s.elements) , first_free(s.first_free) ,cap(s.cap) {
    //令s进入这样一种状态--对其运行析构函数是安全的
    s.elements = s.first_free = s.cap = nullptr;

}

StrVec::~StrVec() { free(); }

StrVec &StrVec::operator=(const StrVec &rhs ){
    auto data = alloc_n_copy(rhs.begin(),rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
    //检测是否是自赋值
    if (this != &rhs){
        free(); //释放左侧运算对象的空间
        //从rhs接管资源
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        //将rhs至于可析构状态
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

StrVec &StrVec::operator=(std::initializer_list<std::string> il){
    auto data = alloc_n_copy(il.begin(),il.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
void StrVec::reallocate(){
    //分配当前大小两倍的内存空间
    auto newcapacity = size() ? 2*size() : 1;
    //分配新空间
    auto newdata = alloc.allocate(newcapacity); //返回新分配空间的首地址
    //将数据从旧内存移动到新内存
    auto dest = newdata;
    auto elem = elements; //原数据首地址
    for (size_t i=0; i != size() ; i++)
        alloc.construct(dest++ , std::move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

#endif