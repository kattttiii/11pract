#include "utils.h"
#include <iostream>
#include <limits>

// ��������� �������������� ����� �� ������������ � ��������� ����������
int Utils::getIntInput(const std::string& prompt) {
    int input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail()) {
            std::cin.clear(); // ����� ��������� ������
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������������� ������������� �����
            std::cout << "�������� ����. ����������, ������� ����� �����.\n";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������� ������ �����
            return input;
        }
    }
}

// ��������� ����� ���� double �� ������������ � ��������� ����������
double Utils::getDoubleInput(const std::string& prompt) {
    double input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail()) {
            std::cin.clear(); // ����� ��������� ������
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������������� ������������� �����
            std::cout << "�������� ����. ����������, ������� �����.\n";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������� ������ �����
            return input;
        }
    }
}

// ��������� ���������� ����� �� ������������ � ��������� ����������
std::string Utils::getStringInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}