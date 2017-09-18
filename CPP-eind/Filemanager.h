#pragma once
#include "AthleticGroup.h"
#include "Athletics.h"

class Filemanager {
public:
	Filemanager(std::string, std::string);
	Filemanager(const Filemanager &other);
	Filemanager(Filemanager &&other);
	Filemanager& operator=(const Filemanager&);
	Filemanager& operator=(Filemanager&&);
	virtual int findIndex(int, int);
	virtual void findName(std::string);
	virtual void findAge(int);
	virtual void printMember(unsigned);
	virtual void findMember();
	virtual void editGroup();
	virtual void addMember();
	virtual void removeMember();
	virtual void modifyMember();
	virtual void addGroup();
	virtual void removeGroup();
	virtual void findGroup();
	virtual void readGroupFile(std::string);
	virtual void readMemberFile(std::string);
	virtual void writeGroupFile(std::string);
	virtual void writeMemberFile(std::string);
	virtual void printGroups();
	virtual void printMembers();
	virtual void print();
	virtual ~Filemanager();
private:
	size_t amount_members;
	size_t amount_groups;
	AthleticGroup2 *groups;
	AthleticsMember *members;
};