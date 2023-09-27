#include "Player.h"
#include "../../Map/Map.h"

using namespace std;

// Player methods
Player::Player() {}
Player::~Player() {}
void Player::addTerritory(Territory* territory) { territories.push_back(territory); }
void Player::addCard(Card* card) { hand.push_back(card); }
std::vector<Territory*> Player::toDefend() { return territories; } // Placeholder
std::vector<Territory*> Player::toAttack() { return territories; } // Placeholder
void Player::issueOrder() {} // Placeholder