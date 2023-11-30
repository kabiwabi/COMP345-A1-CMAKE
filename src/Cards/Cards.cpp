#include "Cards.h"
using namespace std;

/**
 * @brief Constructor for the Card class with a type parameter.
 * @param type The type of the card.
 * @param game Pointer to the GameEngine.
 */
// Card constructor with a type parameter
Card::Card(const CardType &type, GameEngine *game)
    : cardType(type), game(game)
{
  if (game == nullptr)
  {
    throw std::runtime_error("Card::Error | Cannot set Card Game Engine to null");
  }
}

/**
 * @brief Copy constructor for the Card class.
 * @param initial The Card object to be copied.
 */
// Copy constructor
Card::Card(const Card &initial)
    : cardType(initial.cardType), game(initial.game)
{
  if (game == nullptr)
  {
    throw std::runtime_error("Card::Error | Cannot set Card Game Engine to null");
  }
}

/**
 * @brief Setter for the card type.
 * @param type The new card type to set.
 */
void Card::setCardType(const CardType &type)
{
  cardType = type;
}

/**
 * @brief Getter for the card type.
 * @return The card type.
 */
CardType Card::getCardType() const
{
  return cardType;
}

/**
 * @brief Plays the card, adding an order to the current player's orders list.
 */
void Card::play()
{
  // check to see whose turn it is
  Player *currentPlayer = game->getCurrentPlayerTurn();
  auto orders = currentPlayer->getOrdersListObject();
  auto order = currentPlayer->createOrderFromCard(this);

  if (order)
  {
    orders->add(order);
  }
  else if (cardType != CardType::CT_Reinforcement)
  {
    cout << "Order was not decided " << currentPlayer->getName() << ". Skipping card..." << endl;
    return;
  }

  Card *card = currentPlayer->getHand()->removeCard(cardType);

  if (card == nullptr)
  {
    throw std::runtime_error("Hand did not contain card type: " + Card::CardTypeToString(cardType));
  }
  Deck *gameDeck = game->getDeck();
  gameDeck->addCardToDeck(card);
}

/**
 * @brief Converts CardType enum to a string.
 * @param c The CardType to convert.
 * @return The string representation of the CardType.
 */
std::string Card::CardTypeToString(CardType &c)
{
  switch (c)
  {
  case CT_Bomb:
    return "Bomb";
  case CT_Reinforcement:
    return "Reinforcement";
  case CT_Blockade:
    return "Blockade";
  case CT_Airlift:
    return "Airlift";
  case CT_Diplomacy:
    return "Diplomacy";
  default:
    throw std::runtime_error("ASSERT: Invalid Card Type");
  }
}

/**
 * @brief Getter for the string representation of the card type.
 * @return The string representation of the card type.
 */
std::string Card::getCardTypeString()
{
  return Card::CardTypeToString(cardType);
}

/**
 * @brief Destructor for the Card class.
 */
// Destructor
Card::~Card() = default;

/**
 * @brief Copy constructor for the Hand class.
 * @param initial The Hand object to be copied.
 */
// Copy construct
Hand::Hand(const Hand &initial)
{
  for (auto &&temp : initial.handCards)
  {
    handCards.push_back(new Card(*temp));
  }
}

/**
 * @brief Destructor for the Hand class.
 */
// Destructor
Hand::~Hand()
{
  for (auto card : handCards)
  {
    delete card;
  }
  handCards.clear();
}

/**
 * @brief Get a pointer to the vector of cards in the hand.
 * @return Pointer to the vector of cards.
 */
std::vector<Card *> *Hand::getCards()
{
  return &this->handCards;
}

/**
 * @brief Get a card from the hand at a specific index.
 * @param index The index of the card to retrieve.
 * @return The card at the specified index.
 * @throw std::invalid_argument if the index is out of range.
 */
Card *Hand::getCardFromHand(int index)
{
  if (index < 0 || index >= handCards.size())
  {
    throw std::invalid_argument("Index out of range.");
  }
  return handCards.at(index);
}

/**
 * @brief Add a card to the hand.
 * @param card Pointer to the card to be added.
 * @throw std::invalid_argument if the card is nullptr.
 */
void Hand::addToHand(Card *card)
{
  if (card == nullptr)
  {
    throw std::invalid_argument("Card is a nullptr.");
  }
  handCards.push_back(card);
}

/**
 * @brief Remove a card of the specified type from the hand.
 * @param type The type of the card to be removed.
 * @return Pointer to the removed card or nullptr if not found.
 */
Card *Hand::removeCard(CardType type)
{
  for (int i = 0; i < handCards.size(); i++)
  {
    auto cardType = handCards.at(i)->getCardType();
    if (cardType == (int)type)
    {
      Card *card = handCards.at(i);
      handCards.erase(handCards.begin() + i);
      return card;
    }
  }
  return nullptr;
}

/**
 * @brief Default constructor for the Hand class.
 */
// Default constructor
Hand::Hand()
{
  handCards = vector<Card *>();
}

/**
 * @brief Default constructor for the Deck class.
 * @param game Pointer to the GameEngine.
 * @throw std::runtime_error if the provided GameEngine pointer is null.
 */
// Default constructor
Deck::Deck(GameEngine *game)
    : game(game)
{
  if (game == nullptr)
  {
    throw std::runtime_error("Deck::Error | Cannot set deck Game Engine to null");
  }
}

/**
 * @brief Destructor for the Deck class.
 */
// Destructor
Deck::~Deck()
{
  for (auto card : deckCards)
  {
    delete card;
  }
  deckCards.clear();
}

/**
 * @brief Copy constructor for the Deck class.
 * @param initial The Deck object to be copied.
 */
// Copy constructor
Deck::Deck(const Deck &initial)
{
  this->game = initial.game;
  for (auto &&temp : initial.deckCards)
  {
    deckCards.push_back(new Card(*temp));
  }
}

/**
 * @brief Draw a card from the deck and add it to the specified hand.
 * @param currentHand The hand to which the card will be added.
 * @throw std::runtime_error if the deck is empty.
 */
// Draw card from the deck of hand
void Deck::draw(Hand &currentHand)
{
  if (deckCards.empty())
  {
    throw std::runtime_error("The deck is currently empty.");
  }
  Card *c = removeCardRandom();
  currentHand.addToHand(c);
}

/**
 * @brief Shuffle the deck of cards.
 */
// Method shuffling the deck of hand
void Deck::shuffleDeck()
{
  std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
  std::shuffle(std::begin(deckCards), std::end(deckCards), rng);
}

/**
 * @brief Add a card to the deck.
 * @param card

 Pointer to the card to be added.
 */
void Deck::addCardToDeck(Card *card)
{
  deckCards.push_back(card);
}

/**
 * @brief Remove a card randomly from the deck.
 * @return Pointer to the removed card.
 */
Card *Deck::removeCardRandom()
{
  // randomly get a card from the deck
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> range_deck(0, deckCards.size() - 1);
  int index = (int)range_deck(rng);

  Card *c = deckCards.at(index);
  // remove the card ptr from the deck
  deckCards.erase(deckCards.begin() + index);
  return c;
}

/**
 * @brief Get a pointer to the vector of cards in the deck.
 * @return Pointer to the vector of cards.
 */
std::vector<Card *> *Deck::getDeckCards()
{
  return &this->deckCards;
}

/**
 * @brief Create a deck of cards for testing purposes.
 *
 * Assigns 40 cards in deck vector, each type having 8 cards (5 types).
 */
// For the testing purpose
void Deck::create_deck()
{
  // Assign 40 cards in deck vector, each type has 8 cards, 5 types
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      // Type 1 = Bomb
      if (j == 0)
      {
        deckCards.push_back(new Card(CardType::CT_Bomb, game));
      }
      // Type 2 = Reinforcement
      else if (j == 1)
      {
        deckCards.push_back(new Card(CardType::CT_Reinforcement, game));
      }
      // Type 3 = Blockade
      else if (j == 2)
      {
        deckCards.push_back(new Card(CardType::CT_Blockade, game));
      }
      // Type 4 = Airlift
      else if (j == 3)
      {
        deckCards.push_back(new Card(CardType::CT_Airlift, game));
      }
      // Type 5 = Diplomacy
      else if (j == 4)
      {
        deckCards.push_back(new Card(CardType::CT_Diplomacy, game));
      }
    }
  }
}
