/*
** EPITECH PROJECT, 2019
** Mutex.cpp
** File description:
** Mutex
*/
#include "../../include/Mutex.hpp"

Mutex::~Mutex()
{
}

void Mutex::lock()
{
    this->mutex.lock();
}

void Mutex::unlock()
{
    this->mutex.unlock();
}