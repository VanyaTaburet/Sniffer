#ifndef SNIFFER_H
#define SNIFFER_H

#include <string>
#include <vector>

// ����� ��� �������� ���������� � MAC-������ � ���������� �������
class Men {
public:
    int frame; // ���������� �������
    std::string macAdr; // MAC-�����

    Men(const int& frame, const std::string& macAdr); // �����������

    void printInfo() const; // ������� ��� ������ ���������� � MAC-������ � �������
};

// ������� ��� ��������� ���� � �����
void validateFilePath(int argc, char* argv[]);

// ������� ��� �������� ����� � ��������� ������� �������� Men
std::vector<Men> parseFile(const std::string& filePath);

// ������� ��� ���������� ������� �������� Men �� ���������� �������
void sortMenVector(std::vector<Men>& menVector);

// ������� ��� ������ ���������� ��� ���� �������� Men
void printMenVector(const std::vector<Men>& menVector);

#endif // SNIFFER_H
