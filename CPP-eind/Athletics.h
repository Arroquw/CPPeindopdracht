#pragma once
class AthleticsMember {
public:
	virtual void addMember();
private:
	char *name;
	unsigned age;
	unsigned ID;
};