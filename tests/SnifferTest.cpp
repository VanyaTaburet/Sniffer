#include "gtest/gtest.h"
#include "Sniffer.h"
#include <fstream>
#include <string>

// Глобальная переменная для хранения пути к файлу
std::string testFilePath;

// Тест на проверку обработки файла и правильности вывода
TEST(SnifferTest, AcceptanceTest) {
    ASSERT_FALSE(testFilePath.empty()) << "Путь к тестовому файлу не указан";

    // Проверяем, что файл существует
    std::ifstream file(testFilePath);
    ASSERT_TRUE(file.is_open()) << "Не удалось открыть тестовый файл: " << testFilePath;


    // Ожидаемые результаты
    std::vector<std::pair<std::string, int>> expectedResults = {
        {"b8:69:f4:7a:a5:ac", 8340},
        {"34:1c:f0:d3:40:a2", 5796},
        {"34:1c:f0:d2:78:5a", 5233},
        {"00:0c:29:65:08:ee", 3713},
        {"ff:ff:ff:ff:ff:ff", 98},
        {"4a:5f:99:ae:ea:99", 98},
        {"6e:52:4e:5f:f9:eb", 79},
        {"84:c5:a6:07:38:66", 73},
        {"b8:69:f4:7a:a5:93", 68},
        {"52:ff:20:52:16:9a", 14},
        {"70:c9:32:1b:54:e2", 13},
        {"80:b6:55:60:6f:58", 4},
        {"c8:7f:54:28:74:ac", 3}
    };

    // Запускаем обработку файла
    std::vector<SnifferMen> menVector = parseFile(testFilePath);
    sortMenVector(menVector);

    // Проверяем количество MAC-адресов
    ASSERT_EQ(menVector.size(), expectedResults.size()) << "Количество MAC-адресов не совпадает";

    // Проверяем количество фреймов для каждого MAC-адреса
    for (size_t i = 0; i < menVector.size(); ++i) {
        EXPECT_EQ(menVector[i].macAdr, expectedResults[i].first) << "MAC-адрес на позиции " << i << " не совпадает";
        EXPECT_EQ(menVector[i].frame, expectedResults[i].second) << "Количество фреймов для MAC-адреса " << menVector[i].macAdr << " не совпадает";
    }
}

// Основная функция main
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    // Проверка наличия аргументов командной строки
    if (argc < 2) {
        std::cerr << "Использование: " << argv[0] << " <путь_к_тестовому_файлу>" << std::endl;
        return 1;
    }

    // Сохраняем путь к тестовому файлу в глобальной переменной
    testFilePath = argv[1];

    return RUN_ALL_TESTS();
}