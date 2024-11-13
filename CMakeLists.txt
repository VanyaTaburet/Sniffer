cmake_minimum_required(VERSION 3.10)

# Название проекта
project(SnifferProject2)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавление исполняемого файла
add_executable(SnifferApp src/main.cpp src/Sniffer.cpp)

# Добавление Google Test
add_subdirectory(extern/googletest)

# Добавление тестов
enable_testing()
add_subdirectory(tests)