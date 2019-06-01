//  Binariy_Search
//  Created by Александр on 6/1/19.
//  Copyright © 2019 Александр. All rights reserved.

#include <iostream>

int searchBinary(int arr[],int left,int right, int key)
{
    int mid  = 0;
    while (1)
    {
        mid  = (left + right)/2;
        if(key<arr[mid])
        {
            right = mid - 1; //Смыкаем правую границу
        }
        else if(key>arr[mid])
        {
            left = mid + 1; //Смыкаем левую границу
        }else
        {
            return mid;
        }
        
        if(left>right) //Границы сомкнулись
        return -1;
    }
}


int main(int argc, const char * argv[]) {
    
    int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12}; //Масив должен быть отсортирован
    int index = searchBinary(arr, 0, 11, 4);
    
    std::cout << "Find number in array on index: "<<index<<std::endl;
    
    return 0;
}
