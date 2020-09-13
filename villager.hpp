#ifndef VILLAGER_CLASS
#define VILLAGER_CLASS

#include <iostream>
#include <vector>
#include "players.hpp"

class Villager : public Player
{
public:
	Villager(std::string name)  : Player(name) {}
	virtual bool is_mafia() {return false;}
	~Villager() = default;
};

#endif