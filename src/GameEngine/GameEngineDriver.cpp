#include "GameEngineDriver.h"

/**
 * @brief Tests the startup phase of the game engine.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 */
void testStartupPhase(int argc, char **argv)
{
  auto gameEngine = GameEngine(argc, argv);
  gameEngine.startupPhase();
}

/**
 * @brief Tests the main game loop of the game engine.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 */
void testGameLoop(int argc, char **argv)
{
  // create a game engine
  auto gameEngine = GameEngine(argc, argv);

  // add cards to the gameEngine deck
  auto deck = gameEngine.getDeck();
  // Adding cards of different types for testing
  deck->addCardToDeck(new Card(CardType::CT_Reinforcement, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Reinforcement, &gameEngine));
  // ... Add more cards of different types

  // load a map before the game starts
  gameEngine.loadMap("../res/TestMap1_valid.map");

  // create players
  auto player1 = new Player(&gameEngine, new Hand(), "Rick Astley", "Human");
  auto player2 = new Player(&gameEngine, new Hand(), "Bob Ross", "Aggressive");
  // ... Create more players

  // Adding territories to players for testing
  auto map = gameEngine.getMap();
  auto continents = map->getContinents();

  for (auto t : *continents->at(0)->getTerritories())
  {
    player1->addTerritory(*t);
  }
  // ... Add territories to other players

  // Manually add cards to players for testing
  player1->getHand()->addToHand(new Card(CardType::CT_Reinforcement, &gameEngine));
  // ... Add more cards to other players

  // Start the main game loop
  gameEngine.mainGameLoop();
}
#include "GameEngineDriver.h"

/**
 * @brief Tests the startup phase of the game engine.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 */
void testStartupPhase(int argc, char **argv)
{
  auto gameEngine = GameEngine(argc, argv);
  gameEngine.startupPhase();
}

/**
 * @brief Tests the main game loop of the game engine.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 */
void testGameLoop(int argc, char **argv)
{
  // create a game engine
  auto gameEngine = GameEngine(argc, argv);

  // add cards to the gameEngine deck
  auto deck = gameEngine.getDeck();
  // Adding cards of different types for testing
  deck->addCardToDeck(new Card(CardType::CT_Reinforcement, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Reinforcement, &gameEngine));
  // ... Add more cards of different types

  // load a map before the game starts
  gameEngine.loadMap("../res/TestMap1_valid.map");

  // create players
  auto player1 = new Player(&gameEngine, new Hand(), "Rick Astley", "Human");
  auto player2 = new Player(&gameEngine, new Hand(), "Bob Ross", "Aggressive");
  // ... Create more players

  // Adding territories to players for testing
  auto map = gameEngine.getMap();
  auto continents = map->getContinents();

  for (auto t : *continents->at(0)->getTerritories())
  {
    player1->addTerritory(*t);
  }
  // ... Add territories to other players

  // Manually add cards to players for testing
  player1->getHand()->addToHand(new Card(CardType::CT_Reinforcement, &gameEngine));
  // ... Add more cards to other players

  // Start the main game loop
  gameEngine.mainGameLoop();
}
