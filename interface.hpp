#ifndef INTERFACE_CLASS
#define INTERFACE_CLASS

#include <iostream>
#include <vector>
#include <map>
#include "players.hpp"
#include "mafia.hpp"
#include "godfather.hpp"
#include "silencer.hpp"
#include "villager.hpp"
#include "detector.hpp"
#include "doctor.hpp"
#include "rouintan.hpp"
#include "joker.hpp"
#include "room.hpp"
#include "BadInputException.hpp"

#define NOT_FOUND -1

class Interface
{
public:
	Interface(){}
	void process(std::string line);
	~Interface();
private:
	void Create_room(std::vector<std::string> splitted_line);
	void Switch_room(std::vector<std::string> splitted_line);
	void Join(std::vector<std::string> splitted_line, Room* current_room);
	std::vector<std::string> split_line(std::string command);
	std::vector<Room*> rooms;
	int index_of_current_room = NOT_FOUND;
};

#endif