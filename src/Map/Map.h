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

/// Forward declarations
class Continent;
class GameEngine;
class Player;

/**
 * @class Territory
 * @brief Represents a territory in the game world.
 */
class Territory {
private:
    Continent* continent; ///< Pointer to the Continent this territory belongs to.
    std::string name; ///< Name of the territory.
    std::vector<Territory*> adjacentTerritories; ///< Territories adjacent to this one.

    int armies = 0; ///< Number of armies present in this territory.
    int ownerId = -1; ///< ID of the player who owns this territory.
    Player* player; ///< Pointer to the Player who owns this territory.

    int x = -1; ///< X-coordinate for UI.
    int y = -1; ///< Y-coordinate for UI.

public:
    /// Explicit constructor for Territory.
    explicit Territory(std::string name);
    /// Copy constructor.
    Territory(const Territory &other);
    /// Get the name of the territory.
    std::string getName();
    /// Get adjacent territories.
    std::vector<Territory *>* getAdjacentTerritories();
    /// Set the ID of the owner.
    void setOwnerId(int id);
    /// Get the ID of the owner.
    int getOwnerId() const;
    /// Get the number of armies.
    int getArmies() const;
    /// Set the number of armies.
    void setArmies(int);
    /// Get the owner player.
    Player* getPlayer();
    /// Set the owner player.
    void setPlayer(Player*);
    /// Get X coordinate.
    int getX() const;
    /// Get Y coordinate.
    int getY() const;
    /// Set X coordinate.
    void setX(int x);
    /// Set Y coordinate.
    void setY(int y);
    /// Get the continent.
    Continent* getContinent();
    /// Set the continent.
    void setContinent(Continent* c);
    /// Remove army units.
    int removeArmyUnits(int);
    /// Add army units.
    int addArmyUnits(int);
    /// Add an adjacent territory.
    void addAdjacentTerritory(Territory* territory);
    /// Assignment operator.
    Territory& operator=(const Territory& other);
    /// Stream insertion operator.
    friend std::ostream& operator<<(std::ostream& stream, const Territory& other);
};

/**
 * @class Map
 * @brief Represents a map in the game containing territories and continents.
 */
class Map {
private:
    std::string name; ///< Name of the map.
    std::string image; ///< Image path for the map.
    std::string author; ///< Author of the map.

    bool wrap{};  ///< Wrap setting.
    bool scroll{};  ///< Scroll setting.
    bool warn{};  ///< Warn setting.

    std::vector<Territory*> territories;  ///< List of territories in the map.
    std::vector<Continent*> continents;  ///< List of continents in the map.

    GameEngine* game;  ///< Pointer to the game engine.

    bool isMapStronglyConnected();  ///< Checks if the map is strongly connected.
    bool isTerritories1to1Continents();  ///< Checks territory to continent mapping.
    void DFS(Territory* territory, std::vector<Territory*>& visited);  ///< Depth-first search.
    bool isTerritoryStronglyConnected(Territory* territory);  ///< Checks if a territory is strongly connected.

public:
    /// Explicit constructor for Map.
    explicit Map(GameEngine* game);
    /// Destructor for Map.
    ~Map();
    /// Validates the map.
    bool validate();

    /// Copy constructor for Map.
    Map(const Map &other);
    /// Assignment operator for Map.
    Map& operator=(const Map& other);

    /// Adds a continent to the map.
    void addContinent(Continent* continent);
    /// Adds a territory to the map.
    void addTerritory(Territory* territory);

    /// Sets the name of the map.
    void setName(std::string _name);
    /// Gets the name of the map.
    std::string getName();
    /// Sets the image of the map.
    void setImage(std::string _image);
    /// Gets the image of the map.
    std::string getImage();
    /// Sets the author of the map.
    void setAuthor(std::string author);
    /// Gets the author of the map.
    std::string getAuthor();
    /// Sets the wrap setting of the map.
    void setWrap(bool wrap);
    /// Gets the wrap setting of the map.
    bool getWrap() const;
    /// Sets the scroll setting of the map.
    void setScroll(bool scroll);
    /// Gets the scroll setting of the map.
    bool getScroll() const;
    /// Sets the warn setting of the map.
    void setWarn(bool warn);
    /// Gets the warn setting of the map.
    bool getWarn() const;
    /// Gets the list of territories.
    std::vector<Territory *> * getTerritories();
    /// Gets the list of continents.
    std::vector<Continent *> * getContinents();

    /// Stream insertion operator.
    friend std::ostream& operator<<(std::ostream& stream, const Map& other);
};

/**
 * @class Continent
 * @brief Represents a continent in the game.
 */
class Continent {
private:
    std::string name; ///< Name of the continent.
    int bonus; ///< Bonus armies for owning this continent.
    std::vector<Territory*> territories; ///< Territories within this continent.

public:
    /// Constructor for Continent.
    Continent(std::string name, int bonus);
    /// Copy constructor for Continent.
    Continent(const Continent& other);

    /// Adds a territory to this continent.
    void addTerritory(Territory* territory);
    /// Gets the name of the continent.
    std::string getName();
    /// Gets the bonus for owning this continent.
    int getBonus() const;
    /// Gets the territories within this continent.
    std::vector<Territory *> * getTerritories();

    /// Assignment operator for Continent.
    Continent& operator=(const Continent& other);

    /// Stream insertion operator.
    friend std::ostream& operator<<(std::ostream& stream, const Continent& other);
};

/**
 * @class MapLoader
 * @brief Static class for loading maps.
 */
class MapLoader {
private:
    /// Reading states for parsing map files.
    enum ReadingState {
        ReadingState_Idle,
        ReadingState_Map,
        ReadingState_Continents,
        ReadingState_Territories
    };

    /// Stores the state of the map loader.
    struct MapLoaderState {/// Map of territories by name.
        std::unordered_map<std::string, Territory*> territories;
        /// Map of territories to be created.
        std::unordered_map<std::string, Territory*> territoriesToCreate;
        /// Map of continents by name.
        std::unordered_map<std::string, Continent*> continents;
        /// Current parsing state.
        ReadingState parseState = ReadingState_Idle;
    };

    /// Parses a line from the map file.
    static void parseLine(std::string &line, Map* map, MapLoaderState& mapLoaderState);

    /// Trims the left whitespace of a string.
    static std::string ltrim(const std::string &s);

    /// Trims the right whitespace of a string.
    static std::string rtrim(const std::string &s);

    /// Trims the left and right whitespace of a string.
    static std::string trim(const std::string &s);

public:
    /// Loads a map from a file.
    static void load(const std::string& path, Map* out_map);

    /// Deleted constructor.
    MapLoader() = delete;

    /// Deleted copy constructor.
    MapLoader(const MapLoader &other) = delete;

    /// Deleted assignment operator.
    MapLoader& operator=(const MapLoader& other) = delete;

    /// Deleted stream insertion operator.
    friend std::ostream& operator<<(std::ostream& stream, const MapLoader& other) = delete;
};