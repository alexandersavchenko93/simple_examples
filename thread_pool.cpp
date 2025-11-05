#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

std::mutex mtx;

class MyGuard
{
public:
    MyGuard()
    {
        mtx.lock();
    }

    ~MyGuard()
    {
        mtx.unlock();
    }
};

/*
uint64_t AddOne(uint64_t& number)
{
    mtx.lock();
    number++;
    uint64_t tmp = number;
    std::cout << tmp << std::endl;
    mtx.unlock();
    return tmp;
}
*/

uint64_t AddOne(uint64_t& number)
{
    MyGuard g;
    number++;
    std::cout << number << std::endl;
    return number;
}

int main()
{
    uint64_t number = 0;
    std::vector<std::thread> threads;

    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) {
        num_threads = 2;
    }

    for (int i = 0; i < num_threads; i++)
    {
        std::thread t(AddOne, std::ref(number));
        threads.push_back(std::move(t));
    }

    for (std::thread& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}
