//  STD::VECTOR
//  Created by Александр on 4/21/19.
//  Copyright © 2019 Александр. All rights reserved.

#include <iostream>
using namespace std;

template <typename T>
class Vector{
public:
    size_t mSize = 0;
    size_t mCapacity = 2;
    T* mVector = new T[mCapacity];
public:
    void push_back(const T& value);
};

template<typename T>
void Vector<T>::push_back(const T& value)
{
    if (mSize == mCapacity)
    {
        size_t capacity = mCapacity * 2;
        // Выделить новый массив tmp размером mCapacity*2
        T* result = new T[capacity];
        
        // Перенести в него всю информацию из старого массива
        for (decltype(mSize) i = 0; i < mSize; ++i)
            result[i] = mVector[i];
        
        // Удалить старый и присвоить новый ( delete[] mVector; mVector = tmp)
        delete[] mVector;
        mVector = result;
        // Не забыть обновить mCapacity = mCapacity*2
        mCapacity = capacity;
    }
    
    mVector[mSize++] = value;
}

int main(int argc, const char * argv[]) {
    Vector<int> myVec;
    myVec.push_back(3);
    myVec.push_back(5);
    myVec.push_back(9);

    int result = myVec.mVector[2];
    std::cout<<result<<std::endl;
      
    return 0;
}
