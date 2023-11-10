#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <utility>

class Continent;
class Player;

/**
 * @brief Represents a territory in the game.
 */
class Territory
{
private:
    Continent* continent;
    std::string name;
    std::vector<Territory*> adjacentTerritories;

    int armies = 0;
    Player* player = nullptr;

    int x = -1;
    int y = -1;

public:
  // ----------------------------------------
  // Constructors
  // ----------------------------------------

    /**
     * @brief Explicit constructor for the Territory class.
     *
     * @param name The name of the territory.
     */
    explicit Territory(std::string name);

    /**
     * @brief Copy constructor for the Territory class.
     *
     * @param other The Territory to copy from.
     */
    Territory(const Territory &other);

    /**
     * @brief Gets the name of the territory.
     *
     * @return The name of the territory.
     */
    std::string getName();

    /**
     * @brief Gets a pointer to the vector of adjacent territories.
     *
     * @return Pointer to the vector of adjacent territories.
     */
    std::vector<Territory *>* getAdjacentTerritories();

  // ----------------------------------------
  // getters and setters
  // ----------------------------------------

    /**
     * @brief Gets the player who owns the territory.
     *
     * @return Pointer to the player who owns the territory.
     */
    Player* getPlayer();

    /**
     * @brief Sets the player who owns the territory.
     *
     * @param p Pointer to the player to set as the owner of the territory.
     */
    void setPlayer(Player*);

    /**
     * @brief Gets the number of armies in the territory.
     *
     * @return The number of armies in the territory.
     */
    int getArmies() const;

    /**
     * @brief Sets the number of armies in the territory.
     *
     * @param army_units The number of armies to set.
     */
    void setArmies(int);

    /**
     * @brief Gets the x-coordinate of the territory.
     *
     * @return The x-coordinate of the territory.
     */
    int getX() const;

    /**
     * @brief Gets the y-coordinate of the territory.
     *
     * @return The y-coordinate of the territory.
     */
    int getY() const;

    /**
     * @brief Sets the x-coordinate of the territory.
     *
     * @param x The x-coordinate to set.
     */
    void setX(int x);

    /**
     * @brief Sets the y-coordinate of the territory.
     *
     * @param y The y-coordinate to set.
     */
    void setY(int y);

  // ----------------------------------------
  // adders and removers
  // ----------------------------------------

/**
     * @brief Gets the continent to which the territory belongs.
     *
     * @return The continent to which the territory belongs.
     */
    Continent* getContinent();

    /**
     * @brief Sets the continent to which the territory belongs.
     *
     * @param c The continent to set.
     */
    void setContinent(Continent* c);

    /**
     * @brief Removes a specified number of army units from the territory.
     *
     * @param removed The number of army units to remove.
     * @return The total number of armies in the territory after removal.
     * @throw std::runtime_error if trying to remove a negative amount or more armies than the territory has.
     */
    int removeArmyUnits(int);

    /**
     * @brief Adds a specified number of army units to the territory.
     *
     * @param added The number of army units to add.
     * @return The total number of armies in the territory after addition.
     * @throw std::runtime_error if trying to add a negative amount.
     */
    int addArmyUnits(int);

    /**
     * @brief Adds an adjacent territory to the current territory.
     *
     * @param territory The territory to add as adjacent.
     */
    void addAdjacentTerritory(Territory* territory);

  // ----------------------------------------
  // Operator Overloads
  // ----------------------------------------

  /**
   * @brief Copy assignment operator for the Territory class.
   *
   * @param other The Territory to copy from.
   * @return Reference to the current Territory.
   */
  Territory& operator=(const Territory& other);

public:
  // ----------------------------------------
  // ostream overload
  // ----------------------------------------

    /**
   * @brief Stream insertion operator for the Territory class.
   *
   * @param stream The output stream.
   * @param other The Territory object.
   * @return The output stream.
   */
    friend std::ostream& operator<<(std::ostream& stream, const Territory& other);
};
