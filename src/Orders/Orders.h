#pragma once

#include <iostream>
#include "Cards/Cards.h"

class Card;
enum CardType : int;
// --------------------------------
// Abstract Order class data members and methods to be implemented by derived classes
// --------------------------------
/**
 * @class Order
 * @brief Abstract class defining general order functionalities. Derived classes should implement these functionalities.
 */
class Order
{
public:
    /**
     * @brief Returns the label of the order.
     * @return Label of the order.
     */
    virtual std::string getLabel() const = 0;

    /**
     * @brief Validates the order.
     * @return True if valid, False otherwise.
     */
    virtual bool validate() const = 0;

    /**
     * @brief Executes the order.
     */
    virtual void execute() const = 0;

    /**
     * @brief Virtual destructor for the Order class.
     */
    virtual ~Order() = 0;

    /**
     * @brief Creates and returns a clone of the order.
     * @return Pointer to the cloned order.
     */
    virtual Order *clone() const = 0;

private:
    virtual std::ostream &orderCout(std::ostream &) const = 0;

    /// Overloading the output stream operator for the Order class.
    friend std::ostream &operator<<(std::ostream &, const Order &);
};

/**
 * @class OrdersList
 * @brief Represents a list of orders.
 */
class OrdersList
{
private:
    std::vector<Order *> orders{}; ///< Vector of pointers to orders.

public:
    OrdersList() = default; ///< Default constructor for OrdersList.

    /**
     * @brief Destructor for OrdersList.
     * Ensures all order pointers are deleted.
     */
    ~OrdersList();

    /**
     * @brief Copy constructor for OrdersList.
     * @param oldList Reference to the list being copied.
     */
    OrdersList(const OrdersList &oldList);

    /**
     * @brief Overloading the assignment operator.
     * @param copyList Reference to the list being assigned/copied.
     * @return Reference to the updated OrdersList.
     */
    OrdersList &operator=(const OrdersList &copyList);

    /**
     * @brief Adds an order to the list.
     * @param o Pointer to the order to be added.
     */
    void add(Order *o);

    /**
     * @brief Removes an order from the list.
     * @param pos Position of the order in the list.
     */
    void remove(int pos);

    /**
     * @brief Moves an order from one position to another in the list.
     * @param pos1 Initial position of the order.
     * @param pos2 Desired position of the order.
     */
    void move(int pos1, int pos2);

    /**
     * @brief Executes all orders in the list and removes them.
     */
    void execute();

    /**
     * @brief Retrieves a pointer to the list of orders.
     * @return Pointer to the vector of order pointers.
     */
    std::vector<Order *>* getList();

private:
    /// Overloading the output stream operator for OrdersList.
    friend std::ostream &operator<<(std::ostream &, const OrdersList &);
};

/**
 * @class Advance
 * @brief Derived class representing an Advance order.
 */
class Advance : public Order
{
public:
    /**
     * @brief Retrieves the label for the Advance order.
     * @return Label of the order.
     */
    std::string getLabel() const override;

    /**
     * @brief Validates the Advance order.
     * @return True if the order is valid, otherwise False.
     */
    bool validate() const override;

    /**
     * @brief Executes the Advance order.
     */
    void execute() const override;

    /**
     * @brief Destructor for the Advance order.
     */
    ~Advance() override;

private:
    static const std::string label; ///< Label for the Advance order.

    /**
     * @brief Creates and returns a deep copy (clone) of the Advance order.
     * @return Pointer to the cloned Advance order.
     */
    Order *clone() const override;

    /**
     * @brief Prints the details of the Advance order to the provided output stream.
     * @param output Output stream to which the order details are printed.
     * @return Modified output stream.
     */
    std::ostream &orderCout(std::ostream &) const override;
};

/**
 * @class Airlift
 * @brief Derived class representing an Airlift order.
 */
class Airlift : public Order
{
public:
    std::string getLabel() const override;
    bool validate() const override;
    void execute() const override;
    ~Airlift() override;

private:
    static const std::string label; ///< Label for the Airlift order.
    Order *clone() const override;
    std::ostream &orderCout(std::ostream &) const override;
};

/**
 * @class Blockade
 * @brief Derived class representing a Blockade order.
 */
class Blockade : public Order
{
public:
    std::string getLabel() const override;
    bool validate() const override;
    void execute() const override;
    ~Blockade() override;

private:
    static const std::string label; ///< Label for the Blockade order.
    Order *clone() const override;
    std::ostream &orderCout(std::ostream &) const override;
};

/**
 * @class Bomb
 * @brief Derived class representing a Bomb order.
 */
class Bomb : public Order
{
public:
    /**
     * @brief Retrieves the label for the Bomb order.
     * @return Label of the order.
     */
    std::string getLabel() const override;

    /**
     * @brief Validates the Bomb order.
     * @return True if the order is valid, otherwise False.
     */
    bool validate() const override;

    /**
     * @brief Executes the Bomb order.
     */
    void execute() const override;

    /**
     * @brief Destructor for the Bomb order.
     */
    ~Bomb() override;

private:
    static const std::string label; ///< Label for the Bomb order.

    /**
     * @brief Creates and returns a deep copy (clone) of the Bomb order.
     * @return Pointer to the cloned Bomb order.
     */
    Order *clone() const override;

    /**
     * @brief Prints the details of the Bomb order to the provided output stream.
     * @param output Output stream to which the order details are printed.
     * @return Modified output stream.
     */
    std::ostream &orderCout(std::ostream &) const override;
};

/**
 * @class Deploy
 * @brief Derived class representing a Deploy order.
 */
class Deploy : public Order
{
public:
    std::string getLabel() const override;
    bool validate() const override;
    void execute() const override;
    ~Deploy() override;

private:
    static const std::string label; ///< Label for the Deploy order.
    Order *clone() const override;
    std::ostream &orderCout(std::ostream &) const override;
};

/**
 * @class Negotiate
 * @brief Derived class representing a Negotiate order.
 */
class Negotiate : public Order
{
public:
    std::string getLabel() const override;
    bool validate() const override;
    void execute() const override;
    ~Negotiate() override;

private:
    static const std::string label; ///< Label for the Negotiate order.
    Order *clone() const override;
    std::ostream &orderCout(std::ostream &) const override;
};

/**
 * @class UserInputOrder
 * @brief A class to create an order based on user input.
 */
class UserInputOrder
{
public:
    /**
     * @brief Factory method to create a specific order type based on a string.
     * @param orderType The type of order as a string.
     * @return Pointer to the created Order object.
     */
    static Order *create(const std::string&) ;
};

/**
 * @class OrdersFactory
 * @brief Factory class to create Order objects based on card types.
 */
class OrdersFactory
{
public:
    /**
     * @brief Factory method to create a specific order type based on a CardType.
     * @param cardType The type of card to base the order creation on.
     * @return Pointer to the created Order object.
     */
    static Order* CreateOrder(CardType cardType);
};
