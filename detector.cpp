#include "detector.hpp"

#define ALREADY_ASKED "Detective has already asked"

using namespace std;

void Detector::do_task(Player* player)
{
	if(detected_tonight)
		throw BadInputException(ALREADY_ASKED);
	else
	{
		if(player->is_mafia())
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
		detected_tonight = true;
	}
}

void Detector::start_new_day()
{
	detected_tonight = false;
}