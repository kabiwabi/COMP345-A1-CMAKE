#ifndef ORDERS_H
#define ORDERS_H

#include <vector>
#include "Player.h"

// Class representing an order
class Order {
public:
    Order(Player* player);
    virtual ~Order();
    virtual bool validate() = 0;
    virtual void execute() = 0;
protected:
    Player* player;
};

// Class representing a list of orders
class OrdersList {
public:
    OrdersList();
    ~OrdersList();
    void addOrder(Order* order);
    void removeOrder(Order* order);
    void moveOrder(Order* order, int index);
private:
    std::vector<Order*> orders;
};

#endif