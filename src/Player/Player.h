#pragma once

#include "GameEngine/GameEngine.h"
#include "Cards/Cards.h"
#include "Orders/Orders.h"
#include "Map/Map.h"

#include <vector>
#include <utility>
#include <algorithm>

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

/**
 * @class Player
 * @brief Represents a player in the game.
 *
 * This class is responsible for managing the player's state,
 * including their territories, cards, orders, and game phase.
 */
class Player {
private:
  std::string phase;
  int reinforcementPool;
  std::vector<Territory*> territories;
  Hand* hand;
  OrdersList* orders;
  GameEngine* game;
  std::string name;
  std::vector<Player*> friendlyPlayers;


  int deployedArmiesThisTurn = 0;

public:
  // --------------------------------
  // Constructors
  // --------------------------------
   /**
   * @brief Constructs a new Player object.
   * @param game The game engine instance.
   * @param cards The player's hand of cards.
   * @param name The name of the player.
   */
  Player(GameEngine* game, Hand* cards, std::string name);
  /**
   * @brief Destructor for the Player class.
   */
  ~Player();
  /**
   * @brief Copy constructor for the Player class.
   * @param p The Player object to be copied.
   */
  Player(const Player &p) = default;

  // --------------------------------
  // Operator Overloads
  // --------------------------------
   /**
   * @brief Overloads the assignment operator.
   * @param other The Player object to assign from.
   * @return Reference to the updated Player object.
   */
  Player& operator=(const Player &other);

  // --------------------------------
  // Actions
  // --------------------------------
  std::vector<Territory *> toDefend();
  std::vector<Territory *> toAttack();

  void removeArmies(int n);

  void issueOrder();
  void addTerritory(Territory& territory);
  void removeTerritory(Territory& territory);
  void addReinforcement(int reinforcement);
  int getContinentBonus();
  Territory* findFirstNeighbourTerritory(Territory* target);
    /**
   * @brief Gets the list of enemy players.
   * @return Vector of pointers to Player objects representing enemies.
   */
  std::vector<Player*> getEnemies();

  // --------------------------------
  // Strategies
  // --------------------------------
  Order* decideOrder(CardType);
  Airlift* decideCardOrderAirlift();
  Bomb* decideCardOrderBomb();
  Blockade* decideCardOrderBlockade();
  Negotiate* decideCardOrderNegotiate();
  void decideCardReinforcement();

  // --------------------------------
  // Setters
  // --------------------------------
  void setReinforcementPool(int n);
  void addFriendly(Player *pPlayer);
  void clearFriendly();
  void setPhase(std::string ph);
  void addDeployedArmies(int a);
  void clearDeploymentArmies();

  // --------------------------------
  // Getters
  // --------------------------------
  Hand* getHand();
  OrdersList* getOrdersListObject();
  std::vector<Territory*>* getTerritories();
  std::string getPhase();
  int getReinforcementPool() const;
  std::string getName() const;
  int getDeployedArmiesThisTurn() const;
  GameEngine* getGameInstance();


public:

  /**
   * @brief Overloads the stream insertion operator for the Player class.
   * @param out The output stream.
   * @param player The Player object to be inserted into the stream.
   * @return Reference to the output stream.
   */
  friend std::ostream& operator <<(std::ostream &out, const Player &player);
    /**
   * @brief Determines if the player can attack another player.
   * @param pPlayer Pointer to the Player object to potentially attack.
   * @return True if the player can attack, false otherwise.
   */
  bool canAttack(Player *pPlayer);
};
