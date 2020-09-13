#ifndef DETECTOR_CLASS
#define DETECTOR_CLASS

#include <iostream>
#include <vector>
#include "villager.hpp"
#include "players.hpp"

class Detector : public Villager  
{
public:
	Detector(std::string name) : Villager(name) {}
	virtual bool is_mafia() {return false;}
	virtual void do_task(Player* player);
	virtual void start_new_day();
	~Detector() = default;
private:
	bool detected_tonight = false;	
};


#endif

