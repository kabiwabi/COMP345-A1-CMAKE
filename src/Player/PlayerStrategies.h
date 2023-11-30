#pragma once

#include "Cards/Cards.h"
#include <iostream>
#include <vector>

class Player;
class Order;
class Territory;

// ----------------------------------------
// PlayerStrategy: Abstract class representing a player strategy.
// ----------------------------------------
class PlayerStrategy
{
public:
  Player *player = nullptr;

public:
  /**
   * @brief Pure virtual function to issue orders based on the player's strategy.
   */
  virtual void issueOrder() = 0;

  /**
   * @brief Pure virtual function to decide orders based on the player's strategy and a given card.
   *
   * @param card The card to make decisions based on.
   * @return An Order object representing the decision.
   */
  virtual Order *decideCard(Card *) = 0;

  /**
   * @brief Pure virtual function to determine territories to defend based on the player's strategy.
   *
   * @return A vector of territories to defend.
   */
  virtual std::vector<Territory *> toDefend() = 0;

  /**
   * @brief Pure virtual function to determine territories to attack based on the player's strategy.
   *
   * @return A vector of territories to attack.
   */
  virtual std::vector<Territory *> toAttack() = 0;

  /**
   * @brief Static method to create a PlayerStrategy based on the player and a specified strategy.
   *
   * @param player The player associated with the strategy.
   * @param strategy The strategy to be implemented.
   * @return A pointer to the created PlayerStrategy.
   */
  static PlayerStrategy *createStrategy(Player *player, const std::string &strategy);
};

// ----------------------------------------
// Human: Concrete implementation of a human player strategy.
// ----------------------------------------
class Human : public PlayerStrategy
{
public:
  explicit Human(Player *player);
  /**
   * @brief Implementation of issuing orders for a human player.
   */
  void issueOrder() override;

  /**
   * @brief Implementation of deciding orders based on a card for a human player.
   *
   * @param card The card to make decisions based on.
   * @return An Order object representing the decision.
   */
  Order *decideCard(Card *) override;

  /**
   * @brief Implementation of determining territories to defend for a human player.
   *
   * @return A vector of territories to defend.
   */
  std::vector<Territory *> toDefend() override;

  /**
   * @brief Implementation of determining territories to attack for a human player.
   *
   * @return A vector of territories to attack.
   */
  std::vector<Territory *> toAttack() override;

  /**
   * @brief Resets the state of the Human player strategy.
   */
  void reset();
};

// ----------------------------------------
// Aggressive: Concrete implementation of an aggressive player strategy.
// ----------------------------------------
class Aggressive : public PlayerStrategy
{
public:
  explicit Aggressive(Player *player);
  /**
   * @brief Implementation of issuing orders for an aggressive player.
   */
  void issueOrder() override;

  /**
   * @brief Implementation of deciding orders based on a card for an aggressive player.
   *
   * @param card The card to make decisions based on.
   * @return An Order object representing the decision.
   */
  Order *decideCard(Card *card) override;

  /**
   * @brief Implementation of determining territories to defend for an aggressive player.
   *
   * @return A vector of territories to defend.
   */
  std::vector<Territory *> toDefend() override;

  /**
   * @brief Implementation of determining territories to attack for an aggressive player.
   *
   * @return A vector of territories to attack.
   */
  std::vector<Territory *> toAttack() override;
};

// ----------------------------------------
// Benevolent: Concrete implementation of a benevolent player strategy.
// ----------------------------------------
class Benevolent : public PlayerStrategy
{
public:
  explicit Benevolent(Player *player);
  /**
   * @brief Implementation of issuing orders for a benevolent player.
   */
  void issueOrder() override;

  /**
   * @brief Implementation of deciding orders based on a card for a benevolent player.
   *
   * @param card The card to make decisions based on.
   * @return An Order object representing the decision.
   */
  Order *decideCard(Card *card) override;

  /**
   * @brief Implementation of determining territories to defend for a benevolent player.
   *
   * @return A vector of territories to defend.
   */
  std::vector<Territory *> toDefend() override;

  /**
   * @brief Implementation of determining territories to attack for a benevolent player.
   *
   * @return A vector of territories to attack.
   */
  std::vector<Territory *> toAttack() override;
};

// ----------------------------------------
// Neutral: Concrete implementation of a neutral player strategy.
// ----------------------------------------
class Neutral : public PlayerStrategy
{
private:
  int numberOfTerritoriesLastTurn = -1;

public:
  explicit Neutral(Player *player);
  /**
   * @brief Implementation of issuing orders for a neutral player.
   */
  void issueOrder() override;

  /**
   * @brief Implementation of deciding orders based on a card for a neutral player.
   *
   * @param card The card to make decisions based on.
   * @return An Order object representing the decision.
   */
  Order *decideCard(Card *card) override;

  /**
   * @brief Implementation of determining territories to defend for a neutral player.
   *
   * @return A vector of territories to defend.
   */
  std::vector<Territory *> toDefend() override;

  /**
   * @brief Implementation of determining territories to attack for a neutral player.
   *
   * @return A vector of territories to attack.
   */
  std::vector<Territory *> toAttack() override;
};

// ----------------------------------------
// Cheater: Concrete implementation of a cheater player strategy.
// ----------------------------------------
class Cheater : public PlayerStrategy
{
public:
  explicit Cheater(Player *player);
  /**
   * @brief Implementation of issuing orders for a cheater player.
   */
  void issueOrder() override;

  /**
   * @brief Implementation of deciding orders based on a card for a cheater player.
   *
   * @param card The card to make decisions based on.
   * @return An Order object representing the decision.
   */
  Order *decideCard(Card *card) override;

  /**
   * @brief Implementation of determining territories to defend for a cheater player.
   *
   * @return A vector of territories to defend.
   */
  std::vector<Territory *> toDefend() override;

  /**
   * @brief Implementation of determining territories to attack for a cheater player.
   *
   * @return A vector of territories to attack.
   */
  std::vector<Territory *> toAttack() override;
};
