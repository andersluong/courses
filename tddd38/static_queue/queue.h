#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include <iostream>

class queue_error : std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

template <typename T, int N>
class Queue {
public:
    static_assert(N > 0, "size should be bigger than 0");

    void enqueue(T value) {
        if (full()) {
            throw queue_error("already full");
        }
        data[tail % N] = value;
        tail++;
    }

    T dequeue() {
        if (empty()) {
            throw queue_error("can't dequeue an empty queue");
        }
        T elem = data[head % N];
        head++;
        return elem;
    }

    void clear() {
        head = 0;
        tail = 0;
    }

    bool empty() const {
        return head == tail;
    }

    bool full() const {
        return (tail - head) >= N;
    }

    T& front() {
        if (empty()) {
            throw queue_error("Cannot access the front of an empty queue");
        }
        return data[head % N];
    }    

    T const& front() const {
        if (empty()) {
            throw queue_error("Cannot access the front of an empty queue");
        }
        return data[head % N];
    }

    template <int M>
    Queue<T, N+M> copy_and_expand() const {
        Queue<T, N+M> newQueue{};
        for (unsigned i = head; i < tail; i++) {
            newQueue.enqueue(data[i % N]);
            //std::cout << "data: " << data[i % N] << std::endl;
        }
        return newQueue;
    }
private:
    T data[N]{};
    int head = 0;
    int tail = 0;
};

#endif