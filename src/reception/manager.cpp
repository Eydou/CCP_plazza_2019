/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** manager
*/

#include "reception.hpp"
#include <unistd.h>
#include <stdio.h>
#include <regex>
#include <string.h>
#include <thread>

#include "kitchen.hpp"
#include "pipe.hpp"
#include "pizza.hpp"

std::vector<std::string> stringtoVec(char *line)
{
    std::string command(line);

    std::istringstream iss(command);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
    std::istream_iterator<std::string>());

    return results;
}

void reception::stringtoVec(char *line)
{
    std::string command(line);

    std::istringstream iss(command);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
    std::istream_iterator<std::string>());

    this->parseCommand.clear();
    this->parseCommand = results;
}

std::vector<std::string> reception::convertoWrite()
{
    std::vector<int> fillerType;
    std::vector<int> fillerSize;
    std::vector<std::string> parsePizza;
    std::string fusion;

    for (size_t i = 0; i != parseCommand.size(); i++) {
        std::istringstream iss(parseCommand[i]);
        std::vector<std::string> results(std::istream_iterator<std::string>{iss},
        std::istream_iterator<std::string>());
        if (!results[0].compare("regina"))
            fillerType.push_back(Regina);
        if (!results[0].compare("margarita"))
            fillerType.push_back(Margarita);
        if (!results[0].compare("americana"))
            fillerType.push_back(Americana);
        if (!results[0].compare("fantasia"))
            fillerType.push_back(Fantasia);

        if (!results[1].compare("s"))
            fillerSize.push_back(S);
        if (!results[1].compare("m"))
            fillerSize.push_back(M);
        if (!results[1].compare("l"))
            fillerSize.push_back(L);
        if (!results[1].compare("xl"))
            fillerSize.push_back(XL);
        if (!results[1].compare("xxl"))
            fillerSize.push_back(XXL);
    }
    for (size_t i = 0; i != fillerSize.size(); i++) {
        fusion = std::to_string(fillerType[i]) + " " + std::to_string(fillerSize[i]);
        parsePizza.push_back(fusion);
    }
    this->parseCommand.clear();
    return parsePizza;
}

void reception::addKitchen(char *av[], std::vector<int> *pipeCommand)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
        exit(84);
    else if (!pid) {
        kitchen_init(atoi(av[1]), atoi(av[2]), atoi(av[3]), pipeCommand);
    }
}

void reception::manageKitchen(char *av[], int status, std::vector<int> *pipeCommand)
{
    float needKitchen = 0.;
    pipes pip;
    char checkOk[3];
    int len;
    std::vector<std::string> copyCommand;

    if (status == 1) {
        for (size_t i = 0; i != (*pipeCommand).size(); i = i + 6) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
            write((*pipeCommand)[i+1], "status\0", 7);
        }
        return;
    }
    copyCommand = parseCommand;
    parseCommand = convertoWrite();
    needKitchen = (float)(parseCommand.size()) / 2 / atof(av[2]);

    //this->Cooks = -((*pipeCommand).size() / 6);
    std::cout << (this->Cooks + needKitchen) << std::endl;
    for (; (this->Cooks + needKitchen) > 0; needKitchen--) {
        pip.newPipe(pipeCommand);
        addKitchen(av, pipeCommand);
    }

   for (;copyCommand.size() != 0;) {
        for (size_t i = 0; i < (*pipeCommand).size(); i = i + 6) {
            write((*pipeCommand)[i+1], parseCommand[0].c_str(), parseCommand[0].size());
            len = read((*pipeCommand)[i+2], checkOk, 3);
            checkOk[len] = '\0';
            if (!strcmp(checkOk, "ok")) {
                copyCommand.erase(copyCommand.begin());
            }
            if (!copyCommand.size())
                break;
        }
   }
}