#include <iostream>
#include <cmath>

using namespace std;

//Большее и меньшее число из двузначного
void MinMaxNumber()
{
    int number;
    cout<< "Введите двузначное число: " <<endl;
    cin>>number;
    int a = 0;
    int b = 0;
    if (number>9 && number<100)
    {
    b = number%10;
    a = number/10;
    a==b?cout<<"Числа равны"<<endl: a>b?cout<<"Большое число: "<< a << endl << "Меньшее число: " << b << endl: cout<<"Большое число: "<< b << endl << "Меньшее число: " << a << endl;
    }else
    {
        cout<<"Вы ввели не двузначное число!!!"<<endl;
    }
};

int main(int argc, const char * argv[]) {
    //MinMaxNumber();
    return 0;
}
