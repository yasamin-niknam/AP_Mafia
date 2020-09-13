#ifndef MAFIA_CLASS
#define MAFIA_CLASS

#include <iostream>
#include <vector>
#include "players.hpp"

class Mafia : public Player
{
public:
	Mafia(std::string name) : Player(name) {} 
	virtual bool is_mafia() {return true;}
	~Mafia();
private:
	bool has_voted_tonight = false;
};

#endif