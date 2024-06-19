#include <iostream>
#include <fstream>
#include <vector>
#include "menu.h"
#include "product.h"
#include "user.h"
#include "order.h"
#include "utils.h"
#include "authentication.h"

void adminMenu(Menu& menu, Authentication& auth);
void guestMenu(Menu& menu, Guest& guest);
void employeeMenu(Menu& menu, const std::string& role);
bool checkProductAvailability(const Menu& menu, const std::vector<Product>& ingredients);

int main() {
    setlocale(LC_ALL, "Russian");

    Menu menu;
    Authentication auth;

    Product sausage(1, "�������", 1.0, 50);
    Product pepperoni(2, "���������", 2.0, 50);
    Product tomato(3, "�������", 0.5, 50);
    Product cheese(4, "���", 1.0, 60);
    Product dough(5, "�����", 1.5, 60);
    Product cheese_mixture(6, "����� �����", 3, 40);

    std::vector<Product> products = { sausage, pepperoni, tomato, cheese, dough, cheese_mixture };
    menu.setProducts(products);

    menu.addItem("���������", { pepperoni, cheese, dough }, "������ ����� ���������", 20, 4.99);
    menu.addItem("������", { cheese_mixture, dough }, "����� ������ �����", 10, 6.99);
    menu.addItem("����������", { sausage, cheese, tomato }, "����� ���������� �� ������� �����������", 10, 3.99);

    User admin(1, "admin", "������", "����", "��������", "admin", "admin");
    auth.addUser(admin);

    User employee(2, "cook", "������", "����", "��������", "cook", "cook");
    auth.addUser(employee);

    std::cout << "�� � ��������!" << std::endl;

    while (true) {
        std::cout << "\n1. �������������\n2. �����\n3. ���������\n4. �����" << std::endl;
        int choice = Utils::getIntInput("������� ��� �����: ");

        switch (choice) {
        case 1: {
            std::cout << "���� ��� ��������������" << std::endl;
            std::string login = Utils::getStringInput("������� �����: ");
            std::string password = Utils::getStringInput("������� ������: ");
            std::string role;

            if (auth.login(login, password, role) && role == "admin") {
                adminMenu(menu, auth);
            }
            else {
                std::cout << "���!�������� ����� ��� ������!" << std::endl;
            }
            break;
        }
        case 2: {
            std::cout << "���� ��� �����" << std::endl;
            Guest guest(1, "�����");
            guestMenu(menu, guest);
            break;
        }
        case 3: {
            std::cout << "���� ��� ����������" << std::endl;
            std::string login = Utils::getStringInput("������� �����: ");
            std::string password = Utils::getStringInput("������� ������: ");
            std::string role;

            if (auth.login(login, password, role)) {
                employeeMenu(menu, role);
            }
            else {
                std::cout << "���!�������� ����� ��� ������!" << std::endl;
            }
            break;
        }
        case 4:
            std::cout << "�����..." << std::endl;
            return 0;
        default:
            std::cout << "���!�������� �����" << std::endl;
        }
    }
}

void adminMenu(Menu& menu, Authentication& auth) {
    while (true) {
        std::cout << "\n1. �������� ����� ����\n2. ������������� ����� ����\n3. ������� ����� ����\n4. ���������� ����\n5. ���������� ����������\n6. ���������� �������� ��������\n7. ��������� � ������� ����" << std::endl;
        int choice = Utils::getIntInput("������� ��� �����: ");

        switch (choice) {
        case 1: {
            std::string name = Utils::getStringInput("������� �������� ������: ");
            std::string description = Utils::getStringInput("������� �������� ������: ");
            double preparationTime = Utils::getIntInput("������� ����� ������������� (� �������): ");
            double price = Utils::getIntInput("������� ����: ");

            std::vector<Product> ingredients;
            ingredients.push_back(Product(1, "�������", 0.5, 50));
            ingredients.push_back(Product(2, "���", 1.0, 60));
            menu.addItem(name, ingredients, description, preparationTime, price);
            break;
        }
        case 2: {
            int id = Utils::getIntInput("������� ID ������ ��� ��������������: ");
            std::string name = Utils::getStringInput("������� ����� �������� ������: ");
            std::string description = Utils::getStringInput("������� ����� �������� ������: ");
            double preparationTime = Utils::getIntInput("������� ����� ����� ������������� (� �������): ");
            double price = Utils::getIntInput("������� ����� ����: ");

            std::vector<Product> ingredients;
            ingredients.push_back(Product(1, "�������", 0.5, 50));

            menu.editItem(id, name, ingredients, description, preparationTime, price);
            break;
        }
        case 3: {
            int id = Utils::getIntInput("������� ID ������ ��� ��������: ");
            menu.removeItem(id);
            break;
        }
        case 4:
            menu.displayMenu();
            break;
        case 5: {
            std::cout << "\n1. �������� �������\n2. ������������� �������\n3. ������� �������\n4. ���������� ��������\n5. ���������" << std::endl;
            int productChoice = Utils::getIntInput("������� ��� �����: ");

            switch (productChoice) {
            case 1: {
                std::string name = Utils::getStringInput("������� �������� ��������: ");
                double cost = Utils::getDoubleInput("������� ��������� ��������: ");
                int quantity = Utils::getIntInput("������� ���������� ��������: ");
                int id = menu.getProducts().size() + 1;

                menu.getProducts().push_back(Product(id, name, cost, quantity));
                break;
            }
            case 2: {
                int id = Utils::getIntInput("������� ID �������� ��� ��������������: ");
                std::string name = Utils::getStringInput("������� ����� �������� ��������: ");
                double cost = Utils::getDoubleInput("������� ����� ��������� ��������: ");
                int quantity = Utils::getIntInput("������� ����� ���������� ��������: ");
                for (auto& product : menu.getProducts()) {
                    if (product.getId() == id) {
                        product = Product(id, name, cost, quantity);
                        break;
                    }
                }
                break;
            }
            case 3: {
                int id = Utils::getIntInput("������� ID �������� ��� ��������: ");
                menu.getProducts().erase(std::remove_if(menu.getProducts().begin(), menu.getProducts().end(), [id](const Product& product) {
                    return product.getId() == id;
                    }), menu.getProducts().end());
                break;
            }
            case 4:
                for (const auto& product : menu.getProducts()) {
                    std::cout << "ID: " << product.getId() << ", ��������: " << product.getName() << ", ���������: " << product.getCost() << ", ����������: " << product.getQuantity() << std::endl;
                }
                break;
            case 5:
                break;
            default:
                std::cout << "���!�������� �����" << std::endl;
            }
            break;
        }
        case 6: {
            std::cout << "\n1. �������� ������� ������\n2. ������������� ������� ������\n3. ������� ������� ������\n4. ���������� ������� ������\n5. ���������" << std::endl;
            int userChoice = Utils::getIntInput("������� ��� �����: ");

            switch (userChoice) {
            case 1: {
                std::string role = Utils::getStringInput("������� ���� ������������: ");
                std::string surname = Utils::getStringInput("������� ������� ������������: ");
                std::string name = Utils::getStringInput("������� ��� ������������: ");
                std::string patronymic = Utils::getStringInput("������� �������� ������������: ");
                std::string login = Utils::getStringInput("������� ����� ������������: ");
                std::string password = Utils::getStringInput("������� ������ ������������: ");
                int id = auth.getUsers().size() + 1;

                auth.addUser(User(id, role, surname, name, patronymic, login, password));
                break;
            }
            case 2: {
                std::string login = Utils::getStringInput("������� ����� ������������ ��� ��������������: ");
                std::string role = Utils::getStringInput("������� ����� ���� ������������: ");
                std::string surname = Utils::getStringInput("������� ����� ������� ������������: ");
                std::string name = Utils::getStringInput("������� ����� ��� ������������: ");
                std::string patronymic = Utils::getStringInput("������� ����� �������� ������������: ");
                std::string password = Utils::getStringInput("������� ����� ������ ������������: ");

                auth.editUser(login, User(auth.getUsers().size() + 1, role, surname, name, patronymic, login, password));
                break;
            }
            case 3: {
                std::string login = Utils::getStringInput("������� ����� ������������ ��� ��������: ");
                auth.removeUser(login);
                break;
            }
            case 4:
                for (const auto& user : auth.getUsers()) {
                    std::cout << "�����: " << user.getLogin() << ", ����: " << user.getRole() << std::endl;
                }
                break;
            case 5:
                break;
            default:
                std::cout << "���!�������� �����" << std::endl;
            }
            break;
        }
        case 7:
            return;
        default:
            std::cout << "�������� �����" << std::endl;
        }
    }
}

void guestMenu(Menu& menu, Guest& guest) {
    while (true) {
        std::cout << "\n1. ������� �����\n2. ���������� ��� ������\n3. ��������� � ������� ����" << std::endl;
        int choice = Utils::getIntInput("������� ��� �����: ");
        switch (choice) {
        case 1: {
            Order order(guest.getOrders().size() + 1);
            while (true) {
                menu.displayMenu();
                int itemId = Utils::getIntInput("������� ID ������ ���� ��� ���������� � ����� (0 ��� ����������): ");
                if (itemId == 0) break;

                MenuItem* item = menu.getItem(itemId);
                if (item && checkProductAvailability(menu, item->getIngredients())) {
                    order.addItem(*item);
                }
                else {
                    std::cout << "������������ ��������� �� ������ ��� ������������� ����� ������ ����" << std::endl;
                }
            }
            guest.addOrder(order);
            break;
        }
        case 2:
            guest.displayOrders();
            break;
        case 3:
            return;
        default:
            std::cout << "�������� �����" << std::endl;
        }
    }
}

void employeeMenu(Menu& menu, const std::string& role) {
    while (true) {
        std::cout << "\n1. ����������� ������\n2. �������� ������ ������\n3. ��������� � ������� ����" << std::endl;
        int choice = Utils::getIntInput("������� ��� �����: ");

        switch (choice) {
        case 1:
            // ����� ����� ���������� ������ � ����������� �� ����
            // ��������, ���� ���� "�����", ���������� ������ �� �������� "������� � ������� �� �����"
            // ���� ���� "��������", ���������� ������ �� �������� "������� ��������� �� ������"
            break;
        case 2: {
            int orderId = Utils::getIntInput("������� ID ������ ��� ��������� �������: ");
            Order* order = nullptr;
            // ����� ����� �� ID

            if (order) {
                if (role == "cook") {
                    order->setStatus(IN_PROGRESS);
                    // ������� ������������� ������
                    for (const auto& item : order->getItems()) {
                        for (const auto& ingredient : item.getIngredients()) {
                            // ����� ����� ��������� ���������� ��������� �� ������
                        }
                    }
                    order->setStatus(READY_FOR_PICKUP);
                }
                else if (role == "waiter") {
                    order->setStatus(COMPLETED);
                }
            }
            else {
                std::cout << "����� � ����� ID �� ������" << std::endl;
            }
            break;
        }
        case 3:
            return;
        default:
            std::cout << "�������� �����" << std::endl;
        }
    }
}

bool checkProductAvailability(const Menu& menu, const std::vector<Product>& ingredients) {
    for (const auto& ingredient : ingredients) {
        bool ingredientFound = false;
        for (const auto& product : menu.getProducts()) {
            if (product.getId() == ingredient.getId() && product.getQuantity() < ingredient.getQuantity()) {
                return false;
            }
            if (product.getId() == ingredient.getId()) {
                ingredientFound = true;
            }
        }
        if (!ingredientFound) {
            return false;
        }
    }
    return true;
}