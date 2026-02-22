#include <atomic>
#include <cstddef>
#include <optional>
#include <thread>
#include <iostream>
#include <mutex>

std::mutex log_mutex;

template<typename T>
class SPSCRingBuffer {
public:
    explicit SPSCRingBuffer(size_t capacity)
        : capacity_(capacity + 1),  // +1 чтобы отличать full от empty
          buffer_(new T[capacity_]),
          head_(0),
          tail_(0) {}

    ~SPSCRingBuffer() {
        delete[] buffer_;
    }

    bool push(const T& value) {
        size_t head = head_.load(std::memory_order_relaxed);
        size_t next = increment(head);

        if (next == tail_.load(std::memory_order_acquire)) {
            return false; // buffer full
        }

        buffer_[head] = value;
        {
            std::lock_guard<std::mutex> lock(log_mutex);
            std::cout << "PUSH: " << value << '\n';
        }

        head_.store(next, std::memory_order_release);
        return true;
    }

    std::optional<T> pop() {
        size_t tail = tail_.load(std::memory_order_relaxed);

        if (tail == head_.load(std::memory_order_acquire)) {
            return std::nullopt; // buffer empty
        }

        T value = buffer_[tail];
        tail_.store(increment(tail), std::memory_order_release);
        {
            std::lock_guard<std::mutex> lock(log_mutex);
            std::cout << "POP: " << value << '\n';
        }
        return value;
    }

private:
    size_t increment(size_t idx) const {
        return (idx + 1) % capacity_;
    }

    const size_t capacity_;
    T* buffer_;

    std::atomic<size_t> head_; // пишет только producer
    std::atomic<size_t> tail_; // пишет только consumer
};

int main()
{
    SPSCRingBuffer<int> queue(5);

    constexpr int N = 50;

    std::thread producer([&] {
        int value = 0;
        for (int i = 0; i <= N; ) {
            if (queue.push(value)) {
                ++value;
                ++i;
            } else {
                std::this_thread::yield();
            }
        }
    });

    std::thread consumer([&] {
        for (int i = 0; i <= N; ) {
            if (auto v = queue.pop()) {
                ++i;
            } else {
                std::this_thread::yield();
            }
        }
    });

    producer.join();
    consumer.join();
    
    return 0;
}
