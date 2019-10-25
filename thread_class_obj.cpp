#include <cstdlib>
#include <thread>
#include <memory>
#include <iostream>

using namespace std;

//A
template<class T>
class A{
public:
    A(){}
    virtual ~A(){}
    virtual void foo(T value){ cout<<"Value A: "<<value<<endl;}
};

//B
template<class T>
struct B: public A<T> {
public:
    B(){};
    virtual ~B(){};
    virtual void foo(T value)
    {
        value = value + 500;
        cout<<"Value B: "<<value<<endl;
    }
};


int main(int argc, char** argv) {
    A<int> a;
    
    thread th1;
    thread th2;
    
    th1 = thread(&A<int>::foo,&a,80);
    th1.join();
    
    th2 = thread([&](){(a.foo(70));});
    th2.join();
    
    return 0;
}
