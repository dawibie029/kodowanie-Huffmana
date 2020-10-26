#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "funkcje.h"


//	WARTO��I LICZBOWE W WEKTORZE KONWERTOWANE NA TABLICE INT�W - LEPIEJ ZROBI� NA STRINGI A POTEM S�OWA KODOWE POCIACHA� TYMI STRINGAMI
/**
	* Funkcja odczytuj�ca zawarto�� pliku tekstowego i zapisuj�ca j� w zmiennej
	* Parametry przekazywane przez referencj�
	* @param adres - adres pliku wej�ciowego
	* @param dane - wektor zawieraj�cy tablic� kod�w, oraz s�owa kodowe (na ostatniej pozycji)
	* @return - zwraca warto�� true, je�eli uda si� otworzy� plik. W przeciwnym wypadku wartosc false
*/
bool wczytaj(const std::string& adres, std::vector<std::string>& dane) {
	std::ifstream plikwe(adres);
	if (!plikwe.is_open())
		return false;
	while (!plikwe.eof()) {		//	p�tla maj�ca na celu podzielenie odczytanego tekstu na pojedyncze wyrazy oddzielone �rednikiem
		std::string napis;	//	tymczasowa zmienna pomocnicza, s�u��ca do zapisywania poszczeg�nych wyraz�w i przeniesienia ich do wektora dane
		getline(plikwe, napis, ';');
		dane.push_back(napis);
	}
	return true;
}
/**
	* Funkcja zapisuj�ca podany tekst w pliku tekstowym o wskazanym adresie
	* Parametry przekazywane przez referencje
	* @param adres - adres pliku wyj�ciowego
	* @param tekst - wektor zawieraj�cy dane, kt�re funckja zapisze w pliku wyj�ciowym
	* @return zwraca warto�� true, je�li funkcja zadzia�a prawid�owo lub warto�� false w razie niepowodzenia
*/
bool zapisz(const std::string& adres, const std::vector<std::string>& dane) {
	std::ofstream plikwy(adres);
	if (!plikwy.is_open())
		return false;
	for (std::string a : dane)	//	P�tla maj�ca na celu zapisanie do pliku tekstowego warto�ci wektora dane rozdzielonych �rednikami
		plikwy << a << ';';	
	return true;
}
/**
	* Funkcja konwertuj�ca uzyskany wektor z danymi na dwie tablice - znak�w i warto�ci oraz na zmienn� zawieraj�c� s�owa kodowe
	* Parametry .. . . . . . .. . . . .. . .
	* @param dane - wektor zawieraj�cy tablic� kod�w oraz s�owa kodowe
	* @param znaki - tablica kod�w zawieraj�ca znaki
	* @param warto�ci - tablica warto�ci przypisanych do odpowiadaj�cych im znak�w
	* @param kod - ci�g s��w kodowych
*/
void konwertuj(const std::vector<std::string>& dane, std::vector<std::string>& znaki, std::vector<std::string>& wartosci, std::string& kod) {
	for (int i = 0; i < dane.size() - 1; i += 2) {	//	P�tla przepisuj�ca warto�ci z wektora dane do dw�ch wektor�w w spos�b wynikaj�cy ze sposobu
		znaki[i] = dane[i];							//	zapisu w tym wektorze - na przemian znak i odpowiadaj�cy mu kod binarny (zawsze liczba parzysta).
		wartosci[i] = dane[i + 1];					//	Po wykonaniu p�tli zawsze zostaje jeden element - jest nim zakodowane zdanie
	}
	kod = dane[-1];
}