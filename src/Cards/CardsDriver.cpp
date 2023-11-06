#include "CardsDriver.h"
#include "Cards/Cards.h"

using namespace std;

/**
 * @brief Function to test the card-related functionalities.
 *
 * This function tests the creation of the deck, adding cards to it, shuffling the deck, drawing cards into a player's hand,
 * and playing a card from a player's hand. It showcases the interactions between the `Card`, `Deck`, and `Hand` classes.
 */
void testCards() {

  cout << "---------------- Testing Cards -------------" << endl;
  auto gameEngine = new GameEngine();
  auto player = new Player(gameEngine, new Hand(), "Player");
  Deck* deck = gameEngine->getDeck();

  cout << "-> Adding 10 cards to deck..." << endl;
  deck->addCardToDeck(new Card(CT_Bomb, gameEngine));
  deck->addCardToDeck(new Card(CT_Diplomacy, gameEngine));
  deck->addCardToDeck(new Card(CT_Airlift, gameEngine));
  deck->addCardToDeck(new Card(CT_Blockade, gameEngine));
  deck->addCardToDeck(new Card(CT_Diplomacy, gameEngine));

  deck->addCardToDeck(new Card(CT_Bomb, gameEngine));
  deck->addCardToDeck(new Card(CT_Diplomacy, gameEngine));
  deck->addCardToDeck(new Card(CT_Bomb, gameEngine));
  deck->addCardToDeck(new Card(CT_Blockade, gameEngine));
  deck->addCardToDeck(new Card(CT_Airlift, gameEngine));


  cout << "-> shuffling deck..." << endl;
  deck->shuffleDeck();

  cout << "-> Content of deck:" << endl;

  for (auto deckCard : *deck->getDeckCards()) {
      cout << *deckCard << endl;
  }

  auto player_hand = player->getHand();

  cout << "-> player draws 4 cards" << endl;
  deck->draw(*player_hand);
  deck->draw(*player_hand);
  deck->draw(*player_hand);
  deck->draw(*player_hand);

  cout << "-> Card in player's hand" << endl;

  for (auto handCard : *player_hand->getHandCards()) {
      cout << *handCard << endl;
  }

  cout << "-> Number of Cards in Deck: " << deck->getDeckCards()->size() << endl;
  cout << "-> Number of Cards in Player's hand: " << player_hand->getHandCards()->size() << endl;

  cout << "-> Player Plays the first card" << endl;
  // play most left hand size card
  Card* card_to_play = player_hand->getHandCards()->at(0);

  cout << "-> Card Played \n" << *card_to_play << endl;
  card_to_play->play();

  cout << "-> Number of Cards in Deck: " << deck->getDeckCards()->size() << endl;

  cout << "-> Cards in Now in Player's hand" << endl;

  for (auto handCard : *player_hand->getHandCards()) {
      cout << *handCard << endl;
  }

}
