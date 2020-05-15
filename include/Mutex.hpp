/*
** EPITECH PROJECT, 2019
** Mutex.hpp
** File description:
** mutex
*/

#ifndef MUTEX_HPP_
#define MUTEX_HPP_

#include <mutex>

class IMutex {
    public:
    virtual ~IMutex() = default;
    virtual void lock() = 0;
    virtual void unlock() = 0;
};

class Mutex : public IMutex {
    public:
    ~Mutex();
    void lock();
    void unlock();

    protected:
    std::mutex mutex;
};

#endif //MUTEX_HPP_