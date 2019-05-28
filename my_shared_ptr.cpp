//  main.cpp
//  SharedPointer_my
//
//  Created by Александр on 5/28/19.
//  Copyright © 2019 Александр. All rights reserved.

#include <iostream>

using namespace std;

template<class T>
class SharedPointer
{
public:
    SharedPointer(T* ptr)
    {
        //Инициализируем ref - указателем на входящий обьект
        ref = ptr;
        //Устанавливаем счетчик ссылок в 1
        ref_count = new unsigned(1);
    }
    
    SharedPointer(SharedPointer& sptr)
    {
        ref = sptr.ref;
        ref_count = sptr.ref_count;
        ++(*ref_count);
        cout<<"Counter: "<<*ref_count<<endl;
    }
    
    ~SharedPointer()
    {
        remove();
    }
    
    SharedPointer& operator=(SharedPointer & sptr) {
        /* Если уже присвоено объекту, удаляем одну ссылку. */
        if (*ref_count > 0) {
            remove();
        }
        if (this != &sptr) {
            ref = sptr.ref;
            ref_count = sptr.ref_count;
            ++(*ref_count);
        }
        return *this;
    }
    
    T operator*() {
        return *ref;
    }
    
protected:
    void remove() {
        --(*ref_count);
        cout<<"Counter: "<<*ref_count<<endl;
        if (*ref_count == 0) {
            delete ref;
            delete ref_count;
            cout<<"Object Deleted"<<endl;
        }
    }
     /*Класс интеллектуального указателя нуждается в указателях на собственно
     себя и на счетчик ссылок. Оба они должны быть указателями, а не реальным
     объектом или значением счетчика ссылок, так как цель интеллектуального
     указателя - в подсчете количества ссылок через множество интеллектуальных
     указателей н один объект.
     */
    T* ref;
    unsigned* ref_count;
};

int main(int argc, const char * argv[]) {
    
    int* a = new int(5);
    int* b = new int(7);
    SharedPointer<int> sa(a);
    SharedPointer<int> sb(sa);
    SharedPointer<int> sc(b);
    //sb = sb;
    sb = sc;
    
    int c = *sc;
    cout<<c<<endl;
    return 0;
}
