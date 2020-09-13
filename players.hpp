#ifndef PLAYERS_CLASS
#define PLAYERS_CLASS

#include <iostream>
#include <vector>
#include "BadInputException.hpp"

class Player
{
public:
	Player(std::string _name) : name(_name) {}
	virtual bool is_mafia() = 0;
	virtual void die(); 
	virtual void do_task(Player* player){}
	virtual void start_new_day(){}
	virtual void start_night(){been_silenced = false;}
	void silent();
	bool died(){return is_dead;}
	void heal(){is_dead = false;}
	bool is_silenced(){return been_silenced;}
	bool is_the_same_person(std::string _player_name){return (name == _player_name);}
	~Player() = default;
protected:
	std::string name;
	bool been_silenced = false;
	bool is_dead = false;
};



#endif


