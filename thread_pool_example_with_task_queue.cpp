#include <iostream>
#include <thread>
#include <queue>
#include <string>
#include <mutex>
#include <vector>

// Глобальный для cout так как longCalc находится вне main()
std::mutex cout_mtx;

void longCalc(const std::string& str)
{
    {
        std::lock_guard<std::mutex> lock(cout_mtx);
        std::cout << "LongCalc: " << str
                  << " in thread " << std::this_thread::get_id() << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // имитация долгой работы
}

int main() {
    std::mutex mtx;
    std::queue<std::string> q_data;

    q_data.push("1");
    q_data.push("2");
    q_data.push("3");
    q_data.push("4");

    const int num_threads = 4;
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&]() {
            while (true) {
                std::string str;

                {
                    std::lock_guard<std::mutex> lock(mtx);
                    if (q_data.empty()) {
                        break;
                    }

                    str = std::move(q_data.front());
                    q_data.pop();
                }

                longCalc(str);
            }
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "All done.\n";
    return 0;
}

