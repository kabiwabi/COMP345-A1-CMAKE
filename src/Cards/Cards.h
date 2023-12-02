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

// --------------------------------
// Enum for the type of card (public)
// --------------------------------
enum CardType : int
{
  CT_Bomb = 0,
  CT_Reinforcement,
  CT_Blockade,
  CT_Airlift,
  CT_Diplomacy
};

/**
 * @brief Class representing a Card in the game.
 */
class Card
{
private:
  /** @brief Type of each card. */
  CardType cardType;

  /** @brief Object owner (GameEngine). */
  GameEngine *game;

public:
  // --------------------------------
  // Play Card
  // --------------------------------
  /**
   * @brief Executes the action associated with playing the card.
   */
  void play();

  // --------------------------------
  // Constructors
  // --------------------------------
  /**
   * @brief Constructor for Card class.
   *
   * @param type Type of the card.
   * @param game Pointer to the GameEngine object.
   */
  explicit Card(const CardType &type, GameEngine *game);

  /**
   * @brief Copy constructor for Card class.
   *
   * @param initial The Card object to be copied.
   */
  Card(const Card &initial);

  // --------------------------------
  // Destructor
  // --------------------------------
  /**
   * @brief Destructor for Card class.
   */
  ~Card();

  // --------------------------------
  // Setters + Getters
  // --------------------------------
  /**
   * @brief Sets the type of the card.
   *
   * @param type Type of the card.
   */
  void setCardType(const CardType &type);

  /**
   * @brief Gets the type of the card.
   *
   * @return Type of the card.
   */
  CardType getCardType() const;

  /**
   * @brief Gets the string representation of the card type.
   *
   * @return String representation of the card type.
   */
  std::string getCardTypeString();

  // --------------------------------
  // Static Method to Map CardType Enum to String
  // --------------------------------
  /**
   * @brief Maps CardType enum to its string representation.
   *
   * @param c CardType enum value.
   * @return String representation of the CardType.
   */
  static std::string CardTypeToString(CardType &c);
};

/**
 * @brief Class representing a Hand of cards for a player.
 */
class Hand
{
private:
  /** @brief Vector of pointers to Card objects. */
  std::vector<Card *> handCards;

public:
  // --------------------------------
  // Constructors
  // --------------------------------
  /**
   * @brief Default constructor for Hand class.
   */
  Hand();

  /**
   * @brief Destructor for Hand class.
   */
  ~Hand();

  /**
   * @brief Copy constructor for Hand class.
   *
   * @param initial The Hand object to be copied.
   */
  Hand(const Hand &initial);

  // --------------------------------
  // Public Methods
  // --------------------------------
  /**
   * @brief Gets the vector of pointers to Card objects in the hand.
   *
   * @return Vector of pointers to Card objects.
   */
  std::vector<Card *> *getCards();

  /**
   * @brief Gets a specific card from the hand based on its index.
   *
   * @param index Index of the card in the hand.
   * @return Pointer to the Card object.
   */
  Card *getCardFromHand(int index);

  /**
   * @brief Adds a card to the hand.
   *
   * @param card Pointer to the Card object to be added.
   */
  void addToHand(Card *card);

  /**
   * @brief Removes and deletes a card from the hand.
   *
   * Once the card is used, it should be deleted.
   *
   * @param type Type of the card to be removed.
   * @return Pointer to the removed Card object.
   */
  Card *removeCard(CardType type);

  /**
   * @brief Gets the vector of pointers to Card objects in the hand.
   *
   * @return Vector of pointers to Card objects.
   */
  std::vector<Card *>* getHandCards() { return &handCards; }
};

/**
 * @brief Class representing a Deck of cards in the game.
 */
class Deck
{
private:
  /** @brief Vector of pointers to Card objects. */
  std::vector<Card *> deckCards;

  /** @brief Object owner (GameEngine). */
  GameEngine *game;

public:
  // --------------------------------
  // Constructors
  // --------------------------------
  /**
   * @brief Constructor for Deck class.
   *
   * @param game Pointer to the GameEngine object.
   */
  explicit Deck(GameEngine *);

  /**
   * @brief Destructor for Deck class.
   */
  ~Deck();

  /**
   * @brief Copy constructor for Deck class.
   *
   * @param initial The Deck object to be copied.
   */
  Deck(const Deck &initial);

  // --------------------------------
  // Public Methods
  // --------------------------------
  /**
   * @brief Draws a random card from the deck to the player's hand.
   *
   * @param currentHand Reference to the Hand object of the player.
   */
  void draw(Hand &currentHand);

    //deck of hand shuffler method
    void shuffleDeck();

  /**
   * @brief Gets the vector of pointers to Card objects in the deck.
   *
   * @return Vector of pointers to Card objects.
   */
  std::vector<Card *> *getDeckCards();

  /**
   * @brief Adds a card to the deck.
   *
   * @param card Pointer to the Card object to be added.
   */
  void addCardToDeck(Card *card);

  /**
   * @brief Creates the initial deck of cards for the game.
   */
  void create_deck();

private:
  /**
   * @brief Removes a card from the deck at random.
   *
   * @return Pointer to the removed Card object.
   */
  Card *removeCardRandom();
};