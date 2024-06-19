#include "menu.h"
#include <algorithm>

void Menu::addItem(const std::string& name, const std::vector<Product>& ingredients, const std::string& description, double preparationTime, double price) {
    int id = items.size() + 1;
    items.push_back(MenuItem(id, name, ingredients, description, preparationTime, price));
}

void Menu::editItem(int id, const std::string& name, const std::vector<Product>& ingredients, const std::string& description, double preparationTime, double price) {
    for (auto& item : items) {
        if (item.getId() == id) {
            item.setName(name);
            item.setIngredients(ingredients);
            item.setDescription(description);
            item.setPreparationTime(preparationTime);
            item.setPrice(price);
            break;
        }
    }
}

void Menu::removeItem(int id) {
    items.erase(std::remove_if(items.begin(), items.end(), [id](const MenuItem& item) {
        return item.getId() == id;
        }), items.end());
}

void Menu::displayMenu() const {
    for (const auto& item : items) {
        item.displayInfo();
    }
}

MenuItem* Menu::getItem(int id) {
    for (auto& item : items) {
        if (item.getId() == id) {
            return &item;
        }
    }
    return nullptr;
}

void Menu::setProducts(const std::vector<Product>& products) {
    this->products = products;
}

const std::vector<Product>& Menu::getProducts() const {
    return products;
}

std::vector<Product>& Menu::getProducts() {
    return products;
}