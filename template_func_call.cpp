#include <iostream>

using namespace std;

//T
template<typename T>
void adl(T)
{
    cout<<"T ";
}


struct S{};

template<typename T>
void call_adl(T t)
{
    adl(S()); //Независимый от типа ищет в шаблоне
    adl(t); //Зависимый от типа Т ищется позже
}

//S
void adl(S)
{
    cout<<"S ";
}


int main(int argc, const char * argv[]) {
    
    call_adl(S());
    
    return 0;
}
//COUT: TS
