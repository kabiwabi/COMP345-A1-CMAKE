#include "Orders.h"

// Order methods
Order::Order(Player* player) : player(player) {}
Order::~Order() {}

// OrdersList methods
OrdersList::OrdersList() {}
OrdersList::~OrdersList() {}
void OrdersList::addOrder(Order* order) { orders.push_back(order); }
void OrdersList::removeOrder(Order* order) { /* Placeholder */ }
void OrdersList::moveOrder(Order* order, int index) { /* Placeholder */ }