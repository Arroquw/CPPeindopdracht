#include "Filemanager.h"
#include <fstream>
#include <algorithm>
#include <regex>
#include <iostream>


Filemanager::Filemanager(std::string memberpath, std::string grouppath) {
	readMemberFile(memberpath);
	readGroupFile(grouppath);
}

Filemanager::Filemanager(const Filemanager & other) :
	amount_groups(other.amount_groups), amount_members(other.amount_members),
	groups(new AthleticGroup2[other.amount_groups]), members(new AthleticsMember[other.amount_members]) {
	std::copy(other.members, other.members + amount_members, members);
	std::copy(other.groups, other.groups + amount_groups, groups);
}

Filemanager::Filemanager(Filemanager && other) : amount_groups(0), amount_members(0), members(nullptr), groups(nullptr) {
	*this = std::move(other);
}

Filemanager & Filemanager::operator=(const Filemanager &other) {
	if (this != &other) {
		delete[] members;
		delete[] groups;
		amount_groups = other.amount_groups;
		amount_members = other.amount_members;
		members = new AthleticsMember[amount_members];
		groups = new AthleticGroup2[amount_groups];
		std::copy(other.members, other.members + amount_members, members);
		std::copy(other.groups, other.groups + amount_groups, groups);
	}
	return *this;
}

Filemanager & Filemanager::operator=(Filemanager &&other) {
	if (this != &other) {
		delete[] members;
		delete[] groups;
		members = other.members;
		groups = other.groups;
		amount_groups = other.amount_groups;
		amount_members = other.amount_members;
		other.amount_groups = 0;
		other.amount_members = 0;
		other.members = nullptr;
		other.groups = nullptr;
	}
	return *this;
}

int Filemanager::findIndex(int ID, int sw) {
	unsigned int i;
	for (i = 0; i != amount_members; i++) {
		if (members[i].getID() == ID) {
			break;
		}
	}
	if (i == amount_members) {
		return -1;
	}
	else {
		if (sw) {
			printMember(i);
			return i;
		}
		else
			return i;
	}
}

void Filemanager::findName(std::string name) {
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	unsigned i = 0;
	bool found = false;
	for (; i != amount_members; i++) {
		std::string tmp = members[i].getName();
		std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
		if (tmp.find(name) != std::string::npos) {
			printMember(i);
			found = true;
		}
	}
	if (!found) {
		std::cout << "Name not found!" << std::endl;
	}
}

void Filemanager::findAge(int age) {
	unsigned i = 0;
	bool found = false;
	for (; i != amount_members; i++) {
		if (age == members[i].getAge()) {
			printMember(i);
			found = true;
		}
	}
	if (!found) {
		std::cout << "Name not found!" << std::endl;
	}
}

void Filemanager::printMember(unsigned index) {
	if (index > amount_members - 1 || index < 0) {
		index = 0;
	}
	std::cout << "name: " << members[index].getName() << "\nage: " << members[index].getAge() << "\nID: " << members[index].getID() << std::endl;
}

void Filemanager::findMember() {
	std::string input;
	std::cout << "Search for name: (N) ; Search for age: (A) ; Search for ID (I) ; Exit (X)" << std::endl;
	getline(std::cin, input);
	std::transform(input.begin(), input.end(), input.begin(), ::toupper);
	if (input == "N") {
		std::cout << "Enter the name or part of the name you would like to search for: " << std::endl;
		getline(std::cin, input);
		findName(input);
	}
	else if (input == "A") {
		std::cout << "Enter the age you would like to search for: " << std::endl;
		getline(std::cin, input);
		try {
			unsigned parse = std::stoi(input);
			if (parse > 150 || parse < 1) {
				throw - 1;
			}
			else
				findAge(parse);
		}
		catch (...) {
			std::cout << "Please enter a number between 1 and 150" << std::endl;
		}
	}
	else if (input == "I") {
		std::cout << "Enter the ID you would like to search for: " << std::endl;
		getline(std::cin, input);
		try {
			unsigned parse = std::stoi(input);
			if (parse > members[amount_members - 1].getID() || parse < 1) {
				throw - 1;
			}
			else
				findIndex(parse, 1);
		}
		catch (...) {
			std::cout << "Enter a valid number!" << std::endl;
		}
	}
	else if (input == "X") {
		return;
	}
	else {
		std::cout << "Enter one of the options given!" << std::endl;
		return findMember();
	}
}


void Filemanager::editGroup() {
	AthleticsMember *newArray1 = 0;
	unsigned int index;
	unsigned int newSize;
	std::string input;
	bool valid = false;
	printGroups();
	std::cout << "Enter the number of the group you would like to modify: " << std::endl;
	getline(std::cin, input);
	try {
		unsigned parse = std::stoi(input);
		if (parse >= amount_groups || parse < 0) {
			valid = false;
		}
		else {
			valid = true;
		}
	}
	catch (...) {
		std::cout << "Please type a number!" << std::endl;
		return editGroup();
	}
	if (valid) {
		index = std::stoi(input);
		std::cout << "Now editing group: " << groups[index].getName() << std::endl;
		newSize = groups[index].getAmount();
		std::cout << "Delete member from group: (D) ; Add member to group: (A) ; change groupname: (N) ; Delete group: (G) ; Exit (X)" << std::endl;
		getline(std::cin, input);
		std::transform(input.begin(), input.end(), input.begin(), ::toupper);
		if (input == "D") {
			try {
				newSize--;
				std::cout << "Enter the ID of the member you'd like to delete" << std::endl;
				getline(std::cin, input);
				unsigned parse = std::stoi(input);
				if (parse > members[amount_members - 1].getID() || parse < 0) {
					std::cout << "enter a valid ID!" << std::endl;
					return editGroup();
				}
				else {
					unsigned int deleted = groups[index].deleteMember(parse);
					if (deleted != -1) {
						std::cout << "Deleted member: " << deleted;
						findIndex(deleted, 1);
						std::cout << std::endl;
					}
				}
			}
			catch (...) {
				std::cout << "Please enter a number!" << std::endl;
				return editGroup();
			}
		}
		else if (input == "A") {
			std::string num = "st";
			std::cout << "Enter the amount of members you want to add" << std::endl;
			getline(std::cin, input);
			try {
				newSize += std::stoi(input);
				unsigned int oldSize = groups[index].getAmount();
				unsigned int nr;
				for (unsigned int k = oldSize; k < (unsigned)newSize; k++) {
					nr = (k - (oldSize - 1));
					if (nr == 1 || ((nr % 10) == 1 && nr != 11)) {
						num = "st";
					}
					else if (nr == 2 || ((nr % 10) == 2) && nr != 12) {
						num = "nd";
					}
					else if (nr == 3 || ((nr % 10) == 3) && nr != 13) {
						num = "rd";
					}
					else {
						num = "th";
					}
					if (std::stoi(input) > 1) {
						std::cout << "Enter the ID of the " << nr << num << " member you would like to add" << std::endl;
					}
					else {
						std::cout << "Enter the ID of the member you would like to add" << std::endl;
					}
					getline(std::cin, input);
					unsigned parse = std::stoi(input);
					if (parse > members[amount_members - 1].getID() || parse < 0) {
						std::cout << "enter a valid ID!" << std::endl;
						return editGroup();
					}
					else {
						int a = findIndex(parse, 0);
						groups[index].addMember(members[a]);
					}
				}
			}
			catch (...) {
				std::cout << "Please enter a number!" << std::endl;
				return editGroup();
			}
		}
		else if (input == "N") {
			std::cout << "Enter new groupname: " << std::endl;
			getline(std::cin, input);
			bool contains_non_alpha = std::regex_match(input, std::regex("^[A-Za-z][A-Za-z0-9]*(?:_?-?/?[A-Za-z0-9]+)*$"));
			if (!contains_non_alpha) {
				std::cout << "Please note that the groupname has to start with a letter and end with a letter or number, and only allows underscores as special characters." << std::endl;
				std::cout << "Press enter to continue" << std::endl;
				std::cin.get();
				return editGroup();
			}
			else
				groups[index].setName(input);
		}
		else if (input == "X") {
			return;
		}
		else {
			std::cout << "Enter something that's given on the list! Press enter to continue" << std::endl;
			std::cin.get();
			return editGroup();
		}

	}
	else {
		std::cout << "The group you entered does not exist! Please try again." << std::endl;
		return editGroup();
	}
}

void Filemanager::addMember() {
	std::string input;
	std::string num;
	AthleticsMember *newArray = 0;
	unsigned oldSize = amount_members;
	std::cout << "Enter the amount of members you want to add" << std::endl;
	getline(std::cin, input);
	try {
		unsigned parse = std::stoi(input);
		unsigned newSize = oldSize;
		newSize += parse; //no need to set amount because amount is incremented in groups->addMember
		unsigned nr;
		for (unsigned k = oldSize; k < newSize; k++) {
			nr = (k - (oldSize - 1));
			if (nr == 1 || ((nr % 10) == 1 && nr != 11)) {
				num = "st";
			}
			else if (nr == 2 || ((nr % 10) == 2) && nr != 12) {
				num = "nd";
			}
			else if (nr == 3 || ((nr % 10) == 3) && nr != 13) {
				num = "rd";
			}
			else {
				num = "th";
			}
			amount_members++;
			try {
				newArray = new AthleticsMember[amount_members];
				if (parse > 1) {
					std::cout << "Enter the name of the " << nr << num << " member you would like to add" << std::endl;
					getline(std::cin, input);
					newArray[amount_members - 1].setName(input);
					std::cout << "Enter the age of the " << nr << num << " new member: " << std::endl;
					getline(std::cin, input);
				}
				else {
					std::cout << "Enter the name of your new member: " << std::endl;
					getline(std::cin, input);
					newArray[amount_members - 1].setName(input);
					std::cout << "Enter the age of your new member: " << std::endl;
					getline(std::cin, input);
				}
				unsigned parse = std::stoi(input);
				if (parse > 150 || parse < 1) {
					newArray[amount_members - 1].setAge(20);
					throw - 1;
				}
				else
					newArray[amount_members - 1].setAge(std::stoi(input));
			}
			catch (...) {
				std::cout << "Please enter a number between 1 and 150! Setting age to 20. Press enter to continue" << std::endl;
				std::cin.get();
				return editGroup();
			}
			newArray[amount_members - 1].setID(amount_members);
			for (unsigned int i = 0; i < amount_members - 1; i++) {
				newArray[i] = members[i];
			}
			delete[] members;
			members = newArray;
		}
	}
	catch (...) {
		std::cout << "Please enter a number!" << std::endl;
		return;
	}
}

void Filemanager::removeMember() {
	std::string input;
	std::cout << "Enter the ID of the member you would like to delete" << std::endl;
	getline(std::cin, input);
	try {
		unsigned parse = std::stoi(input);
		if (parse > members[amount_members - 1].getID() || parse < 0) {
			std::cout << "Please enter a valid ID!" << std::endl;
		}
		else {
			unsigned i = findIndex(parse, 0);
			if (i != -1) {
				int deleted = 0;
				for (unsigned n = 0; n < amount_groups; n++) {
					deleted = groups[n].deleteMember(parse);
					if (deleted > 0) {
						std::cout << "deleted member from group(s): " << groups[n].getName() << std::endl;
					}
				}
				AthleticsMember *newMembers = new AthleticsMember[amount_members];
				amount_members--;
				for (unsigned j = 0; j < amount_members + 1; j++) {
					newMembers[j] = members[j];
				}

				for (; i < amount_members; i++) {
					newMembers[i] = newMembers[i + 1];
				}
				delete[] this->members;
				members = newMembers;
			}
			else {
				std::cout << "Somehow ID is invalid, contact me!" << std::endl;
			}
		}
	}
	catch (...) {
		std::cout << "Please enter a number!" << std::endl;
	}
}

void Filemanager::modifyMember() {
	std::string input;
	std::cout << "Enter the ID of the member you'd like to modify" << std::endl;
	getline(std::cin, input);
	try {
		unsigned parse = std::stoi(input);
		if (parse > members[amount_members - 1].getID() || parse < 1) {
			std::cout << "please enter a valid ID" << std::endl;
		}
		else {
			std::cout << "Now editing member: " << std::endl;
			int found = findIndex(parse, 1);
			if (found != -1) {
				std::cout << "Modify name (N) ; Modify age (A)" << std::endl;
				getline(std::cin, input);
				std::transform(input.begin(), input.end(), input.begin(), ::toupper);
				if (input == "N") {
					std::cout << "Enter the new name for " << members[found].getName() << std::endl;
					getline(std::cin, input);
					members[found].setName(input);
					for (unsigned g = 0; g < amount_groups; g++) {
						groups[g].modifyMemberName(input, members[found].getID());
					}
				}
				else if (input == "A") {
					std::cout << "Enter the new age for " << members[found].getName() << std::endl;
					getline(std::cin, input);
					unsigned parsed = std::stoi(input);
					members[found].setAge(parsed);
					for (unsigned h = 0; h < amount_groups; h++) {
						groups[h].modifyMemberAge(parsed, members[found].getID());
					}
				}
				else {
					std::cout << "Enter one of the options!" << std::endl;
				}
			}
		}
	}
	catch (...) {
		std::cout << "Please enter a number" << std::endl;
		return modifyMember();
	}
}

void Filemanager::addGroup() {
	std::string input;
	amount_groups++;
	AthleticGroup2 *newGroups = new AthleticGroup2[amount_groups];
	for (unsigned m = 0; m < amount_groups - 1; m++) {
		newGroups[m] = groups[m];
	}
	std::cout << "Enter the name for your new group: " << std::endl;
	getline(std::cin, input);
	newGroups[amount_groups - 1].setName(input);
	std::cout << "Group " << input << " added!" << std::endl;
	delete[] groups;
	groups = newGroups;
}

void Filemanager::removeGroup() {
	std::string input;
	std::cout << "Enter the number of the group you would like to delete: " << std::endl;
	getline(std::cin, input);
	try {
		AthleticGroup2 *newGroups = new AthleticGroup2[amount_groups];
		for (unsigned j = 0; j < amount_groups; j++) {
			newGroups[j] = groups[j];
		}
		amount_groups--;
		unsigned i = std::stoi(input);
		std::cout << "Deleting group \"" << groups[i].getName() << "\"" << std::endl;
		for (i; i < amount_groups; i++) {
			newGroups[i] = newGroups[i + 1];
		}
		delete[] groups;
		groups = newGroups;
		std::cout << "Group successfully deleted!" << std::endl;
	}
	catch (...) {
		std::cout << "Enter a valid number!" << std::endl;
	}
}

void Filemanager::findGroup() {
	std::string input;
	std::cout << "Find group by member (M) ; Find group by groupname (G)" << std::endl;
	getline(std::cin, input);
	std::transform(input.begin(), input.end(), input.begin(), ::toupper);
	if (input == "M") {
		std::cout << "Enter the ID of the member you want to search the group for" << std::endl;
		getline(std::cin, input);
		std::string name;
		unsigned parse = std::stoi(input);
		int member = findIndex(parse, 0);
		if (member > -1) {
			name = members[member].getName();
			std::string tmp;
			bool found = false;
			for (unsigned i = 0; i < amount_groups; i++) {
				for (unsigned j = 0; j < groups[i].getAmount(); j++) {
					tmp = groups[i].getMembers()[j].getName();
					if (tmp.find(name) != std::string::npos) {
						std::cout << groups[i].getName() << std::endl;
						found = true;
					}
				}
			}
			if (!found) {
				std::cout << "Name not found in any of the groups!" << std::endl;
			}
		}
		else {
			std::cout << "ID not found!" << std::endl;
		}
	}
	else if (input == "G") {
		std::cout << "Enter part of the name of the group you would like to search for" << std::endl;
		getline(std::cin, input);
		input[0] = toupper(input[0]);
		std::string name1;
		bool found1 = false;
		for (unsigned n = 0; n < amount_groups; n++) {
			name1 = groups[n].getName();
			if (name1.find(input) != std::string::npos) {
				std::cout << "found group(s): " << name1 << std::endl;
				found1 = true;
			}
		}
		if (!found1) {
			std::cout << "No group was found with a name containing \"" << input << "\"" << std::endl;
		}
	}
	else {
		std::cout << "Enter something given on the list!" << std::endl;
	}
}


void Filemanager::readGroupFile(std::string path) {
	std::fstream file;
	file.open(path, std::fstream::in);
	std::string tmp;
	unsigned amount = 0;
	unsigned line = 0;
	size_t members_in_group = 0;
	bool groupN = false;
	std::string dummyLine;
	AthleticsMember *a = 0;
	if (file.is_open()) {
		getline(file, dummyLine);
		if (!this->amount_groups) {
			this->amount_groups = std::stoi(dummyLine);
			this->groups = new AthleticGroup2[amount_groups];
		}
		while (1) {
			getline(file, tmp);
			bool contains_non_alpha = !std::regex_match(tmp, std::regex("^[A-Za-z][A-Za-z0-9]*(?:_?-?/?[A-Za-z0-9]+)*$"));
			if (!contains_non_alpha) {
				if ((amount >= 0 && a != nullptr)) {
					groups[amount - 1].setMembers(a);
					line = 0;
				}
				amount++;
				groups[amount - 1].setName(tmp);
				groupN = true;
			}
			else if (groupN) {
				members_in_group = std::stoi(tmp);
				groups[amount - 1].setAmount(members_in_group);
				a = new AthleticsMember[members_in_group];
				groupN = false;
			}
			else {
				if (line < members_in_group) {
					if (members[std::stoi(tmp)].getName() != nullptr) {
						a[line] = members[std::stoi(tmp)];
						line++;
					}
				}
				if ((amount >= 0 && a != nullptr) && file.eof()) {
					groups[amount - 1].setMembers(a);
					line = 0;
					break;
				}
				else if (file.eof()) {
					break;
				}
			}
		}
		file.close();
		a = nullptr;
	}
	else {
		std::cout << "File \"" << path << "\" not found!" << std::endl;
		std::cout << "Enter correct file path: " << std::endl;
		getline(std::cin, tmp);
		return readGroupFile(tmp);
	}
	delete[] a;
}

void Filemanager::readMemberFile(std::string path) {
	std::fstream file;
	file.open(path, std::fstream::in);
	std::string tmp;
	unsigned amount = 0;
	unsigned line = 0;
	std::string dummyLine;
	if (file.is_open()) {
		getline(file, dummyLine);
		if (!amount_members) {
			int parse = std::stoi(dummyLine);
			if (parse > 0) {
				amount_members = parse;
				members = new AthleticsMember[amount_members];
			}
		}
		while (getline(file, tmp)) {
			if (!(line % 2) && tmp != "") {
				if (amount < amount_members) {
					amount++;
				}
				else { break; }
				members[amount - 1].setName(tmp);
				members[amount - 1].setID(amount);
			}
			else {
				if (tmp.find("jaar")) {
					tmp.resize(3);
					tmp.erase(tmp.find_last_not_of(" \n\r\t") + 1);
				}
				members[amount - 1].setAge(std::stoi(tmp));
			}
			line++;
		}
		file.close();
	}
	else {
		std::cout << "File \"" << path << "\" not found!" << std::endl;
		std::cout << "Enter correct file path: " << std::endl;
		getline(std::cin, tmp);
		return readMemberFile(tmp);
	}
}

void Filemanager::writeGroupFile(std::string path) {
	std::fstream file;
	file.open(path, std::fstream::out);
	if (file.is_open()) {
		file << amount_groups << std::endl;
		for (unsigned i = 0; i < amount_groups; i++) {
			file << groups[i].getName() << std::endl;
			file << groups[i].getAmount() << std::endl;
			for (unsigned j = 0; j < groups[i].getAmount(); j++) {
				if (i == amount_groups - 1 && j == (groups[i].getAmount() - 1)) {
					file << members[(groups[i].getMembers()[j].getID() - 1)].getID() - 1;
				}
				else {
					file << members[(groups[i].getMembers()[j].getID() - 1)].getID() - 1 << std::endl;
				}
			}
		}
		file.close();
	}
	else {
		std::cout << "File not found!" << std::endl;
	}
}

void Filemanager::writeMemberFile(std::string path) {
	std::fstream file;
	file.open(path, std::fstream::out);
	if (file.is_open()) {
		file.clear();
		file << amount_members << std::endl;
		for (unsigned i = 0; i < amount_members; i++) {
			file << members[i].getName() << std::endl;
			if (i < amount_members - 1) {
				file << members[i].getAge() << " jaar" << std::endl;
			}
			else file << members[i].getAge() << "jaar";
		}
		file.close();
	}
	else {
		std::cout << "file not found!";
	}
}

void Filemanager::printGroups() {
	std::cout << "Groups: " << std::endl;
	for (unsigned i = 0; i < amount_groups; i++) {
		std::cout << groups[i].getName() << "\nGroup number: " << i << std::endl;
		for (unsigned j = 0; j < groups[i].getAmount(); j++) {
			std::cout << "\t" << groups[i].getMembers()[j].getName() << ",  " << groups[i].getMembers()[j].getAge() << std::endl;
		}
	}
}

void Filemanager::printMembers() {
	std::cout << "Members: " << std::endl;
	for (unsigned int j = 0; j < amount_members; j++) {
		std::cout << "name: " << members[j].getName() << "\tage: " << members[j].getAge() << "\tID: " << members[j].getID() << std::endl;
	}
}

void Filemanager::print() {
	std::cout << "Groups: " << std::endl;
	for (unsigned int i = 0; i < amount_groups; i++) {
		std::cout << groups[i].getName() << std::endl;
		for (unsigned int j = 0; j < groups[i].getAmount(); j++) {
			std::cout << "\t" << groups[i].getMembers()[j].getName() << ",\t" << groups[i].getMembers()[j].getAge() << std::endl;
		}
	}
	std::cout << "---------------------";
	std::cout << "\nMembers: " << std::endl;
	for (unsigned int j = 0; j < amount_members; j++) {
		std::cout << "name: " << members[j].getName() << "\tage: " << members[j].getAge() << "\tID: " << members[j].getID() << std::endl;
	}
}

Filemanager::~Filemanager() {
	writeMemberFile("memberfile.txt");
	writeGroupFile("groupfile.txt");
	delete[] this->groups;
	delete[] this->members;
	members = nullptr;
	groups = nullptr;
}