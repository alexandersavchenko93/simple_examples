#include <iostream>
#include <cmath>

using namespace std;

//Длинна вектора по трем кординатам
double vectorLength(double x,double y,double z)
{
    double vectorLenght = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    cout<<vectorLenght<<endl;
    return vectorLenght;
};

int main(int argc, const char * argv[]) {
    //vectorLength(16, 19, 9);
    return 0;
}
