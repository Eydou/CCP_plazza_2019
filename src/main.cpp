/*
** main.cpp for OOP_nanotekspice_2019 in /home/eydou/2019/OOP/OOP_nanotekspice_2019/src
**
** Made by Edouard.touch
** Login   <edouard.touch@epitech.eu>
**
** Started on  Wed Feb 12 3:36:47 PM 2020 Edouard.touch
** Last update Fri Feb 13 12:59:00 AM 2020 Edouard.touch
*/

#include "errors.hpp"
#include "reception.hpp"

#include <string.h>

static void printHelp(void)
{
    std::cout << "USAGE\n" << "\t./plazza [ct] [nbc] [stock]\n" << "DESCRIPTION" << std::endl;
    std::cout << "\tct     multiplier for the cooking time of the pizzas" << std::endl;
    std::cout << "\tnbc    number of cooks per kitchen" << std::endl;
    std::cout << "\tstock   time in milliseconds, used by the kitchen stock to replace ingredients" << std::endl;
}

int main(int ac, char *av[])
{
    std::vector<int> pipeCommand;

    if (ac == 2 && !strcmp("-h", av[1])) {
        printHelp();
        return 0;
    }
    checkErrors(ac, av);
    myReception(av, &pipeCommand);
}