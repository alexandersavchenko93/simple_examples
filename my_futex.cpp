#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

#include <atomic>

class SpinLock {
public:
    SpinLock() = default;
    SpinLock(const SpinLock&) = delete;
    SpinLock& operator=(const SpinLock&) = delete;

    void lock() {
        while (flag_.test_and_set(std::memory_order_acquire)) {
            flag_.wait(true, std::memory_order_relaxed);
        }
    }

    void unlock() {
        flag_.clear(std::memory_order_release);
        flag_.notify_one();
    }

private:
    std::atomic_flag flag_{};
};

SpinLock spin;
int counter = 0;

void worker(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        spin.lock();
        ++counter;
        spin.unlock();
    }
}

int main() {
    const int threads_count = 4;
    const int iterations = 100000;

    std::vector<std::thread> threads;

    for (int i = 0; i < threads_count; ++i) {
        threads.emplace_back(worker, iterations);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final counter: " << counter << std::endl;
    return 0;
}
