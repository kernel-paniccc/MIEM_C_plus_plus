#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

using namespace std;

class TaskQueue {
public:
    void push(int task) {
        {
            lock_guard<mutex> lock(queue_mutex);
            tasks.push(task);
        }
        condition.notify_one();
    }

    bool pop(int& task) {
        unique_lock<mutex> lock(queue_mutex);
        condition.wait(lock, [this]() {
            return closed || !tasks.empty();
        });

        if (tasks.empty()) {
            return false;
        }

        task = tasks.front();
        tasks.pop();
        return true;
    }

    void close() {
        {
            lock_guard<mutex> lock(queue_mutex);
            closed = true;
        }
        condition.notify_all();
    }

private:
    queue<int> tasks;
    mutex queue_mutex;
    condition_variable condition;
    bool closed = false;
};

void worker(TaskQueue& queue, size_t worker_id, mutex& output_mutex) {
    int task = 0;
    while (queue.pop(task)) {
        this_thread::sleep_for(chrono::seconds(1));
        lock_guard<mutex> lock(output_mutex);
        cout << "[Worker-" << worker_id << "] обработал задачу " << task << '\n';
    }
}

int main() {
    constexpr size_t kWorkerCount = 4;
    constexpr int kFirstTask = 1;
    constexpr int kLastTask = 20;

    TaskQueue queue;
    mutex output_mutex;
    vector<thread> workers;
    workers.reserve(kWorkerCount);

    for (int task = kFirstTask; task <= kLastTask; ++task) {
        queue.push(task);
    }

    for (size_t i = 0; i < kWorkerCount; ++i) {
        workers.emplace_back(worker, ref(queue), i + 1, ref(output_mutex));
    }

    queue.close();

    for (thread& thread : workers) {
        thread.join();
    }

    return 0;
}
