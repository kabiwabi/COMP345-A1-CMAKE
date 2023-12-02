#include "PlayerStrategiesDriver.h"
#include "GameEngine/GameEngine.h"

using namespace std;

/**
 * @brief Function to test player strategies using the Strategy design pattern.
 *
 * This function tests various aspects of player strategies, including:
 *   1) Assigning different strategies to players leading to different behaviors.
 *   2) Dynamically changing the strategy during play (e.g., from neutral to aggressive when attacked).
 *   3) Implementing strategy patterns for both human and computer players.
 *
 * @details
 *   The function sets up a game engine, creates a deck, loads a map, and creates players with different strategies.
 *   Territories are assigned to players for testing purposes. Each player is given a set of cards in their hand.
 *   The main game loop is then executed to observe player strategies in action.
 */
void testPlayerStrategies()
{
    // arrange
    // mocking argc and argv
    int argc = 1;
    char *argv[] = {(char *)"-console"};

    // create a game engine
    auto gameEngine = GameEngine(argc, argv);

    // add cards to the gameEngine deck; 5 of each
    auto deck = gameEngine.getDeck();
    deck->addCardToDeck(new Card(CardType::CT_Reinforcement, &gameEngine));
    deck->addCardToDeck(new Card(CardType::CT_Reinforcement, &gameEngine));
    deck->addCardToDeck(new Card(CardType::CT_Reinforcement, &gameEngine));
    deck->addCardToDeck(new Card(CardType::CT_Reinforcement, &gameEngine));
    deck->addCardToDeck(new Card(CardType::CT_Reinforcement, &gameEngine));

    deck->addCardToDeck(new Card(CardType::CT_Airlift, &gameEngine));
    deck->addCardToDeck(new Card(CardType::CT_Airlift, &gameEngine));
    deck->addCardToDeck(new Card(CardType::CT_Airlift, &gameEngine));
    deck->addCardToDeck(new Card(CardType::CT_Airlift, &gameEngine));
    deck->addCardToDeck(new Card(CardType::CT_Airlift, &gameEngine));

    deck->addCardToDeck(new Card(CardType::CT_Diplomacy, &gameEngine));
    deck->addCardToDeck(new Card(CardType::CT_Diplomacy, &gameEngine));
    deck->addCardToDeck(new Card(CardType::CT_Diplomacy, &gameEngine));
    deck->addCardToDeck(new Card(CardType::CT_Diplomacy, &gameEngine));
    deck->addCardToDeck(new Card(CardType::CT_Diplomacy, &gameEngine));

    deck->addCardToDeck(new Card(CardType::CT_Bomb, &gameEngine));
    deck->addCardToDeck(new Card(CardType::CT_Bomb, &gameEngine));
    deck->addCardToDeck(new Card(CardType::CT_Bomb, &gameEngine));
    deck->addCardToDeck(new Card(CardType::CT_Bomb, &gameEngine));
    deck->addCardToDeck(new Card(CardType::CT_Bomb, &gameEngine));

    deck->addCardToDeck(new Card(CardType::CT_Blockade, &gameEngine));
    deck->addCardToDeck(new Card(CardType::CT_Blockade, &gameEngine));
    deck->addCardToDeck(new Card(CardType::CT_Blockade, &gameEngine));
    deck->addCardToDeck(new Card(CardType::CT_Blockade, &gameEngine));
    deck->addCardToDeck(new Card(CardType::CT_Blockade, &gameEngine));

    // load a map before the game starts
    gameEngine.loadMap("../res/TestMap1_valid.map");

    // create players
    auto player1 = new Player(&gameEngine, new Hand(), "Killer", "Aggressive");
    auto player2 = new Player(&gameEngine, new Hand(), "Bob Ross", "Benevolent");
    auto player3 = new Player(&gameEngine, new Hand(), "Real Human", "Human");
    auto player4 = new Player(&gameEngine, new Hand(), "Big Cheater", "cheater");
    auto player5 = new Player(&gameEngine, new Hand(), "Swiss", "neutral");

    // adding sets of territories just for testing
    auto map = gameEngine.getMap();
    auto continents = map->getContinents();

    for (auto t : *continents->at(0)->getTerritories())
    {
        player1->addTerritory(*t);
    }

    for (auto t : *continents->at(1)->getTerritories())
    {
        player2->addTerritory(*t);
    }

    for (auto t : *continents->at(2)->getTerritories())
    {
        player3->addTerritory(*t);
    }

    for (auto t : *continents->at(3)->getTerritories())
    {
        player4->addTerritory(*t);
    }

    for (auto t : *continents->at(4)->getTerritories())
    {
        player5->addTerritory(*t);
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

    gameEngine.mainGameLoop();
}