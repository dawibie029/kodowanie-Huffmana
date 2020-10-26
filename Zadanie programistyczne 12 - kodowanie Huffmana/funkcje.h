#ifndef FUNKCJE_H
#define FUNKCJE_H

bool wczytaj(const std::string& adres, std::vector<std::string>& dane);
bool zapisz(const std::string& adres, const std::vector<std::string>& dane);
void konwertuj(const std::vector<std::string> dane, std::string znaki[], std::string wartosci[], std::string kod);
#endif