#ifndef GODFATHER_CLASS
#define GODFATHER_CLASS

#include <iostream>
#include <vector>
#include "mafia.hpp"

class GodFather : public Mafia  
{
public:
	GodFather(std::string name) : Mafia(name) {}
	virtual bool is_mafia() {return false;}
	~GodFather() = default;
};


#endif