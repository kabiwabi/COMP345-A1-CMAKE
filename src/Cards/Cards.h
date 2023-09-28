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
 * @brief Enumerations representing different types of cards.
 */
enum CardType: int {
  CT_Bomb = 0,
  CT_Reinforcement,
  CT_Blockade,
  CT_Airlift,
  CT_Diplomacy
};

/**
 * @brief Represents a card used in the game.
 */
class Card
{
private:
  CardType cardType;
  GameEngine* game;

public:
    /**
     * @brief Executes the functionality of the card when played.
     */
  void play();

    /**
     * @brief Constructor with card type and game engine parameters.
     * @param type Type of the card.
     * @param game Pointer to the game engine.
     */
  explicit Card(const CardType& type, GameEngine* game);
      /**
       * @brief Copy constructor.
       * @param initial The card to be copied.
       */
  Card(const Card &initial);
      /**
       * @brief Copy constructor.
       */
  ~Card();

    /**
     * @brief Sets the card type.
     * @param type The new type of the card.
     */
  void setCardType(CardType& type);
    /**
     * @brief Gets the card type.
     * @return The type of the card.
     */
  CardType getCardType();

    /**
     * @brief Converts the card type to its string representation.
     * @param c The card type to be converted.
     * @return The string representation of the card type.
     */
  static std::string CardTypeToString(CardType& c);
};

/**
 * @brief Represents a hand containing multiple cards.
 */
class Hand
{
private:


public:
  std::vector<Card *> handCards;
    /**
     * @brief Default constructor.
     */
  Hand();
    /**
     * @brief Destructor.
     */
  ~Hand();
    /**
     * @brief Copy constructor.
     * @param initial The hand to be copied.
     */
  Hand(const Hand &initial);
    /**
     * @brief Retrieves the cards in the hand.
     * @return Pointer to the vector of cards in the hand.
     */
  std::vector<Card *>* getCards();
    /**
    * @brief Retrieves a specific card from the hand.
    * @param index Index of the card in the hand.
    * @return Pointer to the card.
    */
  Card* getCardFromHand(int index);
    /**
     * @brief Adds a card to the hand.
     * @param card The card to be added.
     */
  void addToHand(Card* card);
    /**
     * @brief Removes and deletes a card of a specific type from the hand.
     * @param type The type of the card to be removed.
     * @return Pointer to the removed card.
     */
  Card* removeCard(CardType);

  std::vector<Card *>* getHandCards() { return &handCards; }
};

/**
 * @brief Represents a deck of cards used in the game.
 */
class Deck
{
private:
    std::vector<Card *> deckCards; ///< Vector of cards in the deck.
    GameEngine* game; ///< Pointer to the game engine.

public:
    /**
     * @brief Constructor with a game engine parameter.
     * @param game Pointer to the game engine.
     */
    explicit Deck(GameEngine*);

    /**
     * @brief Destructor.
     */
    ~Deck();

    /**
     * @brief Draws a card from the deck and adds it to a player's hand.
     * @param currentHand The hand to which the card will be added.
     */
    void draw(Hand& currentHand);

    /**
     * @brief Copy constructor.
     * @param initial The deck to be copied.
     */
    Deck(const Deck &initial);

    /**
     * @brief Shuffles the cards in the deck.
     */
    void shuffleDeck();

    /**
     * @brief Retrieves the cards in the deck.
     * @return Pointer to the vector of cards in the deck.
     */
    std::vector<Card *> * getDeckCards();

    /**
     * @brief Adds a card to the deck.
     * @param card The card to be added.
     */
    void addCardToDeck(Card* card);

private:
    /**
     * @brief Removes a card from the deck at a random index.
     * @return Pointer to the removed card.
     */
  Card* removeCardRandom();
};

