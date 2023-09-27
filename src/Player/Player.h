#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

// Forward declaration of Card class
class Card;

// Forward declaration of Territory class
class Territory;

// Class representing a player
class Player {
public:
    Player();
    ~Player();
    void addTerritory(Territory* territory);
    void addCard(Card* card);
    std::vector<Territory*> toDefend();
    std::vector<Territory*> toAttack();
    void issueOrder();
private:
    std::vector<Territory*> territories;
    std::vector<Card*> hand;
};

#endif