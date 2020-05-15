/*
** main.cpp
**
** Made by Edouard.touch
** Login   <edouard.touch@epitech.eu>
**
** Started on  Wed Feb 12 3:36:47 PM 2020 Edouard.touch
** Last update Fri Feb 13 12:59:00 AM 2020 Edouard.touch
*/
#include <iostream>
#include <string>
#include <regex>
#include "../../include/reception.hpp"
#include "../../include/kitchen.hpp"
#include "../../include/Mutex.hpp"
#include "../../include/Thread.hpp"
#include <regex>
#include <string.h>

kitchen::kitchen(int time_cooking, int nbcook, int time_respawn_alim)
{
	this->doe = 5;
	this->tomato = 5;
	this->gruyere = 5;
	this->ham = 5;
	this->mushrooms = 5;
	this->steak = 5;
	this->eggplant = 5;
	this->goatcheese = 5;
	this->nb_cook = nbcook;
    this->time_cook = time_cooking;
    this->new_alim = time_respawn_alim;
    this->cook_ready = nbcook;
    this->place = nbcook * 2;
    this->nb_command = 0;
    this->pizza_waiting = {};
    this->pizza_wait_size = {};
    this->kitchen_status = 0;
    this->start = 0;
}

kitchen::~kitchen()
{
}

int kitchen::getDoe() const
{
	return (this->doe);
}

int kitchen::getTomato() const
{
	return (this->tomato);
}

int kitchen::getMushrooms() const
{
	return (this->mushrooms);
}

int kitchen::getSteak() const
{
	return (this->steak);
}

int kitchen::getEggplant() const
{
	return (this->eggplant);
}

int kitchen::getGruyere() const
{
	return (this->gruyere);
}

int kitchen::getHam() const
{
	return (this->ham);
}

int kitchen::getGoatCheese() const
{
	return (this->goatcheese);
}

void add_alim(kitchen *kitchen)
{
    Mutex *mutex = new Mutex();
    std::chrono::milliseconds interval(kitchen->new_alim);
    while (1) {
    mutex->lock();
    std::this_thread::sleep_for(interval);
    kitchen->doe++;
    kitchen->tomato++;
    kitchen->gruyere++;
    kitchen->ham++;
    kitchen->mushrooms++;
    kitchen->steak++;
    kitchen->eggplant++;
    kitchen->goatcheese++;
    mutex->unlock();
    } 
}

void kitchen::pizza_regina()
{
    Mutex *mutex = new Mutex();

    mutex->lock();
    this->cook_ready--;
    this->doe--;
    this->tomato--;
    this->gruyere--; 
    this->ham--;
    this->mushrooms--;
    this->pizza_waiting.erase(this->pizza_waiting.begin());
    this->pizza_wait_size.erase(this->pizza_wait_size.begin());
    this->nb_command--;
    std::chrono::seconds interval(2*this->time_cook);
    std::this_thread::sleep_for(interval);
    this->cook_ready++;
    this->place++;
    mutex->unlock();
}

void kitchen::pizza_margarita()
{
    Mutex *mutex = new Mutex();

    mutex->lock();
    this->cook_ready--;
	this->doe--;
	this->tomato--;
	this->gruyere--;
    this->pizza_waiting.erase(this->pizza_waiting.begin());
    this->pizza_wait_size.erase(this->pizza_wait_size.begin());
    this->nb_command--;
    std::chrono::seconds interval(2*this->time_cook);
    std::this_thread::sleep_for(interval);
    this->cook_ready++;
    this->place++;
	mutex->unlock();

}

void kitchen::pizza_american()
{
    Mutex *mutex = new Mutex();

    mutex->lock();
    this->cook_ready--;
	this->doe--;
	this->tomato--;
	this->gruyere--;
	this->steak--;
	this->pizza_waiting.erase(this->pizza_waiting.begin());
    this->pizza_wait_size.erase(this->pizza_wait_size.begin());
    this->nb_command--;
    std::chrono::seconds interval(2*this->time_cook);
    std::this_thread::sleep_for(interval);
    this->cook_ready++;
    this->place++;
    mutex->unlock();
}

void kitchen::pizza_fantasia()
{
    Mutex *mutex = new Mutex();

    mutex->lock();
    this->cook_ready--;
	this->doe--;
	this->tomato--;
	this->eggplant--;
	this->goatcheese--;
    this->pizza_waiting.erase(this->pizza_waiting.begin());
    this->pizza_wait_size.erase(this->pizza_wait_size.begin());
    this->nb_command--;
    std::chrono::seconds interval(2*this->time_cook);
    std::this_thread::sleep_for(interval);
    this->cook_ready++;
    this->place++;  
	mutex->unlock();
}

void launch_regina(kitchen *kitchen)
{
    kitchen->pizza_regina();
}

void launch_margarita(kitchen *kitchen)
{
    kitchen->pizza_margarita();
}

void launch_american(kitchen *kitchen)
{
    kitchen->pizza_american();
}

void launch_fantasia(kitchen *kitchen)
{
    kitchen->pizza_fantasia();
}


void cook_working(kitchen *kitchen)
{
    std::vector<std::thread> tab;
    while (kitchen->kitchen_status != 1) {
    if (kitchen->nb_command > 0) {
    if (kitchen->cook_ready > 0  && kitchen->pizza_waiting[0].compare("regina") == 0 && kitchen->getDoe() >= 1 && kitchen->getTomato() >= 1 && kitchen->getGruyere() >= 1 && kitchen->getHam() >= 1 && kitchen->getMushrooms() >= 1) {
                tab.push_back(std::thread(launch_regina, kitchen));
            }
    else if (kitchen->cook_ready > 0  && kitchen->pizza_waiting[0].compare("americana") == 0 && kitchen->getDoe() >= 1 && kitchen->getTomato() >= 1 && kitchen->getGruyere() >= 1 && kitchen->getSteak() >= 1) {
                tab.push_back(std::thread(launch_american, kitchen));
            }
    else if (kitchen->cook_ready > 0  && kitchen->pizza_waiting[0].compare("margarita") == 0 && kitchen->getDoe() >= 1 && kitchen->getTomato() >= 1 && kitchen->getGruyere() >= 1 && kitchen->getHam() >= 1) {
                tab.push_back(std::thread(launch_margarita, kitchen));
            }
    else if (kitchen->cook_ready > 0  && kitchen->pizza_waiting[0].compare("fantasia") == 0 && kitchen->getDoe() >= 1 && kitchen->getTomato() >= 1 && kitchen->getEggplant() >= 1 && kitchen->getGoatCheese() >= 1) {
                tab.push_back(std::thread(launch_fantasia, kitchen));
            }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    for (size_t i = 0; i < tab.size(); i++)
        tab[i].join();
}

void check_activity(kitchen *kitchen, std::vector<int> *pipeCommand, int id)
{
    int count;
    const char *commandWrite;
    Mutex *mutex = new Mutex();
    std::chrono::milliseconds interval(kitchen->new_alim);

    while (1) {
        count = 0;
    while (kitchen->nb_command == 0 && kitchen->cook_ready == 5) {
        mutex->lock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        count++;
        if (count == 5) {
            kitchen->kitchen_status = 1;
            commandWrite = "close";
            write((*pipeCommand)[id+5], commandWrite, strlen(commandWrite));
            exit(0);
        }
        mutex->unlock();
        }
    }
}

void print_status(kitchen *kitchen, int id)
{
    std::cout << "\n\033[1;36m╭———————— \033[0m" << "Kitchen id:" << id/6 << " Status\033[1;36m ————————╮\033[0m\n";
    std::cout << "  Ingredients stock:\n\ttomato : " << kitchen->tomato << "\n";
    std::cout << "\tdoe : " << kitchen->doe << "\n";
    std::cout << "\t gruyere : " << kitchen->gruyere << "\n";
    std::cout << "\tham : " << kitchen->ham << "\n";
    std::cout << "\tmushrooms : " << kitchen->mushrooms << "\n";
    std::cout << "\tsteak : " << kitchen->steak << "\n";
    std::cout << "\teggplant : " << kitchen->eggplant << "\n";
    std::cout << "\tgoatcheese : " << kitchen->goatcheese << "\n";
    std::cout << "  Cook ready to cook: " << kitchen->cook_ready << "\n";
    std::cout << "  Cooks Actually workings: " << (kitchen->nb_cook - kitchen->cook_ready) << "\n";
    std::cout << "  Pizzas waitings to be cooks:\n";
    for (size_t i = 0; i < kitchen->pizza_waiting.size(); i++)
        std::cout << "\t" + kitchen->pizza_waiting[i] << " " << kitchen->pizza_wait_size[i] << std::endl;
    std::cout << "\033[1;36m╰—————————\033[0m" << "Kitchen Status" << "\033[1;36m—————————╯\033[0m" << std::endl;
    std::cout <<"\n\n";

}

const char *vectoString(std::vector<std::string> command)
{
    std::string fusion;

    for (size_t j = 0; j != command.size(); j++) {
            if (j == command.size()-1)
                fusion += command[j] + '\0';
            else
                fusion += (command[j] + " ");
    }
    return fusion.c_str();
}

std::string nbs_to_string(const char *line, int type_or_size)
{
    char *nb;
    char *lines = strdup(line);

    nb = strtok(lines, " ");
    if (type_or_size == 1) {
        if(!strcmp(nb, "1"))
            return ("regina");
        if(!strcmp(nb, "2"))
            return ("margarita");
        if(!strcmp(nb, "4"))
            return ("americana");
        if(!strcmp(nb, "8"))
            return ("fantasia");
    } else if (type_or_size == 2) {
        nb = strtok(NULL, " ");
        if(!strcmp(nb, "1"))
            return ("s");
        if(!strcmp(nb, "2"))
            return ("m");
        if(!strcmp(nb, "4"))
            return ("l");
        if(!strcmp(nb, "8"))
            return ("xl");
        if(!strcmp(nb, "16"))
            return ("xxl");
    }
    return (NULL);
}

std::vector<std::string> stringtoVector(std::string line)
{
    std::string command(line);

    std::istringstream iss(command);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
    std::istream_iterator<std::string>());

    return results;
}

void kitchen_init(int time_cooking, int nb_cook, int time_respawn_alim, std::vector<int> *pipeCommand)
{
    kitchen *Kitchen = new kitchen(time_cooking, nb_cook, time_respawn_alim);
    std::thread add_ingredients = std::thread(add_alim, Kitchen);
    int id = (*pipeCommand).size() - 6;
    std::thread timer = std::thread(check_activity, Kitchen, pipeCommand, id);
    std::thread cooker = std::thread(cook_working, Kitchen);
    char command[256];
    const char *commandWrite;
    int len = 0;
    std::string fusion;

    while (1) {
        len = read((*pipeCommand)[id], command, 256);
        command[len] = '\0';
        if (!strcmp(command, "stop\0")) 
        break;
    if (!strcmp(command, "status\0")) 
        print_status(Kitchen, id);
    else if (strcmp(command, "status\0") != 0) {
        std::string pizza_type = nbs_to_string(command, 1);
        std::string pizza_size = nbs_to_string(command, 2);
        if (Kitchen->place >= 1) {
            Kitchen->pizza_waiting.push_back(pizza_type);
            Kitchen->pizza_wait_size.push_back(pizza_size);
            Kitchen->nb_command = Kitchen->nb_command + 1;
            Kitchen->place = Kitchen->place - 1;
            commandWrite = "ok";
            write((*pipeCommand)[id+3], commandWrite, strlen(commandWrite));
        }
        else {
            commandWrite = "ko";
            write((*pipeCommand)[id+3], commandWrite, strlen(commandWrite));
        }
    }
    }
    timer.join();
    add_ingredients.join();
    cooker.join();
    exit(0);
}