#include <iostream>
using namespace std;

void reverse(char* str)
{
    char tmp[strlen(str)];
    for(int i = 0; i<strlen(str);++i)
    {
        tmp[i] = str[strlen(str) - i - 1];
    }
    str = tmp;
    cout<<tmp<<endl;
}

int main(int argc, const char * argv[]) {
    //reverse("123");
    return 0;
}
