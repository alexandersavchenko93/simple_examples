#include <iostream>

using namespace std;

class A
{
public:
    A():i(11), s("Alex"){}
private:
    int i;
    string s;
public:
    void printA()
    {
        cout<<i<<endl;
        cout<<s<<endl;
    }
};

struct Hack
{
    int iHack;
    string sHack;
};


int main(int argc, const char * argv[]) {
    A a;
    Hack h;
    
    // First method
    ((Hack*)&a)->iHack = 12;
    ((Hack*)&a)->sHack = "Bob";
    
    a.printA();
    
    // Second method
    reinterpret_cast<Hack*>(&a)->iHack = 777;
    reinterpret_cast<Hack*>(&a)->sHack = "Max";
    
    a.printA();
    return 0;
}
