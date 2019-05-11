#include <iostream>

using namespace std;

///TEMPLATE///

///1_Param & или *
//Template 1
template<typename T>
void foo(T& param){};

//Template 2
template<typename T>
void foo(const T& param){};
//Template 2
template<typename T>
void foo(const T* param){};

///2_Param T&& - универсальная ссылка
//Template 3
template<typename T>
void foo(const T&& param){};

///3_Param T - ни указатель ни ссылка
//Template 4
template<typename T>
void f(T param){};

///4_Шаблон для вывода кол-во елемнтов массива
template <typename T,std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) noexcept { //T (&)[N] - ссылка на массив
    return N;
}

///4_Указатель на функцию
int someFunc(int x){return 1;};

template<typename T>
void f1(T param){};

template<typename T>
void f2(T& param){};

int main(int argc, const char * argv[]) {
    
    //Template 1
    int x = 27;
    const int cx = x;
    const int& rx = x;
    
    foo(x);  //тип T int ,тип param int&
    foo(cx); //тип Т const int, тип param const int&
    foo(rx); //тип T const int, тип param const int&, при выводе типа игнорируется ссылочность
    //!!!Тоесть тип переменной + &
    
    //Template 2
    foo(x);  //тип T int ,тип param const int&
    foo(cx); //тип T int ,тип param const int&
    foo(rx); //тип T int ,тип param const int&, при выводе типа игнорируется ссылочность
    //!!!const + T + &
    
    //Template 3
    foo(x);  //x - lvalue,тип T int& ,тип param int&
    foo(cx); //x - lvalue,тип T const int& ,тип param const int&
    foo(rx); //x - lvalue,тип T const int& ,тип param const int&, при выводе типа игнорируется ссылочность
    foo(25);//27 - rvalue,T - int, param int&&
    ///!!!Если lvalue (int&) or (const int&), если rvalue (int&&)
    
    //Template 4
    f(x);  //тип T int ,тип param int
    f(cx); //тип T int ,тип param int
    f(rx); //тип T int ,тип param int
    ///!!!Какой тип T такой  и тип Param, так как копия передаваемого значеня не обязательно должна перенимать все характеристика переменной из которой она передавалась const и прочие спецификаторы не учитываются при выводе типа
    
    const char* const ptr = "Hello";
    f(ptr); //тип Т const char*, тип param const char*
    //Констанстость того на что указывал указатель сохранится но сам указатель внутри функции не будет костантным
    
    //Аргументы массывы
    const char name[] = "Name";
    
    f(name); //Name * on first char 'N'; param - const char*
    
    foo(name); //Если передать по ссылке то это будет ссылка на масив; T - const char[4] and param const char (&)[4]
    
    cout<<arraySize(name)<<endl; // 5 elements - 4 + "/0"
    
    ///Указатель на функцию
    f1(someFunc); //param - void(*) (int) - передается по значению
    f2(someFunc); //param - void(&) (int) - передается по ссылке
    
    return 0;
}
