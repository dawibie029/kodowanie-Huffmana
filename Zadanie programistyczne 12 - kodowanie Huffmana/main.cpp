#include <iostream>
#include <vector>
#include "funkcje.h"

int main(int argc, char* argv[]) {
	std::vector<std::string> vec;
	wczytaj("C:/Users/Dawid/Desktop/test1.txt", vec);
	for (auto a : vec) {
		std::cout << a << std::endl;
	}
	zapisz("C:/Users/Dawid/Desktop/test2.txt", vec);
}