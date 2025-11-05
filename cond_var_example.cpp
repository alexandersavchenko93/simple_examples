#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx; // Mutex to protect shared data
std::condition_variable cv; // Condition variable
bool data_ready = false; // Shared data indicating if data is ready

void producer_thread() {
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::unique_lock<std::mutex> lock(mtx); // Acquire lock
    data_ready = true; // Modify shared data
    std::cout << "Producer: Data is ready." << std::endl;
    cv.notify_one(); // Notify one waiting thread
}

void consumer_thread() {
    std::unique_lock<std::mutex> lock(mtx); // Acquire lock
    std::cout << "Consumer: Waiting for data..." << std::endl;
    cv.wait(lock, [] { return data_ready; }); // Wait until data_ready is true

    std::cout << "Consumer: Data received and processed." << std::endl;
}

int main() {
    std::thread producer(producer_thread);
    std::thread consumer(consumer_thread);

    producer.join();
    consumer.join();

    return 0;
}

/* std::condition_variable вимагає саме std::unique_lock, а не простіший std::lock_guard.
Це пов'язано з тим, що unique_lock надає велику гнучкість та явні методи для управління станом блокування (lock.unlock(), lock.lock(), lock.release()),
що необхідно внутрішньому механізму wait() для звільнення та повторного захоплення мьютексу в потрібні моменти.
lock_guard управляється лише областю видимості і не має такої гнучкості. */
