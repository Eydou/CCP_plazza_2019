/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** reception
*/

#include "reception.hpp"
#include "pipe.hpp"

#include <future>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <thread>
#include <regex>

void reception::printAddition()
{
    if (this->totalAddition.size() != 0) {
        std::cout << "\033[1;36m╭———————— \033[0m" << "Addition" << "\033[1;36m ————————╮\033[0m";
        for (size_t i = 0; i != this->totalAddition.size(); i++)
            std::cout << "\n\t" << this->totalAddition[i] + "\n\033[0;36m   ——————————"
            << i+1 << "——————————   \033[0m" << std::endl;
        std::cout << "\033[1;36m╰—————————\033[0m" << " Total  " << "\033[1;36m—————————╯\033[0m" << std::endl;
    }
}

void printMenu()
{
    std::cout << "\033[1;36m╭———————— \033[0m" << " Menu " << "\033[1;36m ————————╮\033[0m";
    std::cout << "\n\t  regina\n\t margarita\n\t americana\n\t fantasia" << std::endl;
     std::cout << "\033[1;36m╰———————— \033[0m" << " Menu " << "\033[1;36m ————————╯\033[0m" << std::endl;
}

void checkCloseKitchen(std::vector<int> *pipeCommand)
{
    char checkOk[256];
    int len;

    while (1) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    if ((*pipeCommand).size() > 1)
    for (size_t i = 0; i < (*pipeCommand).size(); i = i + 6) {
        len = read((*pipeCommand)[i+4], checkOk, 256);
        checkOk[len] = '\0';
        if (!strcmp(checkOk, "close")) {
             for (int v = 0; v != 6; v++)
                (*pipeCommand).erase((*pipeCommand).begin() + i);
            }
        }
    }
}

void reception::parseLine(std::string command)
{
    command.erase(std::remove(command.begin(), command.end(), ';'), command.end());
    std::istringstream iss(command);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
    std::istream_iterator<std::string>());
    std::vector<std::string> parse;
    std::string fusion;

    for (size_t i = 0; i != results.size(); i++) {
        if (!((i+1) % 3)) {
            std::string fusion = results[i-2] + " " + results[i-1] + " " + results[i];
            this->totalAddition.push_back(fusion);
            results[i].erase(std::remove(results[i].begin(), results[i].end(), 'x'), results[i].end());
        }
        if ((i+1) % 3 == 0) {
            parse.push_back(results[i-2]);
            parse.push_back(results[i-1]);
            parse.push_back(results[i]);
        }
    }
    for (size_t i = 0; i != parse.size(); i++)
        if (!((i+1) % 3)) {
            for (int j = 0; j != std::stoi(parse[i]); j++) {
                fusion = parse[i-2] + " " + parse[i-1];
                this->parseCommand.push_back(fusion);
            }
        }
}

void myReception(char *av[], std::vector<int> *pipeCommand)
{
    reception st;
    pipes pip;

    std::cout << "Welcome to Plazza !" << std::endl;
    std::thread checkKitchen(checkCloseKitchen, pipeCommand);
    for (;;) {
        std::string command;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        std::cout << "\033[1;34m->\033[0m ";
        std::getline(std::cin, command);
        if (std::cin.eof()) break;
        std::for_each(command.begin(), command.end(), [](char & c) { c = ::tolower(c); });
        if (!command.compare("stop")) {
            st.printAddition();
            exit(0);
        } else if (!command.compare("menu"))
            printMenu();
        else if (!command.compare("status")) {
            st.manageKitchen(av, 1, pipeCommand);
        } else if (st.checkParsing(command) != 0)
            std::cout << "error command" << std::endl;
        else {
            st.parseLine(command);
            st.manageKitchen(av, 0, pipeCommand);
        }
    }
    checkKitchen.join();
}

reception::reception(/* args */) : Cooks(0) { }