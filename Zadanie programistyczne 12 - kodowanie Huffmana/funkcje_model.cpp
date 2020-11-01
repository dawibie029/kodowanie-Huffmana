#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "funkcje_model.h"

/**
	* Funkcja odczytuj�ca zawarto�� pliku tekstowego i zapisuj�ca j� w zmiennej
	* Parametry przekazywane przez referencj�
	* @param adres - adres pliku wej�ciowego
	* @param dane - wektor zawieraj�cy tablic� kod�w, oraz s�owa kodowe (na ostatniej pozycji)
	* @return - zwraca warto�� true, je�eli uda si� otworzy� plik. W przeciwnym wypadku wartosc false
*/
/*bool read(const std::string& adres, std::vector<std::string>& dane) {
	std::ifstream plikwe(adres);
	if (!plikwe.is_open())
		return false;
	while (!plikwe.eof()) {		//	p�tla maj�ca na celu podzielenie odczytanego tekstu na pojedyncze wyrazy oddzielone �rednikiem
		std::string napis;	//	tymczasowa zmienna pomocnicza, s�u��ca do zapisywania poszczeg�nych wyraz�w i przeniesienia ich do wektora dane
		getline(plikwe, napis, ';');
		dane.push_back(napis);
	}
	return true;
}*/
/**
	* Funkcja wczytuj�ca zawarto�� pliku tekstowego zapisanego w formacie: s�owa_kodowe;znak,wartosc,znak,wartosc...
	* Znaki i odpowiadaj�ce im kody s� zapisywane w zmiennej mapa_wartosci, a zakodowane dane w zmiennej slowa_kodowe
	* Parametry przekazywane przez referencj�
	* @param adres - adres pliku wej�ciowego
	* @param mapa_wartosci - mapa, w kt�rej zapisane zostan� znaki i odpowiadaj�ce im kody
	* @param slowa_kodowe - zmienna, w kt�rej zapisana zostanie zakodowana wiadomo��
	* @return - zwraca warto�� true, je�eli uda si� otworzy� plik. W przeciwnym wypadku wartosc false
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
		plikwe.get();	//	Pomija symbol oddzielaj�cy znaki od definicji (dla pliku wej�ciowego dowolny, domy�lnie (oraz w pliku wyj�ciowym) u�ywany jest przecinek)
		getline(plikwe, wartosc, ',');	//	Wczytuje warto�� znaku wczytanego w linijce wy�ej. Oddzielaj�c kod od nast�pnego znaku konieczne jest ju� u�ycie przecinka.
		mapa_wartosci[znak] = wartosc;
	}
	return true;
}

/**
	* Funkcja zapisuj�ca podany tekst w pliku tekstowym o wskazanym adresie
	* Parametry przekazywane przez referencje
	* @param adres - adres pliku wyj�ciowego
	* @param mapa_wartosci - mapa zawieraj�ca pary znak-warto��
	* @param slowa_kodowe - zmienna zawieraj�ca zakodowan� wiadomo��
	* @return zwraca warto�� true, je�li funkcja zadzia�a prawid�owo lub warto�� false w razie niepowodzenia
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
	for (std::string a : dane)	//	P�tla maj�ca na celu zapisanie do pliku tekstowego warto�ci wektora dane rozdzielonych �rednikami
		plikwy << a << ';';	
	return true;
}*/
/**
	* Funkcja konwertuj�ca uzyskany wektor z danymi na dwie tablice - znak�w i warto�ci oraz na zmienn� zawieraj�c� s�owa kodowe
	* Parametry przekazywane przez referencje
	* @param dane - wektor zawieraj�cy tablic� kod�w oraz s�owa kodowe
	* @param znaki - tablica kod�w zawieraj�ca znaki
	* @param warto�ci - tablica warto�ci przypisanych do odpowiadaj�cych im znak�w
	* @param kod - ci�g s��w kodowych
*/
/*void convert(const std::vector<std::string>& dane, std::vector<std::string>& znaki, std::vector<std::string>& wartosci, std::string& kod) {
	for (std::size_t i = 0; i < dane.size() - 1; i += 2) {	//	P�tla przepisuj�ca warto�ci z wektora dane do dw�ch wektor�w w spos�b wynikaj�cy ze sposobu
		znaki.push_back(dane[i]);							//	zapisu w tym wektorze - na przemian znak i odpowiadaj�cy mu kod binarny (zawsze liczba parzysta).
		wartosci.push_back(dane[i + 1]);					//	Po wykonaniu p�tli zawsze zostaje jeden element - jest nim zakodowane zdanie
	}
	kod = dane.back();
}*/
/**
	* Funkcja konwertuj�ca wektory znaki i dane oraz zakodowany tekst na jeden wektor w formacie gotowym do zapisu jako plik tekstowy
	* Parametry przekazywane przez referencje
	* @param dane - wektor zawieraj�cy tablic� kod�w oraz s�owa kodowe
	* @param znaki - tablica kod�w zawieraj�ca znaki
	* @param warto�ci - tablica warto�ci przypisanych do odpowiadaj�cych im znak�w
	* @param kod - ci�g s��w kodowych
*/
/*void convert_back(std::vector<std::string>& dane, const std::vector<std::string>& znaki, const std::vector<std::string>& wartosci, const std::string& kod) {
	dane.clear();	// dla upewnienia si�, �e wektor dane jest pusty.
	for (std::size_t i = 0; i < wartosci.size(); i++) {
		dane.push_back(znaki[i]);
		dane.push_back(znaki[i + 1]);
	}
	dane.push_back(kod);
}*/