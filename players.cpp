#include "players.hpp"

using namespace std;

void Player::die()
{
	is_dead = true;
}

void Player::silent()
{
	been_silenced = true;
}
