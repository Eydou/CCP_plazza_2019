/*
** errors.cpp for Untitled (Workspace) in /home/xelium/2019/cpp/cpp_nanotekspice
**
** Made by alexis lopes
** Login   <alexis.lopes@epitech.eu>
**
** Started on  Sat Feb 1 14:22:39 2020 alexis lopes
** Last update Fri Feb 13 12:45:43 AM 2020 Edouard.touch
*/

#include "errors.hpp"
#include "reception.hpp"
#include <ctype.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include <regex>

void checkErrors(int ac, char *av[])
{
    if (ac != 4)
        throw Error(1, "error arguments", 2);
    for (size_t i = 1; i != 4; i++) {
        for (size_t j = 0; j < strlen(av[i]); j++)
            if (!isdigit(av[i][j]))
                throw Error(1, "error numbers", 2);
    }
    if (!strcmp(av[2], "0"))
        throw Error(1, "no cooker = go to rsa", 2);
}

int reception::checkParsing(std::string command)
{
    std::string pizza[9] = {"regina", "margarita", "americana", "fantasia",
                    "s", "m", "l", "xl", "xxl"};
    
    bool check1, check2 = false;
    command.erase(std::remove(command.begin(), command.end(), ';'), command.end());
    std::istringstream iss(command);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
    std::istream_iterator<std::string>());

    if (results.size() % 3 != 0)
        return 1;
    
    for (size_t i = 0; i != results.size(); i++) {
        if (!((i+1) % 3)) {
            for (size_t nb = 0; nb != 9; nb++) {
                if (results[i-2] == pizza[nb] && check1 == false && nb < 4)
                    check1 = true;
                else if (nb == 3 && check1 == false)
                    return 1;
                else if (results[i-1] == pizza[nb] && check2 == false && nb >= 4 && nb < 9)
                    check2 = true;
                else if (nb == 8 && check2 == false) {
                    return 1;
                }
                if (results[i].size() >= 2 && nb == 8)
                    if (results[i][0] == 'x') {
                        for (size_t j = 1; j != results[i].size(); j++)
                            if (results[i][j] < '0' && results[i][j] > '9')
                                return 1;
                        return 0;
                    }
            }
        }
    }
    return 1;
}