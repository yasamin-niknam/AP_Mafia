#include "interface.hpp"

#define ALPHABETIC "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@._-0123456789,;"

#define MAFIA "-Mafia"
#define JOKER "-Joker"
#define DOCTOR "-Doctor"
#define DETECTOR "-Detector"
#define ROUINTAN "-RouinTan"
#define VILLAGER "-Villager"
#define SILENCER "-Silencer"
#define GODFATHER "-GodFather"

#define HEAL "Heal"
#define VOTE "Vote"
#define JOIN "Join"
#define DETECT "Detect"
#define SILENT "Silent"
#define END_VOTE "End_vote"
#define CREATE_ROOM "Create_room"
#define SWITCH_ROOM "Switch_room"
#define ROOM_STATE "Get_room_state"

#define INVALID_NAME "Invalid room name"
#define WRONG_INPUTS "Wrong input arguments"
#define WRONG_COMMAND "Wrong Command! Please try Again"

using namespace std;

Interface::~Interface() 
{
	for (int i = 0; i < rooms.size(); i++)
		delete rooms[i];
}

vector<string> Interface::split_line(string command)
{
	vector<string> splitted_command;
	string word;
	while(true){
		int ptr_to_first_of_word = command.find_first_of(ALPHABETIC);
		if(ptr_to_first_of_word == NOT_FOUND)
			break;
		int ptr_to_end_of_word =command.find_first_not_of(ALPHABETIC, ptr_to_first_of_word);
		if(ptr_to_end_of_word == NOT_FOUND)
		{
			word = command.substr(ptr_to_first_of_word);
			splitted_command.push_back(word);
			break;
		}
		word = command.substr(ptr_to_first_of_word, (ptr_to_end_of_word - ptr_to_first_of_word));
		splitted_command.push_back(word);
		command = command.substr(ptr_to_end_of_word);
	}
	return splitted_command;
}

void Interface::Create_room(vector<string> splitted_line)
{
	if((splitted_line.size() % 2 != 0) || (splitted_line.size() < 4))
		throw BadInputException(WRONG_INPUTS);
	for (int i = 0; i < rooms.size(); i++)
	{
		if(rooms[i]->is_same_name(splitted_line[1]))
			throw BadInputException(INVALID_NAME);
	}
	map<PlayerTypeEnum, int> num_of_players;
	for (int i = 2; i < splitted_line.size(); i++)
	{
		if(splitted_line[i] == MAFIA)
			num_of_players[mafia] = stoi(splitted_line[i+1]);
		else if(splitted_line[i] == VILLAGER)
			num_of_players[villager] = stoi(splitted_line[i+1]);
		else if(splitted_line[i] == JOKER)
			num_of_players[joker] = stoi(splitted_line[i+1]);
		else if(splitted_line[i] == DETECTOR)
			num_of_players[detector] = stoi(splitted_line[i+1]);
		else if(splitted_line[i] == DOCTOR)
			num_of_players[doctor] = stoi(splitted_line[i+1]);
		else if(splitted_line[i] == ROUINTAN)
			num_of_players[rouintan] = stoi(splitted_line[i+1]);
		else if(splitted_line[i] == GODFATHER)
			num_of_players[godfather] = stoi(splitted_line[i+1]);
		else if(splitted_line[i] == SILENCER)
			num_of_players[silencer] = stoi(splitted_line[i+1]);
	}
	if((num_of_players[mafia] == 0) || (num_of_players[villager] == 0))
					throw BadInputException(WRONG_INPUTS);
	bool valid_num_of_mafia = ((num_of_players[silencer] + num_of_players[godfather]) 
							> num_of_players[mafia]);
	bool valid_num_of_villager = ((num_of_players[detector] + num_of_players[doctor] 
							+ num_of_players[rouintan]) > num_of_players[villager]);
	if(valid_num_of_mafia || valid_num_of_villager)
			throw BadInputException(WRONG_INPUTS);
	Room* new_room = new Room(splitted_line[1], num_of_players);
	rooms.push_back(new_room);
}

void Interface::Switch_room(vector<string> splitted_line)
{
	if(splitted_line.size() != 2)
		throw BadInputException(WRONG_INPUTS);
	else
	{
		bool founded_room_name = false;
		for (int i = 0; i < rooms.size(); i++)
		{
			if(rooms[i]->is_same_name(splitted_line[1]))
			{
				founded_room_name = true;
				index_of_current_room = i;
			}									
		}
		if(!founded_room_name)
			throw BadInputException(INVALID_NAME);
	}
}

void Interface::Join(vector<string> splitted_line, Room* current_room)
{
	for (int i = 1; i < splitted_line.size(); i++)
		current_room->join(splitted_line[i]);
}

void Interface::process(string line)
{
	vector<string> splitted_line = split_line(line);
	if(index_of_current_room != NOT_FOUND)
	{
		rooms[index_of_current_room]->check_day();
		rooms[index_of_current_room]->check_num_of_players();
		if(rooms[index_of_current_room]->check_the_end_of_game())
		{
			index_of_current_room = NOT_FOUND;
			return;
		}
	}
	else
	{
		if((splitted_line[0] == CREATE_ROOM) || (splitted_line[0] == SWITCH_ROOM))
		{}
		else
			return;
	}
	if(splitted_line[0] == CREATE_ROOM)
	{
		try
		{
			Create_room(splitted_line);
			index_of_current_room = rooms.size() - 1;
		}
		catch(BadInputException ex)
		{
			ex.print();
		}
	}
	else if(splitted_line[0] == SWITCH_ROOM)
	{
		try
		{
			Switch_room(splitted_line);
		}
		catch(BadInputException ex)
		{
			ex.print();
		}
	}
	else if(splitted_line[0] == JOIN)
	{
		try
		{
			Join(splitted_line, rooms[index_of_current_room]);
		}
		catch(BadInputException ex)
		{
			ex.print();
		}
	}
	else if(splitted_line[0] == VOTE)
	{
		try
		{
			rooms[index_of_current_room]->vote(splitted_line);
		}
		catch(BadInputException ex)
		{
			ex.print();
		}
	}
	else if(splitted_line[0] == END_VOTE)
	{
		try
		{
			rooms[index_of_current_room]->end_vote_in_day();
		}
		catch(BadInputException ex)
		{
			ex.print();
		}
	}
	else if(splitted_line[0] == DETECT)
	{
		try
		{
			rooms[index_of_current_room]->detect(splitted_line[1], splitted_line[2]);
		}
		catch(BadInputException ex)
		{
			ex.print();
		}
	}
	else if(splitted_line[0] == HEAL)
	{
		try
		{
			rooms[index_of_current_room]->heal(splitted_line[1], splitted_line[2]);
		}
		catch(BadInputException ex)
		{
			ex.print();
		}
	}
	else if(splitted_line[0] == SILENT)
	{
		try
		{
			rooms[index_of_current_room]->silent(splitted_line[1], splitted_line[2]);
		}
		catch(BadInputException ex)
		{
			ex.print();
		}
	}
	else if(splitted_line[0] == ROOM_STATE)
		rooms[index_of_current_room]->get_room_state();
	else
	{
		BadInputException error = BadInputException(WRONG_COMMAND);
		error.print();
	}
}
