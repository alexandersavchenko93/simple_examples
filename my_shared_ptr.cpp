//  SharedPointer_my
//  Created by Александр on 5/28/19.
//  Copyright © 2019 Александр. All rights reserved.

/*
Класс интеллектуального указателя нуждается в указателях на собственно
себя и на счетчик ссылок. Оба они должны быть указателями, а не реальным
объектом или значением счетчика ссылок, так как цель интеллектуального
указателя - в подсчете количества ссылок через множество интеллектуальных
указателей н один объект.
*/

#include <iostream>

using namespace std;

template<class T>
class SharedPointer
{
public:
    //Когда приходит дата делем ее сет во внутренний указатель
    //Создаем динамически счетчик ссылок на обьект
    SharedPointer(T* ptr)
    {
        ref = ptr;
        ref_count = new unsigned(1);
    }
    
    //Получаем по ссылке смарт-указатель на обьект и присваиваем его данные в указатель получатель
    //Плюсуем +1 ссылку к указателям на обьект
    SharedPointer(SharedPointer& sptr)
    {
        ref = sptr.ref;
        ref_count = sptr.ref_count;
        ++(*ref_count);
    }
    
    ~SharedPointer()
    {
        remove();
    }
    
    SharedPointer& operator=(SharedPointer & sptr) {
        //При присваивании одного смарт поинтера в другой
        //Проверяем если внтутри уже есть указатель не на туже дату то уменьшаем счетчик ссылок на нее
        if(this != &sptr && *ref_count > 0)
        {
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
        if (*ref_count == 0) {
            cout<<"Deleted "<<*ref<<endl;
            delete ref;
            delete ref_count;
        }
    }
    
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
