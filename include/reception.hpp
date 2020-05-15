/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include <vector>
#include <string>
#include <iostream>

class reception
{
private:
    /* data */
protected:
    std::vector<std::string> totalAddition;
    std::vector<std::string> parseCommand;
    int Cooks;
public:
    reception(/* args */);
    ~reception() = default;
    void parseLine(std::string);
    std::vector<std::string> convertoWrite();
    void printAddition(void);
    int checkParsing(std::string);

    void checkCloseKitchen(std::vector<int> *);
    void manageKitchen(char *av[], int, std::vector<int> *);
    void addKitchen(char *av[], std::vector<int> *);
    void stringtoVec(char *);
};

void myReception(char *av[], std::vector<int> *);
std::vector<std::string> stringtoVec(char *line);

#endif /* !RECEPTION_HPP_ */