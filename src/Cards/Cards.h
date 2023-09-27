#ifndef CARDS_H
#define CARDS_H

#include <vector>
#include "Player.h"

// Class representing a card
class Card {
public:
    Card(Player* player);
    virtual ~Card();
    virtual void play() = 0;
protected:
    Player* player;
};

// Class representing a deck of cards
class Deck {
public:
    Deck();
    ~Deck();
    Card* draw();
private:
    std::vector<Card*> cards;
};

// Class representing a hand of cards
class Hand {
public:
    Hand();
    ~Hand();
    void addCard(Card* card);
    void playCard(Card* card);
private:
    std::vector<Card*> cards;
};

#endif