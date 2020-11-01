#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
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
std::pair<std::string, int> znajdz_najmniejszy_string(std::vector<std::pair<std::string, int>>& ilosci_sumy_znakow, const int& numer_wyrazu_od_konca) {

	sort(ilosci_sumy_znakow.begin(), ilosci_sumy_znakow.end(), [](std::pair<std::string, int> a, std::pair<std::string, int> b) {return a.second < b.second; });
	return ilosci_sumy_znakow[ilosci_sumy_znakow.size() - 1 - numer_wyrazu_od_konca];
}
void zakoduj(const std::string& uncoded_data) {
	std::map<char, int> ilosci_znakow_mapa = policz_znaki(uncoded_data);
	std::vector<std::pair<char, int>> ilosci_znakow = konwertuj_na_wektor(ilosci_znakow_mapa);
	std::vector<std::pair<std::string, int>> ilosci_sumy_znakow;
	std::pair<std::string, int> zmienna_pomocnicza;
	zmienna_pomocnicza.first.push_back(ilosci_znakow[0].first);	// wektor ilosci_znakow jest uporz�dkowany, wi�c pierwsze dwa wyrazy w ka�dym przypadku b�d�
	zmienna_pomocnicza.first.push_back(ilosci_znakow[1].first);	// si� ��czy� w drzewie
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