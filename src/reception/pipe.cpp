/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** pipe
*/

#include "pipe.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pipes::pipes(/* args */) { }

std::vector<int> pipes::getpipes()
{
    return pipeCommand;
}

void pipes::setpipes(std::vector<int> pipe)
{
    pipeCommand = pipe;
}

std::vector<int> *pipes::newPipe(std::vector<int> *pipeCommand)
{
    int descriptorPipe[2], receivePipe[2], closePipe[2];
    pipe(descriptorPipe);
    pipe(receivePipe);
    pipe(closePipe);
    
    (*pipeCommand).push_back(descriptorPipe[0]);
    (*pipeCommand).push_back(descriptorPipe[1]);
    (*pipeCommand).push_back(receivePipe[0]);
    (*pipeCommand).push_back(receivePipe[1]);
    (*pipeCommand).push_back(closePipe[0]);
    (*pipeCommand).push_back(closePipe[1]);
    return (pipeCommand);
}