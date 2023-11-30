#include <iomanip> // To format output.
#include <cstdlib>
#include "Orders.h"
#include "Map/Map.h"
#include "Player/Player.h"

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Orders
//
// -----------------------------------------------------------------------------------------------------------------

/**
 * @brief Overloaded stream insertion operator for the Order class.
 *
 * Outputs the order using the orderCout method.
 *
 * @param stream The output stream.
 * @param o The Order object to output.
 * @return The output stream after processing.
 */
std::ostream &operator<<(std::ostream &stream, const Order &o) { return o.orderCout(stream); }

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                OrdersList
//
// -----------------------------------------------------------------------------------------------------------------

/**
 * @brief Destructor for OrdersList.
 *        Deletes all orders and detaches the log observer from the game.
 */
OrdersList::~OrdersList()
{
  for (auto order : orders)
  {
    delete order;
  }
  if (game)
  {
    Subject::detach((ILogObserver *)game->getLogObserver());
  }
}

/**
 * @brief Copy constructor for OrdersList.
 *        Makes a deep copy of the order list.
 *
 * @param oldList The OrdersList to copy.
 */
OrdersList::OrdersList(const OrdersList &oldList)
    : Subject(oldList)
{
  unsigned listLength = oldList.orders.size();
  orders = std::vector<Order *>(listLength);
  game = oldList.game;
  Subject::attach((ILogObserver *)game->getLogObserver());
  // cloning the same object into another memory slot
  for (unsigned o = 0; o < listLength; o++)
  {
    orders[o] = oldList.orders[o]->clone();
  }
}

/**
 * @brief Adds an order to the order list vector.
 *
 * @param o The Order to add.
 */
void OrdersList::add(Order *o)
{
  if (o)
  {
    orders.push_back(o);
  }
  else
  {
    throw std::runtime_error("Inserting a nullptr in OrderList.");
  }
  Subject::notify(this);
}

/**
 * @brief Removes an order at the specified position.
 *
 * @param pos The position of the order to remove.
 */
void OrdersList::remove(int pos)
{
  unsigned listLength = orders.size();
  // as listLength is 0 the list is empty, no need to remove an order
  if (listLength == 0)
  {
    throw std::runtime_error("The order list is empty, can't remove any more orders.");
  }
  // make sure order position is valid
  else if (pos >= listLength || pos < 0)
  {
    throw std::runtime_error("The inputed position isn't valid, please make another entry.");
  }
  else
  {
    // need to empty memory for dynamically created order objects
    delete orders[pos];
    // when the memory is deleted, need to remove the pointer from the list as well to avoid memory leak
    orders.erase(orders.begin() + pos);
  }
}

/**
 * @brief Moves orders from one position to another.
 *
 * @param pos1 The starting position of the order to move.
 * @param pos2 The destination position of the order to move.
 */
void OrdersList::move(int pos1, int pos2)
{
  // checks number of orders in order list to make sure the move is valid
  unsigned listLength = orders.size();
  // checks if the order list is empty; if so, no need to move anything
  if (listLength == 0)
  {
    std::cout << "Order list is empty, won't move anything." << std::endl;
  }
  // check to make sure user-inputted positions are valid
  else if (pos1 >= listLength || pos2 >= listLength || pos1 < 0 || pos2 < 0)
  {
    throw std::runtime_error("None or only one inputted position is valid. Please try again.");
  }
  else
  {
    // change the 2 pointers together without changing the address of objects that are being pointed to
    Order *temp = orders[pos1];
    orders[pos1] = orders[pos2];
    orders[pos2] = temp;
  }
}

/**
 * @brief Executes all orders in the order list and clears the list.
 */
void OrdersList::execute()
{
  unsigned listLength = orders.size();
  if (listLength == 0)
  {
    throw std::runtime_error("As order list is empty, won't execute an order.");
  }
  else
  {
    for (auto order : orders)
    {
      order->execute();
      delete order;
    }
    orders.clear();
  }
}

/**
 * @brief Assignment operator for OrdersList.
 *        Deep copies the order list from the right-hand side to the left-hand side.
 *
 * @param copyList The OrdersList to copy.
 * @return A reference to the modified OrdersList.
 */
OrdersList &OrdersList::operator=(const OrdersList &copyList)
{
  // let go of left-hand side memory and deep copy to right-hand side
  // checks if we're self-assigning
  if (&copyList == this)
  {
    return *this;
  }

  unsigned initialListLength = orders.size();
  unsigned copyListLength = copyList.orders.size();

  for (int o = 0; o < initialListLength; o++)
  {
    delete orders[o];
  }

  // Grab memory same size as the right-hand side vector
  orders = std::vector<Order *>(copyListLength);

  for (int i = 0; i < copyListLength; i++)
  {
    // clone copied element to left-hand side
    orders[i] = copyList.orders[i]->clone();
  }

  return *this;
}

/**
 * @brief Gets the size of the order list.
 *
 * @return The size of the order list.
 */
size_t OrdersList::getOrdersListSize()
{
  return orders.size();
}

/**
 * @brief Gets the order at the specified index.
 *
 * @param index The index of the order to retrieve.
 * @return The order at the specified index, or nullptr if the index is out of bounds.
 */
Order *OrdersList::getOrder(int index)
{
  if (index < orders.size() && index >= 0)
  {
    return orders[index];
  }
  return nullptr;
}

/**
 * @brief Stream insertion operator for OrdersList.
 *        Outputs the list of orders in the order list.
 *
 * @param stream The output stream.
 * @param ol The OrdersList to output.
 * @return The output stream after processing.
 */
std::ostream &operator<<(std::ostream &stream, const OrdersList &ol)
{
  unsigned listLength = ol.orders.size();

  for (unsigned l = 0; l < listLength; l++)
  {
    stream << l + 1 << " --> " << ol.orders[l]->getLabel() << " // ";
  }
  stream << "\n";
  return stream;
}

/**
 * @brief Gets the vector of orders in the order list.
 *
 * @return A pointer to the vector of orders.
 */
std::vector<Order *> *OrdersList::getList()
{
  return &this->orders;
}

/**
 * @brief Casts the order type to a string.
 *
 * @param o The Order object.
 * @return The string representation of the order type.
 * @throw std::runtime_error if the Order is null.
 */
std::string OrdersList::castOrderType(Order *o)
{
  if (auto advance = dynamic_cast<Advance *>(o))
  {
    return advance->getLabel();
  }
  else if (auto airlift = dynamic_cast<Airlift *>(o))
  {
    return airlift->getLabel();
  }
  else if (auto blockade = dynamic_cast<Blockade *>(o))
  {
    return blockade->getLabel();
  }
  else if (auto bomb = dynamic_cast<Bomb *>(o))
  {
    return bomb->getLabel();
  }
  else if (auto deploy = dynamic_cast<Deploy *>(o))
  {
    return deploy->getLabel();
  }
  else if (auto negotiate = dynamic_cast<Negotiate *>(o))
  {
    return negotiate->getLabel();
  }
  throw std::runtime_error("OrderList::Error Order is null");
}

/**
 * @brief Generates a string representation of the order list for logging purposes.
 *
 * @return The string representation of the order list.
 */
std::string OrdersList::stringToLog()
{
  Order &o = *orders.back();
  std::string orderType = castOrderType(&o);

  std::stringstream ss;
  ss << "ORDER LIST: ";
  ss << "Order List Added ";
  ss << orderType;
  return ss.str();
}

/**
 * @brief Constructor for OrdersList that takes a GameEngine pointer.
 *        Attaches the log observer from the game to the order list.
 *
 * @param gameEngine The GameEngine pointer.
 */
OrdersList::OrdersList(GameEngine *gameEngine)
    : game(gameEngine)
{
  Subject::attach((ILogObserver *)game->getLogObserver());
}

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Advance
//
// -----------------------------------------------------------------------------------------------------------------

/**
 * @brief Constructor for the Advance class.
 *        Initializes an Advance order with the provided parameters and attaches the log observer from the game.
 *
 * @param game The GameEngine pointer.
 * @param source The source territory.
 * @param target The target territory.
 * @param currentPlayer The player initiating the advance order.
 * @param amount The number of armies to advance.
 */
Advance::Advance(GameEngine *game, Territory *source, Territory *target, Player *currentPlayer, int amount)
    : source(source), target(target), currentPlayer(currentPlayer), amount(amount), game(game)
{
  Subject::attach((ILogObserver *)game->getLogObserver());
}

/**
 * @brief Stream insertion operator for Advance class.
 *        Outputs a string indicating an Advance order.
 *
 * @param output The output stream.
 * @return The output stream after processing.
 */
std::ostream &Advance::orderCout(std::ostream &output) const
{
  return output << "-> Advance order.";
}

/**
 * @brief Gets the label of the Advance order.
 *
 * @return The label of the Advance order.
 */
std::string Advance::getLabel() const
{
  return label;
}

/**
 * @brief Static member variable representing the label of the Advance order.
 */
const std::string Advance::label = "Advance";

/**
 * @brief Validates the Advance order.
 *
 * @return True if the order is valid; false otherwise.
 */
bool Advance::validate() const
{
  std::cout << "-> Advance order validation check" << std::endl;

  if (source->getPlayer() != currentPlayer)
  {
    cout << "The source territory is not your own!\n"
         << endl;
    return false;
  }
  else if (!(std::find(source->getAdjacentTerritories()->begin(), source->getAdjacentTerritories()->end(), target) !=
             source->getAdjacentTerritories()->end()))
  {
    cout << "The target territory is not adjacent to the source territory!\n"
         << endl;
    return false;
  }
  else if (amount > source->getArmies())
  {
    cout << "You do not have this many armies in this territory!\n"
         << endl;
    return false;
  }
  else if (amount < 1)
  {
    cout << "Please enter a value that is at least 1 for this order\n"
         << endl;
  }
  cout << "Your order has been validated!\n"
       << endl;
  return true;
}

/**
 * @brief Executes the Advance order.
 *        Transfers armies between territories or simulates an attack.
 */
void Advance::execute()
{
  if (validate())
  {
    std::cout << "Advance execution." << std::endl;
    if (source->getPlayer() == target->getPlayer()) // Transferring army to another territory
    {
      source->setArmies(source->getArmies() - amount);
      target->setArmies(target->getArmies() + amount);
    }
    else // If you try to transfer on enemy territory, considered as an attack.
    {
      if (!currentPlayer->canAttack(target->getPlayer()))
      {
        cout << "You cannot attack this player!\n"
             << endl;
        return;
      }
      attackSimulation(source, target, currentPlayer, amount);
    }
    cout << "Advance has finished executing!\n"
         << endl;
    Subject::notify(this);
  }
}

/**
 * @brief Clones the Advance order.
 *
 * @return A pointer to the cloned Advance order.
 */
Order *Advance::clone() const
{
  return new Advance(*this);
}

/**
 * @brief Generates a string representation of the Advance order for logging purposes.
 *
 * @return The string representation of the Advance order.
 */
std::string Advance::stringToLog()
{
  std::stringstream ss;
  ss << "ORDER: ";
  ss << "Order Executed ";
  ss << *this;
  return ss.str();
}

/**
 * @brief Simulates an attack between territories.
 *
 * @param pSource The source territory.
 * @param pTarget The target territory.
 * @param pCurrentPlayer The player initiating the attack.
 * @param army The number of armies involved in the attack.
 */
void Advance::attackSimulation(Territory *pSource, Territory *pTarget, Player *pCurrentPlayer, int army)
{
  pSource->setArmies(pSource->getArmies() - army); // Attackers leave home territory

  int successAttack = 0;
  int successDefend = 0;

  for (int i = 1; i <= army; i++) // Attacking Phase
  {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> range(0, 100);

    int roll = (int)range(rng) % 100 + 1;
    if (roll <= 60)
    {
      successAttack++;
    }
  }

  for (int i = 1; i <= pTarget->getArmies(); i++) // Defending Phase
  {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> range(0, 100);

    int roll = (int)range(rng) % 100 + 1;

    if (roll <= 70)
    {
      successDefend++;
    }
  }

  int remainingAttackArmies = max(army - successDefend, 0);
  int remainingDefendArmies = max(pTarget->getArmies() - successAttack, 0);

  if (remainingAttackArmies > 0 && remainingDefendArmies == 0) // Win
  {
    cout << "Territory conquered! " << pCurrentPlayer->getName() << " has won this battle for " << pTarget->getName() << "!" << endl;
    if (pTarget->getPlayer() != nullptr)
    {
      pTarget->getPlayer()->removeTerritory(*pTarget);
    }
    pCurrentPlayer->addTerritory(*pTarget); // territory added to the player list

    // give the player an army card from the deck (if there is one)
    if (!pCurrentPlayer->getGameInstance()->getDeck()->getDeckCards()->empty())
    {
      cout << pCurrentPlayer->getName() << " has won a card" << endl;
      pCurrentPlayer->getGameInstance()->getDeck()->draw(*pCurrentPlayer->getHand());
    }
  }
  else // Lose. A draw is considered an army loss. If any, attackers retreat. If any, defenders retreat.
  {
    cout << "Territory " << pTarget->getName() << " has not been conquered. " << pCurrentPlayer->getName() << " has lost this battle!" << endl;
    pSource->setArmies(pSource->getArmies() + remainingAttackArmies); // Attackers retreat
    pTarget->setArmies(remainingDefendArmies);
  }

  if (pSource->getArmies() == 0)
  {
    cout << pCurrentPlayer->getName() << " has lost their territory: " + pSource->getName() + " in the process!" << endl;
    if (pSource->getPlayer() != nullptr)
    {
      pSource->getPlayer()->removeTerritory(*pSource);
    }
    pSource->setPlayer(nullptr);
  }

  if (pTarget->getArmies() == 0)
  {
    if (pTarget->getPlayer() != nullptr)
    {
      cout << pTarget->getPlayer()->getName() << " has lost their territory " + pTarget->getName() + " in the process!\n"
           << endl;
      pTarget->getPlayer()->removeTerritory(*pTarget);
    }
    pTarget->setPlayer(nullptr);
  }
}

/**
 * @brief Destructor for the Advance class.
 *        Detaches the log observer from the game.
 */
Advance::~Advance()
{
  if (game)
  {
    Subject::detach((ILogObserver *)game->getLogObserver());
  }
}

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Airlift
//
// -----------------------------------------------------------------------------------------------------------------

/**
 * @brief Constructor for the Airlift class.
 *        Initializes an Airlift order with the provided parameters and attaches the log observer from the game.
 *
 * @param game The GameEngine pointer.
 * @param source The source territory.
 * @param target The target territory.
 * @param currentPlayer The player initiating the airlift order.
 * @param amount The number of armies to airlift.
 */
Airlift::Airlift(GameEngine *game, Territory *source, Territory *target, Player *currentPlayer, int amount)
    : source(source), target(target), currentPlayer(currentPlayer), amount(amount), game(game)
{
  Subject::attach((ILogObserver *)game->getLogObserver());
}

/**
 * @brief Static member variable representing the label of the Airlift order.
 */
const std::string Airlift::label = "Airlift";

/**
 * @brief Gets the label of the Airlift order.
 *
 * @return The label of the Airlift order.
 */
std::string Airlift::getLabel() const
{
  return label;
}

/**
 * @brief Stream insertion operator for Airlift class.
 *        Outputs a string indicating an Airlift order.
 *
 * @param output The output stream.
 * @return The output stream after processing.
 */
std::ostream &Airlift::orderCout(std::ostream &output) const
{
  return output << "-> Airlift order.";
}

/**
 * @brief Validates the Airlift order.
 *
 * @return True if the order is valid; false otherwise.
 */
bool Airlift::validate() const
{
  std::cout << "-> Airlift order validation check" << std::endl;
  if (source->getPlayer() != currentPlayer && target->getPlayer() != currentPlayer)
  {
    cout << "The territory is not your own!\n"
         << endl;
    return false;
  }
  else if (amount > source->getArmies())
  {
    cout << "You do not have this many armies in this territory!\n"
         << endl;
  }
  else if (amount < 1)
  {
    cout << "Please enter a value that is at least 1 for this order\n"
         << endl;
  }
  cout << "Your order has been validated!\n"
       << endl;
  return true;
}

/**
 * @brief Executes the Airlift order.
 *        Transfers armies between territories.
 */
void Airlift::execute()
{
  if (validate())
  {
    std::cout << "Airlift execution." << std::endl;
    if (source->getPlayer() == target->getPlayer()) // Transferring army to another territory
    {
      source->setArmies(source->getArmies() - amount);
      target->setArmies(target->getArmies() + amount);
    }
    if (source->getArmies() == 0)
    {
      if (source->getPlayer())
      {
        source->getPlayer()->removeTerritory(*source);
      }
      source->setPlayer(nullptr);
    }
    Subject::notify(this);
  }
}

/**
 * @brief Clones the Airlift order.
 *
 * @return A pointer to the cloned Airlift order.
 */
Order *Airlift::clone() const
{
  return new Airlift(*this);
}

/**
 * @brief Generates a string representation of the Airlift order for logging purposes.
 *
 * @return The string representation of the Airlift order.
 */
std::string Airlift::stringToLog()
{
  std::stringstream ss;
  ss << "ORDER: ";
  ss << "Order Executed ";
  ss << *this;
  return ss.str();
}

/**
 * @brief Destructor for the Airlift class.
 *        Detaches the log observer from the game.
 */
Airlift::~Airlift()
{
  if (game)
  {
    Subject::detach((ILogObserver *)game->getLogObserver());
  }
}

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Blockade
//
// -----------------------------------------------------------------------------------------------------------------

/**
 * @brief Constructor for the Blockade class.
 *        Initializes a Blockade order with the provided parameters and attaches the log observer from the game.
 *
 * @param game The GameEngine pointer.
 * @param target The target territory for the blockade.
 * @param currentPlayer The player initiating the blockade order.
 */
Blockade::Blockade(GameEngine *game, Territory *target, Player *currentPlayer)
    : target(target), currentPlayer(currentPlayer), game(game)
{
  Subject::attach((ILogObserver *)game->getLogObserver());
}

/**
 * @brief Static member variable representing the label of the Blockade order.
 */
const std::string Blockade::label = "Blockade";

/**
 * @brief Gets the label of the Blockade order.
 *
 * @return The label of the Blockade order.
 */
std::string Blockade::getLabel() const
{
  return label;
}

/**
 * @brief Stream insertion operator for Blockade class.
 *        Outputs a string indicating a Blockade order.
 *
 * @param output The output stream.
 * @return The output stream after processing.
 */
std::ostream &Blockade::orderCout(std::ostream &output) const
{
  return output << "-> Blockade order.";
}

/**
 * @brief Validates the Blockade order.
 *
 * @return True if the order is valid; false otherwise.
 */
bool Blockade::validate() const
{
  std::cout << "-> Blockade order validation check" << std::endl;
  if (target->getPlayer() != currentPlayer)
  {
    cout << "This is not your territory! This order can only be played on your own territory!\n"
         << endl;
    return false;
  }
  cout << "Your order has been validated!\n"
       << endl;
  return true;
}

/**
 * @brief Executes the Blockade order.
 *        Triples the armies in the target territory, removes it from the player's territory list, and sets the player to null (neutral).
 */
void Blockade::execute()
{
  if (validate())
  {
    std::cout << "Blockade execution." << std::endl;
    target->setArmies(target->getArmies() * 3);
    if (target->getPlayer())
    {
      target->getPlayer()->removeTerritory(*target);
    }
    target->setPlayer(nullptr); // Transfer to neutral
    cout << "Blockade has finished executing!\n"
         << endl;
    Subject::notify(this);
  }
}

/**
 * @brief Clones the Blockade order.
 *
 * @return A pointer to the cloned Blockade order.
 */
Order *Blockade::clone() const
{
  return new Blockade(*this);
}

/**
 * @brief Generates a string representation of the Blockade order for logging purposes.
 *
 * @return The string representation of the Blockade order.
 */
std::string Blockade::stringToLog()
{
  std::stringstream ss;
  ss << "ORDER: ";
  ss << "Order Executed ";
  ss << *this;
  return ss.str();
}

/**
 * @brief Destructor for the Blockade class.
 *        Detaches the log observer from the game.
 */
Blockade::~Blockade()
{
  if (game)
  {
    Subject::detach((ILogObserver *)game->getLogObserver());
  }
}

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Bomb
//
// -----------------------------------------------------------------------------------------------------------------

/**
 * @brief Constructor for the Bomb class.
 *        Initializes a Bomb order with the provided parameters and attaches the log observer from the game.
 *
 * @param game The GameEngine pointer.
 * @param target The target territory for the bomb.
 * @param currentPlayer The player initiating the bomb order.
 */
Bomb::Bomb(GameEngine *game, Territory *target, Player *currentPlayer)
    : target(target), currentPlayer(currentPlayer), game(game)
{
  Subject::attach((ILogObserver *)game->getLogObserver());
}

/**
 * @brief Static member variable representing the label of the Bomb order.
 */
const std::string Bomb::label = "Bomb";

/**
 * @brief Gets the label of the Bomb order.
 *
 * @return The label of the Bomb order.
 */
std::string Bomb::getLabel() const
{
  return label;
}

/**
 * @brief Stream insertion operator for Bomb class.
 *        Outputs a string indicating a Bomb order.
 *
 * @param output The output stream.
 * @return The output stream after processing.
 */
std::ostream &Bomb::orderCout(std::ostream &output) const
{
  return output << "-> Bomb order.";
}

/**
 * @brief Validates the Bomb order.
 *
 * @return True if the order is valid; false otherwise.
 */
bool Bomb::validate() const
{
  std::cout << "-> Bomb order validation check" << std::endl;
  if (target->getPlayer() == currentPlayer)
  {
    cout << "This territory is your own!\n"
         << endl;
    return false;
  }
  cout << "Your order has been validated!\n"
       << endl;
  return true;
}

/**
 * @brief Executes the Bomb order.
 *        Reduces the target territory's armies to half (rounded up) and removes the territory from the current player if armies become zero.
 */
void Bomb::execute()
{

  if (validate())
  {
    if (!currentPlayer->canAttack(target->getPlayer()))
    {
      cout << "You cannot attack this player!\n"
           << endl;
      return;
    }
    std::cout << "Bomb execution." << std::endl;
    target->setArmies((target->getArmies() / 2) + 1);
    // if target army is cleared. Remove player from ownership
    if (target->getArmies() == 0)
    {
      if (target->getPlayer())
      {
        target->getPlayer()->removeTerritory(*target);
      }
      target->setPlayer(nullptr);
    }
    cout << "Bomb has finished executing!\n"
         << endl;
    Subject::notify(this);
  }
}

/**
 * @brief Clones the Bomb order.
 *
 * @return A pointer to the cloned Bomb order.
 */
Order *Bomb::clone() const
{
  return new Bomb(*this);
}

/**
 * @brief Generates a string representation of the Bomb order for logging purposes.
 *
 * @return The string representation of the Bomb order.
 */
std::string Bomb::stringToLog()
{
  std::stringstream ss;
  ss << "ORDER: ";
  ss << "Order Executed ";
  ss << *this;
  return ss.str();
}

/**
 * @brief Destructor for the Bomb class.
 *        Detaches the log observer from the game.
 */
Bomb::~Bomb()
{
  if (game)
  {
    Subject::detach((ILogObserver *)game->getLogObserver());
  }
}

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Deploy
//
// -----------------------------------------------------------------------------------------------------------------

/**
 * @brief Constructor for the Deploy class.
 *        Initializes a Deploy order with the provided parameters and attaches the log observer from the game.
 *
 * @param game The GameEngine pointer.
 * @param target The target territory for deploying armies.
 * @param currentPlayer The player initiating the deploy order.
 * @param amount The number of armies to deploy.
 */
Deploy::Deploy(GameEngine *game, Territory *target, Player *currentPlayer, int amount)
    : target(target), currentPlayer(currentPlayer), amount(amount), game(game)
{
  Subject::attach((ILogObserver *)game->getLogObserver());
}

/**
 * @brief Static member variable representing the label of the Deploy order.
 */
const std::string Deploy::label = "Deploy";

/**
 * @brief Gets the label of the Deploy order.
 *
 * @return The label of the Deploy order.
 */
std::string Deploy::getLabel() const
{
  return label;
}

/**
 * @brief Stream insertion operator for Deploy class.
 *        Outputs a string indicating a Deploy order.
 *
 * @param output The output stream.
 * @return The output stream after processing.
 */
std::ostream &Deploy::orderCout(std::ostream &output) const
{
  return output << "-> Deploy order.";
}

/**
 * @brief Validates the Deploy order.
 *
 * @return True if the order is valid; false otherwise.
 */
bool Deploy::validate() const
{
  std::cout << "-> Deploy order validation check" << std::endl;

  if (target->getPlayer() != currentPlayer)
  {
    cout << "You do not own this territory!\n"
         << endl;
    return false;
  }
  else if (amount > currentPlayer->getReinforcementPool())
  {
    cout << "You do not have this many armies in the reinforcement pool!\n"
         << endl;
    return false;
  }
  else if (amount < 1)
  {
    cout << "Please enter a value that is at least 1 for this order\n"
         << endl;
    return false;
  }
  cout << "Your order has been validated!\n"
       << endl;
  return true;
}

/**
 * @brief Executes the Deploy order.
 *        Adds the specified number of armies to the target territory and removes them from the current player's reinforcement pool.
 */
void Deploy::execute()
{
  if (validate())
  {
    std::cout << "Deploy execution." << std::endl;
    target->setArmies(amount + target->getArmies());
    currentPlayer->removeArmies(amount);
    cout << "Deploy has finished executing!\n"
         << endl;
    Subject::notify(this);
  }
}

/**
 * @brief Clones the Deploy order.
 *
 * @return A pointer to the cloned Deploy order.
 */
Order *Deploy::clone() const
{
  return new Deploy(*this);
}

/**
 * @brief Generates a string representation of the Deploy order for logging purposes.
 *
 * @return The string representation of the Deploy order.
 */
std::string Deploy::stringToLog()
{
  std::stringstream ss;
  ss << "ORDER: ";
  ss << "Order Executed ";
  ss << *this;
  return ss.str();
}

/**
 * @brief Destructor for the Deploy class.
 *        Detaches the log observer from the game.
 */
Deploy::~Deploy()
{
  if (game)
  {
    Subject::detach((ILogObserver *)game->getLogObserver());
  }
}

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Negotiate
//
// -----------------------------------------------------------------------------------------------------------------

/**
 * @brief Constructor for the Negotiate class.
 *        Initializes a Negotiate order with the provided parameters and attaches the log observer from the game.
 *
 * @param game The GameEngine pointer.
 * @param targetPlayer The player to negotiate with.
 * @param currentPlayer The player initiating the negotiate order.
 */
Negotiate::Negotiate(GameEngine *game, Player *targetPlayer, Player *currentPlayer)
    : targetPlayer(targetPlayer), currentPlayer(currentPlayer), game(game)
{
  Subject::attach((ILogObserver *)game->getLogObserver());
}

/**
 * @brief Static member variable representing the label of the Negotiate order.
 */
const std::string Negotiate::label = "Negotiate";

/**
 * @brief Gets the label of the Negotiate order.
 *
 * @return The label of the Negotiate order.
 */
std::string Negotiate::getLabel() const
{
  return label;
}

/**
 * @brief Validates the Negotiate order.
 *
 * @return True if the order is valid; false otherwise.
 */
bool Negotiate::validate() const
{
  std::cout << "-> Negotiate order validation check" << std::endl;
  if (targetPlayer == currentPlayer)
  {
    cout << "You cannot negotiate with yourself.\n"
         << endl;
    return false;
  }
  cout << "Your order has been validated.\n"
       << endl;
  return true;
}

/**
 * @brief Executes the Negotiate order.
 *        Adds both players to each other's friendly list.
 */
void Negotiate::execute()
{
  if (validate())
  {
    std::cout << "Negotiate execution." << std::endl;
    currentPlayer->addFriendly(targetPlayer);
    targetPlayer->addFriendly(currentPlayer);
  }
  cout << "Negotiate has finished executing." << endl;
  Subject::notify(this);
}

/**
 * @brief Clones the Negotiate order.
 *
 * @return A pointer to the cloned Negotiate order.
 */
Order *Negotiate::clone() const
{
  return new Negotiate(*this);
}

/**
 * @brief Stream insertion operator for Negotiate class.
 *        Outputs a string indicating a Negotiate order.
 *
 * @param ostream The output stream.
 * @return The output stream after processing.
 */
std::ostream &Negotiate::orderCout(std::ostream &ostream) const
{
  return ostream << "-> Negotiate order.";
}

/**
 * @brief Generates a string representation of the Negotiate order for logging purposes.
 *
 * @return The string representation of the Negotiate order.
 */
std::string Negotiate::stringToLog()
{
  std::stringstream ss;
  ss << "ORDER: ";
  ss << "Order Executed ";
  ss << *this;
  return ss.str();
}

/**
 * @brief Destructor for the Negotiate class.
 *        Detaches the log observer from the game.
 */
Negotiate::~Negotiate()
{
  if (game)
  {
    Subject::detach((ILogObserver *)game->getLogObserver());
  }
}