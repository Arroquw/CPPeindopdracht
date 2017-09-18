#include "AthleticGroup.h"


void AthleticGroup2::createArray(size_t size) {
	members = new AthleticsMember[size];
}

void AthleticGroup2::resizeArray(size_t size) {
	AthleticsMember *newArray = new AthleticsMember[size];
	std::copy(members, members + size, newArray);
	delete[] members;
	members = newArray;
}

AthleticGroup2::AthleticGroup2() {
	name = 0;
	members = 0;
	amount = 0;
}

AthleticGroup2::AthleticGroup2(const AthleticGroup2 & other) : amount(other.amount), members(new AthleticsMember[other.amount]) {
	name = _strdup(other.name);
	std::copy(other.members, other.members + amount, members);
}

AthleticGroup2::AthleticGroup2(AthleticGroup2 && other) : name(nullptr), members(nullptr), amount(0) {
	*this = std::move(other);
}

AthleticGroup2 & AthleticGroup2::operator=(const AthleticGroup2 &other) {
	if (this != &other) {
		delete[] name;
		delete[] members;
		amount = other.amount;
		name = _strdup(other.name);
		createArray(amount);
		std::copy(other.members, other.members + amount, members);
	}
	return *this;
}

AthleticGroup2 & AthleticGroup2::operator=(AthleticGroup2 &&other) {
	if (this != &other) {
		delete[] members;
		delete[] name;
		name = other.name;
		members = other.members;
		amount = other.amount;
		other.name = nullptr;
		other.members = nullptr;
		other.amount = 0;
	}
	return *this;
}

AthleticGroup2::~AthleticGroup2() {
	delete[] name;
	delete[] members;
	name = NULL;
	members = nullptr;
}

int AthleticGroup2::deleteMember(int ID) {
	unsigned i = findGroupMember(ID);
	AthleticsMember *newArray1 = 0;
	if (i != -1) {
		amount--;
		newArray1 = new AthleticsMember[amount + 1];
		for (unsigned j = 0; j < amount + 1; j++) {
			newArray1[j] = members[j];
		}
		for (; i < amount; i++) {
			newArray1[i] = newArray1[i + 1];
		}
		delete[] members;
		setMembers(newArray1);
		resizeArray(amount);
		return i;
	}
	return i;
}

int AthleticGroup2::findGroupMember(int ID) {
	unsigned int i;
	for (i = 0; i != amount; i++) {
		if (members[i].getID() == ID) {
			break;
		}
	}
	if (i == amount) {
		return -1;
	}
	else {
		return i;
	}
}

void AthleticGroup2::addMember(AthleticsMember member) {
	if (findGroupMember(member.getID()) >= 0) {
		return;
	}
	else {
		amount++;
		AthleticsMember *newMembers = new AthleticsMember[amount];
		for (unsigned n = 0; n < amount - 1; n++) {
			newMembers[n] = members[n];
		}
		delete[] members;
		newMembers[amount - 1] = member;
		members = newMembers;
	}
}

void AthleticGroup2::modifyMemberName(std::string name, int ID) {
	int index = findGroupMember(ID);
	if (index > -1) {
		members[index].setName(name);
	}
}

void AthleticGroup2::modifyMemberAge(int newAge, int ID) {
	int index = findGroupMember(ID);
	if (index > -1) {
		members[index].setAge(newAge);
	}
}

char * AthleticGroup2::getName() {
	return this->name;
}

void AthleticGroup2::setName(std::string name) {
	delete[] this->name;
	this->name = new char[name.size() + 1];
	std::copy(name.begin(), name.end(), this->name);
	this->name[name.size()] = '\0';
}

AthleticsMember *AthleticGroup2::getMembers() {
	return this->members;
}

void AthleticGroup2::setMembers(AthleticsMember * member) {
	members = member;
}

unsigned AthleticGroup2::getAmount() {
	return this->amount;
}

void AthleticGroup2::setAmount(unsigned amount) {
	this->amount = amount;
}