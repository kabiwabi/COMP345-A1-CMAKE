#include "Territory.h"

/**
 * @brief Constructor for the Territory class.
 *
 * @param name The name of the territory.
 */
Territory::Territory(std::string name)
  : name(std::move(name)), continent(nullptr), player(nullptr)
{}

/**
 * @brief Adds an adjacent territory to the current territory.
 *
 * @param territory The territory to add as adjacent.
 */
void Territory::addAdjacentTerritory(Territory* territory)
{
  this->adjacentTerritories.push_back(territory);
}

/**
 * @brief Gets the name of the territory.
 *
 * @return The name of the territory.
 */
std::string Territory::getName()
{
  return this->name;
}

/**
 * @brief Gets a pointer to the vector of adjacent territories.
 *
 * @return Pointer to the vector of adjacent territories.
 */
std::vector<Territory *>* Territory::getAdjacentTerritories()
{
  return &this->adjacentTerritories;
}

/**
 * @brief Gets the x-coordinate of the territory.
 *
 * @return The x-coordinate of the territory.
 */
int Territory::getX() const
{
  return this->x;
}

/**
 * @brief Gets the y-coordinate of the territory.
 *
 * @return The y-coordinate of the territory.
 */
int Territory::getY() const
{
  return this->y;
}

/**
 * @brief Sets the x-coordinate of the territory.
 *
 * @param _x The x-coordinate to set.
 */
void Territory::setX(int _x)
{
  this->x = _x;
}

/**
 * @brief Sets the y-coordinate of the territory.
 *
 * @param _y The y-coordinate to set.
 */
void Territory::setY(int _y)
{
  this->y = _y;
}

/**
 * @brief Gets the continent to which the territory belongs.
 *
 * @return The continent to which the territory belongs.
 */
Continent* Territory::getContinent()
{
  return this->continent;
}

/**
 * @brief Sets the continent to which the territory belongs.
 *
 * @param c The continent to set.
 */
void Territory::setContinent(Continent* c)
{
  this->continent = c;
}

/**
 * @brief Copy constructor for the Territory class.
 *
 * Avoids deep copy (due to other territories being only pointers).
 */
Territory::Territory(const Territory &other)= default;

/**
 * @brief Copy assignment operator for the Territory class.
 *
 * @param other The Territory to copy from.
 * @return Reference to the current Territory.
 */
Territory& Territory::operator=(const Territory &other) {
  if(this == &other){
    return *this;
  }

  this->name = other.name;
  this->continent = other.continent;

  this->armies = other.armies;
  this->player = other.player;

  this->x = other.x;
  this->y = other.y;

  this->adjacentTerritories = other.adjacentTerritories;
  return *this;
}

/**
 * @brief Stream insertion operator for the Territory class.
 *
 * @param stream The output stream.
 * @param other The Territory object.
 * @return The output stream.
 */
std::ostream &operator<<(std::ostream &stream, const Territory &other) {
  stream << "Territory Name: " << other.name << '\n'
  << "Territory Coordinates: " << '(' << other.x << ", " << other.y << ')' << '\n';
  return stream ;
}

/**
 * @brief Gets the number of armies in the territory.
 *
 * @return The number of armies in the territory.
 */
int Territory::getArmies() const {
  return this->armies;
}

/**
 * @brief Sets the number of armies in the territory.
 *
 * @param army_units The number of armies to set.
 */
void Territory::setArmies(int army_units) {
  this->armies = army_units;
}

/**
 * @brief Removes a specified number of army units from the territory.
 *
 * @param removed The number of army units to remove.
 * @return The total number of armies in the territory after removal.
 * @throw std::runtime_error if trying to remove a negative amount or more armies than the territory has.
 */
int Territory::removeArmyUnits(int removed) {
  if(removed < 0){ throw std::runtime_error("Cannot remove a negative amount of army units."); }
  int total = this->armies - removed;
  if(total < 0){ throw std::runtime_error("Cannot remove more armies than the territory currently has."); }
  this->armies = total;
  return total;
}

/**
 * @brief Adds a specified number of army units to the territory.
 *
 * @param added The number of army units to add.
 * @return The total number of armies in the territory after addition.
 * @throw std::runtime_error if trying to add a negative amount.
 */
int Territory::addArmyUnits(int added) {
  if(added < 0){ throw std::runtime_error("Cannot add a negative amount of army units."); }
  int total = this->armies + added;
  this->armies = total;
  return total;
}

/**
 * @brief Gets the player who owns the territory.
 *
 * @return Pointer to the player who owns the territory.
 */
Player *Territory::getPlayer() {
  return this->player;
}

/**
 * @brief Sets the player who owns the territory.
 *
 * @param p Pointer to the player to set as the owner of the territory.
 */
void Territory::setPlayer(Player* p) {
  this->player = p;
}