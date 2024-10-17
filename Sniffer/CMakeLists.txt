cmake_minimum_required(VERSION 3.10)

# Название проекта
project(Sniffer)

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем исполняемый файл
add_executable(Sniffer Sniffer.cpp)

# Добавляем библиотеку файловой системы, если требуется
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(Sniffer stdc++fs)
endif()