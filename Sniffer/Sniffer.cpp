#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

class Men {
public:
    int frame;
    std::string macAdr;

    Men(const int& frame, const std::string& macAdr) : frame(frame), macAdr(macAdr) {}

    void printInfo() const {
        std::cout << macAdr << " " << frame << std::endl;
    }
};

void validateFilePath(int argc, char* argv[]) {
    std::setlocale(LC_ALL, "Russian");

    // Проверяем, что передан путь к файлу
    if (argc < 2) {
        std::cerr << "Использование: " << argv[0] << " <путь_к_файлу>" << std::endl;
        exit(1);
    }

    // Получаем путь к файлу из аргументов командной строки
    std::string filePath = argv[1];

    // Проверяем, что файл существует
    if (!fs::exists(filePath)) {
        std::cerr << "Ошибка: файл не существует: " << filePath << std::endl;
        exit(1);
    }

    // Проверяем, что файл имеет расширение .log
    if (fs::path(filePath).extension() != ".log") {
        std::cerr << "Ошибка: файл должен иметь расширение .log" << std::endl;
        exit(1);
    }
}

std::vector<Men> parseFile(const std::string& filePath) {
    // Открываем файл для чтения
    std::ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл: " << filePath << std::endl;
        exit(1);
    }

    // Создаем вектор объектов Men
    std::vector<Men> menVector;

    // Читаем содержимое файла
    std::string line;
    while (std::getline(fileStream, line)) {
        // Ищем "RA", "SA" или "TA" в строке
        for (size_t pos = 0; pos < line.length(); ) {
            if ((line[pos] == ',' || line[pos] == '/') &&
                (line.compare(pos + 1, 2, "RA") == 0 ||
                    line.compare(pos + 1, 2, "SA") == 0 ||
                    line.compare(pos + 1, 2, "TA") == 0) &&
                (line[pos + 3] == '/' || line[pos + 3] == '=')) {
                // Ищем следующее '=' после pos
                size_t equalPos = line.find('=', pos + 3);
                if (equalPos != std::string::npos) {
                    // Находим следующую запятую после '='
                    size_t commaPos = line.find(',', equalPos);
                    std::string macAdr = line.substr(equalPos + 1, commaPos - equalPos - 1);

                    // Проверяем, встречался ли этот MAC адрес ранее
                    bool found = false;
                    for (auto& men : menVector) {
                        if (men.macAdr == macAdr) {
                            men.frame += 1; // Увеличиваем количество встреч данного MAC адреса
                            found = true;
                            break;
                        }
                    }

                    // Если MAC адрес новый, создаем нового Men и добавляем в вектор
                    if (!found) {
                        menVector.emplace_back(1, macAdr);
                    }

                    // Перемещаем pos на следующую запятую после '='
                    pos = commaPos != std::string::npos ? commaPos + 1 : line.length();
                }
                else {
                    pos = line.length();
                }
            }
            else {
                ++pos;
            }
        }
    }

    fileStream.close();
    return menVector;
}

void sortMenVector(std::vector<Men>& menVector) {
    // Сортируем вектор по количеству фреймов (по убыванию)
    std::sort(menVector.begin(), menVector.end(), [](const Men& a, const Men& b) {
        return b.frame < a.frame;
        });
}

void printMenVector(const std::vector<Men>& menVector) {
    // Выводим информацию обо всех объектах Men в векторе
    for (const auto& men : menVector) {
        men.printInfo();
    }
}

int main(int argc, char* argv[]) {
    validateFilePath(argc, argv);

    // Получаем путь к файлу из аргументов командной строки
    std::string file = argv[1];

    // Парсим файл и получаем вектор объектов Men
    std::vector<Men> menVector = parseFile(file);

    // Сортируем вектор по количеству фреймов
    sortMenVector(menVector);

    // Печатаем информацию обо всех объектах Men
    printMenVector(menVector);

    return 0;
}
