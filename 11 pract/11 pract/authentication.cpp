#include "authentication.h"
#include <algorithm>
#include "authentication.h"

bool Authentication::login(const std::string& login, const std::string& password, std::string& role) {
    for (const auto& user : users) {
        if (user.getLogin() == login && user.getPassword() == password) {
            role = user.getRole(); // Записываем роль пользователя в переданный аргумент role
            return true;
        }
    }
    return false;
}

void Authentication::addUser(const User& user) {
    users.push_back(user);
}

void Authentication::removeUser(const std::string& login) {
    users.erase(std::remove_if(users.begin(), users.end(), [&](const User& user) {
        return user.getLogin() == login;
        }), users.end());
}

void Authentication::editUser(const std::string& login, const User& newUser) {
    for (auto& user : users) {
        if (user.getLogin() == login) {
            user = newUser;
            break;
        }
    }
}

const std::vector<User>& Authentication::getUsers() const {
    return users;
}