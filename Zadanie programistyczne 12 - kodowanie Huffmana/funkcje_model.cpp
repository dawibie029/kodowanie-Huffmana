#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "funkcje_model.h"

/**
	* Funkcja odczytuj¹ca zawartoœæ pliku tekstowego i zapisuj¹ca j¹ w zmiennej
	* Parametry przekazywane przez referencjê
	* @param adres - adres pliku wejœciowego
	* @param dane - wektor zawieraj¹cy tablicê kodów, oraz s³owa kodowe (na ostatniej pozycji)
	* @return - zwraca wartoœæ true, je¿eli uda siê otworzyæ plik. W przeciwnym wypadku wartosc false
*/
bool read(const std::string& adres, std::vector<std::string>& dane) {
	std::ifstream plikwe(adres);
	if (!plikwe.is_open())
		return false;
	while (!plikwe.eof()) {		//	pêtla maj¹ca na celu podzielenie odczytanego tekstu na pojedyncze wyrazy oddzielone œrednikiem
		std::string napis;	//	tymczasowa zmienna pomocnicza, s³u¿¹ca do zapisywania poszczegó³nych wyrazów i przeniesienia ich do wektora dane
		getline(plikwe, napis, ';');
		dane.push_back(napis);
	}
	return true;
}
/**
	* Funkcja zapisuj¹ca podany tekst w pliku tekstowym o wskazanym adresie
	* Parametry przekazywane przez referencje
	* @param adres - adres pliku wyjœciowego
	* @param tekst - wektor zawieraj¹cy dane, które funckja zapisze w pliku wyjœciowym
	* @return zwraca wartoœæ true, jeœli funkcja zadzia³a prawid³owo lub wartoœæ false w razie niepowodzenia
*/
bool save(const std::string& adres, const std::vector<std::string>& dane) {
	std::ofstream plikwy(adres);
	if (!plikwy.is_open())
		return false;
	for (std::string a : dane)	//	Pêtla maj¹ca na celu zapisanie do pliku tekstowego wartoœci wektora dane rozdzielonych œrednikami
		plikwy << a << ';';	
	return true;
}
/**
	* Funkcja konwertuj¹ca uzyskany wektor z danymi na dwie tablice - znaków i wartoœci oraz na zmienn¹ zawieraj¹c¹ s³owa kodowe
	* Parametry .. . . . . . .. . . . .. . .
	* @param dane - wektor zawieraj¹cy tablicê kodów oraz s³owa kodowe
	* @param znaki - tablica kodów zawieraj¹ca znaki
	* @param wartoœci - tablica wartoœci przypisanych do odpowiadaj¹cych im znaków
	* @param kod - ci¹g s³ów kodowych
*/
void convert(const std::vector<std::string>& dane, std::vector<std::string>& znaki, std::vector<std::string>& wartosci, std::string& kod) {
	for (std::size_t i = 0; i < dane.size() - 1; i += 2) {	//	Pêtla przepisuj¹ca wartoœci z wektora dane do dwóch wektorów w sposób wynikaj¹cy ze sposobu
		znaki.push_back(dane[i]);							//	zapisu w tym wektorze - na przemian znak i odpowiadaj¹cy mu kod binarny (zawsze liczba parzysta).
		wartosci.push_back(dane[i + 1]);					//	Po wykonaniu pêtli zawsze zostaje jeden element - jest nim zakodowane zdanie
	}
	kod = dane.back();
}