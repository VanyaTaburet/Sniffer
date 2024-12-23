#include "Sniffer.h"

// Основная функция
int main(int argc, char* argv[]) {
    validateFilePath(argc, argv);

    // Получаем путь к файлу из аргументов командной строки
    std::string file = argv[1];

    // Парсим файл и получаем вектор объектов Men
    std::vector<SnifferMen> menVector = parseFile(file);

    // Сортируем вектор по количеству фреймов
    sortMenVector(menVector);

    // Печатаем информацию обо всех объектах Men
    printMenVector(menVector);

    return 0;
}