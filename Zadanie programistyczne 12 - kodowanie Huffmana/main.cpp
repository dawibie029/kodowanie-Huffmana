#include <iostream>
#include <vector>
#include "funkcje_model.h"

int main(int argc, char* argv[]) {
	std::vector<std::string> vec;
	read("C:/Users/Dawid/Desktop/test1.txt", vec);
	for (auto a : vec) {
		std::cout << a << std::endl;
	}
	std::vector< std::string> znaki;
	std::vector< std::string> wartosci;
	std::string kod;
	convert(vec, znaki, wartosci, kod);
	save("C:/Users/Dawid/Desktop/test2.txt", vec);
	for (int i = 0; i < wartosci.size(); i++) {
		std::cout << znaki[i] << ": " << wartosci[i] << std::endl;
	}
	std::cout << kod << std::endl;
}