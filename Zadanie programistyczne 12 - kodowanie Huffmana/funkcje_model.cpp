#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "funkcje_model.h"

/**
	* Funkcja wczytuj�ca zawarto�� pliku tekstowego zapisanego w formacie: s�owa_kodowe;znak,wartosc,znak,wartosc...
	* Znaki i odpowiadaj�ce im kody s� zapisywane w zmiennej mapa_wartosci, a zakodowane dane w zmiennej slowa_kodowe
	* Parametry przekazywane przez referencj�
	* @param adres - adres pliku wej�ciowego
	* @param mapa_wartosci - mapa, w kt�rej zapisane zostan� znaki i odpowiadaj�ce im kody
	* @param slowa_kodowe - zmienna, w kt�rej zapisana zostanie zakodowana wiadomo��
	* @return - zwraca warto�� true, je�eli uda si� otworzy� plik. W przeciwnym wypadku wartosc false
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
		plikwe.get();	//	Pomija symbol oddzielaj�cy znaki od definicji (dla pliku wej�ciowego dowolny, domy�lnie (oraz w pliku wyj�ciowym) u�ywany jest przecinek)
		getline(plikwe, wartosc, ',');	//	Wczytuje warto�� znaku wczytanego w linijce wy�ej. Oddzielaj�c kod od nast�pnego znaku konieczne jest ju� u�ycie przecinka.
		mapa_wartosci[znak] = wartosc;
	}
	return true;
}

/**
	* Funkcja wczytuj�ca zawarto�� niezakodowanego pliku i zapisuj�ca jego tre��
	* Parametry przekazywane przez referencj�
	* @param adres - adres pliku wej�ciowego
	* @param uncoded_data - niezakodowany tekst
	* @return - zwraca warto�� true w przypadku powodzenia, lub false
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
	* Funkcja zapisuj�ca podany tekst w pliku tekstowym o wskazanym adresie
	* Parametry przekazywane przez referencje
	* @param adres - adres pliku wyj�ciowego
	* @param mapa_wartosci - mapa zawieraj�ca pary znak-warto��
	* @param slowa_kodowe - zmienna zawieraj�ca zakodowan� wiadomo��
	* @return zwraca warto�� true, je�li funkcja zadzia�a prawid�owo lub warto�� false w razie niepowodzenia
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