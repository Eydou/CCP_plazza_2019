/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** pipe
*/

#ifndef PIPE_HPP_
#define PIPE_HPP_

#include <iostream>
#include <vector>

class pipes
{
private:
protected:
    std::vector<int> pipeCommand;
public:
    pipes();
    ~pipes() = default;
    std::vector<int> getpipes();
    void setpipes(std::vector<int> pipe);
    std::vector<int> *newPipe(std::vector<int>*);
};

#endif /* !PIPE_HPP_ */
