#include "Cards.h"

using namespace std;

/**
 * @brief Constructor for Card class.
 *
 * @param type Type of card being constructed.
 * @param game Pointer to the GameEngine object.
 */
Card::Card(const CardType& type, GameEngine* game)
: cardType(type), game(game)
{
  if(game == nullptr){throw std::runtime_error("Card::Error | Cannot set Card Game Engine to null");}
}

/**
 * @brief Copy constructor for Card class.
 *
 * @param initial Reference to the Card object being copied.
 */
Card::Card(const Card &initial)
  : cardType(initial.cardType), game(initial.game)
{
  if(game == nullptr){throw std::runtime_error("Card::Error | Cannot set Card Game Engine to null");}
}


/**
 * @brief Sets the type for the card.
 *
 * @param type The new type to set for the card.
 */
void Card::setCardType(CardType& type)
{
    cardType = type;
}

/**
 * @brief Gets the card type.
 *
 * @return Returns the type of the card.
 */
CardType Card::getCardType()
{
    return cardType;
}

/**
 * @brief Executes the card's play functionality.
 */
void Card::play() {
  // check to see whose turn it is
  Player* currentPlayer = game->getCurrentPlayerTurn();
  currentPlayer->issueOrder(cardType);
  Card* card = currentPlayer->getHand()->removeCard(cardType);

  if(card == nullptr){ throw std::runtime_error(&"Hand did not contain card type: " [cardType]); }
  Deck* gameDeck = game->getDeck();
  gameDeck->addCardToDeck(card);
}

/**
 * @brief Converts a card type to its corresponding string representation.
 *
 * @param c The card type to be converted.
 * @return Returns the string representation of the card type.
 */
std::string Card::CardTypeToString(CardType& c) {
  switch (c) {
    case CT_Bomb:
      return "Bomb";
    case CT_Reinforcement:
      return "CT_Reinforcement";
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
 * @brief Destructor for Card class.
 */
Card::~Card() = default;

/**
 * @brief Copy constructor for Hand class.
 *
 * @param initial Reference to the Hand object being copied.
 */
Hand::Hand(const Hand &initial)
{
  for (auto &&temp : initial.handCards) {
    handCards.push_back(new Card(*temp));
  }
};

/**
 * @brief Destructor for Hand class.
 */
Hand::~Hand()
{
  for (auto card : handCards) {
    delete card;
  }
  handCards.clear();
}


/**
 * @brief Gets all the cards in hand.
 *
 * @return Returns a pointer to the vector containing all the cards in hand.
 */
std::vector<Card *> *Hand::getCards() {
  return &this->handCards;
}

/**
 * @brief Retrieves a card from the hand given an index.
 *
 * @param index The index of the card to retrieve.
 * @return Returns a pointer to the card at the specified index.
 */
Card *Hand::getCardFromHand(int index) {
  if (index < 0 || index >= handCards.size()){
    throw std::invalid_argument("Index out of range.");
  }
  return handCards.at(index);
}

/**
 * @brief Adds a card to the hand.
 *
 * @param card The card to be added.
 */
void Hand::addToHand(Card *card) {
  if(card == nullptr){
    throw std::invalid_argument("Card is a nullptr.");
  }
  handCards.push_back(card);
}

/**
 * @brief Removes a card of a given type from the hand.
 *
 * @param type The type of card to remove.
 * @return Returns a pointer to the removed card.
 */
Card* Hand::removeCard(CardType type) {

  for(int i = 0; i < handCards.size(); i++){
    if(handCards.at(i)->getCardType() == type){
      Card* card = handCards.at(i);
      handCards.erase(handCards.begin() + i);
      return card;
    }
  }
  return nullptr;
}

/**
 * @brief Default constructor for the Hand class.
 */
Hand::Hand() {
  handCards = vector<Card*>();
}

/**
 * @brief Constructor for Deck class.
 *
 * @param game Pointer to the GameEngine object.
 */
Deck::Deck(GameEngine* game)
    :game(game)
{}


/**
 * @brief Destructor for Deck class.
 */
Deck::~Deck()
{
  for (auto card : deckCards)  {
    delete card;
  }
  deckCards.clear();
}

/**
 * @brief Copy constructor for Deck class.
 *
 * @param initial Reference to the Deck object being copied.
 */
Deck::Deck(const Deck &initial)
{
  this->game = initial.game;
  for (auto &&temp : initial.deckCards) {
    deckCards.push_back(new Card(*temp));
  }
}

/**
 * @brief Draws a card from the deck to a player's hand.
 *
 * @param currentHand The player's hand to which the card will be added.
 */
void Deck::draw(Hand& currentHand)
{
  if (deckCards.empty())
  {
    throw std::runtime_error("The deck is currently empty.");
  }
  Card* c = removeCardRandom();
  currentHand.addToHand(c);
}

/**
 * @brief Shuffles the deck of cards.
 */
void Deck::shuffleDeck()
{
  std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
  std::shuffle(std::begin(deckCards), std::end(deckCards), rng);
}

/**
 * @brief Adds a card to the deck.
 *
 * @param card The card to be added to the deck.
 */
void Deck::addCardToDeck(Card* card) {
  deckCards.push_back(card);
}

/**
 * @brief Removes a card randomly from the deck.
 *
 * @return Returns a pointer to the removed card.
 */
Card *Deck::removeCardRandom() {
  // randomly get a card from the deck
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> range_deck(0,deckCards.size() - 1);
  int index = (int)range_deck(rng);

  Card* c = deckCards.at(index);
  // remove the card ptr from the deck
  deckCards.erase(deckCards.begin() + index);
  return c;
}

/**
 * @brief Gets all the cards in the deck.
 *
 * @return Returns a pointer to the vector containing all the cards in the deck.
 */
std::vector<Card *> *Deck::getDeckCards() {
  return &this->deckCards;
};
