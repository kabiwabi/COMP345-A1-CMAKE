#pragma once

#include "GameEngine/GameEngine.h"
#include "Map/Map.h"
#include "Orders/Orders.h"

#include <algorithm>
#include <utility>
#include <vector>

class Territory;
enum CardType : int;
class GameEngine;
class Hand;
class OrdersList;
class Order;
class Airlift;
class Bomb;
class Blockade;
class Negotiate;
class PlayerStrategy;
class Card;

/**
 * @brief Concrete implementation of a log observer.
 */
class Player
{
private:
  std::string phase;
  int reinforcementPool;
  std::vector<Territory *> territories;
  Hand *hand;
  OrdersList *orders;
  GameEngine *game;
  std::string name;
  std::vector<Player *> friendlyPlayers;

  PlayerStrategy *strategy;

  int deployedArmiesThisTurn = 0;

public:
  // --------------------------------
  // Constructors
  // --------------------------------

  /**
   * @brief Constructor for the Player class.
   *
   * @param game Pointer to the associated GameEngine instance.
   * @param cards Pointer to the player's hand of cards.
   * @param name The name of the player.
   * @param strategy The player's strategy.
   */
  Player(GameEngine *game, Hand *cards, std::string name, const std::string &strategy);

  /**
   * @brief Destructor for the Player class.
   */
  ~Player();

  /**
   * @brief Copy constructor for the Player class.
   *
   * @param p Reference to the Player to copy.
   */
  Player(const Player &p) = default;

  // --------------------------------
  // Operator Overloads
  // --------------------------------

  /**
   * @brief Overloaded assignment operator for the Player class.
   *
   * @param other Reference to the Player to assign.
   * @return Reference to the assigned Player.
   */
  Player &operator=(const Player &other);

  // --------------------------------
  // Actions
  // --------------------------------

  /**
   * @brief Determines the territories to defend.
   *
   * @return Vector of Territory pointers to defend.
   */
  std::vector<Territory *> toDefend();

  /**
   * @brief Determines the territories to attack.
   *
   * @return Vector of Territory pointers to attack.
   */
  std::vector<Territory *> toAttack();

  /**
   * @brief Removes armies from the player's territories.
   *
   * @param n Number of armies to remove.
   */
  void removeArmies(int n);

  /**
   * @brief Issues an order for the player.
   */
  void issueOrder();

  /**
   * @brief Adds a territory to the player.
   *
   * @param territory Reference to the Territory to add.
   */
  void addTerritory(Territory &territory);

  /**
   * @brief Removes a territory from the player.
   *
   * @param territory Reference to the Territory to remove.
   */
  void removeTerritory(Territory &territory);

  /**
   * @brief Adds reinforcement armies to the player.
   *
   * @param reinforcement Number of reinforcement armies.
   */
  void addReinforcement(int reinforcement);

  /**
   * @brief Calculates the continent bonus for the player.
   *
   * @return Continent bonus.
   */
  int getContinentBonus();

  /**
   * @brief Finds the first neighboring territory of a target territory.
   *
   * @param target Pointer to the target territory.
   * @return Pointer to the first neighboring territory.
   */
  Territory *findFirstNeighbourTerritory(Territory *target);

  /**
   * @brief Gets the list of enemy players.
   *
   * @return Vector of pointers to enemy players.
   */
  std::vector<Player *> getEnemies();

  /**
   * @brief Gets the player's strategy.
   *
   * @return Pointer to the PlayerStrategy.
   */
  PlayerStrategy *getStrategy() const;

  /**
   * @brief Creates an order from a card.
   *
   * @param card Pointer to the Card.
   * @return Pointer to the created Order.
   */
  Order *createOrderFromCard(Card *card);

  // --------------------------------
  // Setters
  // --------------------------------

  /**
   * @brief Sets the reinforcement pool for the player.
   *
   * @param n Number of armies in the reinforcement pool.
   */
  void setReinforcementPool(int n);

  /**
   * @brief Adds a friendly player to the list.
   *
   * @param pPlayer Pointer to the friendly player.
   */
  void addFriendly(Player *pPlayer);

  /**
   * @brief Clears the list of friendly players.
   */
  void clearFriendly();

  /**
   * @brief Sets the current phase for the player.
   *
   * @param ph The current phase.
   */
  void setPhase(std::string ph);

  /**
   * @brief Adds deployed armies for the player.
   *
   * @param a Number of deployed armies.
   */
  void addDeployedArmies(int a);

  /**
   * @brief Clears the deployed armies for the player.
   */
  void clearDeploymentArmies();

  /**
   * @brief Sets the number of deployed armies for this turn.
   *
   * @param a Number of deployed armies for this turn.
   */
  void setDeployedArmiesThisTurn(int a);

  /**
   * @brief Sets the player's strategy.
   *
   * @param strategy The player's strategy.
   */
  void setStrategy(const std::string &strategy);

  // --------------------------------
  // Getters
  // --------------------------------

  /**
   * @brief Gets the player's hand.
   *
   * @return Pointer to the Hand.
   */
  Hand *getHand();

  /**
   * @brief Gets the player's orders list.
   *
   * @return Pointer to the OrdersList.
   */
  OrdersList *getOrdersListObject();

  /**
   * @brief Gets the list of territories owned by the player.
   *
   * @return Pointer to the vector of territories.
   */
  std::vector<Territory *> *getTerritories();

  /**
   * @brief Gets the current phase of the player.
   *
   * @return The current phase.
   */
  std::string getPhase();

  /**
   * @brief Gets the reinforcement pool for the player.
   *
   * @return Number of armies in the reinforcement pool.
   */
  int getReinforcementPool() const;

  /**
   * @brief Gets the name of the player.
   *
   * @return The name of the player.
   */
  std::string getName() const;

  /**
   * @brief Gets the number of deployed armies for this turn.
   *
   * @return Number of deployed armies for this turn.
   */
  int getDeployedArmiesThisTurn() const;

  /**
   * @brief Gets the associated GameEngine instance.
   *
   * @return Pointer to the GameEngine instance.
   */
  GameEngine *getGameInstance();

public:
  friend std::ostream &operator<<(std::ostream &out, const Player &player);

  /**
   * @brief Checks if the player can attack another player.
   *
   * @param pPlayer Pointer to the target player.
   * @return True if the player can attack the target player, false otherwise.
   */
  bool canAttack(Player *pPlayer);
};
