#ifndef SNIFFER_H
#define SNIFFER_H

#include <string>
#include <vector>

// Класс для хранения информации о MAC-адресе и количестве фреймов
class Men {
public:
    int frame; // Количество фреймов
    std::string macAdr; // MAC-адрес

    Men(const int& frame, const std::string& macAdr); // Конструктор

    void printInfo() const; // Функция для вывода информации о MAC-адресе и фреймах
};

// Функция для валидации пути к файлу
void validateFilePath(int argc, char* argv[]);

// Функция для парсинга файла и получения вектора объектов Men
std::vector<Men> parseFile(const std::string& filePath);

// Функция для сортировки вектора объектов Men по количеству фреймов
void sortMenVector(std::vector<Men>& menVector);

// Функция для печати информации обо всех объектах Men
void printMenVector(const std::vector<Men>& menVector);

#endif // SNIFFER_H
