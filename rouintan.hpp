#ifndef ROUINTAN_CLASS
#define ROUINTAN_CLASS

#include <iostream>
#include <vector>
#include "villager.hpp"
#include "players.hpp"

class RouinTan : public Villager  
{
public:
	RouinTan(std::string name) : Villager(name) {}
	virtual bool is_mafia() {return false;}
	virtual void die();
	~RouinTan() = default;
private:
	bool been_killed_once = false;
};

#endif

