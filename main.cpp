#include <iostream>
#include "interface.hpp"

using namespace std;


int main()
{
	srand(time(NULL));
	string line;
	Interface game = Interface();
	while(getline(cin, line))
	{
		game.process(line);
	}
	return 0;
}