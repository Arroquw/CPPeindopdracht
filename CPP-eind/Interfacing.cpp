#include "Interfacing.h"
#include <iostream>
#include <string>
#include <algorithm>

void ClubInterface::printInterface() {
	std::cout << ("___________________________________\n") << std::endl;
	std::cout << ("Make a choice:			---") << std::endl;
	std::cout << ("(A) Add member  		---") << std::endl;
	std::cout << ("(M) Modify member		---") << std::endl;
	std::cout << ("(R) Remove member		---") << std::endl;
	std::cout << ("(P) Print everything		---") << std::endl;
	std::cout << ("(1) Print members		---") << std::endl;
	std::cout << ("(2) Print groups			---") << std::endl;
	std::cout << ("(E) Edit group			---") << std::endl;
	std::cout << ("(F) Find member			---") << std::endl;
	std::cout << ("(G) Add group			---") << std::endl;
	std::cout << ("(T) Remove group		---") << std::endl;
	std::cout << ("(H) find group			---") << std::endl;
	std::cout << ("(X) Save & exit			---") << std::endl;
	std::cout << ("___________________________________") << std::endl;
	std::cout << std::endl;;
}

int ClubInterface::readInput() {
	printInterface();
	std::string str;
	getline(std::cin, str);
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	switch (str[0]) {
	case 'X': return 1; break;
	case 'H': return 2; break;
	case 'T': return 3; break;
	case 'G': return 4; break;
	case 'F': return 5; break;
	case 'E': return 6; break;
	case 'P': return 7; break;
	case '1': return 8; break;
	case '2': return 9; break;
	case 'R': return 10; break;
	case 'M': return 11; break;
	case 'A': return 12; break;
	default: return -1; break;
	}
}

