#ifndef _MYITERATOR
#define  _MYITERATOR

#include "myList.h"

template <class Item>
struct ListIter{
    Item* ptr;
    ListIter (Item* p = NULL): ptr(p){}
    
    // 重载运算符* 返回Item
    Item& operator*() const {return *ptr;}
    // 重载运算符-> 返回指向Item的指针
    Item* operator->() const{return ptr;}
    // prefix increment, 返回迭代器
    ListIter& operator++(){
        ptr = ptr->next(); return *this;
    }
    // postfix increment
    ListIter operator++(int){
        ListIter tmp = *this;
        ++*this;
        return tmp;
    } 
    // 重载==
    bool operator==(const ListIter& i) const{
        return ptr == i.ptr;
    }
    // 重载!=
    bool operator!=(const ListIter& i) const{
        return ptr != i.ptr;
    }
    
};

#endif