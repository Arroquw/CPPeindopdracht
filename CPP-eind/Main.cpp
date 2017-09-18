#include "AthleticGroup.h"
#include "Athletics.h"
#include "Filemanager.h"
#include "Interfacing.h"
#include <iostream>

void checkForLeaks();

void checkForLeaks() {
#ifdef _DEBUG

	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

	flag |= _CRTDBG_LEAK_CHECK_DF;

	_CrtSetDbgFlag(flag);

#endif
}

int main(int argc, char *argv[]) {
	Filemanager *a = new Filemanager(argv[1], argv[2]);
	ClubInterface *in = new ClubInterface();
	int input = in->readInput();
	checkForLeaks();
	void(Filemanager::*functionPointers[])() = {0, &Filemanager::findGroup, 
		&Filemanager::removeGroup, &Filemanager::addGroup, &Filemanager::findMember, &Filemanager::editGroup, 
		&Filemanager::print, &Filemanager::printMembers, &Filemanager::printGroups, &Filemanager::removeMember, 
		&Filemanager::modifyMember, &Filemanager::addMember};
	while (input != 1) {
		(*a.*functionPointers[input-1])();
		input = in->readInput();
	}
 	delete a;
	delete in;
	std::cin.get();
	return 0;
}