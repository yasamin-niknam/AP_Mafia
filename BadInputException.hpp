#ifndef BADINPUTEXCEPTION
#define BADINPUTEXCEPTION

#include <iostream>
#include <vector>

class BadInputException
{
public:
	BadInputException(std::string _error) : error(_error) {}
	void print(){std::cout << error << std::endl;}
private:
	std::string error;
};


#endif