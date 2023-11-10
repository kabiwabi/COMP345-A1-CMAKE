#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

#include "Map/Map.h"
#include "Player/Player.h"

class GameEngine;
class Map;
class Player;

using namespace std;

/**
 * @brief Enumeration representing the type of a card.
 *
 * Defines five card types: Bomb, Reinforcement, Blockade, Airlift, and Diplomacy.
 */
enum CardType: int {
  CT_Bomb = 0,
  CT_Reinforcement,
  CT_Blockade,
  CT_Airlift,
  CT_Diplomacy
};

/**
 * @brief Class representing a card in the game.
 */
class Card
{
private:
  //type of each card
  CardType cardType;

  // Object Owner
  GameEngine* game;

public:
    /**
     * @brief Play the card, executing its effect in the game.
     */
  void play();

    /**
     * @brief Constructor for the Card class.
     *
     * @param type The type of the card.
     * @param game Pointer to the GameEngine.
     */
  explicit Card(const CardType& type, GameEngine* game);

    /**
   * @brief Copy constructor for the Card class.
   *
   * @param initial The Card object to be copied.
   */
  Card(const Card &initial);

    /**
     * @brief Destructor for the Card class.
     */
  ~Card();

    /**
     * @brief Setter for the card type.
     *
     * @param type The new card type to set.
     */
  void setCardType(const CardType& type);

   /**
   * @brief Getter for the card type.
   *
   * @return The card type.
   */
  CardType getCardType();

    /**
     * @brief Static method to map CardType enum to a string.
     *
     * @param c The CardType to convert.
     * @return The string representation of the CardType.
     */
  static std::string CardTypeToString(CardType& c);
};


/**
 * @brief Class representing a hand of cards for a player.
 */
class Hand
{
private:


public:
  //hand pointer vector
  std::vector<Card *> handCards;

    /**
   * @brief Default constructor for the Hand class.
   */
  Hand();

    /**
   * @brief Destructor for the Hand class.
   */
  ~Hand();

    /**
   * @brief Copy constructor for the Hand class.
   *
   * @param initial The Hand object to be copied.
   */
  Hand(const Hand &initial);

    /**
   * @brief Getter for the vector of cards in the hand.
   *
   * @return Pointer to the vector of cards.
   */
  std::vector<Card *>* getCards();

    /**
   * @brief Get a card from the hand at a specific index.
   *
   * @param index The index of the card to retrieve.
   * @return The card at the specified index.
   * @throw std::invalid_argument if the index is out of range.
   */
  Card* getCardFromHand(int index);

    /**
   * @brief Add a card to the hand.
   *
   * @param card Pointer to the card to be added.
   * @throw std::invalid_argument if the card is nullptr.
   */
  void addToHand(Card* card);

    /**
   * @brief Remove a card of the specified type from the hand.
   *
   * @param type The type of the card to be removed.
   * @return Pointer to the removed card or nullptr if not found.
   */
  Card* removeCard(CardType);

    /**
   * @brief Get a pointer to the vector of cards in the hand.
   *
   * @return Pointer to the vector of cards.
   */
  std::vector<Card *>* getHandCards() { return &handCards; }
};


/**
 * @brief Class representing a deck of cards in the game.
 */
class Deck
{
private:
  //deck pointer vector
  std::vector<Card *> deckCards;
  // Object Owner
  GameEngine* game;

public:
    /**
  * @brief Constructor for the Deck class.
  *
  * @param game Pointer to the GameEngine.
  * @throw std::runtime_error if the provided GameEngine pointer is null.
  */
  explicit Deck(GameEngine*);

    /**
     * @brief Destructor for the Deck class.
     *
     * Frees the memory allocated for each Card object in the deck
     * and clears the vector of Card pointers.
     */
  ~Deck();

    /**
     * @brief Draw a card from the deck and add it to the specified hand.
     *
     * @param currentHand The hand to which the card will be added.
     * @throw std::runtime_error if the deck is empty.
     */
  void draw(Hand& currentHand);

    /**
   * @brief Copy constructor for the Deck class.
   *
   * @param initial The Deck object to be copied.
   */
  Deck(const Deck &initial);

    /**
   * @brief Shuffle the deck of cards.
   *
   * Uses a random number generator to shuffle the cards in the deck.
   */
  void shuffleDeck();

    /**
   * @brief Get a pointer to the vector of cards in the deck.
   *
   * @return Pointer to the vector of cards.
   */
  std::vector<Card *> * getDeckCards();

    /**
   * @brief Add a card to the deck.
   *
   * @param card Pointer to the card to be added.
   */
  void addCardToDeck(Card* card);

    /**
   * @brief Create a deck of cards for testing purposes.
   *
   * Assigns 40 cards in the deck vector, each type having 8 cards (5 types).
   */
  void create_deck();
private:

    /**
 * @brief Remove a card randomly from the deck.
 *
 * @return Pointer to the removed card.
 */
  Card* removeCardRandom();
};

