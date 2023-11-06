#include "GameEngineDriver.h"

/**
 * @brief Test function for the startup phase of the Game Engine.
 *
 * This function initializes a GameEngine object with command-line arguments and
 * calls its startupPhase method to simulate the startup phase of the game.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 */
void testStartupPhase(int argc, char** argv){
  auto gameEngine = GameEngine(argc,argv);
  gameEngine.startupPhase();
}

/**
 * @brief Test function for the main game loop of the Game Engine.
 *
 * This function sets up a game scenario by creating a GameEngine object with command-line
 * arguments, initializing a deck with cards, loading a map, creating players and assigning
 * territories, and finally adding cards to the players' hands. The main game loop is then started.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 */
void testMainGameLoop(int argc, char** argv){
  auto gameEngine = GameEngine(argc, argv);

  auto deck = gameEngine.getDeck();
  deck->addCardToDeck(new Card(CardType::CT_Reinforcement, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Reinforcement, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Reinforcement, &gameEngine));

  deck->addCardToDeck(new Card(CardType::CT_Airlift, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Airlift, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Airlift, &gameEngine));

  deck->addCardToDeck(new Card(CardType::CT_Diplomacy, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Diplomacy, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Diplomacy, &gameEngine));

  deck->addCardToDeck(new Card(CardType::CT_Bomb, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Bomb, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Bomb, &gameEngine));

  deck->addCardToDeck(new Card(CardType::CT_Blockade, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Blockade, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Blockade, &gameEngine));


  gameEngine.loadMap("../res/TestMap1_valid.map");

  auto player1 = new Player(&gameEngine, new Hand(), "Player 1");
  auto player2 = new Player(&gameEngine, new Hand(), "Player 2");
  auto player3 = new Player(&gameEngine, new Hand(), "Player 3");
  auto player4 = new Player(&gameEngine, new Hand(), "Player 4");
  auto player5 = new Player(&gameEngine, new Hand(), "Player 5");
  auto player6 = new Player(&gameEngine, new Hand(), "Player 6");

  auto map = gameEngine.getMap();
  auto continents = map->getContinents();

  for(auto t : *continents->at(0)->getTerritories()){
    player1->addTerritory(*t);
  }

  for(auto t : *continents->at(1)->getTerritories()){
    player2->addTerritory(*t);
  }

  for(auto t : *continents->at(2)->getTerritories()){
    player3->addTerritory(*t);
  }

  for(auto t : *continents->at(3)->getTerritories()){
    player4->addTerritory(*t);
  }

  for(auto t : *continents->at(4)->getTerritories()){
    player5->addTerritory(*t);
  }

  for(auto t : *continents->at(5)->getTerritories()){
    player6->addTerritory(*t);
  }

  player1->getHand()->addToHand(new Card(CardType::CT_Reinforcement, &gameEngine));
  player1->getHand()->addToHand(new Card(CardType::CT_Blockade, &gameEngine));
  player1->getHand()->addToHand(new Card(CardType::CT_Bomb, &gameEngine));
  player1->getHand()->addToHand(new Card(CardType::CT_Diplomacy, &gameEngine));
  player1->getHand()->addToHand(new Card(CardType::CT_Airlift, &gameEngine));

  player2->getHand()->addToHand(new Card(CardType::CT_Reinforcement, &gameEngine));
  player2->getHand()->addToHand(new Card(CardType::CT_Blockade, &gameEngine));
  player2->getHand()->addToHand(new Card(CardType::CT_Bomb, &gameEngine));
  player2->getHand()->addToHand(new Card(CardType::CT_Diplomacy, &gameEngine));
  player2->getHand()->addToHand(new Card(CardType::CT_Airlift, &gameEngine));

  player3->getHand()->addToHand(new Card(CardType::CT_Reinforcement, &gameEngine));
  player3->getHand()->addToHand(new Card(CardType::CT_Blockade, &gameEngine));
  player3->getHand()->addToHand(new Card(CardType::CT_Bomb, &gameEngine));
  player3->getHand()->addToHand(new Card(CardType::CT_Diplomacy, &gameEngine));
  player3->getHand()->addToHand(new Card(CardType::CT_Airlift, &gameEngine));

  player4->getHand()->addToHand(new Card(CardType::CT_Reinforcement, &gameEngine));
  player4->getHand()->addToHand(new Card(CardType::CT_Blockade, &gameEngine));
  player4->getHand()->addToHand(new Card(CardType::CT_Bomb, &gameEngine));
  player4->getHand()->addToHand(new Card(CardType::CT_Diplomacy, &gameEngine));
  player4->getHand()->addToHand(new Card(CardType::CT_Airlift, &gameEngine));

  player5->getHand()->addToHand(new Card(CardType::CT_Reinforcement, &gameEngine));
  player5->getHand()->addToHand(new Card(CardType::CT_Blockade, &gameEngine));
  player5->getHand()->addToHand(new Card(CardType::CT_Bomb, &gameEngine));
  player5->getHand()->addToHand(new Card(CardType::CT_Diplomacy, &gameEngine));
  player5->getHand()->addToHand(new Card(CardType::CT_Airlift, &gameEngine));

  player6->getHand()->addToHand(new Card(CardType::CT_Reinforcement, &gameEngine));
  player6->getHand()->addToHand(new Card(CardType::CT_Blockade, &gameEngine));
  player6->getHand()->addToHand(new Card(CardType::CT_Bomb, &gameEngine));
  player6->getHand()->addToHand(new Card(CardType::CT_Diplomacy, &gameEngine));
  player6->getHand()->addToHand(new Card(CardType::CT_Airlift, &gameEngine));

  gameEngine.mainGameLoop();
}
