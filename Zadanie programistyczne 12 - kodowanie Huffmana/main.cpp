#include <iostream>
#include <vector>
#include "funkcje.h"

int main(int argc, char* argv[]) {
	std::vector<std::string> vec;
	read("C:/Users/Dawid/Desktop/test1.txt", vec);
	for (auto a : vec) {
		std::cout << a << std::endl;
	}
	save("C:/Users/Dawid/Desktop/test2.txt", vec);
}