#include <iostream>
using namespace std;

void reverse(char* &str)
{
    char* tmp = new char[strlen(str)];
    for(int i = 0; i<strlen(str);++i)
    {
        tmp[i] = str[strlen(str) - i - 1];
    }
    str = tmp;
}

int main(int argc, const char * argv[]) {
    char* str = "Hello World";
    reverse(str);
    cout<<str<<endl;
    return 0;
}
