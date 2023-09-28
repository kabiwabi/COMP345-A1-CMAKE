#pragma once

#include "GameEngine/GameEngine.h"
#include "Cards/Cards.h"
#include "Orders/Orders.h"
#include "Map/Map.h"

#include <vector>

class Territory;
enum CardType : int;
class GameEngine;
class Hand;
class OrdersList;

/**
 * @class Player
 * @brief Represents a player in the game.
 *
 * This class holds the player's properties and provides the necessary functions
 * to manage and interact with these properties during the game.
 */
class Player {
private:
    /// Static variable for tracking the next player ID.
    static int nextId;

    /// The unique ID for the player.
    int id;

    /// The territories that this player owns.
    std::vector<Territory*> territories;

    /// The player's hand of cards.
    Hand* hand;

    /// The orders that this player has issued.
    OrdersList* orders;

    /// The game engine that this player is a part of.
    GameEngine* game;

public:
    /**
     * @name Constructors and Destructors
     * @{
     */
    Player(GameEngine* game, Hand* cards);
    ~Player();
    Player(const Player &p);
    /** @} */

    /**
     * @name Operator Overloads
     * @{
     */
    Player& operator=(const Player &other);
    /** @} */

    /**
     * @name Player Actions
     * @{
     */
    std::vector<Territory *> toDefend();
    std::vector<Territory *> toAttack();

    void issueOrder(CardType cardType);
    void addTerritory(Territory& territory);
    void removeTerritory(Territory& territory);
    /** @} */

    /**
     * @name Getters
     * @{
     */
    Hand* getHand();
    OrdersList* getOrdersListObject();
    std::vector<Territory*>* getTerritories();
    int getId() const;
    /** @} */

public:
    /// Friend function to print the player details.
    friend std::ostream& operator <<(std::ostream &out, const Player &player);
};