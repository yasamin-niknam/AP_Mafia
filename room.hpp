#ifndef ROOM_CLASS
#define ROOM_CLASS

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
#include "BadInputException.hpp"

enum DayTypeEnum
{
	day,
	night
};

enum PlayerTypeEnum
{
	mafia,
	villager,
	joker,
	silencer,
	godfather,
	doctor,
	detector,
	rouintan
};

enum StateTypeEnum
{
	vote_day,
	vote_night,
	detecting,
	healing,
	silenting,
	end_night
};

class Room
{
public:
	Room(std::string _room_name, std::map<PlayerTypeEnum, int> _num_of_players);
	bool is_same_name(std::string new_room_name){return (new_room_name == room_name);}
	void join(std::string player_name);
	void initial_players(std::vector<std::string> player_names);
	void get_room_state();
	int find_index_of_player(std::string player_name);
	void print_joined_people();
	void end_vote_in_day();
	void check_day();
	bool kill_with_vote();
	void check_num_of_players();
	bool check_the_end_of_game();
	void initial_for_new_day();
	void vote(std::vector<std::string> splitted_line);
	void silent(std::string silencer_name, std::string player_name);
	void heal(std::string doctor_name, std::string player_name);
	void detect(std::string detector_name, std::string player_name);
	~Room();
private:
	DayTypeEnum day_or_night = day;
	StateTypeEnum state = vote_day;
	std::string killed_player = "";
	std::map<PlayerTypeEnum, int> num_of_players; 
	std::map<PlayerTypeEnum, int> num_of_alive_players; 
	std::vector<std::string> silenced_players;
	std::map<std::string, PlayerTypeEnum> roles;	
	std::map<std::string, std::string> votes;	
	std::vector<Player*> players;	
	std::string room_name;
	int count_day = 1;
	int num_of_people_detected = 0;
	int num_of_people_healed = 0;
};



#endif


