#pragma once

#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <fstream>


#include "GameEngine/GameEngine.h"
#include "Player/Player.h"


// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Territory
//
// ----------------------------------------------------------------------------------------------------------------

class Continent;
class GameEngine;
class Player;

/**
 * @brief Represents a territory in the game map.
 */
class Territory
{
private:
  Continent* continent;
  std::string name;
  std::vector<Territory*> adjacentTerritories;

  int armies = 0;
  Player* player;

  int x = -1;
  int y = -1;

public:
  // ----------------------------------------
  // Constructors
  // ----------------------------------------
    /**
   * @brief Constructor for creating a territory with a given name.
   * @param name The name of the territory.
   */
  explicit Territory(std::string name);

  /**
    * @brief Copy constructor for creating a territory by copying another territory.
    * @param other The territory to copy.
    */
  Territory(const Territory &other);

  /**
    * @brief Gets the name of the territory.
    * @return The name of the territory.
    */
  std::string getName();

  /**
    * @brief Gets the list of territories adjacent to this territory.
    * @return A pointer to the vector of adjacent territories.
    */
  std::vector<Territory *>* getAdjacentTerritories();
  // ----------------------------------------
  // getters and setters
  // ----------------------------------------
/**
   * @brief Gets the number of armies on the territory.
   * @return The number of armies on the territory.
   */
    int getArmies() const;

    /**
     * @brief Sets the number of armies on the territory.
     * @param army_units The number of armies to set.
     */
    void setArmies(int army_units);

    /**
     * @brief Gets the player who owns the territory.
     * @return A pointer to the player who owns the territory.
     */
    Player* getPlayer();

    /**
     * @brief Sets the player who owns the territory.
     * @param p A pointer to the player who owns the territory.
     */
    void setPlayer(Player* p);

    /**
     * @brief Gets the X-coordinate of the territory on the game map.
     * @return The X-coordinate of the territory.
     */
    int getX() const;

    /**
     * @brief Gets the Y-coordinate of the territory on the game map.
     * @return The Y-coordinate of the territory.
     */
    int getY() const;

    /**
     * @brief Sets the X-coordinate of the territory on the game map.
     * @param x The X-coordinate to set.
     */
    void setX(int x);

    /**
     * @brief Sets the Y-coordinate of the territory on the game map.
     * @param y The Y-coordinate to set.
     */
    void setY(int y);

  // ----------------------------------------
  // adders and removers
  // ----------------------------------------

/**
   * @brief Gets the continent that the territory belongs to.
   * @return A pointer to the continent that the territory belongs to.
   */
    Continent* getContinent();

    /**
     * @brief Sets the continent that the territory belongs to.
     * @param c A pointer to the continent that the territory belongs to.
     */
    void setContinent(Continent* c);

    /**
     * @brief Removes a specified number of armies from the territory.
     * @param removed The number of armies to remove.
     * @return The total number of armies on the territory after removal.
     * @throw std::runtime_error if an attempt is made to remove a negative amount of army units or more armies than the territory currently has.
     */
    int removeArmyUnits(int removed);

    /**
     * @brief Adds a specified number of armies to the territory.
     * @param added The number of armies to add.
     * @return The total number of armies on the territory after addition.
     * @throw std::runtime_error if an attempt is made to add a negative amount of army units.
     */
    int addArmyUnits(int added);

    /**
     * @brief Adds an adjacent territory to the list of adjacent territories.
     * @param territory A pointer to the adjacent territory to add.
     */
    void addAdjacentTerritory(Territory* territory);

  // ----------------------------------------
  // Operator Overloads
  // ----------------------------------------

    /**
   * @brief Assignment operator overload for copying the content of another territory.
   * @param other The territory to copy.
   * @return A reference to the current territory after copying.
   */
  Territory& operator=(const Territory& other);

public:
  // ----------------------------------------
  // ostream overload
  // ----------------------------------------
    /**
   * @brief Ostream operator overload for outputting the territory information.
   * @param stream The output stream.
   * @param other The territory to output.
   * @return A reference to the output stream.
   */
  friend std::ostream& operator<<(std::ostream& stream, const Territory& other);

};

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Map
//
// ----------------------------------------------------------------------------------------------------------------

class Map
{
public:
  std::vector<Continent*> continents;

private:
  std::string name;
  std::string image;
  std::string author;

  bool wrap{};
  bool scroll{};
  bool warn{};

  std::vector<Territory*> territories;


  // Object Owner
  GameEngine* game;

private:
/**
   * @brief Checks if the map is strongly connected.
   * @return True if the map is strongly connected; otherwise, false.
   */
    bool isMapStronglyConnected();

    /**
     * @brief Checks if territories belong to exactly one continent.
     * @return True if territories belong to exactly one continent; otherwise, false.
     */
    bool isTerritories1to1Continents();

    /**
     * @brief Depth-First Search (DFS) traversal starting from a specific territory.
     * @param territory The starting territory for DFS.
     * @param visited Vector to track visited territories during DFS.
     */
    void DFS(Territory* territory, std::vector<Territory*>& visited);

    /**
     * @brief Checks if a territory is strongly connected to all other territories in the map.
     * @param territory The territory to check.
     * @return True if the territory is strongly connected to all other territories; otherwise, false.
     */
    bool isTerritoryStronglyConnected(Territory* territory);

public:
  // --------------------------------------------------
  // Destructors + Constructors + Operator Overloads
  // --------------------------------------------------
/**
   * @brief Constructor for creating a map with a specified GameEngine.
   * @param game A pointer to the GameEngine that owns the map.
   */
    explicit Map(GameEngine* game);

    /**
     * @brief Destructor for the Map class.
     */
    ~Map();

    /**
     * @brief Validates the integrity of the map.
     * @return True if the map is valid; otherwise, false.
     */
    bool validate();

    /**
     * @brief Copy constructor for creating a map by copying another map.
     * @param other The map to copy.
     */
    Map(const Map &other);

    /**
     * @brief Assignment operator overload for copying the content of another map.
     * @param other The map to copy.
     * @return A reference to the current map after copying.
     */
    Map& operator=(const Map& other);

  // --------------------------------------------------
  // map adders
  // --------------------------------------------------
/**
   * @brief Adds a continent to the map.
   * @param continent A pointer to the continent to add.
   */
    void addContinent(Continent* continent);

    /**
     * @brief Adds a territory to the map.
     * @param territory A pointer to the territory to add.
     */
    void addTerritory(Territory* territory);

  // --------------------------------------------------
  // setters
  // --------------------------------------------------
/**
   * @brief Sets the name of the map.
   * @param _name The name to set.
   */
    void setName(std::string _name);

    /**
     * @brief Sets the image associated with the map.
     * @param _image The image to set.
     */
    void setImage(std::string _image);

    /**
     * @brief Sets the author of the map.
     * @param author The author to set.
     */
    void setAuthor(std::string author);

    /**
     * @brief Sets the wrap-around feature of the map.
     * @param wrap True to enable wrap-around; false otherwise.
     */
    void setWrap(bool wrap);

    /**
     * @brief Sets the scrolling direction of the map.
     * @param scroll True for horizontal scrolling; false for vertical scrolling.
     */
    void setScroll(bool scroll);

    /**
     * @brief Sets the warning flag for the map.
     * @param warn True to enable warnings; false otherwise.
     */
    void setWarn(bool warn);

  // --------------------------------------------------
  // getters
  // --------------------------------------------------
/**
   * @brief Gets the name of the map.
   * @return The name of the map.
   */
    std::string getName();

    /**
     * @brief Gets the image associated with the map.
     * @return The image associated with the map.
     */
    std::string getImage();

    /**
     * @brief Gets the author of the map.
     * @return The author of the map.
     */
    std::string getAuthor();

    /**
     * @brief Gets the wrap-around feature of the map.
     * @return True if wrap-around is enabled; otherwise, false.
     */
    bool getWrap() const;

    /**
     * @brief Gets the scrolling direction of the map.
     * @return True for horizontal scrolling; false for vertical scrolling.
     */
    bool getScroll() const;

    /**
     * @brief Gets the warning flag for the map.
     * @return True if warnings are enabled; otherwise, false.
     */
    bool getWarn() const;

    /**
   * @brief Gets a pointer to the vector of territories in the map.
   * @return A pointer to the vector of territories.
   */
    std::vector<Territory *> * getTerritories();

    /**
     * @brief Gets a pointer to the vector of continents in the map.
     * @return A pointer to the vector of continents.
     */
    std::vector<Continent *> * getContinents();

public:
    /**
     * @brief Overloads the ostream operator for printing the map details.
     * @param stream The output stream.
     * @param other The map to print.
     * @return A reference to the output stream.
     */
  friend std::ostream& operator<<(std::ostream& stream, const Map& other);
};



// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Continent
//
// ----------------------------------------------------------------------------------------------------------------

/**
 * @brief Represents a continent in the game map.
 */
class Continent
{
public:
    /**
 * @brief Vector of territories within the continent.
 */
    std::vector<Territory*> territories;

private:
    /**
   * @brief Name of the continent.
   */
    std::string name;

    /**
     * @brief Bonus associated with the continent.
     */
    int bonus;

public:
  // ----------------------------------------
  // Constructors
  // ----------------------------------------
    /**
   * @brief Constructs a continent with a specified name and bonus.
   * @param name The name of the continent.
   * @param bonus The bonus associated with the continent.
   */
    Continent(std::string name, int bonus);

    /**
     * @brief Copy constructor for a continent.
     * @param other The continent to copy.
     */
    Continent(const Continent& other);


  // ----------------------------------------
  // Adders
  // ----------------------------------------
    /**
     * @brief Adds a territory to the continent.
     * @param territory The territory to add.
     */
    void addTerritory(Territory* territory);

  // ----------------------------------------
  // Getters
  // ----------------------------------------

    /**
     * @brief Gets the name of the continent.
     * @return The name of the continent.
     */
    std::string getName();

    /**
     * @brief Gets the bonus associated with the continent.
     * @return The bonus of the continent.
     */
    int getBonus() const;

    /**
     * @brief Gets a pointer to the vector of territories in the continent.
     * @return A pointer to the vector of territories.
     */
    std::vector<Territory *> * getTerritories();

  // ----------------------------------------
  // Operator Overloads
  // ----------------------------------------
    /**
   * @brief Overloads the assignment operator for continents.
   * @param other The continent to assign.
   * @return A reference to the assigned continent.
   */
  Continent& operator=(const Continent& other);
public:
  // ----------------------------------------
  // Ostream Overload
  // ----------------------------------------
    /**
     * @brief Overloads the ostream operator for printing continent details.
     * @param stream The output stream.
     * @param other The continent to print.
     * @return A reference to the output stream.
     */
  friend std::ostream& operator<<(std::ostream& stream, const Continent& other);
};



// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Map Loader
//
// ----------------------------------------------------------------------------------------------------------------



class Map;

/**
 * @brief Represents a loader for reading game maps from files.
 */
class MapLoader
{
private:

  // ----------------------------------------
  // State Enum
  // ----------------------------------------
    /**
     * @brief Enumeration representing the different states during map file parsing.
     */
  enum ReadingState
  {
    ReadingState_Idle,
    ReadingState_Map,
    ReadingState_Continents,
    ReadingState_Territories
  };

  // ----------------------------------------
  // Map Loader Data / State
  // ----------------------------------------

    /**
     * @brief Struct representing the state of the map loader during parsing.
     */
  struct MapLoaderState
  {
    std::unordered_map<std::string, Territory*> territories;
    // territories to add to the map
    std::unordered_map<std::string, Territory*> territoriesToCreate;
    // continent name -> Continent
    std::unordered_map<std::string, Continent*> continents;
    ReadingState parseState = ReadingState_Idle;
  };

  // ----------------------------------------
  // Map Loader Parse Line
  // ----------------------------------------

    /**
     * @brief Parses a line during map file reading.
     * @param line The line to parse.
     * @param map The map to update.
     * @param mapLoaderState The current state of the map loader.
     */
    static void parseLine(std::string &line, Map* map, MapLoaderState& mapLoaderState);

  // ----------------------------------------
  // Map Loader Line Trim Utilities
  // ----------------------------------------
/**
   * @brief Trims whitespace from the beginning of a string.
   * @param s The string to trim.
   * @return The trimmed string.
   */
    static std::string ltrim(const std::string &s);

    /**
     * @brief Trims whitespace from the end of a string.
     * @param s The string to trim.
     * @return The trimmed string.
     */
    static std::string rtrim(const std::string &s);

public:
    /**
   * @brief Trims whitespace from both ends of a string.
   * @param s The string to trim.
   * @return The trimmed string.
   */
    static std::string trim(const std::string &s);

  // ----------------------------------------
  // Map Loader Load File
  // ----------------------------------------
    /**
    * @brief Loads a map from a file.
    * @param path The path to the map file.
    * @param out_map The map to populate.
    */
    static void load(const std::string& path, Map* out_map);

  // ----------------------------------------
  // Map loader is a static class and should not have any constructor or assignment operator overloaded.
  // ----------------------------------------
    /**
   * @brief Deleted default constructor to prevent instantiation.
   */
    MapLoader() = delete;

    /**
     * @brief Deleted copy constructor to prevent instantiation.
     */
    MapLoader(const MapLoader &other) = delete;

    /**
     * @brief Deleted assignment operator to prevent instantiation.
     */
    MapLoader& operator=(const MapLoader& other) = delete;

public:
  // ----------------------------------------
  // Map loader cannot be instantiated and therefore cannot be printed out.
  // ----------------------------------------

    /**
   * @brief Deleted friend function to prevent instantiation.
   */
  friend std::ostream& operator<<(std::ostream& stream, const MapLoader& other) = delete;
};
