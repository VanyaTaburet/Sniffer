#include "gtest/gtest.h"
#include "Sniffer.h"

// Тест для проверки запуска сниффера
TEST(SnifferTest, StartTest) {
    Sniffer sniffer;
    EXPECT_NO_THROW(sniffer.start());
}
