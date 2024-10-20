#include "../SnifferApp/Sniffer.h"
#include "gtest/gtest.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <algorithm>

// Функция для выполнения команды и захвата её вывода
std::string executeCommand(const std::string& command) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

// Функция для разделения строки по разделителю
std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Тест для проверки выполнения SnifferApp и сравнения его вывода с ожидаемым
TEST(SnifferAppTest, ExecuteAndCheckOutputLineByLine) {
    // Путь к исполняемому файлу
    std::string snifferAppPath = "../build/SnifferApp/SnifferApp";
    std::string inputFilePath = "../test_input.log";

    // Формируем команду для запуска
    std::string command = snifferAppPath + " " + inputFilePath;

    // Ожидаемый вывод (замените на реальный ожидаемый вывод для вашего файла)
    std::string expectedOutput = "b8:69:f4:7a:a5:ac 8340\n34:1c:f0:d3:40:a2 5796\n34:1c:f0:d2:78:5a 5233\n00:0c:29:65:08:ee 3713\nff:ff:ff:ff:ff:ff 98\n4a:5f:99:ae:ea:99 98\n6e:52:4e:5f:f9:eb 79\n84:c5:a6:07:38:66 73\nb8:69:f4:7a:a5:93 68\n52:ff:20:52:16:9a 14\n70:c9:32:1b:54:e2 13\n80:b6:55:60:6f:58 4\nc8:7f:54:28:74:ac 3\n";

    // Выполняем команду и захватываем вывод
    std::string actualOutput = executeCommand(command);

    // Разделяем выводы на строки
    std::vector<std::string> expectedLines = splitString(expectedOutput, '\n');
    std::vector<std::string> actualLines = splitString(actualOutput, '\n');

    // Проверяем, что количество строк совпадает
    ASSERT_EQ(expectedLines.size(), actualLines.size()) << "Количество строк в выводах не совпадает.";

    // Сравниваем построчно
    for (size_t i = 0; i < expectedLines.size(); ++i) {
        EXPECT_EQ(expectedLines[i], actualLines[i]) << "Ошибка в строке " << i + 1 << ": ожидалось '" << expectedLines[i] << "', получено '" << actualLines[i] << "'.";
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

