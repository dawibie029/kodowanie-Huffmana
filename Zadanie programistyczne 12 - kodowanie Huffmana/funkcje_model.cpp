#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
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
std::pair<std::string, int> znajdz_najmniejszy_string(std::vector<std::pair<std::string, int>>& ilosci_sumy_znakow, const int& numer_wyrazu_od_konca) {

	sort(ilosci_sumy_znakow.begin(), ilosci_sumy_znakow.end(), [](std::pair<std::string, int> a, std::pair<std::string, int> b) {return a.second < b.second; });
	return ilosci_sumy_znakow[ilosci_sumy_znakow.size() - 1 - numer_wyrazu_od_konca];
}
void zakoduj(const std::string& uncoded_data) {
	std::map<char, int> ilosci_znakow_mapa = policz_znaki(uncoded_data);
	std::vector<std::pair<char, int>> ilosci_znakow = konwertuj_na_wektor(ilosci_znakow_mapa);
	std::vector<std::pair<std::string, int>> ilosci_sumy_znakow;
	std::pair<std::string, int> zmienna_pomocnicza;
	zmienna_pomocnicza.first.push_back(ilosci_znakow[0].first);	// wektor ilosci_znakow jest uporz¹dkowany, wiêc pierwsze dwa wyrazy w ka¿dym przypadku bêd¹
	zmienna_pomocnicza.first.push_back(ilosci_znakow[1].first);	// siê ³¹czyæ w drzewie
	zmienna_pomocnicza.second = ilosci_znakow[0].second + ilosci_znakow[1].second;
	ilosci_sumy_znakow.push_back(zmienna_pomocnicza);

	for (int i = 2; i < ilosci_znakow.size(); i++) {
		std::pair<std::string, int> help1 = znajdz_najmniejszy_string(ilosci_sumy_znakow, 0);
		if (ilosci_znakow[i].second <= help1.second && ilosci_znakow[i + 1].second <= help1.second) {
			std::pair<std::string, int> zmienna_pomocnicza;
			zmienna_pomocnicza.first.push_back(ilosci_znakow[i].first);
			zmienna_pomocnicza.first.push_back(ilosci_znakow[i + 1].first);
			zmienna_pomocnicza.second = ilosci_znakow[i].second + ilosci_znakow[1].second;
			ilosci_sumy_znakow.push_back(zmienna_pomocnicza);
		}
	}
}
std::vector<std::pair<char, int>> konwertuj_na_wektor(std::map<char, int>& ilosci_znakow_mapa) {
	std::vector<std::pair<char, int>> ilosci_znakow_wektor(ilosci_znakow_mapa.begin(), ilosci_znakow_mapa.end());
	sort(ilosci_znakow_wektor.begin(), ilosci_znakow_wektor.end(), [](std::pair<char, int> a, std::pair<char, int> b) {return a.second < b.second; });
	ilosci_znakow_mapa.clear();
	return ilosci_znakow_wektor;
}