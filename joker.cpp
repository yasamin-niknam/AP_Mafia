#include "joker.hpp"

#define JOKER_WON "Do I look like a guy with a plan?"

using namespace std;

void Joker::die()
{
	is_dead = true;
	throw BadInputException(JOKER_WON);
}