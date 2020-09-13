#include "rouintan.hpp"

using namespace std;

void RouinTan::die()
{
	if(been_killed_once)
		is_dead = true;
	else
		been_killed_once = true;
}