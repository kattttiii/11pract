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

    Product sausage(1, "Колбаса", 1.0, 50);
    Product pepperoni(2, "Пепперони", 2.0, 50);
    Product tomato(3, "Помидор", 0.5, 50);
    Product cheese(4, "Сыр", 1.0, 60);
    Product dough(5, "Тесто", 1.5, 60);
    Product cheese_mixture(6, "Смесь сыров", 3, 40);

    std::vector<Product> products = { sausage, pepperoni, tomato, cheese, dough, cheese_mixture };
    menu.setProducts(products);

    menu.addItem("Пепперони", { pepperoni, cheese, dough }, "Острая пицца пепперони", 20, 4.99);
    menu.addItem("Сырная", { cheese_mixture, dough }, "Супер сырная пицца", 10, 6.99);
    menu.addItem("Маргаритта", { sausage, cheese, tomato }, "Пицца маргаритта со свежими помидорками", 10, 3.99);

    User admin(1, "admin", "Иванов", "Иван", "Иванович", "admin", "admin");
    auth.addUser(admin);

    User employee(2, "cook", "Петров", "Петр", "Петрович", "cook", "cook");
    auth.addUser(employee);

    std::cout << "Вы в пиццерии!" << std::endl;

    while (true) {
        std::cout << "\n1. Администратор\n2. Гость\n3. Сотрудник\n4. Выход" << std::endl;
        int choice = Utils::getIntInput("Введите ваш выбор: ");

        switch (choice) {
        case 1: {
            std::cout << "Вход для администратора" << std::endl;
            std::string login = Utils::getStringInput("Введите логин: ");
            std::string password = Utils::getStringInput("Введите пароль: ");
            std::string role;

            if (auth.login(login, password, role) && role == "admin") {
                adminMenu(menu, auth);
            }
            else {
                std::cout << "Упс!Неверный логин или пароль!" << std::endl;
            }
            break;
        }
        case 2: {
            std::cout << "Меню для гостя" << std::endl;
            Guest guest(1, "Гость");
            guestMenu(menu, guest);
            break;
        }
        case 3: {
            std::cout << "Меню для сотрудника" << std::endl;
            std::string login = Utils::getStringInput("Введите логин: ");
            std::string password = Utils::getStringInput("Введите пароль: ");
            std::string role;

            if (auth.login(login, password, role)) {
                employeeMenu(menu, role);
            }
            else {
                std::cout << "Упс!Неверный логин или пароль!" << std::endl;
            }
            break;
        }
        case 4:
            std::cout << "Выход..." << std::endl;
            return 0;
        default:
            std::cout << "Упс!Неверный выбор" << std::endl;
        }
    }
}

void adminMenu(Menu& menu, Authentication& auth) {
    while (true) {
        std::cout << "\n1. Добавить пункт меню\n2. Редактировать пункт меню\n3. Удалить пункт меню\n4. Отобразить меню\n5. Управление продуктами\n6. Управление учетными записями\n7. Вернуться в главное меню" << std::endl;
        int choice = Utils::getIntInput("Введите ваш выбор: ");

        switch (choice) {
        case 1: {
            std::string name = Utils::getStringInput("Введите название товара: ");
            std::string description = Utils::getStringInput("Введите описание товара: ");
            double preparationTime = Utils::getIntInput("Введите время приготовления (в минутах): ");
            double price = Utils::getIntInput("Введите цену: ");

            std::vector<Product> ingredients;
            ingredients.push_back(Product(1, "Помидор", 0.5, 50));
            ingredients.push_back(Product(2, "Сыр", 1.0, 60));
            menu.addItem(name, ingredients, description, preparationTime, price);
            break;
        }
        case 2: {
            int id = Utils::getIntInput("Введите ID товара для редактирования: ");
            std::string name = Utils::getStringInput("Введите новое название товара: ");
            std::string description = Utils::getStringInput("Введите новое описание товара: ");
            double preparationTime = Utils::getIntInput("Введите новое время приготовления (в минутах): ");
            double price = Utils::getIntInput("Введите новую цену: ");

            std::vector<Product> ingredients;
            ingredients.push_back(Product(1, "Колбаса", 0.5, 50));

            menu.editItem(id, name, ingredients, description, preparationTime, price);
            break;
        }
        case 3: {
            int id = Utils::getIntInput("Введите ID товара для удаления: ");
            menu.removeItem(id);
            break;
        }
        case 4:
            menu.displayMenu();
            break;
        case 5: {
            std::cout << "\n1. Добавить продукт\n2. Редактировать продукт\n3. Удалить продукт\n4. Отобразить продукты\n5. Вернуться" << std::endl;
            int productChoice = Utils::getIntInput("Введите ваш выбор: ");

            switch (productChoice) {
            case 1: {
                std::string name = Utils::getStringInput("Введите название продукта: ");
                double cost = Utils::getDoubleInput("Введите стоимость продукта: ");
                int quantity = Utils::getIntInput("Введите количество продукта: ");
                int id = menu.getProducts().size() + 1;

                menu.getProducts().push_back(Product(id, name, cost, quantity));
                break;
            }
            case 2: {
                int id = Utils::getIntInput("Введите ID продукта для редактирования: ");
                std::string name = Utils::getStringInput("Введите новое название продукта: ");
                double cost = Utils::getDoubleInput("Введите новую стоимость продукта: ");
                int quantity = Utils::getIntInput("Введите новое количество продукта: ");
                for (auto& product : menu.getProducts()) {
                    if (product.getId() == id) {
                        product = Product(id, name, cost, quantity);
                        break;
                    }
                }
                break;
            }
            case 3: {
                int id = Utils::getIntInput("Введите ID продукта для удаления: ");
                menu.getProducts().erase(std::remove_if(menu.getProducts().begin(), menu.getProducts().end(), [id](const Product& product) {
                    return product.getId() == id;
                    }), menu.getProducts().end());
                break;
            }
            case 4:
                for (const auto& product : menu.getProducts()) {
                    std::cout << "ID: " << product.getId() << ", Название: " << product.getName() << ", Стоимость: " << product.getCost() << ", Количество: " << product.getQuantity() << std::endl;
                }
                break;
            case 5:
                break;
            default:
                std::cout << "Упс!Неверный выбор" << std::endl;
            }
            break;
        }
        case 6: {
            std::cout << "\n1. Добавить учетную запись\n2. Редактировать учетную запись\n3. Удалить учетную запись\n4. Отобразить учетные записи\n5. Вернуться" << std::endl;
            int userChoice = Utils::getIntInput("Введите ваш выбор: ");

            switch (userChoice) {
            case 1: {
                std::string role = Utils::getStringInput("Введите роль пользователя: ");
                std::string surname = Utils::getStringInput("Введите фамилию пользователя: ");
                std::string name = Utils::getStringInput("Введите имя пользователя: ");
                std::string patronymic = Utils::getStringInput("Введите отчество пользователя: ");
                std::string login = Utils::getStringInput("Введите логин пользователя: ");
                std::string password = Utils::getStringInput("Введите пароль пользователя: ");
                int id = auth.getUsers().size() + 1;

                auth.addUser(User(id, role, surname, name, patronymic, login, password));
                break;
            }
            case 2: {
                std::string login = Utils::getStringInput("Введите логин пользователя для редактирования: ");
                std::string role = Utils::getStringInput("Введите новую роль пользователя: ");
                std::string surname = Utils::getStringInput("Введите новую фамилию пользователя: ");
                std::string name = Utils::getStringInput("Введите новое имя пользователя: ");
                std::string patronymic = Utils::getStringInput("Введите новое отчество пользователя: ");
                std::string password = Utils::getStringInput("Введите новый пароль пользователя: ");

                auth.editUser(login, User(auth.getUsers().size() + 1, role, surname, name, patronymic, login, password));
                break;
            }
            case 3: {
                std::string login = Utils::getStringInput("Введите логин пользователя для удаления: ");
                auth.removeUser(login);
                break;
            }
            case 4:
                for (const auto& user : auth.getUsers()) {
                    std::cout << "Логин: " << user.getLogin() << ", Роль: " << user.getRole() << std::endl;
                }
                break;
            case 5:
                break;
            default:
                std::cout << "Упс!Неверный выбор" << std::endl;
            }
            break;
        }
        case 7:
            return;
        default:
            std::cout << "Неверный выбор" << std::endl;
        }
    }
}

void guestMenu(Menu& menu, Guest& guest) {
    while (true) {
        std::cout << "\n1. Сделать заказ\n2. Отобразить мои заказы\n3. Вернуться в главное меню" << std::endl;
        int choice = Utils::getIntInput("Введите ваш выбор: ");
        switch (choice) {
        case 1: {
            Order order(guest.getOrders().size() + 1);
            while (true) {
                menu.displayMenu();
                int itemId = Utils::getIntInput("Введите ID пункта меню для добавления в заказ (0 для завершения): ");
                if (itemId == 0) break;

                MenuItem* item = menu.getItem(itemId);
                if (item && checkProductAvailability(menu, item->getIngredients())) {
                    order.addItem(*item);
                }
                else {
                    std::cout << "Недостаточно продуктов на складе для приготовления этого пункта меню" << std::endl;
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
            std::cout << "Неверный выбор" << std::endl;
        }
    }
}

void employeeMenu(Menu& menu, const std::string& role) {
    while (true) {
        std::cout << "\n1. Просмотреть заказы\n2. Изменить статус заказа\n3. Вернуться в главное меню" << std::endl;
        int choice = Utils::getIntInput("Введите ваш выбор: ");

        switch (choice) {
        case 1:
            // Здесь нужно отобразить заказы в зависимости от роли
            // Например, если роль "повар", отобразить заказы со статусом "оплачен и передан на кухню"
            // Если роль "официант", отобразить заказы со статусом "передан официанту на выдачу"
            break;
        case 2: {
            int orderId = Utils::getIntInput("Введите ID заказа для изменения статуса: ");
            Order* order = nullptr;
            // Найти заказ по ID

            if (order) {
                if (role == "cook") {
                    order->setStatus(IN_PROGRESS);
                    // Процесс приготовления заказа
                    for (const auto& item : order->getItems()) {
                        for (const auto& ingredient : item.getIngredients()) {
                            // Здесь нужно уменьшить количество продуктов на складе
                        }
                    }
                    order->setStatus(READY_FOR_PICKUP);
                }
                else if (role == "waiter") {
                    order->setStatus(COMPLETED);
                }
            }
            else {
                std::cout << "Заказ с таким ID не найден" << std::endl;
            }
            break;
        }
        case 3:
            return;
        default:
            std::cout << "Неверный выбор" << std::endl;
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