#include <iostream>
#include <valarray>

int main()
{
    std::valarray<int> a{1,2,7,4,5,6,7,8,9};
    a[a>5] = 0;
    for ( auto elem: a)
        std::cout << elem << " ";
    return 0;
}

// result = 1 2 0 4 5 0 0 0 0 Program ended with exit code: 0
