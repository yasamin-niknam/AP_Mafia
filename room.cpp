#include "room.hpp"

#define NOT_FOUND -1

#define DAY "Day "
#define DIED "Died "
#define NIGHT "Night "
#define WIN "Victory!"
#define LOOSE "Loose!"
#define KILLED "Killed "
#define SILENCED "Silenced "
#define MAFIA_KILLED "Mafia try to kill "

#define MAFIA "Mafia"
#define JOKER "Joker"
#define DOCTOR "Doctor"
#define DETECTOR "Detector"
#define ROUINTAN "RouinTan"
#define VILLAGER "Villager"
#define SILENCER "Silencer"
#define GODFATHER "GodFather"

#define DEAD "Person is dead"
#define MANY_USERS "many users"
#define NOT_JOINED "User not joined"
#define CANNOT_ASK "User can not ask"
#define CANNOT_HEAL "User can not heal"
#define ALREADY_DIED "User already died"
#define WRONG_INPUTS "Wrong input arguments"
#define CANNOT_VOTE "This user can not vote"
#define CANNOT_SILENT "User can not silence"
#define ALREADY_HEALED "Doctor has already healed"
#define ALREADY_ASKED "Dotective has already asked"
#define CANNOT_JOIN "You can not join members at night"
#define CANNOT_ENDVOTE "User can not end vote at night"
#define ALREADY_SILENCED "Silencer has already silenced"
#define USER_BEEN_ADDED "This user has been added before"
#define USER_IS_SILENT "This user has been silenced before"

using namespace std;

Room::Room(string _room_name, map<PlayerTypeEnum, int> _num_of_players)
{
	room_name = _room_name;
	num_of_players = _num_of_players;
	num_of_alive_players = num_of_players;
}

Room::~Room()
{
	for (int i = 0; i < players.size(); i++)
		delete players[i]; 
}

void Room::join(string player_name)
{
	if(day_or_night == night)
		throw BadInputException(CANNOT_JOIN);
	if(roles.size() == (num_of_players[mafia] + num_of_players[villager] + num_of_players[joker]))
		throw BadInputException(MANY_USERS);
	map<string, PlayerTypeEnum>::iterator itr;
	for (itr = roles.begin(); itr != roles.end(); itr++) 
	{
		if(itr->first == player_name)
			throw BadInputException(USER_BEEN_ADDED);
    } 
 	roles[player_name];
	if(roles.size() == (num_of_players[mafia] + num_of_players[villager] + num_of_players[joker]))
	{
		vector<string> player_names(roles.size());
		int count =0;
		for (itr = roles.begin(); itr != roles.end(); itr++) 
		{
			player_names[count] = itr->first;
			count++;
	    } 		
		initial_players(player_names);
		print_joined_people();
	}
}

void Room::print_joined_people()
{
	map<string, PlayerTypeEnum>::iterator itr;
	for (itr = roles.begin(); itr != roles.end(); ++itr) 
	{ 
        cout << itr->first << " is " ;
        if(itr->second == mafia)
        	cout << MAFIA << endl;
        if(itr->second == villager)
        	cout << VILLAGER << endl;
        if(itr->second == silencer)
        	cout << SILENCER << endl;
        if(itr->second == godfather)
        	cout << GODFATHER << endl;
        if(itr->second == joker)
        	cout << JOKER << endl;
        if(itr->second == rouintan)
        	cout << ROUINTAN << endl;
        if(itr->second == doctor)
        	cout << DOCTOR << endl;
        if(itr->second == detector)
        	cout << DETECTOR << endl;
    }
}

void Room::initial_players(vector<string> names)
{
	int random_index;
	int num_of_mafia_needed = num_of_players[mafia] - num_of_players[godfather] 
							- num_of_players[silencer];
	int num_of_villager_needed = num_of_players[villager] - num_of_players[doctor]
							- num_of_players[detector] - num_of_players[rouintan];
	for (int i = 0; i < num_of_villager_needed; i++)
	{
		random_index = rand() % names.size();
		Villager* new_villager = new Villager(names[random_index]);
		players.push_back(new_villager);
		roles[names[random_index]] = villager;
		names.erase(names.begin() + random_index);
	}
	for (int i = 0; i < num_of_mafia_needed; i++)
	{
		random_index = rand() % names.size();
		Mafia* new_mafia = new Mafia(names[random_index]);
		players.push_back(new_mafia);
		roles[names[random_index]] = mafia;
		names.erase(names.begin() + random_index);
	}
	for (int i = 0; i < num_of_players[silencer]; i++)
	{
		random_index = rand() % names.size();
		Silencer* new_silencer = new Silencer(names[random_index]);
		players.push_back(new_silencer);
		roles[names[random_index]] = silencer;
		names.erase(names.begin() + random_index);
	}
	for (int i = 0; i < num_of_players[rouintan]; i++)
	{
		random_index = rand() % names.size();
		RouinTan* new_rouintan = new RouinTan(names[random_index]);
		players.push_back(new_rouintan);
		roles[names[random_index]] = rouintan;
		names.erase(names.begin() + random_index);
	}
	for (int i = 0; i < num_of_players[godfather]; i++)
	{
		random_index = rand() % names.size();
		GodFather* new_godfather = new GodFather(names[random_index]);
		players.push_back(new_godfather);
		roles[names[random_index]] = godfather;
		names.erase(names.begin() + random_index);
	}
	for (int i = 0; i < num_of_players[doctor]; i++)
	{
		random_index = rand() % names.size();
		Doctor* new_doctor = new Doctor(names[random_index]);
		players.push_back(new_doctor);
		roles[names[random_index]] = doctor;
		names.erase(names.begin() + random_index);
	}
	for (int i = 0; i < num_of_players[detector]; i++)
	{
		random_index = rand() % names.size();
		Detector* new_detector = new Detector(names[random_index]);
		players.push_back(new_detector);
		roles[names[random_index]] = detector;
		names.erase(names.begin() + random_index);
	}
	for (int i = 0; i < num_of_players[joker]; i++)
	{
		random_index = rand() % names.size();
		Joker* new_joker = new Joker(names[random_index]);
		players.push_back(new_joker);
		roles[names[random_index]] = joker;
		names.erase(names.begin() + random_index);
	}
}

void Room::get_room_state()
{
	cout << MAFIA << " = " << num_of_alive_players[mafia] << endl;
	cout << VILLAGER << " = " << num_of_alive_players[villager] << endl;
}

int Room::find_index_of_player(string player_name)
{
	for (int i = 0; i < players.size(); i++)
	{
		if(players[i]->is_the_same_person(player_name))
			return i;
	}
	return NOT_FOUND;
}

void Room::silent(string silencer_name, string player_name)
{
	if((state != silenting) || (day_or_night == day))
	{
		if(roles[silencer_name] == silencer)		
			throw BadInputException(ALREADY_SILENCED);
		else
			throw BadInputException(CANNOT_SILENT);
	}
	if(roles[silencer_name] == silencer)
	{
		int index_of_silencer = find_index_of_player(silencer_name);
		int index_of_player = find_index_of_player(player_name);
		if((index_of_silencer == NOT_FOUND) || (index_of_player == NOT_FOUND))
 			throw BadInputException(NOT_JOINED);
		if(players[index_of_silencer]->died())
			throw BadInputException(CANNOT_SILENT);
		if(players[index_of_player]->died())
			throw BadInputException(DEAD);
		players[index_of_silencer]->do_task(players[index_of_player]);
		silenced_players.push_back(player_name);
		if(silenced_players.size() == num_of_players[silencer])
			state = end_night;
	}
	else
		throw BadInputException(CANNOT_SILENT);
}

void Room::heal(std::string doctor_name, std::string player_name)
{
	if((state != healing) || (day_or_night == day))
	{
		if(roles[doctor_name] == doctor)		
			throw BadInputException(ALREADY_HEALED);
		else
			throw BadInputException(CANNOT_HEAL);
	}
	if(roles[doctor_name] == doctor)
	{
		int index_of_doctor = find_index_of_player(doctor_name);
		int index_of_player = find_index_of_player(player_name);
		if((index_of_doctor == NOT_FOUND) || (index_of_player == NOT_FOUND))
			throw BadInputException(NOT_JOINED);
		if(players[index_of_doctor]->died())
			throw BadInputException(CANNOT_HEAL);
		if(players[index_of_player]->died() && (player_name != killed_player))
			throw BadInputException(DEAD);
		players[index_of_doctor]->do_task(players[index_of_player]);
		if((killed_player == player_name) && (players[index_of_player]->died() == false))
			killed_player.clear();
		num_of_people_healed++;
		if(num_of_people_healed == num_of_players[doctor])
		{
			if(num_of_players[silencer] != 0)
				state = silenting;
			else
				state = end_night;
		}
	}
	else
		throw BadInputException(CANNOT_HEAL);	
}

void Room::detect(std::string detector_name, std::string player_name)
{
	if((state != detecting) || (day_or_night == day))
	{
		if(roles[detector_name] == detector)		
			throw BadInputException(ALREADY_ASKED);
		else
			throw BadInputException(CANNOT_ASK);
	}
	int index_of_detector = find_index_of_player(detector_name);
	int index_of_player = find_index_of_player(player_name);
	if((index_of_detector == NOT_FOUND) || (index_of_player == NOT_FOUND))
		throw BadInputException(NOT_JOINED);
	if(roles[detector_name] == detector)
	{
		if(players[index_of_detector]->died())
			throw BadInputException(CANNOT_ASK);
		if(players[index_of_player]->died())
			throw BadInputException(DEAD);
		players[index_of_detector]->do_task(players[index_of_player]);
		num_of_people_detected++;
		if(num_of_people_detected == num_of_players[detector])
		{
			if(num_of_players[doctor] != 0)
				state = healing;
			else if(num_of_players[silencer] != 0)
				state = silenting;
			else
				state = end_night;
		}
	}
	else
		throw BadInputException(CANNOT_ASK);	
}

void Room::vote(vector<string> splitted_line)
{
	if(splitted_line.size() != 3)
		throw BadInputException(WRONG_INPUTS);
	string voter_name = splitted_line[1];
	string votee_name = splitted_line[2];
	int index_of_voter = find_index_of_player(voter_name);
	int index_of_votee = find_index_of_player(votee_name);
	if ((index_of_votee == NOT_FOUND) || (index_of_voter == NOT_FOUND))
		throw BadInputException(NOT_JOINED);
	if(players[index_of_voter]->died())
		throw BadInputException(CANNOT_VOTE);
	if(players[index_of_votee]->died())
		throw BadInputException(ALREADY_DIED);
	if(players[index_of_voter]->is_silenced())
		throw BadInputException(USER_IS_SILENT);
	if((day_or_night == day) && (state == vote_day))
		votes[voter_name] = votee_name;
	else if((day_or_night == night) && (state == vote_night))
	{
		if((players[index_of_voter]->is_mafia()) || (roles[voter_name] == godfather))
		{
			votes[voter_name] = votee_name;
			if(votes.size() == num_of_alive_players[mafia])
			{
				kill_with_vote();
				cout << MAFIA_KILLED << killed_player << endl;
				if(num_of_players[detector] != 0)
					state = detecting;
				else if(num_of_players[doctor] != 0)
					state = healing;
				else if(num_of_players[silencer] != 0)
					state = silenting;
				else
					state = end_night;
			}
		}
		else 
			throw BadInputException(CANNOT_VOTE);
	}
	else 
		throw BadInputException(CANNOT_VOTE);
}

void Room::end_vote_in_day()
{
	if(day_or_night == night)
		throw BadInputException(CANNOT_ENDVOTE);
	if(kill_with_vote())
	{
		cout << DIED << killed_player << endl;
		killed_player.clear();
		cout << NIGHT << count_day << endl;	
	}
	state = vote_night;
	day_or_night = night;
	for (int i = 0; i < players.size(); i++)
	{
		players[i]->start_night();
	}
}

bool Room::kill_with_vote()
{
	int max_votes = 0;
	string voted_player;
	map<string, int> final_votes;
	map<string, int>::iterator votes_itr;
	map<string, string>::iterator itr;
	for (itr = votes.begin(); itr != votes.end(); ++itr) 
		final_votes[itr->second] = 0;
    for (itr = votes.begin(); itr != votes.end(); ++itr) 
    {
    	for (votes_itr = final_votes.begin(); votes_itr != final_votes.end(); ++votes_itr) 
    	{
    		if(itr->second == votes_itr->first)
    			(votes_itr->second)++;
    	}
    }
    for (votes_itr = final_votes.begin(); votes_itr != final_votes.end(); ++votes_itr) 
	{
		if(votes_itr->second > max_votes)
			max_votes = votes_itr->second;
	}
	for (votes_itr = final_votes.begin(); votes_itr != final_votes.end(); ++votes_itr) 
	{
		if(votes_itr->second == max_votes)
			voted_player = votes_itr->first;
	}
	votes.clear();
	int index_of_voted_player = find_index_of_player(voted_player);
	players[index_of_voted_player]->die();
	if((roles[voted_player] == rouintan) && (players[index_of_voted_player]->died() == false) 
		&& (day_or_night == day))
		players[index_of_voted_player]->die();
	
	killed_player = voted_player;
	if(players[index_of_voted_player]->died())
	{
		return true;
	}
	return false;
}

void Room::check_num_of_players()
{
	std::map<std::string, PlayerTypeEnum>::iterator itr;
	num_of_alive_players = num_of_players;	
	for (itr = roles.begin(); itr != roles.end(); ++itr)
	{
		int index_of_player = find_index_of_player(itr->first);
		if(players[index_of_player]->died())
		{
			num_of_alive_players[itr->second]--;
			if((itr->second == rouintan) || (itr->second == doctor) || (itr->second == detector))
				num_of_alive_players[villager]--;
			else if((itr->second == godfather) || (itr->second == silencer))
				num_of_alive_players[mafia]--;
		}
	} 
}

void Room::check_day()
{
	if(state == end_night)
	{
		int index_of_voted_player = find_index_of_player(killed_player);
		if(index_of_voted_player != NOT_FOUND)
			players[index_of_voted_player]->die();
		count_day++;
		cout << DAY << count_day << endl;
		if(index_of_voted_player != NOT_FOUND)
		{
			if((players[index_of_voted_player]->died()))
				cout << KILLED << killed_player << endl;
		}
		for (int i = 0; i < silenced_players.size(); i++)
			cout << SILENCED << silenced_players[i] << endl;
		initial_for_new_day();
	}
}

void Room::initial_for_new_day()
{
	num_of_alive_players.clear();
		num_of_alive_players = num_of_players;	
		num_of_people_healed = 0;
		num_of_people_detected = 0;
		killed_player.clear();
		silenced_players.clear();
		for (int i = 0; i < players.size(); i++)
			players[i]->start_new_day();
		state = vote_day;
		day_or_night = day;
}

bool Room::check_the_end_of_game()
{
	std::map<std::string, PlayerTypeEnum>::iterator itr;
	for (itr = roles.begin(); itr != roles.end(); ++itr) 
	{
		if(itr->second == joker)
		{
			int index_of_joker = find_index_of_player(itr->first);
			if(players[index_of_joker]->died())
				return true;
		}
	}
	if(num_of_alive_players[villager] <= num_of_alive_players[mafia])
	{
		cout << LOOSE << endl;
		return true;
	}
	else if(num_of_alive_players[mafia] == 0)
	{
		cout << WIN << endl;
		return true;
	}
	return false;	
}
