#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "funkcje_model.h"

/**
	* Funkcja odczytuj¹ca zawartoœæ pliku tekstowego i zapisuj¹ca j¹ w zmiennej
	* Parametry przekazywane przez referencjê
	* @param adres - adres pliku wejœciowego
	* @param dane - wektor zawieraj¹cy tablicê kodów, oraz s³owa kodowe (na ostatniej pozycji)
	* @return - zwraca wartoœæ true, je¿eli uda siê otworzyæ plik. W przeciwnym wypadku wartosc false
*/
/*bool read(const std::string& adres, std::vector<std::string>& dane) {
	std::ifstream plikwe(adres);
	if (!plikwe.is_open())
		return false;
	while (!plikwe.eof()) {		//	pêtla maj¹ca na celu podzielenie odczytanego tekstu na pojedyncze wyrazy oddzielone œrednikiem
		std::string napis;	//	tymczasowa zmienna pomocnicza, s³u¿¹ca do zapisywania poszczegó³nych wyrazów i przeniesienia ich do wektora dane
		getline(plikwe, napis, ';');
		dane.push_back(napis);
	}
	return true;
}*/
/**
	* Funkcja wczytuj¹ca zawartoœæ pliku tekstowego zapisanego w formacie: s³owa_kodowe;znak,wartosc,znak,wartosc...
	* Znaki i odpowiadaj¹ce im kody s¹ zapisywane w zmiennej mapa_wartosci, a zakodowane dane w zmiennej slowa_kodowe
	* Parametry przekazywane przez referencjê
	* @param adres - adres pliku wejœciowego
	* @param mapa_wartosci - mapa, w której zapisane zostan¹ znaki i odpowiadaj¹ce im kody
	* @param slowa_kodowe - zmienna, w której zapisana zostanie zakodowana wiadomoœæ
	* @return - zwraca wartoœæ true, je¿eli uda siê otworzyæ plik. W przeciwnym wypadku wartosc false
*/
bool read_coded(const std::string& adres, std::map<char, std::string>& mapa_wartosci, std::string& slowa_kodowe){
	std::ifstream plikwe(adres);
	if (!plikwe.is_open())
		return false;
	getline(plikwe, slowa_kodowe, ';');	//*	odczytuje zakodowane slowa i zapisuje w zmiennej
	while (!plikwe.eof()) {		
		char znak;
		std::string wartosc;
		plikwe.get(znak);	//*Pobiera znak
		plikwe.get();	//	Pomija symbol oddzielaj¹cy znaki od definicji (dla pliku wejœciowego dowolny, domyœlnie (oraz w pliku wyjœciowym) u¿ywany jest przecinek)
		getline(plikwe, wartosc, ',');	//	Wczytuje wartoœæ znaku wczytanego w linijce wy¿ej. Oddzielaj¹c kod od nastêpnego znaku konieczne jest ju¿ u¿ycie przecinka.
		mapa_wartosci[znak] = wartosc;
	}
	return true;
}

/**
	* Funkcja zapisuj¹ca podany tekst w pliku tekstowym o wskazanym adresie
	* Parametry przekazywane przez referencje
	* @param adres - adres pliku wyjœciowego
	* @param mapa_wartosci - mapa zawieraj¹ca pary znak-wartoœæ
	* @param slowa_kodowe - zmienna zawieraj¹ca zakodowan¹ wiadomoœæ
	* @return zwraca wartoœæ true, jeœli funkcja zadzia³a prawid³owo lub wartoœæ false w razie niepowodzenia
*/
bool save_coded(const std::string& adres, const std::map<char, std::string>& mapa_wartosci, const std::string& slowa_kodowe) {
	std::ofstream plikwy(adres);
	if (!plikwy.is_open())
		return false;
	plikwy << slowa_kodowe << ";";
	int i = 0;
	for (auto a : mapa_wartosci) {
		if (i++ != 0) {
			plikwy << ',' << a.first << ',' << a.second;	
		}
		else {
			plikwy << a.first << ',' << a.second;
		}
	}
	return true;
}

/*bool save(const std::string& adres, const std::vector<std::string>& dane) {
	std::ofstream plikwy(adres);
	if (!plikwy.is_open())
		return false;
	for (std::string a : dane)	//	Pêtla maj¹ca na celu zapisanie do pliku tekstowego wartoœci wektora dane rozdzielonych œrednikami
		plikwy << a << ';';	
	return true;
}*/
/**
	* Funkcja konwertuj¹ca uzyskany wektor z danymi na dwie tablice - znaków i wartoœci oraz na zmienn¹ zawieraj¹c¹ s³owa kodowe
	* Parametry przekazywane przez referencje
	* @param dane - wektor zawieraj¹cy tablicê kodów oraz s³owa kodowe
	* @param znaki - tablica kodów zawieraj¹ca znaki
	* @param wartoœci - tablica wartoœci przypisanych do odpowiadaj¹cych im znaków
	* @param kod - ci¹g s³ów kodowych
*/
/*void convert(const std::vector<std::string>& dane, std::vector<std::string>& znaki, std::vector<std::string>& wartosci, std::string& kod) {
	for (std::size_t i = 0; i < dane.size() - 1; i += 2) {	//	Pêtla przepisuj¹ca wartoœci z wektora dane do dwóch wektorów w sposób wynikaj¹cy ze sposobu
		znaki.push_back(dane[i]);							//	zapisu w tym wektorze - na przemian znak i odpowiadaj¹cy mu kod binarny (zawsze liczba parzysta).
		wartosci.push_back(dane[i + 1]);					//	Po wykonaniu pêtli zawsze zostaje jeden element - jest nim zakodowane zdanie
	}
	kod = dane.back();
}*/
/**
	* Funkcja konwertuj¹ca wektory znaki i dane oraz zakodowany tekst na jeden wektor w formacie gotowym do zapisu jako plik tekstowy
	* Parametry przekazywane przez referencje
	* @param dane - wektor zawieraj¹cy tablicê kodów oraz s³owa kodowe
	* @param znaki - tablica kodów zawieraj¹ca znaki
	* @param wartoœci - tablica wartoœci przypisanych do odpowiadaj¹cych im znaków
	* @param kod - ci¹g s³ów kodowych
*/
/*void convert_back(std::vector<std::string>& dane, const std::vector<std::string>& znaki, const std::vector<std::string>& wartosci, const std::string& kod) {
	dane.clear();	// dla upewnienia siê, ¿e wektor dane jest pusty.
	for (std::size_t i = 0; i < wartosci.size(); i++) {
		dane.push_back(znaki[i]);
		dane.push_back(znaki[i + 1]);
	}
	dane.push_back(kod);
}*/