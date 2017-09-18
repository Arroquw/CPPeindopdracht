#include "Athletics.h"

AthleticsMember::AthleticsMember() {
	name = 0;
	age = 0;
	ID = 0;
}

AthleticsMember::AthleticsMember(const AthleticsMember& other) : age(other.age), ID(other.ID) {
	name = _strdup(other.name);
}

AthleticsMember::AthleticsMember(AthleticsMember&& other) : name(nullptr), age(0), ID(0){
	*this = std::move(other);
}

AthleticsMember::~AthleticsMember() {
	delete[] name;
	name = NULL;
}

AthleticsMember& AthleticsMember::operator = (const AthleticsMember& other) {
	if (this != &other) {
		delete[] name;
		name = _strdup(other.name);
		age = other.age;
		ID = other.ID;
	}
	return *this;
}

AthleticsMember& AthleticsMember::operator = (AthleticsMember&& other){
	if (this != &other) {
		delete[] name;
		name = _strdup(other.name);
		age = other.age;
		ID = other.ID;
		other.name = nullptr;
		other.age = 0;
		other.ID = 0;
	}
	return *this;
}

char * AthleticsMember::getName() {
	return this->name;
}

void AthleticsMember::setName(std::string name) {
	delete[] this->name;
	this->name = new char[name.size()+1];
	std::copy(name.begin(), name.end(), this->name);
	this->name[name.size()] = '\0';
}

unsigned AthleticsMember::getAge() {
	return this->age;
}

void AthleticsMember::setAge(unsigned age) {
	this->age = age;
}

unsigned AthleticsMember::getID() {
	return this->ID;
}

void AthleticsMember::setID(unsigned ID) {
	this->ID = ID;
}