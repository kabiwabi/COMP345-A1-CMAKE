#include "Player.h"

/// Static variable to track the next player ID to be assigned.
int Player::nextId = 0;

/**
 * @brief Constructor to create a player with a given game and hand of cards.
 * @param game Pointer to the game engine the player belongs to.
 * @param cards Pointer to the hand of cards the player possesses.
 */
Player::Player(GameEngine* game, Hand* cards, const std::string& name)
        : game(game), hand(cards), id(nextId++), name(name), reinforcementPool(0)
{
    orders = new OrdersList();
    game->addPlayer(this);
}

/// Default copy constructor.
Player::Player(const Player &p) = default;

/**
 * @brief Returns territories the player wants to defend.
 * @return Vector of territories to defend.
 */
std::vector<Territory *> Player::toDefend() {
    unsigned length = territories.size();
    if(length > 0){
        auto first = territories.begin();
        auto last = territories.begin() + length/2;
        return {first, last};
    }
    return {};
}

/**
 * @brief Returns territories the player wants to attack.
 * @return Vector of territories to attack.
 */
std::vector<Territory *> Player::toAttack() {
    unsigned length = territories.size();
    if(length > 0){
        auto first = territories.begin() + length/2;
        auto last = territories.end();
        return {first, last};
    }
    return {};
}

/**
 * @brief Issues an order for the player based on card type.
 * @param cardType The type of card (order) to be issued.
 */
void Player::issueOrder(CardType cardType){
    auto order = OrdersFactory::CreateOrder(cardType);
    orders->add(order);
}

/**
 * @brief Adds a territory to the player's list of territories.
 * @param territory Reference to the territory to be added.
 */
void Player::addTerritory(Territory& territory) {
    territory.setPlayer(this);
    territory.setOwnerId(this->id);
    territory.setPlayer(this);
    territories.push_back(&territory);
}

/**
 * @brief Removes a territory from the player's list of territories.
 * @param territory Reference to the territory to be removed.
 */
void Player::removeTerritory(Territory& territory) {
    territory.setPlayer(nullptr);
    territory.setOwnerId(-1);
    auto end = territories.end();
    for(auto it = territories.begin(); it != end; it++){
        if(territory.getName() == (*it)->getName()){
            territory.setOwnerId(-1);
            territories.erase(it);
        }
    }
}

/// Player destructor, responsible for cleaning up allocated resources.
Player::~Player() {
    delete hand;
    delete orders;
};

/**
 * @brief Overload assignment operator for Player class.
 * @param other The player object to assign from.
 * @return A reference to the current player after assignment.
 */
Player &Player::operator=(const Player &other) {
    if(this == &other){
        return *this;
    }
    this->id = other.id;
    this->game = other.game;
    this->orders = other.orders;
    this->hand = other.hand;
    this->territories = other.territories;
    return *this;
}

/**
 * @brief Overload stream insertion operator for Player class.
 * @param out The output stream.
 * @param player The player object to print.
 * @return A reference to the updated stream.
 */
std::ostream &operator<<(std::ostream &out, const Player &player) {
    out << "-------------------" << "\n";
    for(auto t : player.territories){
        out << *t << "\n";
    }
    out << "-------------------" << "\n";
    return out;
}

// ------------------------ Getters ------------------------

/**
 * @brief Retrieves the territories owned by the player.
 * @return Pointer to a vector of territories.
 */
std::vector<Territory *>* Player::getTerritories() {
    return &territories;
}

/**
 * @brief Retrieves the hand of cards of the player.
 * @return Pointer to the hand.
 */
Hand *Player::getHand() {
    return hand;
}

/**
 * @brief Retrieves the order list of the player.
 * @return Pointer to the OrdersList.
 */
OrdersList *Player::getOrdersListObject() {
    return orders;
}
/**
 * @brief Adds to the player's armies
 */
void Player::addToReinforcementPool(int armiesToAdd) {
    reinforcementPool += armiesToAdd;
}

/**
 * @brief Remove from the player's armies
 */
void Player::removefromReinforcementPool(int armiesToAdd) {
    reinforcementPool -= armiesToAdd;
}

/**
 * @brief Retrieves the ID of the player.
 * @return The player's ID.
 */
int Player::getId() const {
    return id;
}

/**
 * @brief Retrieves the armies of the player.
 * @return The player's armies.
 */
int Player::getReinforcementPool(){
    return reinforcementPool;
}

/**
 * @brief Retrieves the name of the player.
 * @return Reference of the name.
 */
std::string Player::getName() const {
    return name;
}