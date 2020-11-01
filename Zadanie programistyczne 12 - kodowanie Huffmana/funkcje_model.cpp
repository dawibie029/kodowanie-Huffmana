#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "funkcje_model.h"

/**
	* Funkcja wczytuj¹ca zawartoœæ pliku tekstowego zapisanego w formacie: s³owa_kodowe;znak,wartosc,znak,wartosc...
	* Znaki i odpowiadaj¹ce im kody s¹ zapisywane w zmiennej mapa_wartosci, a zakodowane dane w zmiennej slowa_kodowe
	* Parametry przekazywane przez referencjê
	* @param adres - adres pliku wejœciowego
	* @param mapa_wartosci - mapa, w której zapisane zostan¹ znaki i odpowiadaj¹ce im kody
	* @param slowa_kodowe - zmienna, w której zapisana zostanie zakodowana wiadomoœæ
	* @return - zwraca wartoœæ true, je¿eli uda siê otworzyæ plik. W przeciwnym wypadku wartosc false
*/
bool read_coded(const std::string& adres, std::map<char, std::string>& mapa_wartosci, std::string& kod){
	std::ifstream plikwe(adres);
	if (!plikwe.is_open())
		return false;
	getline(plikwe, kod, ';');	//*	odczytuje zakodowane slowa i zapisuje w zmiennej
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
	* Funkcja wczytuj¹ca zawartoœæ niezakodowanego pliku i zapisuj¹ca jego treœæ
	* Parametry przekazywane przez referencjê
	* @param adres - adres pliku wejœciowego
	* @param uncoded_data - niezakodowany tekst
	* @return - zwraca wartoœæ true w przypadku powodzenia, lub false
*/
bool read_uncoded(const std::string& adres, std::string& uncoded_data) {
	std::ifstream plikwe(adres);
	std::string zmienna_pomocnicza;
	if (plikwe.is_open()) {
		while (getline(plikwe, zmienna_pomocnicza)) {
			uncoded_data += zmienna_pomocnicza;
		}
		return true;
	}
	else
		return false;		
}
std::map<char, int> policz_znaki(const std::string& uncoded_data){
	std::map<char, int> ilosc_znakow;
	for (char znak : uncoded_data) {
		ilosc_znakow[znak]++;
	}
	return ilosc_znakow;
}
/**
	* Funkcja zapisuj¹ca podany tekst w pliku tekstowym o wskazanym adresie
	* Parametry przekazywane przez referencje
	* @param adres - adres pliku wyjœciowego
	* @param mapa_wartosci - mapa zawieraj¹ca pary znak-wartoœæ
	* @param slowa_kodowe - zmienna zawieraj¹ca zakodowan¹ wiadomoœæ
	* @return zwraca wartoœæ true, jeœli funkcja zadzia³a prawid³owo lub wartoœæ false w razie niepowodzenia
*/
bool save_coded(const std::string& adres, const std::map<char, std::string>& mapa_wartosci, const std::string& kod) {
	std::ofstream plikwy(adres);
	if (!plikwy.is_open())
		return false;
	plikwy << kod << ";";
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
char znajdz_najmniejszy_char(const std::map<char, int>& ilosc_znakow, const int& wyraz_poczatkowy) {
	int i = 0;
	std::pair<char, int> zmienna_pomocnicza;
	for (auto a : ilosc_znakow) {
		if (i++ == wyraz_poczatkowy) {
			zmienna_pomocnicza.first = a.first;
			zmienna_pomocnicza.second = a.second;
		}
		else if (i > wyraz_poczatkowy) {
			if (a.first < zmienna_pomocnicza.first) {
				zmienna_pomocnicza.first = a.first;
				zmienna_pomocnicza.second = a.second;
			}
		}
	}
	return zmienna_pomocnicza.first;
}
std::string znajdz_najmniejszy_string(const std::map<std::string, int>& suma_ilosci_znakow, const int& wyraz_poczatkowy) {
	int i = 0;
	std::pair<std::string, int> zmienna_pomocnicza;
	for (auto a : suma_ilosci_znakow) {
		if (i++ == wyraz_poczatkowy) {
			zmienna_pomocnicza.first = a.first;
			zmienna_pomocnicza.second = a.second;
		}
		else if (i > wyraz_poczatkowy) {
			if (a.first < zmienna_pomocnicza.first) {
				zmienna_pomocnicza.first = a.first;
				zmienna_pomocnicza.second = a.second;
			}
		}
	}
	return zmienna_pomocnicza.first;
}
void zakoduj(const std::string& uncoded_data) {
	std::map<char, int> ilosc_znakow = policz_znaki(uncoded_data);

}