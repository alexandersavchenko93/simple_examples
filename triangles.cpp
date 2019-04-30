#include<iostream>

using namespace std;

//Равнобедеренные триугольники
void drawTriangle()
{
    cout<<"Enter number of triangles: ";
    int number;
    cin>>number;
    for(int y=1;y<=number;++y)//высота треугольника расходящаяся к низу
    {
        for(int i=1;i<=number;++i)//кол-во треугольников
        {
            for(int x=1;x<=number-y;++x)//пробелы слева
            {
                cout<<" ";
            }
            
            if(y==1)
            {
                cout<<"*";
            }
            else
            {
                for(int x=(-1)*y;x<y-1;++x)//выводим треугольник
                {
                    cout<<"*";
                }
            }
            
            for(int x=1;x<=number-y;++x)//пробелы справа
            {
                cout<<" ";
            }
            cout<<" ";//пробел между треугольниками
        }
        
        cout<<endl;
    }
}

int main(int argc, const char * argv[]) {
    //drawTriangle();
    return 0;
}
