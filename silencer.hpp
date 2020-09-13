#ifndef SILENCER_CLASS
#define SILENCER_CLASS

#include <iostream>
#include <vector>
#include "mafia.hpp"

class Silencer : public Mafia  
{
public:
	Silencer(std::string name) : Mafia(name) {}
	virtual bool is_mafia() {return true;}
	virtual void do_task(Player* player);
	virtual void start_new_day();
	~Silencer() = default;
private:
	bool silenced_tonight = false;	
};

#endif

