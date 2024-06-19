#include "utils.h"
#include <iostream>
#include <limits>

// Получение целочисленного ввода от пользователя с указанной подсказкой
int Utils::getIntInput(const std::string& prompt) {
    int input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail()) {
            std::cin.clear(); // Сброс состояния ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорирование некорректного ввода
            std::cout << "Неверный ввод. Пожалуйста, введите целое число.\n";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
            return input;
        }
    }
}

// Получение ввода типа double от пользователя с указанной подсказкой
double Utils::getDoubleInput(const std::string& prompt) {
    double input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail()) {
            std::cin.clear(); // Сброс состояния ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорирование некорректного ввода
            std::cout << "Неверный ввод. Пожалуйста, введите число.\n";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
            return input;
        }
    }
}

// Получение строкового ввода от пользователя с указанной подсказкой
std::string Utils::getStringInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}