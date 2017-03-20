#include "AthleticGroup.h"
#include <fstream>
#include <iostream>
#include <string>

void AthleticGroup2::readGroupFile(std::string path) {
	std::fstream file;
	file.open(path);
	std::string tmp;
	if (file.is_open()) {
		while (getline(file, tmp)) {
			
			amount++;
			std::cout << name << std::endl;
		}
	}
	else exit(404);
}

AthleticGroup2::~AthleticGroup2() {
	delete name;
	delete members;
}

AthleticGroup2::AthleticGroup2() {

}
