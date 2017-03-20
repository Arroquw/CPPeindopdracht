#pragma once
#include "Athletics.h"
#include <iostream>
#include <iterator>

class AthleticGroup2 {
public:
	virtual void readGroupFile(std::string path);
	virtual ~AthleticGroup2();
	AthleticGroup2();
private:
	char *name;
	AthleticsMember *members;
	unsigned amount;
	unsigned line;
};
