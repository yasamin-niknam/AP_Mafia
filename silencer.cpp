#include "silencer.hpp"

#define ALREADY_SILENCED "Silencer has alredy silenced"

using namespace std;

void Silencer::do_task(Player* player)
{
	if(silenced_tonight)
		throw BadInputException(ALREADY_SILENCED);
	else
	{
		player->silent();
		silenced_tonight = true;
	}
}

void Silencer::start_new_day()
{
	silenced_tonight = false;
}