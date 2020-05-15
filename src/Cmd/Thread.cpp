/*
** EPITECH PROJECT, 2019
** Thread.cpp
** File description:
** thread
*/

#include <iostream>
#include "../../include/Thread.hpp"

Thread::Thread()
{
}

Thread::~Thread()
{
    this->thread.join();
}

void Thread::join()
{
    this->thread.join();
}