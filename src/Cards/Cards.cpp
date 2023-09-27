#include "Cards.h"

// Card methods
Card::Card(Player* player) : player(player) {}
Card::~Card() {}

// Deck methods
Deck::Deck() {}
Deck::~Deck() {}
Card* Deck::draw() { return nullptr; } // Placeholder

// Hand methods
Hand::Hand() {}
Hand::~Hand() {}
void Hand::addCard(Card* card) { cards.push_back(card); }
void Hand::playCard(Card* card) { /* Placeholder */ }