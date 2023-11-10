#include <iomanip> // To format output.
#include <cstdlib>
#include "Orders.h"
#include "Map/Map.h"
#include "Player/Player.h"
/**
 * @file Orders.cpp
 * @brief This file contains the implementation of various order types for a strategy game.
 * It includes classes such as OrdersList, Advance, Airlift, Blockade, Bomb, Deploy, and Negotiate,
 * each representing a different type of game action.
 */

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Orders
//
// -----------------------------------------------------------------------------------------------------------------
/**
 * @brief Overload the << operator for outputting Order objects.
 * @param stream The output stream.
 * @param o The Order object to be outputted.
 * @return Returns the modified output stream.
 */
std::ostream &operator<<(std::ostream &stream, const Order &o) { return o.orderCout(stream); }




// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                OrdersList
//
// -----------------------------------------------------------------------------------------------------------------

/**
 * Destructor
 */
/**
 * @brief Destructor for the OrdersList class.
 * Cleans up the dynamically allocated orders and detaches the observer if a game is associated.
 */
OrdersList::~OrdersList(){
  for(auto order: orders){ delete order; }
  if(game){Subject::detach((ILogObserver* )game->getLogObserver());}
}

/**
 * @brief Copy constructor for the OrdersList class.
 * Performs a deep copy of the order list from another OrdersList instance.
 * @param oldList The OrdersList instance to be copied.
 */
OrdersList::OrdersList(const OrdersList &oldList)
 : Subject(oldList) {
  unsigned listLength = oldList.orders.size();
  orders = std::vector<Order *>(listLength);
  game = oldList.game;
  Subject::attach((ILogObserver*)game->getLogObserver());
  // cloning the same object into another memory slot
  for (unsigned o = 0; o < listLength; o++) { orders[o] = oldList.orders[o]->clone(); }
}

/**
 * @brief Adds an Order to the order list.
 * Throws a runtime error if a nullptr is passed.
 * @param o Pointer to the Order object to be added.
 */
void OrdersList::add(Order *o)
{
  if(o){ orders.push_back(o); } else { throw std::runtime_error("Inserting a nullptr in OrderList."); }
  Subject::notify(this);
}

/**
 * @brief Removes an Order from the order list at a specified position.
 * Throws a runtime error if the list is empty or if the position is invalid.
 * @param pos The position of the Order in the list to be removed.
 */
void OrdersList::remove(int pos)
{
  unsigned listLength = orders.size();
  // as listLength is 0 the list is empty no need to remove an order
  if (listLength == 0){
    throw std::runtime_error("The order list is empty, can't remove any more orders.");
  }
    // make sure order position is valid
  else if (pos >= listLength || pos < 0) {
    throw std::runtime_error("The inputed position isn't valid please make another entry.");
  }
  else
  {
    // need to empty memory for dynamically created order objs
    delete orders[pos];
    // when the memory is deleted need to remove the pointer from the list as well to avoid memory leak
    orders.erase(orders.begin() + pos);
  }
}

/**
 * @brief Moves an Order within the list from one position to another.
 * Throws a runtime error if positions are invalid or if the list is empty.
 * @param pos1 The original position of the Order.
 * @param pos2 The new position of the Order.
 */
void OrdersList::move(int pos1, int pos2)
{
  // checks number of orders in order list to make sure the move is valid
  unsigned listLength = orders.size();
  // checks if the order list is empty if so no need to move anything
  if (listLength == 0){
    std::cout << "Order list is empty, won't move anything." << std::endl;
  }
  else if (listLength == 1)
  {
    throw std::runtime_error("There is only one order in the list, need more than one orders for the move.");
  }
    // check to make sure user inputted positions are valid
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
 * @brief Executes all Orders in the order list.
 * Throws a runtime error if the order list is empty.
 */
void OrdersList::execute()
{
  unsigned listLength = orders.size();
  if (listLength == 0){
    throw std::runtime_error("As order list is empty won't execute an order.");
  }
  else
  {
    for(auto order : orders){
      order->execute();
      delete order;
    }
    orders.clear();
  }
}

/**
 * @brief Overloads the assignment operator for the OrdersList class.
 * Performs a deep copy of the orders from another OrdersList instance.
 * @param copyList The OrdersList instance to be copied.
 * @return Returns a reference to the copied OrdersList.
 */
OrdersList &OrdersList::operator=(const OrdersList &copyList)
{
  // let go of left hand side memory and deep copy to right hand side
  // checks if we're self assigning
  if (&copyList == this){
    return *this;
  }

  unsigned initialListLength = orders.size();
  unsigned copyListLength = copyList.orders.size();

  for (int o = 0; o < initialListLength; o++) { delete orders[o]; }

  // Grab memory same size as the right hand side vector
  orders = std::vector<Order *>(copyListLength);


  for (int i = 0; i < copyListLength; i++) {
    // clone copied element to left hand side
    orders[i] = copyList.orders[i]->clone();
  }

  return *this;
}

/**
 * @brief Gets the size of the order list.
 * @return Returns the number of Orders in the list.
 */
size_t OrdersList::getOrdersListSize()
{
    return orders.size();
}

/**
 * @brief Retrieves an Order from the order list at a specific index.
 * @param index The index of the Order to retrieve.
 * @return Returns a pointer to the Order at the specified index or nullptr if the index is invalid.
 */
Order* OrdersList::getOrder(int index)
{
    if(index < orders.size() && index >= 0)
    {
        return orders[index];
    }
    return nullptr;
}

/**
 * @brief Overloads the << operator for outputting OrdersList objects.
 * @param stream The output stream.
 * @param ol The OrdersList object to be outputted.
 * @return Returns the modified output stream.
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

std::vector<Order *> *OrdersList::getList() {
  return &this->orders;
}

/**
 * @brief Determines the type of an Order object.
 * Throws a runtime error if the Order object is null.
 * @param o Pointer to the Order object whose type is to be determined.
 * @return Returns a string representing the type of the Order.
 */
std::string OrdersList::castOrderType(Order * o){
  if(auto advance = dynamic_cast<Advance*>(o)){
      return advance->getLabel();
  }
  else if(auto airlift = dynamic_cast<Airlift*>(o)){
      return airlift->getLabel();
  }
  else if(auto blockade = dynamic_cast<Blockade*>(o)){
      return blockade->getLabel();
  }
  else if(auto bomb = dynamic_cast<Bomb*>(o)){
      return bomb->getLabel();
  }
  else if(auto deploy = dynamic_cast<Deploy*>(o)){
      return deploy->getLabel();
  }
  else if(auto negotiate = dynamic_cast<Negotiate*>(o)){
      return negotiate->getLabel();
  }
  throw std::runtime_error("OrderList::Error Order is null");
}

/**
 * @brief Converts the most recent Order in the list to a string for logging purposes.
 * @return Returns a string representing the most recent Order.
 */
std::string OrdersList::stringToLog() {
  Order &o = *orders.back();
  std::string orderType = castOrderType(&o);

  std::stringstream ss;
  ss << "ORDER LIST: ";
  ss << "Order List Added ";
  ss << orderType;
  return ss.str();
}
OrdersList::OrdersList(GameEngine *gameEngine) : game(gameEngine) {
  Subject::attach((ILogObserver*)game->getLogObserver());
}


// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Advance
//
// -----------------------------------------------------------------------------------------------------------------

/**
 * @brief Constructor for the Advance class.
 * Initializes an Advance order with game engine, source and target territories, current player, and army amount.
 * @param game Pointer to the GameEngine.
 * @param source Pointer to the source Territory.
 * @param target Pointer to the target Territory.
 * @param currentPlayer Pointer to the current Player.
 * @param amount The number of armies involved in the Advance order.
 */
Advance::Advance(GameEngine* game, Territory* source, Territory* target, Player* currentPlayer, int amount) : source(source), target(target), currentPlayer(currentPlayer), amount(amount), game(game){
  Subject::attach((ILogObserver*)game->getLogObserver());
}

/**
 * @brief Outputs the Advance order details to the provided stream.
 * @param output The output stream.
 * @return Returns the modified output stream.
 */
std::ostream &Advance::orderCout(std::ostream &output) const { return output << "-> Advance order."; }

/**
 * @brief Retrieves the label of the Advance order.
 * @return Returns a string representing the label of the Advance order.
 */
std::string Advance::getLabel() const { return label; }

const std::string Advance::label = "Advance";

/**
 * @brief Validates the Advance order based on game rules.
 * @return Returns true if the order is valid, false otherwise.
 */
bool Advance::validate() const
{
  std::cout << "-> Advance order validation check" << std::endl;

    if (source->getPlayer() != currentPlayer)
    {
        cout << "The source territory is not your own!\n" << endl;
        return false;
    }

    else if (!(std::find(source->getAdjacentTerritories()->begin(), source->getAdjacentTerritories()->end(), target) != source->getAdjacentTerritories()->end()))
    {
        cout << "The target territory is not adjacent to the source territory!\n" << endl;
        return false;
    }
    else if (amount > source->getArmies())
    {
        cout << "You do not have this many armies in this territory!\n" << endl;
        return false;
    }
    else if (amount < 1)
    {
        cout << "Please enter a value that is at least 1 for this order\n" << endl;
    }
    cout << "Your order has been validated!\n" << endl;
  return true;
}

/**
 * @brief Executes the Advance order if it is valid.
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
        else // If you try to transfer on enemy territory, considered as attack.
        {
            if (!currentPlayer->canAttack(target->getPlayer()))
            {
                cout << "You cannot attack this player!\n" << endl;
                return;
            }
            attackSimulation(source, target, currentPlayer, amount);
        }
        cout << "Advance has finished executing!\n" << endl;
        Subject::notify(this);
    }
}

/**
 * @brief Clones the Advance order.
 * @return Returns a new Advance order object that is a clone of the current object.
 */
Order *Advance::clone() const { return new Advance(*this); }

/**
 * @brief Converts the Advance order to a string for logging purposes.
 * @return Returns a string representing the Advance order.
 */
std::string Advance::stringToLog() {
  std::stringstream ss;
  ss << "ORDER: ";
  ss << "Order Executed ";
  ss << *this;
  return ss.str();
}

/**
 * @brief Simulates an attack in the game, managing army movements and battle outcomes.
 *
 * This function simulates an attack from a source territory to a target territory. It involves
 * calculating success rates for both attacking and defending armies, updating army counts,
 * and handling territory ownership changes based on the outcome of the attack.
 *
 * @param pSource Pointer to the source territory from which the attack is initiated.
 * @param pTarget Pointer to the target territory being attacked.
 * @param pCurrentPlayer Pointer to the player performing the attack.
 * @param army Number of armies involved in the attack.
 */
void Advance::attackSimulation(Territory* pSource, Territory* pTarget, Player* pCurrentPlayer, int army) {
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
    if(pTarget->getPlayer() != nullptr){
      pTarget->getPlayer()->removeTerritory(*pTarget);
    }
    pCurrentPlayer->addTerritory(*pTarget);// territory added to player list
    pTarget->setArmies(remainingAttackArmies); // Attackers advance to conquered territory

    // give player army card from deck (if there is one)
    if(!pCurrentPlayer->getGameInstance()->getDeck()->getDeckCards()->empty()){
      cout << pCurrentPlayer->getName() <<" has won a card" << endl;
      pCurrentPlayer->getGameInstance()->getDeck()->draw(*pCurrentPlayer->getHand());
    }
  }
  else // Lose. A draw is considered army loss. If any, attackers retreat. If any, defenders retreat.
  {
    cout << "Territory " << pTarget->getName() << " has not been conquered. " << pCurrentPlayer->getName() << " has lost this battle!" << endl;
    pSource->setArmies(pSource->getArmies() + remainingAttackArmies); // Attackers retreat
    pTarget->setArmies(remainingDefendArmies);
  }

  if (pSource->getArmies() == 0)
  {
    cout << pCurrentPlayer->getName()  << " has lost their territory: " + pSource->getName() + " in the process!" << endl;
    if(pSource->getPlayer() != nullptr){
      pSource->getPlayer()->removeTerritory(*pSource);
    }
    pSource->setPlayer(nullptr);
  }

  if (pTarget->getArmies() == 0)
  {
    if(pTarget->getPlayer() != nullptr){
      cout << pTarget->getPlayer()->getName() << " has lost their territory " + pTarget->getName() + " in the process!\n" << endl;
      pTarget->getPlayer()->removeTerritory(*pTarget);
    }
    pTarget->setPlayer(nullptr);
  }
}

/**
 * @brief Destructor for the Advance class.
 *
 * Detaches the log observer from the game instance, if it exists.
 */
Advance::~Advance() {
  if(game){ Subject::detach((ILogObserver* )game->getLogObserver()); }
}


// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Airlift
//
// -----------------------------------------------------------------------------------------------------------------
/**
 * @brief Constructs an Airlift order with the specified parameters.
 *
 * This constructor initializes an Airlift order, attaching a log observer to the game instance.
 *
 * @param game Pointer to the game engine.
 * @param source Pointer to the source territory for the airlift.
 * @param target Pointer to the target territory for the airlift.
 * @param currentPlayer Pointer to the player issuing the order.
 * @param amount Number of armies to be airlifted.
 */
Airlift::Airlift(GameEngine* game, Territory* source, Territory* target, Player* currentPlayer, int amount) : source(source), target(target), currentPlayer(currentPlayer), amount(amount), game(game){
  Subject::attach((ILogObserver*)game->getLogObserver());
}

const std::string Airlift::label = "Airlift";

/**
 * @brief Returns the label of the Airlift order.
 * 
 * @return A string representing the label of the Airlift order.
 */
std::string Airlift::getLabel() const { return label; }

/**
 * @brief Outputs the Airlift order details to an output stream.
 * 
 * @param output The output stream.
 * @return A reference to the output stream.
 */
std::ostream &Airlift::orderCout(std::ostream &output) const { return output << "-> Airlift order."; }

/**
 * @brief Validates the Airlift order.
 * 
 * Checks if the Airlift order is valid based on the game state, such as ownership of territories and army counts.
 * 
 * @return True if the order is valid, false otherwise.
 */
bool Airlift::validate() const
{
  std::cout << "-> Airlift order validation check" << std::endl;
    if (source->getPlayer() != currentPlayer && target->getPlayer() != currentPlayer)
    {
        cout << "The territory is not your own!\n" << endl;
        return false;
    }
    else if (amount > source->getArmies())
    {
        cout << "You do not have this many armies in this territory!\n" << endl;
    }
    else if (amount < 1)
    {
        cout << "Please enter a value that is at least 1 for this order\n" << endl;
    }
    cout << "Your order has been validated!\n" << endl;
  return true;
}

/**
 * @brief Executes the Airlift order.
 * 
 * Transfers armies from the source territory to the target territory if the order is valid.
 */
void Airlift::execute()
{
  if (validate()) {
      std::cout << "Airlift execution." << std::endl;
      if (source->getPlayer() == target->getPlayer()) // Transferring army to another territory
      {
          source->setArmies(source->getArmies() - amount);
          target->setArmies(target->getArmies() + amount);
      }
      if(source->getArmies() == 0){
        if(source->getPlayer()){
          source->getPlayer()->removeTerritory(*source);
        }
        source->setPlayer(nullptr);
      }
      Subject::notify(this);
  }
}


/**
 * @brief Creates a clone of the Airlift order.
 * 
 * @return A pointer to the cloned Airlift order.
 */
Order *Airlift::clone() const { return new Airlift(*this); }

/**
 * @brief Generates a string representation of the Airlift order for logging purposes.
 * 
 * @return A string representing the executed Airlift order.
 */
std::string Airlift::stringToLog() {
  std::stringstream ss;
  ss << "ORDER: ";
  ss << "Order Executed ";
  ss << *this;
  return ss.str();
}

/**
 * @brief Destructor for the Airlift class.
 *
 * Detaches the log observer from the game instance, if it exists.
 */
Airlift::~Airlift() {
  if(game){ Subject::detach((ILogObserver* )game->getLogObserver()); }
}


// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Blockade
//
// -----------------------------------------------------------------------------------------------------------------
/**
 * @class Blockade
 * @brief Represents a Blockade order in the game.
 *
 * The Blockade order triples the number of armies on a territory and then makes it neutral.
 */
Blockade::Blockade(GameEngine* game, Territory* target, Player* currentPlayer) : target(target), currentPlayer(currentPlayer), game(game){
  Subject::attach((ILogObserver*)game->getLogObserver());
}

const std::string Blockade::label = "Blockade";

/**
 * @brief Get the label of the Blockade order.
 * @return The label of the Blockade order.
 */
std::string Blockade::getLabel() const { return label; }

/**
 * @brief Output the Blockade order to the output stream.
 * @param output The output stream.
 * @return The output stream.
 */
std::ostream &Blockade::orderCout(std::ostream &output) const { return output << "-> Blockade order."; }

/**
 * @brief Validate the Blockade order.
 * @return True if the order is valid, false otherwise.
 */
bool Blockade::validate() const
{
  std::cout << "-> Blockade order validation check" << std::endl;
    if(target->getPlayer() != currentPlayer)
    {
        cout << "This is not your territory! This order can only be played on your own territory!\n" << endl;
        return false;
    }
    cout << "Your order has been validated!\n" << endl;
  return true;
}

/**
 * @brief Execute the Blockade order.
 */
void Blockade::execute()
{
  if (validate()) {
      std::cout << "Blockade execution." << std::endl;
      target->setArmies(target->getArmies() * 3);
      if(target->getPlayer()){
        target->getPlayer()->removeTerritory(*target);
      }
      target->setPlayer(nullptr); // Transfer to neutral
      cout << "Blockade has finished executing!\n" << endl;
      Subject::notify(this);
  }
}

/**
 * @brief Clone the Blockade order.
 * @return A pointer to the cloned Blockade order.
 */
Order *Blockade::clone() const { return new Blockade(*this); }

/**
 * @brief Convert the Blockade order to a string for logging purposes.
 * @return The string representation of the Blockade order.
 */
std::string Blockade::stringToLog() {
  std::stringstream ss;
  ss << "ORDER: ";
  ss << "Order Executed ";
  ss << *this;
  return ss.str();
}
Blockade::~Blockade() {
  if(game){Subject::detach((ILogObserver* )game->getLogObserver());}
}


// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Bomb
//
// -----------------------------------------------------------------------------------------------------------------


Bomb::Bomb(GameEngine* game, Territory* target, Player* currentPlayer) : target(target), currentPlayer(currentPlayer), game(game){
  Subject::attach((ILogObserver*)game->getLogObserver());
}

const std::string Bomb::label = "Bomb";

/**
 * @brief Get the label of the Bomb order.
 * @return The label of the Bomb order.
 */
std::string Bomb::getLabel() const { return label; }

/**
 * @brief Output the Bomb order to the output stream.
 * @param output The output stream.
 * @return The output stream.
 */
std::ostream &Bomb::orderCout(std::ostream &output) const { return output << "-> Bomb order."; }

/**
 * @brief Validate the Bomb order.
 * @return True if the order is valid, false otherwise.
 */
bool Bomb::validate() const
{
  std::cout << "-> Bomb order validation check" << std::endl;
    if(target->getPlayer() == currentPlayer)
    {
        cout << "This territory is your own!\n" << endl;
        return false;
    }
    cout << "Your order has been validated!\n" << endl;
  return true;
}

/**
 * @brief Execute the Bomb order.
 */
void Bomb::execute()
{

  if (validate()) {
      if (!currentPlayer->canAttack(target->getPlayer()))
      {
          cout << "You cannot attack this player!\n" << endl;
          return;
      }
      std::cout << "Bomb execution." << std::endl;
      target->setArmies((target->getArmies() / 2) + 1);
      // if target army is cleared. Remove player from ownership
      if(target->getArmies() == 0){
        if(target->getPlayer()){
          target->getPlayer()->removeTerritory(*target);
        }
        target->setPlayer(nullptr);
      }
      cout << "Bomb has finished executing!\n" << endl;
      Subject::notify(this);
  }
}

/**
 * @brief Clone the Bomb order.
 * @return A pointer to the cloned Bomb order.
 */
Order *Bomb::clone() const { return new Bomb(*this); }

/**
 * @brief Convert the Bomb order to a string for logging purposes.
 * @return The string representation of the Bomb order.
 */
std::string Bomb::stringToLog() {
  std::stringstream ss;
  ss << "ORDER: ";
  ss << "Order Executed ";
  ss << *this;
  return ss.str();
}
Bomb::~Bomb() {
  if(game){
    Subject::detach((ILogObserver* )game->getLogObserver());
  }
}


// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Deploy
//
// -----------------------------------------------------------------------------------------------------------------

Deploy::Deploy(GameEngine* game, Territory* target, Player* currentPlayer, int amount) : target(target), currentPlayer(currentPlayer), amount(amount), game(game){
  Subject::attach((ILogObserver*)game->getLogObserver());
}

const std::string Deploy::label = "Deploy";

/**
 * @brief Get the label of the Deploy order.
 * @return The label of the Deploy order.
 */
std::string Deploy::getLabel() const { return label; }

/**
 * @brief Output the Deploy order to the output stream.
 * @param output The output stream.
 * @return The output stream.
 */
std::ostream &Deploy::orderCout(std::ostream &output) const { return output << "-> Deploy order."; }

/**
 * @brief Validate the Deploy order.
 * @return True if the order is valid, false otherwise.
 */
bool Deploy::validate() const
{
  std::cout << "-> Deploy order validation check" << std::endl;

    if (target->getPlayer() != currentPlayer)
    {
        cout << "You do not own this territory!\n" << endl;
        return false;
    }
    else if (amount > currentPlayer->getReinforcementPool())
    {
        cout << "You do not have this many armies in the reinforcement pool!\n" << endl;
        return false;
    }
    else if (amount < 1)
    {
        cout << "Please enter a value that is at least 1 for this order\n" << endl;
        return false;
    }
    cout << "Your order has been validated!\n" << endl;
  return true;
}

/**
 * @brief Execute the Deploy order.
 */
void Deploy::execute()
{
  if (validate()) {
      std::cout << "Deploy execution." << std::endl;
      target->setArmies(amount + target->getArmies());
      currentPlayer->removeArmies(amount);
      cout << "Deploy has finished executing!\n" << endl;
      Subject::notify(this);
  }
}

/**
 * @brief Clone the Deploy order.
 * @return A pointer to the cloned Deploy order.
 */
Order *Deploy::clone() const { return new Deploy(*this); }

/**
 * @brief Convert the Deploy order to a string for logging purposes.
 * @return The string representation of the Deploy order.
 */
std::string Deploy::stringToLog() {
  std::stringstream ss;
  ss << "ORDER: ";
  ss << "Order Executed ";
  ss << *this;
  return ss.str();
}
Deploy::~Deploy() {
  if(game){ Subject::detach((ILogObserver* )game->getLogObserver()); }
}


// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Negotiate
//
// -----------------------------------------------------------------------------------------------------------------


/**
 * @class Negotiate
 * @brief Represents a Negotiate order in the game.
 *
 * The Negotiate order establishes a friendly relationship between two players.
 */
Negotiate::Negotiate(GameEngine* game, Player* targetPlayer, Player* currentPlayer) : targetPlayer(targetPlayer), currentPlayer(currentPlayer), game(game){
  Subject::attach((ILogObserver*)game->getLogObserver());
}

const std::string Negotiate::label = "Negotiate";

/**
 * @brief Get the label of the Negotiate order.
 * @return The label of the Negotiate order.
 */
std::string Negotiate::getLabel() const { return label; }

/**
 * @brief Validates the Negotiate order.
 * 
 * Checks if the Negotiate order is valid based on the game state, such as the players involved.
 * 
 * @return True if the order is valid, false otherwise.
 */
bool Negotiate::validate() const
{
  std::cout << "-> Negotiate order validation check" << std::endl;
    if(targetPlayer == currentPlayer)
    {
        cout << "You cannot negotiate with yourself.\n" << endl;
        return false;
    }
    cout << "Your order has been validated.\n" << endl;
  return true;
}

/**
 * @brief Execute the Negotiate order.
 */
void Negotiate::execute()
{
  if (validate()) {
      std::cout << "Negotiate execution." << std::endl;
      currentPlayer->addFriendly(targetPlayer);
      targetPlayer->addFriendly(currentPlayer);
  }
    cout << "Negotiate has finished executing." << endl;
    Subject::notify(this);
}


/**
 * @brief Clone the Negotiate order.
 * @return A pointer to the cloned Negotiate order.
 */
Order *Negotiate::clone() const { return new Negotiate(*this); }

/**
 * @brief Output the Negotiate order to the output stream.
 * @param ostream The output stream.
 * @return The output stream.
 */
std::ostream &Negotiate::orderCout(std::ostream &ostream) const {
  return ostream << "-> Negotiate order.";
}

/**
 * @brief Convert the Negotiate order to a string for logging purposes.
 * @return The string representation of the Negotiate order.
 */
std::string Negotiate::stringToLog() {
  std::stringstream ss;
  ss << "ORDER: ";
  ss << "Order Executed ";
  ss << *this;
  return ss.str();
}
Negotiate::~Negotiate() {
  if(game){ Subject::detach((ILogObserver* )game->getLogObserver()); }
}
