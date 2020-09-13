#ifndef DOCTOR_CLASS
#define DOCTOR_CLASS

#include <iostream>
#include <vector>
#include "villager.hpp"
#include "players.hpp"

class Doctor : public Villager  
{
public:
	Doctor(std::string name) : Villager(name) {}
	virtual bool is_mafia() {return false;}
	virtual void do_task(Player* player);
	virtual void start_new_day();
	~Doctor() = default;
private:
	bool healed_tonight = false;	
};

#endif