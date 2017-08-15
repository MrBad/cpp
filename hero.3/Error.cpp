//
// Created by vio on 8/15/17.
//

#include <iostream>
#include <string>

void fatalError(const std::string &errorMessage)
{
	std::cerr << errorMessage << std::endl;
	exit(1);
}
