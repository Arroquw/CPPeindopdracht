#pragma once
#include <string>

class AthleticsMember {
public:
	AthleticsMember();
	AthleticsMember(const AthleticsMember& other);
	AthleticsMember(AthleticsMember&& other);
	virtual ~AthleticsMember();
	AthleticsMember& operator = (const AthleticsMember& other);
	AthleticsMember& operator = (AthleticsMember&& other);
	virtual char* getName();
	virtual void setName(std::string name);
	virtual unsigned getAge();
	virtual void setAge(unsigned age);
	virtual unsigned getID();
	virtual void setID(unsigned ID);
private:
	char *name;
	unsigned age;
	unsigned ID;
};
