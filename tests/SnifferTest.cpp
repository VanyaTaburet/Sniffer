#include "gtest/gtest.h"
#include "Sniffer.h"

// ���� ��� �������� ������� ��������
TEST(SnifferTest, StartTest) {
    Sniffer sniffer;
    EXPECT_NO_THROW(sniffer.start());
}
