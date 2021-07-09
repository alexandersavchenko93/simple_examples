//  Created by Александр on 2/25/19.
//  Copyright © 2019 Александр. All rights reserved.
#include <iostream>

using namespace std;


int main(int argc, const char* argv[]) {

    int* mutable_pointer_to_mutable_int = new int(1);
    int const* mutable_pointer_to_constant_int = new int(1);
    int* const constant_pointer_to_mutable_int = new int(1);
    int const* const constant_pointer_to_constant_int = new int(1);

    return 0;
}
