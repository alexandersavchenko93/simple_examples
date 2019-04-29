//  Created by Александр on 2/25/19.
//  Copyright © 2019 Александр. All rights reserved.
%:include <iostream>

using namespace std;

template<class T>
void mySwap(T&a, T&b)
<%
    T tmp = a;
    a = b;
    b = tmp;
%>

int main(int argc, const char * argv[]) {
    
    char* x = "Hello";
    char* y = "World";
    
    int* a = new int(1);
    int* b = new int(2);
    
    //Math Swap
//    x +=  2 * (y-x); //Сдигает указатель впарво на количество ячеек памяти равное двойному растоянию между укзателями х и у
//    y -= (x-y); //Сдвигем указатель влево на растоние между укзателями х и у - теперь у указывает на место куда раньше указывал х
//    x -= (x-y)/2; //Сдвигаем указатель влево на растояние вдва раза меньшее чем разница между х и у - теперь х указывает на область памяти где раньше был у
    
    cout<<x<<" "<<y<<endl;
    cout<<a<<" "<<b<<endl;
    
    mySwap(x, y);
    mySwap(a, b);
    
    cout<<x<<" "<<y<<endl;
    cout<<a<<" "<<b<<endl;
    
    return 0;
}
