#include "doctor.hpp"

#define ALREADY_HEALED "Doctor has already healed"

using namespace std;

void Doctor::do_task(Player* player)
{
	if(healed_tonight)
		throw BadInputException(ALREADY_HEALED);
	else
	{
		player->heal();
		healed_tonight = true;
	}
}

void Doctor::start_new_day()
{
	healed_tonight = false;
}