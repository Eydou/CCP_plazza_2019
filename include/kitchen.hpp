/*
** EPITECH PROJECT, 2019
** kitchen.hpp
** File description:
** kitchen
*/

#ifndef HPP_PLAZZA
#define HPP_PLAZZA

#include <ostream>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <mutex>

class kitchen {
public:
	kitchen(int time_cooking, int nbcook, int time_respawn_alim);
	~kitchen();

	int getDoe() const;
	int getTomato() const;
	int getGruyere() const;
	int getHam() const;
	int getMushrooms() const;
	int getSteak() const;
	int getEggplant() const;
	int getGoatCheese() const;
	void pizza_regina();
	void pizza_margarita();
	void pizza_american();
	void pizza_fantasia();

	int steak, eggplant, goatcheese, doe;
	int tomato, gruyere, ham;
	int mushrooms, nb_cook, time_cook, new_alim;
	int cook_ready,place, nb_command, kitchen_status, start;
	std::vector<std::string> pizza_waiting, pizza_wait_size;
};

void kitchen_init(int time_cooking, int nb_cook, int time_respawn_alim, std::vector<int> *pipeCommand);

#endif
