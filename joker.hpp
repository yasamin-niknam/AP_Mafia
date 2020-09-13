#ifndef JOKER_CLASS
#define JOKER_CLASS

#include <iostream>
#include <vector>
#include "players.hpp"

class Joker : public Player
{
public:
	Joker(std::string name)  : Player(name) {}
	virtual void die();
	virtual bool is_mafia() {return false;}
	~Joker() = default;
private:
	bool been_killed = false;
};

#endif



