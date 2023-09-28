#include "PlayerDriver.h"

/**
 * @brief Function to test the Player class functionalities.
 *
 * This function sets up a basic test scenario for Player class. It tests various
 * functionalities such as adding and removing territories, issuing orders, etc.
 */
void testPlayers() {

    /// Setting up game engine
    auto gameEngine = new GameEngine();

    /// Creating a player
    auto p = new Player(gameEngine, new Hand());

    /// Loading a map to access territories
    gameEngine->loadMap("map_resources/TestMap1_valid.map");
    auto map_territories = gameEngine->getMap()->getTerritories();

    /// Adding specific territories from the map to the player
    auto t1 = *map_territories->at(0);
    auto t2 = *map_territories->at(1);
    auto t3 = *map_territories->at(2);
    auto t4 = *map_territories->at(3);

    p->addTerritory(t1);
    p->addTerritory(t2);
    p->addTerritory(t3);
    p->addTerritory(t4);

    /// Displaying territories
    std::cout << "All 4: " << std::endl;
    for(auto t: *p->getTerritories()) {
        std::cout << t->getName() << std::endl;
    }

    /// Removing a territory
    p->removeTerritory(t4);
    std::cout << "After Removing last one: " << std::endl;
    for(auto t: *p->getTerritories()) {
        std::cout << t->getName() << std::endl;
    }

    /// Displaying defended territories
    std::cout << "\n " << std::endl;
    std::cout << "Defending Territories: " << std::endl;
    auto defend = p->toDefend();
    for(auto d: defend) {
        std::cout << d->getName() << std::endl;
    }

    /// Displaying territories to attack
    std::cout << "\n " << std::endl;
    std::cout << "Attacking Territories: " << std::endl;
    auto attack = p->toAttack();
    for(auto a: attack) {
        std::cout << a->getName() << std::endl;
    }

    /// Testing stream insertion overload
    std::cout << "\n " << std::endl;
    std::cout << "Testing stream insertion overload " << std::endl;
    std::cout << p << std::endl;

    /// Testing issue order function
    std::cout << "\n " << std::endl;
    std::cout << "Testing player issueOrder Airlift" << std::endl;
    p->issueOrder(CT_Airlift);
    auto orders = p->getOrdersListObject()->getList();
    std::cout << "Order that has been added to Player OrderList: " << std::endl;
    std::cout << *orders->at(0) << std::endl;
}