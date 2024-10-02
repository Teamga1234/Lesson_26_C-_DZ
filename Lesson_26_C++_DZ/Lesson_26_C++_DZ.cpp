#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>

using namespace std;

class Order {

    static int totalOrders;
    int orderNumber;
    string orderDescription;
    float price;
    time_t orderDate;
    time_t orderTime;
    int cookingTime; // У хвилинах
public:
    Order(string description, float price, int cookingTime) {
        this->orderDescription = description;
        this->price = price;
        this->cookingTime = cookingTime;

        time(&this->orderDate);
        this->orderTime = this->orderDate;
        totalOrders++;
        this->orderNumber = totalOrders;
    }

    time_t getReadyTime() const {
        return orderTime + (cookingTime * 60);
    }

    void printOrder() const {
        cout << "Номер замовлення: " << orderNumber << endl;
        cout << "Опис: " << orderDescription << endl;
        cout << "Ціна: " << price << endl;
        cout << "Час приготування: " << cookingTime << " хвилин" << endl;
        cout << "Дата замовлення: " << ctime(&orderDate);
        time_t readyTime = getReadyTime();
        cout << "Час готовності: " << ctime(&readyTime) << endl;
    }
};

int Order::totalOrders = 0;

class OrdersSystem {
private:
    vector<Order> orders;

public:

    void addOrder(const string& description, float price, int cookingTime) {
        Order newOrder(description, price, cookingTime);
        orders.push_back(newOrder);
    }

    void sortOrdersByReadyTime() {
        sort(orders.begin(), orders.end(), [](const Order& a, const Order& b) {
            return a.getReadyTime() < b.getReadyTime();
            });
    }


    void processFirstOrder() {
        if (!orders.empty()) {
            sortOrdersByReadyTime(); 
            Order firstOrder = orders.front();
            cout << "Виконання першого замовлення:" << endl;
            firstOrder.printOrder();
            orders.erase(orders.begin());
        }
        else {
            cout << "Немає замовлень для виконання." << endl;
        }
    }

    void printAllOrders() const {
        if (orders.empty()) {
            cout << "Немає активних замовлень." << endl;
        }
        else {
            cout << "Список замовлень:" << endl;
            for (const auto& order : orders) {
                order.printOrder();
                cout << "-------------------------" << endl;
            }
        }
    }
};

int main() {
    setlocale(0, "");
    OrdersSystem a;
    a.addOrder("Кава", 50.0, 5);
    a.addOrder("Піца", 200.0, 30);
    a.addOrder("Бургер", 100.0, 15);

    a.printAllOrders();

    a.processFirstOrder();

    a.printAllOrders();
}