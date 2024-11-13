# Принудительно задаем статическую библиотеку времени выполнения для тестов
if (MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
endif()

# Добавление тестов
add_executable(SnifferTest SnifferTest.cpp)

# Добавляем Sniffer.cpp для линковки с тестами
target_sources(SnifferTest PRIVATE ${CMAKE_SOURCE_DIR}/src/Sniffer.cpp)

# Линкуем тесты с Google Test
target_link_libraries(SnifferTest PRIVATE gtest gtest_main)

# Добавляем include директорию для доступа к Sniffer.h
target_include_directories(SnifferTest PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Регистрация тестов
add_test(NAME SnifferTest COMMAND SnifferTest)
