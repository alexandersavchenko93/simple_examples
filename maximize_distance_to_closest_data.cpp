// Есть вектор данных из 0 и 1.
// Нужно найти место с самым плохим распределением, и вывести индекс для вставки 1 равноудаленно от других значений.
// Например [1,0,0,0,0,0,0,0,1,0,1] - результат 4. после вставки получится вектор [1,0,0,0,1,0,0,0,1,0,1].

#include <iostream>
#include <vector>

int main()
{
    std::vector<int> data = {1,0,0,0,0,0,0,0,1,0,1};
    int counter = 1;
    
    int max_s_length = 0;
    int s_length = 0;
    int begin_s = 0;
    int end_s = 0;
    
    int result = 0;
    
    for(int i = 0;i<data.size();++i)
    {
        //Is sequence end
        if(data[i] != data[i+1])
        {
            end_s = i;
            begin_s = end_s - counter+1;
            s_length = end_s-begin_s+1;
            //Update res
            if(max_s_length<s_length)
            {
                max_s_length = s_length;
                result = (end_s + begin_s)/2;
            }
            counter = 0;
        }else
        {
            counter++;
        }
    }
    std::cout << result << "\n";
}
