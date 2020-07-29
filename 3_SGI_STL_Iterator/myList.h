#ifndef  _MYLIST
#define  _MYLIST

#include <iostream>
/***
 * 设计list类
 * 封装在_font前和_end后插入一个节点
 */
template <typename T>
class ListItem;

// list节点结构
template<typename T>
class ListItem{
    public:
        ListItem(T value): _value(value){
                 _next = NULL;
            }
        T value() const {return _value;}
        ListItem* next() const {return _next;}
        void set_next(ListItem* t){ _next = t;}
        //void set_value(T value)    {_value = value};
        
    private:
        T _value;
        ListItem* _next; // 指向下一个节点 单向链表 single linked list
};
// List 类实现
template<typename T>
class List{
    public:
       
        List(){
            _front = NULL;
            _end   = NULL;
            _size  = 0;
        }
        ListItem<T> * front(){_front;}
        void insert_front(T value){
           ListItem<T> *p = new ListItem<T>(value);
           // 空链表
            if(_front == NULL && _end ==NULL &&_front == _end) {
                _front = p;
                _end = p;
            }
            else{ // 非空
                ListItem<T>* temp = _front;
                _front = p;
                _front->set_next(temp);
            }
            _size++; // 计数器
        }
        void insert_end(T value);
        void display() const;
    private: // 定义前后指针
        ListItem<T>* _end;
        ListItem<T>* _front;
        long _size;
};

template<typename T>
void List<T>::display() const{
    ListItem<T> *temp = _front;
    while(temp!= NULL){
        std::cout<<temp->value()<<" ";
        temp = temp->next();
    }
    std::cout<<std::endl;
}

template<typename T>
void List<T>::insert_end(T value){
    ListItem<T> *p = new ListItem<T>(value);
   // ListItem<T> *temp = _end;
   // 空列表
    if(_end == NULL && _front == NULL && _end == _front){
        _end = p;
        _front = p;
    }
    else{ // 非空列表
        _end->set_next(p); // 更新_end指针
        _end = p;
    }
    _size++; // 计数器自增
};



#endif