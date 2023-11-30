#include "Player.h"
#include "PlayerStrategies.h"

#include <utility>

/**
 * @brief Player constructor.
 *
 * @param game The GameEngine instance.
 * @param cards The Hand of cards for the player.
 * @param name The name of the player.
 * @param strategy The strategy chosen by the player.
 */
Player::Player(GameEngine *game, Hand *cards, std::string name, const std::string &strategy)
    : game(game), hand(cards), name(std::move(name)), reinforcementPool(0)
{
  orders = new OrdersList(game);
  game->addPlayer(this);
  this->strategy = PlayerStrategy::createStrategy(this, strategy);
}

/**
 * @brief Get a vector of territories to defend.
 *
 * @return A vector of territories to defend.
 */
std::vector<Territory *> Player::toDefend()
{
  return strategy->toDefend();
}

/**
 * @brief Get a vector of territories to attack.
 *
 * @return A vector of territories to attack.
 */
std::vector<Territory *> Player::toAttack()
{
  return strategy->toAttack();
}

/**
 * @brief Issue orders based on the player's strategy.
 */
void Player::issueOrder()
{
  strategy->issueOrder();
}

/**
 * @brief Add a territory to the player.
 *
 * @param territory The territory to add.
 */
void Player::addTerritory(Territory &territory)
{
  if (territory.getPlayer() == this)
  {
    return;
  }
  if (territory.getPlayer())
  {
    territory.getPlayer()->removeTerritory(territory);
  }
  territory.setPlayer(this);
  territories.push_back(&territory);
}

/**
 * @brief Remove a territory from the player.
 *
 * @param territory The territory to remove.
 */
void Player::removeTerritory(Territory &territory)
{
  territory.setPlayer(nullptr);
  auto end = territories.end();
  for (auto it = territories.begin(); it != end; it++)
  {
    if (territory.getName() == (*it)->getName())
    {
      territories.erase(it);
      return;
    }
  }
  throw std::runtime_error("Territory wasn't in the player's list.");
}

/**
 * @brief Player destructor.
 */
Player::~Player()
{
  delete hand;
  delete orders;
}

/**
 * @brief Assignment operator for Player class.
 *
 * @param other The player to copy.
 * @return The reference to the assigned player.
 */
Player &Player::operator=(const Player &other)
{
  if (this == &other)
  {
    return *this;
  }

  this->game = other.game;
  this->orders = other.orders;
  this->hand = other.hand;
  this->territories = other.territories;
  this->reinforcementPool = other.reinforcementPool;
  this->deployedArmiesThisTurn = other.deployedArmiesThisTurn;
  this->name = other.name;
  this->strategy = other.strategy;

  return *this;
}

/**
 * @brief Output operator for Player class.
 *
 * @param out The output stream.
 * @param player The player to output.
 * @return The reference to the output stream.
 */
std::ostream &operator<<(std::ostream &out, const Player &player)
{
  out << "-------------------"
      << "\n";
  for (auto t : player.territories)
  {
    out << *t << "\n";
  }
  out << "-------------------"
      << "\n";
  return out;
}

/**
 * @brief Get the territories owned by the player.
 *
 * @return A pointer to the vector of territories.
 */
std::vector<Territory *> *Player::getTerritories()
{
  return &territories;
}

/**
 * @brief Get the player's hand of cards.
 *
 * @return A pointer to the player's hand.
 */
Hand *Player::getHand()
{
  return hand;
}

/**
 * @brief Get the player's orders list.
 *
 * @return A pointer to the player's orders list.
 */
OrdersList *Player::getOrdersListObject()
{
  return orders;
}

/**
 * @brief Get the current phase of the player.
 *
 * @return The current phase as a string.
 */
string Player::getPhase()
{
  return phase;
}

/**
 * @brief Set the current phase of the player.
 *
 * @param ph The phase to set.
 */
void Player::setPhase(string ph)
{
  phase = std::move(ph);
}

/**
 * @brief Get the reinforcement pool of the player.
 *
 * @return The reinforcement pool.
 */
int Player::getReinforcementPool() const
{
  return reinforcementPool;
}

/**
 * @brief Set the reinforcement pool of the player.
 *
 * @param i The value to set the reinforcement pool.
 */
void Player::setReinforcementPool(int i)
{
  reinforcementPool = i;
}

/**
 * @brief Calculate the continent bonus for the player.
 *
 * This method calculates the bonus the player receives based on owning entire continents.
 *
 * @return The total continent bonus for the player.
 */
int Player::getContinentBonus()
{
  int continentBonusTotal = 0;

  // Iterate over all continents on the map
  for (auto &continent : game->getMap()->continents)
  {
    int numOfTerritoriesInContinentMap = static_cast<int>(continent->territories.size());
    int playerTerritoryIsInContinentCount = 0;

    // Count how many territories the player owns in the continent
    for (auto &territory : territories)
    {
      if (territory->getContinent()->getName() == continent->getName())
      {
        playerTerritoryIsInContinentCount++;
      }
    }

    // If the player owns all territories in the continent, add the continent bonus
    if (playerTerritoryIsInContinentCount == numOfTerritoriesInContinentMap)
    {
      continentBonusTotal += continent->getBonus();
    }
  }
  return continentBonusTotal;
}

/**
 * @brief Get the name of the player.
 *
 * @return The name of the player.
 */
std::string Player::getName() const
{
  return name;
}

/**
 * @brief Add reinforcement armies to the player's reinforcement pool.
 *
 * @param reinforcement The number of reinforcement armies to add.
 */
void Player::addReinforcement(int reinforcement)
{
  reinforcementPool += reinforcement;
}

/**
 * @brief Add a player to the list of friendly players.
 *
 * @param pPlayer The player to add to the friendly players list.
 */
void Player::addFriendly(Player *pPlayer)
{
  friendlyPlayers.push_back(pPlayer);
}

/**
 * @brief Clear the list of friendly players.
 */
void Player::clearFriendly()
{
  friendlyPlayers.erase(friendlyPlayers.begin(), friendlyPlayers.end());
}

/**
 * @brief Check if the player can attack another player.
 *
 * @param pPlayer The player to check for attack eligibility.
 * @return True if the player can attack, false otherwise.
 */
bool Player::canAttack(Player *pPlayer)
{
  if (pPlayer == this)
  {
    return false;
  }

  // Check if the player is in the list of friendly players
  for (auto &player : friendlyPlayers)
  {
    if (player == pPlayer)
    {
      return false;
    }
  }
  return true;
}

/**
 * @brief Find the first neighboring territory of a target territory owned by the player.
 *
 * @param target The target territory.
 * @return A pointer to the first neighboring territory owned by the player.
 */
Territory *Player::findFirstNeighbourTerritory(Territory *target)
{
  for (auto &t : *target->getAdjacentTerritories())
  {
    if (t->getPlayer() == this)
    {
      return t;
    }
  }
  return nullptr;
}

/**
 * @brief Create an order from a card based on the player's strategy.
 *
 * @param card The card to decide the order from.
 * @return The order created from the card.
 */
Order *Player::createOrderFromCard(Card *card)
{
  return strategy->decideCard(card);
}

/**
 * @brief Get a vector of enemy players that the player can attack.
 *
 * @return A vector of enemy players.
 */
std::vector<Player *> Player::getEnemies()
{
  std::vector<Player *> enemies;

  // Iterate over all players in the game
  for (auto p : *game->getPlayers())
  {
    if (this->canAttack(p))
    {
      enemies.push_back(p);
    }
  }
  return enemies;
}

/**
 * @brief Add deployed armies for the current turn.
 *
 * @param a The number of armies deployed.
 */
void Player::addDeployedArmies(int a)
{
  deployedArmiesThisTurn += a;
}

/**
 * @brief Get the number of deployed armies for the current turn.
 *
 * @return The number of deployed armies.
 */
int Player::getDeployedArmiesThisTurn() const
{
  return deployedArmiesThisTurn;
}

/**
 * @brief Clear the deployed armies for the current turn.
 */
void Player::clearDeploymentArmies()
{
  deployedArmiesThisTurn = 0;
}

/**
 * @brief Remove armies from the player's reinforcement pool.
 *
 * @param n The number of armies to remove.
 */
void Player::removeArmies(int n)
{
  reinforcementPool -= n;
  if (reinforcementPool < 0)
  {
    throw std::runtime_error("ASSERT: reinforcementPool overdrawn!");
  }
}

/**
 * @brief Get the GameEngine instance associated with the player.
 *
 * @return A pointer to the GameEngine instance.
 */
GameEngine *Player::getGameInstance()
{
  return game;
}

/**
 * @brief Set the number of deployed armies for the current turn.
 *
 * @param a The number of armies to set.
 */
void Player::setDeployedArmiesThisTurn(int a)
{
  deployedArmiesThisTurn = a;
}

/**
 * @brief Set the player's strategy.
 *
 * @param strategyName The name of the strategy to set.
 */
void Player::setStrategy(const string &strategyName)
{
  strategy = PlayerStrategy::createStrategy(this, strategyName);
}

/**
 * @brief Get the player's strategy.
 *
 * @return A pointer to the player's strategy.
 */
PlayerStrategy *Player::getStrategy() const
{
  return strategy;
}