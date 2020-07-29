#include "myIterator.h"
#include "myAlgorithm.h"
#include "myList.h"
#include <iostream>

/**
 * 自己设计的List迭代器虽然能满足要求，但是暴露了内部List的细节如：
 *  1）在main函数中，为了得到begin和end迭代器，暴露了ListItem
 *  2) 在ListIter class中，为了达成operator++，我们暴露了ListItem的next()函数
 *  因此，需要把迭代器的开发工作交给List的设计者，这样就被完全封装起来
 *  这也是为什么每一种STL容器都提供有专属迭代器的缘由。
 */ 



// 重载函数,不重载就会报错
// 因为find函数比较的是 *first != value
// 在myIterator.h中，*重载返回的是迭代指针指向的类型：listItem<int>对象，而value是int型
// 两者属于不同对象，因此不可比较。报错
// 解决方式： 1：修改find方法，将 *first != value 改为：*first->value() != value
//           2: 重载!= 运算符，如下图即可。
template<typename T>
bool operator!=(ListItem<int>& item, const T& value){
    return item.value() != value;
}


int main(int argc, char** argvs){
    List<int> my_lists;
    for(int i = 0; i < 5; i++){
        my_lists.insert_front(i);
        my_lists.insert_end(i+2);
    }
    my_lists.display();  // 4 3 2 1 0 2 3 4 5 6

    ListIter< ListItem<int> > begin(my_lists.front());
    ListIter< ListItem<int> > end;
    ListIter< ListItem<int> > iter;

    iter = find(begin, end,3);
    if(iter == end)
        std::cout<<"Not Find!"<<std::endl;
    else 
        std::cout<<"Found:"<<iter->value()<<std::endl;

    return 0;
}