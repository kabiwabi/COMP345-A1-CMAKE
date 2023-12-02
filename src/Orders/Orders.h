#pragma once

#include <iostream>
#include <sstream>
#include "Cards/Cards.h"
#include "Logger/LogObserver.h"

class Card;
class Player;
class Territory;
enum CardType : int;

/**
 * @brief Abstract Order class with data members and methods to be implemented by derived classes.
 */
class Order
{
public:
  virtual ~Order() = default;
  virtual std::string getLabel() const = 0;
  virtual bool validate() const = 0;
  virtual void execute() = 0;
  virtual Order *clone() const = 0;

private:
  virtual std::ostream &orderCout(std::ostream &) const = 0;

  friend std::ostream &operator<<(std::ostream &, const Order &);
};

/**
 * @brief List of orders with methods to add, remove, move, and execute orders.
 */
class OrdersList : public Subject, ILoggable
{
private:
  std::vector<Order *> orders{};
  GameEngine *game;

public:
  /**
   * @brief Constructor for OrdersList.
   *
   * @param gameEngine The GameEngine instance.
   */
  explicit OrdersList(GameEngine *gameEngine);

  /**
   * @brief Destructor for OrdersList.
   */
  ~OrdersList() override;

  /**
   * @brief Copy constructor for OrdersList.
   *
   * @param other The OrdersList to copy.
   */
  OrdersList(const OrdersList &);

  /**
   * @brief Assignment operator for OrdersList.
   *
   * @param other The OrdersList to assign.
   * @return Reference to the assigned OrdersList.
   */
  OrdersList &operator=(const OrdersList &);

  /**
   * @brief Add an order to the list.
   *
   * @param o The order to add.
   */
  void add(Order *o);

  /**
   * @brief Remove an order from the list.
   *
   * @param index The index of the order to remove.
   */
  void remove(int index);

  /**
   * @brief Move an order within the list.
   *
   * @param fromIndex The index of the order to move.
   * @param toIndex The index to move the order to.
   */
  void move(int fromIndex, int toIndex);

  /**
   * @brief Execute orders in the list.
   */
  void execute();

  /**
   * @brief Get the size of the orders list.
   *
   * @return The size of the orders list.
   */
  size_t getOrdersListSize();

  /**
   * @brief Get the order at the specified index.
   *
   * @param index The index of the order.
   * @return The order at the specified index.
   */
  Order *getOrder(int index);

    // Logging
    static std::string castOrderType(Order * o);

  /**
   * @brief Get the vector of orders.
   *
   * @return The vector of orders.
   */
  std::vector<Order *> *getList();

  /**
   * @brief Get the string representation of the OrdersList for logging.
   *
   * @return The string representation of the OrdersList.
   */
  std::string stringToLog() override;

private:
  /**
   * @brief Output stream overload for OrdersList.
   *
   * @param out The output stream.
   * @param ordersList The OrdersList to output.
   * @return The output stream.
   */
  friend std::ostream &operator<<(std::ostream &out, const OrdersList &);
};

/**
 * @brief Implementation of determining territories to attack for a human player.
 *
 * @return A vector of territories to attack.
 */
class Advance : public Order, Subject, ILoggable
{
private:
  GameEngine *game;
  Player *currentPlayer;
  Territory *source;
  Territory *target;
  int amount = 0;

public:
  Advance(GameEngine *game, Territory *src, Territory *dest, Player *player, int amount);
  ~Advance() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() override;
  std::string stringToLog() override;
  static void attackSimulation(Territory *, Territory *, Player *, int);

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

/**
 * @brief Implementation of determining territories to attack for a human player.
 *
 * @return A vector of territories to attack.
 */
class Airlift : public Order, Subject, ILoggable
{
private:
  GameEngine *game;
  Player *currentPlayer;
  Territory *source;
  Territory *target;
  int amount = 0;

public:
  Airlift(GameEngine *game, Territory *source, Territory *target, Player *player, int amount);
  ~Airlift() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() override;
  std::string stringToLog() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

/**
 * @brief Implementation of determining territories to attack for a human player.
 *
 * @return A vector of territories to attack.
 */
class Blockade : public Order, Subject, ILoggable
{
private:
  GameEngine *game;
  Territory *target;
  Player *currentPlayer;

public:
  Blockade(GameEngine *game, Territory *target, Player *player);
  ~Blockade() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() override;
  std::string stringToLog() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

/**
 * @brief Implementation of determining territories to attack for a human player.
 *
 * @return A vector of territories to attack.
 */
class Bomb : public Order, Subject, ILoggable
{
private:
  GameEngine *game;
  Territory *target;
  Player *currentPlayer;

public:
  Bomb(GameEngine *game, Territory *target, Player *player);
  ~Bomb() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() override;
  std::string stringToLog() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

/**
 * @brief Implementation of determining territories to attack for a human player.
 *
 * @return A vector of territories to attack.
 */
class Deploy : public Order, Subject, ILoggable
{
private:
  GameEngine *game;
  Player *currentPlayer;
  Territory *target;
  int amount;

public:
  Deploy(GameEngine *game, Territory *target, Player *player, int amount);
  ~Deploy() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() override;
  std::string stringToLog() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

/**
 * @brief Implementation of determining territories to attack for a human player.
 *
 * @return A vector of territories to attack.
 */
class Negotiate : public Order, Subject, ILoggable
{
private:
  GameEngine *game;
  Player *currentPlayer;
  Player *targetPlayer;
  std::vector<Player *> friendlyPlayers;

public:
  Negotiate(GameEngine *game, Player *currentPlayer, Player *targetPlayer);
  ~Negotiate() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() override;
  std::string stringToLog() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};