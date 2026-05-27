#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T, std::size_t MaxElements>
class FixedAllocator
{
public:
    using value_type = T;

    FixedAllocator() = default;

    template<typename U>
    FixedAllocator(const FixedAllocator<U, MaxElements>&)
    {
    }

    T* allocate(std::size_t count)
    {
        if (count > MaxElements)
        {
            throw std::bad_alloc();
        }

        std::cout << "[ALLOCATE] "
                  << count
                  << " elements\n";

        return static_cast<T*>(
            ::operator new(count * sizeof(T))
        );
    }

    void deallocate(T* pointer, std::size_t)
    {
        std::cout << "[DEALLOCATE]\n";

        ::operator delete(pointer);
    }
};

int main()
{
    std::vector<int, FixedAllocator<int, 50>> vector;

    vector.reserve(50);

    try
    {
        for (int i = 0; i < 60; ++i)
        {
            vector.push_back(i);

            std::cout << "Push: "
                      << i
                      << '\n';
        }
    }
    catch (const std::bad_alloc&)
    {
        std::cout << "Max capacity reached!\n";
    }
}