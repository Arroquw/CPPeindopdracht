#pragma once
#include "Athletics.h"

class AthleticGroup2 {
public:
	AthleticGroup2();
	AthleticGroup2(const AthleticGroup2& other);
	AthleticGroup2(AthleticGroup2&& other);
	AthleticGroup2& operator = (const AthleticGroup2&);
	AthleticGroup2& operator = (AthleticGroup2&&);
	virtual ~AthleticGroup2();

	virtual int deleteMember(int ID);
	virtual int findGroupMember(int ID);
	virtual void addMember(AthleticsMember);
	virtual void modifyMemberName(std::string, int);
	virtual void modifyMemberAge(int, int);
	virtual void createArray(size_t size);
	virtual void resizeArray(size_t size);
	virtual char * getName();
	virtual void setName(std::string name);
	virtual AthleticsMember *getMembers();
	virtual void setMembers(AthleticsMember *members);
	virtual unsigned getAmount();
	virtual void setAmount(unsigned amount);
private:
	char *name;
	AthleticsMember *members;
	size_t amount;
};
