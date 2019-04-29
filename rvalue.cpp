//  Created by Александр on 4/10/19.
//  Copyright © 2019 Александр. All rights reserved.

#include <iostream>

using namespace std;

struct A
{
    A(){ cout<<"A default constructor\n"; }
    A(const int& i){cout<<i<<endl;}
    
    void foo(const int& i)
    {
        cout<<"This is lvalue\n";
    }

    void foo(int&& i)
    {
        cout<<"This is rvalue\n";
    }
    
    template<class T>
    void fooT(const T& i)
    {
        cout<<"This is lvalue\n";
    }
    
    template<class T>
    void fooT(T&& i)
    {
        cout<<"This is rvalue\n";
    }
    
};

struct B
{
    B(A a){}
};

struct C
{
//    void inc(const int &i)
//    {
//        //i++;
//    }
    
    void inc(int &i)
    {
        i++;
    }
};

int foo() //RVO Return Value Optimaztion -> Все обьекты из функции возвращаются напрямую без копий как rvalue;
{
    return 52;
}

//REMOVE_REFETRENCE
template <class T>
struct my_remove_reference
{
    typedef T value;
};

template <class T>
struct my_remove_reference<T&>
{
    typedef T value;
};

template <class T>
struct my_remove_reference<T&&>
{
    typedef T value;
};

//MOVE
//На стадии компиляции усекаем у Т все ссылки и возвращаем тип Т
//Потом внутри функии статик кастом конвертируем любой тип в rvalue и возвращаем его
//Функция не видает исключний
template<class T>
constexpr typename my_remove_reference<T>::value&& myMove(T&& t) noexcept
{
    return  static_cast<typename my_remove_reference<T>::value&&>(t);
}

//FORWARD
template<class T>
constexpr T&& forardReal(typename my_remove_reference<T>::value& t) noexcept
{
    return static_cast<T&&>(t);
}


int main(int argc, const char * argv[]) {
    
    //CONTEXT MAGIC
    
    //(42); - rvalue
    //A a({43}); //Call default constructor,если нет контрустора принимаещего параметр
    //A a{}; //Call default constructor Mayers
    //int i = 12;
    //B b(A(1)); //Call int constructor -> 1
    A(x); //Call default constructor A(x) == A x2
    //A x2;
    //A x3;
    //int (i42)(42);// -> 42
    //B b(A a); //Прототип функции внутри мейна
    //B b((A(i42))); //-> 42
    //B b1(A({})); //-> 0
    
    //rvalue - temp object;
    
    //int ix5 = 5; //rvalue(pure_value)
    
    //x.foo(5); //rvalue
    //x.foo(ix5); //lvalue
    
    //FooT working corrctly for:
    //x.fooT(nullptr); //->rvalue
    //x.fooT("Hello"); //-> Строковый литерал
    
    C c;
    
    //int i6 = 6;
    //c.inc(i6);
    //c.inc(3); // - Нельзя передавть rvalue в некостантный lvalue!!! //T& x = rvalue //Это скомпилирутся  в VS 2017
    
    //T&& = lvalue - нельзя
    //int i7 = 7;
    //int& i7_ref = i7;
    //int&& i7_ref = i7; -> Не работает
    //int&& i7_ref_r = 7; -> rvalue может стоять слева
    
    //auto i_f = foo();
    //int&& i_f2 = foo();
    //x.foo(foo()); //foo-> 52 -> rvalue
    //x.foo(i_f); //lvalue - так как это не временный обькт и он будет жить
    
    //T&& & a; Нельзя написать ссылку на rvalue ссылку
    //Но такая ситуация может возникнуть в шаблонах по правиду сжатия ссылок
    //Если передать в move lvale тоесть Т& то по правилу тип значеий и возаощаемый тип сожмется в Т& и тогда функция не выполнит приведения к rvalue
    
    //STD::MOVE
    int i8 = 5;
    x.foo(std::move(i8)); //Convert lvalue to rvalue
    
    int i10 = 10;
    x.foo(static_cast<int&&>(i10)); //Приведение типа к rvalue
    
    x.foo(myMove(i10)); //MyMove
    
    
    return 0;
}
