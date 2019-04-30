#include <cstdlib>
#include <iostream>
#include <list>

using namespace std;

int main(int argc, char** argv) {
    list<int> lst{1,5,3,23};
    for(auto it = lst.begin(); it != lst.end();++it)
    {
        cout<<*it<<endl;
        lst.erase(it--); //Удаляем нулевой елемент и сдвигаем следующий на это место для корректной работы программы
    }
    
    lst.push_front(10);
    cout<<lst.front()<<endl;
    
    return 0;
}
