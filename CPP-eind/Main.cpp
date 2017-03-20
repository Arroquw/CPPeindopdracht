#include "AthleticGroup.h"
#include "Athletics.h"

int main(int argc, char *argv[]) {
	AthleticGroup2 *a = new AthleticGroup2();
	a->readGroupFile(argv[1]);
	std::cin.get();
}