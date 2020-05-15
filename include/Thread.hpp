/*
** EPITECH PROJECT, 2019
** Thread.hpp
** File description:
** thread
*/
#include <thread>

class Thread {
    public:
    Thread();
    ~Thread();
    void join();


    private:
    std::thread thread;
};
