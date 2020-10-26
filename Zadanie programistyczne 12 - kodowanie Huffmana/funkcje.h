#ifndef FUNKCJE_H
#define FUNKCJE_H

bool read(const std::string& adres, std::vector<std::string>& dane);
bool save(const std::string& adres, const std::vector<std::string>& dane);
void convert(const std::vector<std::string>& dane, std::vector<std::string>& znaki, std::vector<std::string>& wartosci, std::string& kod);
#endif