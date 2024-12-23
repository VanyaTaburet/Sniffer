#ifndef SNIFFER_H
#define SNIFFER_H

#include <string>
#include <vector>

class SnifferMen {
public:
    int frame;
    std::string macAdr; // MAC-адрес

    SnifferMen(const int& frame, const std::string& macAdr); // Конструктор
};

// Функция для валидации пути к файлу
void validateFilePath(int argc, char* argv[]);

// Функция для парсинга файла и получения вектора объектов Men
std::vector<SnifferMen> parseFile(const std::string& filePath);

// Функция для сортировки вектора объектов Men по количеству фреймов
void sortMenVector(std::vector<SnifferMen>& menVector);

// Функция для печати информации обо всех объектах Men
void printMenVector(const std::vector<SnifferMen>& menVector);

#endif // SNIFFER_H

