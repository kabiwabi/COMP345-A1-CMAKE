#include "Orders.h"
#include "OrdersDriver.h"
#include "GameEngine/GameEngine.h"

/**
 * @brief Function to test the functionality of Orders and OrdersList.
 * 
 * This function showcases various actions that can be performed with Orders and OrdersList such as adding, moving, removing, and executing orders. 
 * The orders are created using a factory method, and their behavior is tested in the context of a GameEngine and Player.
 */
void testOrdersLists()
{
    /// Initialize the game engine and the player
    auto gameEngine = new GameEngine;
    auto player = new Player(gameEngine, new Hand());

    /// Add player to the game engine
    gameEngine->addPlayer(player);

    /// Fetch the player's OrdersList object
    auto orderList = player->getOrdersListObject();

    std::cout << "-> Order Addition" << std::endl;

    /// Add various types of orders to the OrdersList
    orderList->add(UserInputOrder::create("Deploy"));
    orderList->add(UserInputOrder::create("Advance"));
    orderList->add(UserInputOrder::create("Bomb"));
    orderList->add(UserInputOrder::create("Blockade"));
    orderList->add(UserInputOrder::create("Airlift"));
    orderList->add(UserInputOrder::create("Negotiate"));

    std::cout << "-> Move 4 with 2 and remove the new 2" << std::endl;

    /// Move and remove specific orders in the OrdersList
    orderList->move(4, 2);
    orderList->remove(2);

    auto list = *orderList->getList();

    std::cout << "-> Orders can be validated" << std::endl;
    std::cout << "Example: First Order is valid: " << (orderList->getList()->at(0)->validate() ? "True": "False") << endl;

    std::cout << "-> List order execution" << std::endl;

    /// Execute all the orders in the OrdersList
    orderList->execute();
}