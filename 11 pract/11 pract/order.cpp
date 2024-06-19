#include "order.h"

Order::Order(int id) : id(id), status(NEW) {}

void Order::addItem(const MenuItem& item) {
    items.push_back(item);
}

void Order::display() const {
    std::cout << "Order ID: " << id << "\nStatus: " << status << "\nItems:\n";
    for (const auto& item : items) {
        item.displayInfo(); // Предполагается, что в классе MenuItem есть метод displayInfo
    }
}

void Order::setStatus(OrderStatus status) {
    this->status = status;
}

OrderStatus Order::getStatus() const {
    return status;
}

int Order::getId() const {
    return id;
}

const std::vector<MenuItem>& Order::getItems() const {
    return items;
}