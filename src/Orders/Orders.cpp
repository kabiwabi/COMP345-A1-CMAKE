#include "Orders.h"

/**
 * @brief Destructor for the Order class.
 */
Order::~Order() = default;

/**
 * @brief Overloaded insertion operator for the Order class.
 * @param stream The output stream.
 * @param o The Order object.
 * @return Modified output stream.
 */
std::ostream &operator<<(std::ostream &stream, const Order &o) { return o.orderCout(stream); }

/**
 * @brief Destructor for the OrdersList class.
 */
OrdersList::~OrdersList(){ for(auto order: orders){ delete order; } }

/**
 * @brief Copy constructor for OrdersList class.
 * @param oldList The OrdersList object to be copied.
 */
OrdersList::OrdersList(const OrdersList &oldList)
{
  unsigned listLength = oldList.orders.size();
  orders = std::vector<Order *>(listLength);
  // cloning the same object into another memory slot
  for (unsigned o = 0; o < listLength; o++) { orders[o] = oldList.orders[o]->clone(); }
}

/**
 * @brief Adds an order to the OrdersList.
 * @param o Pointer to the order to be added.
 */
void OrdersList::add(Order *o)
{
  if(o){ orders.push_back(o); } else { throw std::runtime_error("Inserting a nullptr in OrderList."); }
}

/**
 * @brief Removes an order from the OrdersList.
 * @param pos The position of the order to be removed.
 */
void OrdersList::remove(int pos)
{
  unsigned listLength = orders.size();
  if (listLength == 0){
    throw std::runtime_error("The order list is empty, can't remove any more orders.");
  }
  else if (pos >= listLength || pos < 0) {
    throw std::runtime_error("The inputed position isn't valid please make another entry.");
  }
  else
  {
    delete orders[pos];
    orders.erase(orders.begin() + pos);
  }
}

/**
 * @brief Moves an order within the OrdersList.
 * @param pos1 The starting position.
 * @param pos2 The ending position.
 */void OrdersList::move(int pos1, int pos2)
{
  unsigned listLength = orders.size();
  if (listLength == 0){
    std::cout << "Order list is empty, won't move anything." << std::endl;
  }
  else if (listLength == 1)
  {
    throw std::runtime_error("There is only one order in the list, need more than one orders for the move.");
  }
  else if (pos1 >= listLength || pos2 >= listLength || pos1 < 0 || pos2 < 0)
  {
    throw std::runtime_error("None or only one inputted position is valid. Please try again.");
  }
  else
  {
    Order *temp = orders[pos1];
    orders[pos1] = orders[pos2];
    orders[pos2] = temp;
  }
}


/**
 * @brief Executes all the orders in the OrdersList.
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
 * @brief Overloaded assignment operator for the OrdersList class.
 * @param copyList The OrdersList object to be copied.
 * @return Reference to the modified OrdersList object.
 */
OrdersList &OrdersList::operator=(const OrdersList &copyList)
{
  if (&copyList == this){
    return *this;
  }

  unsigned initialListLength = orders.size();
  unsigned copyListLength = copyList.orders.size();

  for (int o = 0; o < initialListLength; o++) { delete orders[o]; }

  orders = std::vector<Order *>(copyListLength);

  for (int i = 0; i < copyListLength; i++) {
    // clone copied element to left hand side
    orders[i] = copyList.orders[i]->clone();
  }

  return *this;
}

/**
 * @brief Overloaded insertion operator for the OrdersList class.
 * @param stream The output stream.
 * @param ol The OrdersList object.
 * @return Modified output stream.
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
 * @brief Get a list of orders.
 * @return A pointer to the vector containing the orders.
 */
std::vector<Order *> *OrdersList::getList() {
  return &this->orders;
}

// -------------- ADVANCE --------------

/**
 * @brief Overloaded output operator for Advance order.
 * @param output Output stream.
 * @return Updated output stream.
 */
std::ostream &Advance::orderCout(std::ostream &output) const { return output << "-> Advance order."; }

/**
 * @brief Retrieves the label for the Advance order.
 * @return Label string.
 */
std::string Advance::getLabel() const { return label; }

/**
 * @brief Destructor for Advance order.
 */
Advance::~Advance() = default;

/// Label for the Advance order.
const std::string Advance::label = "Advance";

/**
 * @brief Validates the Advance order.
 * @return Boolean indicating the validity of the order.
 */
bool Advance::validate() const
{
  std::cout << "-> Advance order validation check" << std::endl;
  return true;
}

/**
 * @brief Executes the Advance order.
 */
void Advance::execute() const
{
  if (validate()) { std::cout << "Advance execution." << std::endl; }
}

/**
 * @brief Clones the Advance order.
 * @return Pointer to the cloned order.
 */
Order *Advance::clone() const { return new Advance(*this); }

// -------------- AIRLIFT --------------

/// Label for the Airlift order.
const std::string Airlift::label = "Airlift";

/**
 * @brief Destructor for Airlift order.
 */
Airlift::~Airlift() = default;

/**
 * @brief Retrieves the label for the Airlift order.
 * @return Label string.
 */
std::string Airlift::getLabel() const { return label; }

/**
 * @brief Overloaded output operator for Airlift order.
 * @param output Output stream.
 * @return Updated output stream.
 */
std::ostream &Airlift::orderCout(std::ostream &output) const { return output << "-> Airlift order."; }

/**
 * @brief Validates the Airlift order.
 * @return Boolean indicating the validity of the order.
 */
bool Airlift::validate() const
{
  std::cout << "-> Airlift order validation check" << std::endl;
  return true;
}

/**
 * @brief Executes the Airlift order.
 */
void Airlift::execute() const
{
  if (validate()) { std::cout << "Airlift execution." << std::endl; }
}

/**
 * @brief Clones the Airlift order.
 * @return Pointer to the cloned order.
 */
Order *Airlift::clone() const { return new Airlift(*this); }

// -------------- BLOCKADE --------------

/// Label for the Blockade order.
const std::string Blockade::label = "Blockade";

/**
 * @brief Destructor for Blockade order.
 */
Blockade::~Blockade() = default;

/**
 * @brief Retrieves the label for the Blockade order.
 * @return Label string.
 */
std::string Blockade::getLabel() const { return label; }

/**
 * @brief Overloaded output operator for Blockade order.
 * @param output Output stream.
 * @return Updated output stream.
 */
std::ostream &Blockade::orderCout(std::ostream &output) const { return output << "-> Blockade order."; }

/**
 * @brief Validates the Blockade order.
 * @return Boolean indicating the validity of the order.
 */
bool Blockade::validate() const
{
    std::cout << "-> Blockade order validation check" << std::endl;
    return true;
}

/**
 * @brief Executes the Blockade order.
 */
void Blockade::execute() const
{
    if (validate()) { std::cout << "Blockade execution." << std::endl; }
}

/**
 * @brief Clones the Blockade order.
 * @return Pointer to the cloned order.
 */
Order *Blockade::clone() const { return new Blockade(*this); }

// -------------- BOMB --------------

/// Label for the Bomb order.
const std::string Bomb::label = "Bomb";

/**
 * @brief Destructor for Bomb order.
 */
Bomb::~Bomb() = default;

/**
 * @brief Retrieves the label for the Bomb order.
 * @return Label string.
 */
std::string Bomb::getLabel() const { return label; }

/**
 * @brief Overloaded output operator for Bomb order.
 * @param output Output stream.
 * @return Updated output stream.
 */
std::ostream &Bomb::orderCout(std::ostream &output) const { return output << "-> Bomb order."; }

/**
 * @brief Validates the Bomb order.
 * @return Boolean indicating the validity of the order.
 */
bool Bomb::validate() const
{
    std::cout << "-> Bomb order validation check" << std::endl;
    return true;
}

/**
 * @brief Executes the Bomb order.
 */
void Bomb::execute() const
{
    if (validate()) { std::cout << "Bomb execution." << std::endl; }
}

/**
 * @brief Clones the Bomb order.
 * @return Pointer to the cloned order.
 */
Order *Bomb::clone() const { return new Bomb(*this); }

// -------------- DEPLOY --------------

/// Label for the Deploy order.
const std::string Deploy::label = "Deploy";

/**
 * @brief Destructor for Deploy order.
 */
Deploy::~Deploy() = default;

/**
 * @brief Retrieves the label for the Deploy order.
 * @return Label string.
 */
std::string Deploy::getLabel() const { return label; }

/**
 * @brief Overloaded output operator for Deploy order.
 * @param output Output stream.
 * @return Updated output stream with order description.
 */
std::ostream &Deploy::orderCout(std::ostream &output) const { return output << "-> Deploy order."; }

/**
 * @brief Validates the Deploy order.
 * @return Boolean indicating the validity of the order.
 */
bool Deploy::validate() const
{
    std::cout << "-> Deploy order validation check" << std::endl;
    return true;
}

/**
 * @brief Executes the Deploy order.
 */
void Deploy::execute() const
{
    if (validate()) { std::cout << "Deploy execution." << std::endl; }
}

/**
 * @brief Clones the Deploy order.
 * @return Pointer to the cloned order.
 */
Order *Deploy::clone() const { return new Deploy(*this); }

// -------------- NEGOTIATE --------------

/// Label for the Negotiate order.
const std::string Negotiate::label = "Negotiate";

/**
 * @brief Destructor for Negotiate order.
 */
Negotiate::~Negotiate() = default;

/**
 * @brief Retrieves the label for the Negotiate order.
 * @return Label string.
 */
std::string Negotiate::getLabel() const { return label; }

/**
 * @brief Validates the Negotiate order.
 * @return Boolean indicating the validity of the order.
 */
bool Negotiate::validate() const
{
    std::cout << "-> Negotiate order validation check" << std::endl;
    return true;
}

/**
 * @brief Executes the Negotiate order.
 */
void Negotiate::execute() const
{
    if (validate()) { std::cout << "Negotiate execution." << std::endl; }
}

/**
 * @brief Clones the Negotiate order.
 * @return Pointer to the cloned order.
 */
Order *Negotiate::clone() const { return new Negotiate(*this); }

/**
 * @brief Overloaded output operator for Negotiate order.
 * @param ostream Output stream.
 * @return Updated output stream with order description.
 */
std::ostream &Negotiate::orderCout(std::ostream &ostream) const {
    return ostream << "-> Negotiate order.";
}

// -------------- UserInputOrder --------------

/**
 * @brief Creates an Order object based on the provided order type.
 * @param orderType The type of order to be created.
 * @return Pointer to the created order.
 */
Order* UserInputOrder::create(const std::string& orderType)
{
  if (orderType == "Deploy") { return new Deploy; }
  else if (orderType == "Advance") { return new Advance; }
  else if (orderType == "Bomb") { return new Bomb(); }
  else if (orderType == "Blockade") { return new Blockade(); }
  else if (orderType == "Airlift") { return new Airlift(); }
  else if (orderType == "Negotiate") { return new Negotiate(); }
  else { throw std::runtime_error("Unexpected OrderType: " + orderType ); }
}

// TODO: Remove deploy and add new logic for A#2
Order* OrdersFactory::CreateOrder(CardType cardType) {
  switch(cardType){
    case CT_Bomb:
      return new Bomb();
    case CT_Reinforcement:
      return new Deploy();
    case CT_Blockade:
      return new Blockade();
    case CT_Airlift:
      return new Airlift();
    case CT_Diplomacy:
      return new Negotiate();
    default:
      throw std::runtime_error("Invalid card type");
  }
}