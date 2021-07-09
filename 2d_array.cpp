//  Copyright © 2021 Александр. All rights reserved.
#include <iostream>
using namespace std;

int main(int argc, const char* argv[]) {

    // 3 массива по 5 элеменов
    const unsigned int DIM1 = 3;
    const unsigned int DIM2 = 5;

    int ary[DIM1][DIM2] = {
    { 1, 2, 3, 4, 5 },
    { 2, 4, 6, 8, 10 }, //ary[1][3]
    { 3, 6, 9, 12, 15 }
    };

    int elemet = ary[1][3]; // 8

    return 0;
}
