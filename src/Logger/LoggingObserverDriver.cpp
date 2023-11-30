#include "LoggingObserverDriver.h"

/**
 * @brief Test function for the Logging Observer.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 */
void testLoggingObserver(int argc, char **argv)
{
  // Create a new game engine
  auto gameEngine = new GameEngine(argc, argv);

  // Create two players with empty hands and the "Aggressive" strategy
  auto player1 = new Player(gameEngine, new Hand(), "Player1", "Aggressive");
  auto player2 = new Player(gameEngine, new Hand(), "Player2", "Aggressive");

  // Load a test map
  gameEngine->loadMap("../res/TestMap1_valid.map");

  // Add a territory to player2
  player2->addTerritory(*gameEngine->getMap()->getTerritories()->at(0));

  // Create a Bomb order targeting a territory of player1, initiated by player2
  auto order = new Bomb(gameEngine, player2->getTerritories()->at(0), player1);

  // Get the order list of player1 and attach the order
  auto orderList = player1->getOrdersListObject();
  orderList->add(order);

  // Create a command processor and attach an observer
  auto processor = new CommandProcessor(gameEngine, argc, argv);

  // TEST GAME STATE CHANGE
  gameEngine->setCurrentState(GE_Map_Loaded);

  // TEST ADDITION OF ORDER TO ORDER LIST
  // (The order was already added when creating the orderList)

  // TEST ORDER EXECUTION
  order->execute();

  // TEST EFFECT SAVED and COMMAND SAVED
  // (Command retrieval from the processor, but its effect is not checked in the provided code)
  processor->getCommand();
}
