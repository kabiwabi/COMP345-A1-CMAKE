#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

// Forward declaration of Territory class
class Territory;

// Forward declaration of Player class
class Player;

// Enum for the different sections of a map file
enum mapSections 
{
    // No Section
    none,
    // Map Section
    mapSection,
    // Continents Section
    continentsSection,
    // Territories Section
    territoriesSection
};

// Class for storing a continent
class Continent
{
    public:
        Continent(const std::string& name, int bonus);
        ~Continent();
        void setName(std::string name);
        void setBonus(int bonus);
        void addConnectedContinent(Continent* continent);
        std::string getName();
        int getBonus();
        void setIndex(int index);
        int getIndex();
        std::vector<int> getConnectedContinentIndexes();
        std::vector<Continent*> getConnectedContinents();
        Continent* getConnectedContinent(std::string continentName);

        std::string to_string(int tabNum);
    private:
        // Index of the continent in the map
        int index;
        // Name of the continent
        std::string name;
        // Bonus value for controlling this continent
        int bonus;
        // All continents connected to this continent
        std::vector<Continent*> connectedContinents;
};

// Class for storing a territory
class Territory
{
    public:
        Territory(const std::string& name, Continent* continent, int x, int y);
        Territory(const std::string& name);
        ~Territory();
        void setName(std::string name);
        void setContinent(Continent* continent);
        void setX(int x);
        void setY(int y);
        void addConnectedTerritory(Territory* territory);
        void setOwner(Player* owner);
        void setArmiesCount(int armiesCount);
        void setIndex(int index);
        int getIndex();
        std::string getName();
        Continent* getContinent();
        int getX();
        int getY();
        std::vector<Territory*> getConnectedTerritories();
        std::vector<int> getConnectedTerritoryIndexes();
        Player* getOwner();
        int getArmiesCount();
        std::string to_string(int tabNum);
    private:
        // Index of the territory in the map
        int index;
        // Name of the territory
        std::string name;
        // Continent this territory is in
        Continent* continent;
        // Owner of this territory
        Player* owner;
        // Number of armies on this territory
        int armiesCount;
        // X Coordinate of the center of the territory from the map's top left corner
        int x;
        // Y Coordinate of the center of the territory from the map's top left corner
        int y;
        // Territories connected to this territory
        std::vector<Territory*> connectedTerritories;
        // Number of connected territories
        int connectedTerritoriesCount;
        // Maximum number of territories connected to a territory
        const int MAX_TERRITORY_CONNECTIONS = 10;
};

// Class for storing a map
class Map
{
    public:
        Map();
        ~Map();
        void setAuthor(std::string author);
        void setImage(std::string image);
        void setScroll(std::string scroll);
        void setWarn(std::string warn);
        void setWrap(std::string wrap);
        void addContinent(Continent* continent);
        void addTerritory(Territory* territory);
        Continent* getContinent(std::string name);
        Territory* getTerritory(std::string name);
        std::vector<Continent*> getContinents();
        std::vector<Territory*> getTerritories();
        bool validate();
        std::string to_string(int tabNum);
    private:

        bool validateTerritoriesInContinents();
        bool validateTerritoryConnections();
        bool validateContinentConnections();

        // Author of the map
        std::string author;
        // Image of the map
        std::string image;
        // Scroll of the map
        std::string scroll;
        // Warning of the map
        std::string warn;
        // Wrap of the map
        std::string wrap;
        // Continents in the map
        std::vector<Continent*> continents;
        // Territories in the map
        std::vector<Territory*> territories;
        // Number of continents in the map
        int continentsCount;
        // Number of territories in the map
        int territoriesCount;
        // Maximum number of territories in a map
        const int MAX_TERRITORIES = 255;
        // Maximum number of continents in a map
        const int MAX_CONTINENTS = 32;
};


// Class for loading a map from a .map file
class MapLoader
{
    public:
        MapLoader();
        ~MapLoader();
        Map* loadMap(const std::string& mapFilePath);
    private:
        void extractTerritory(const std::string& line);
        void extractContinent(const std::string& line);

        void extractMapSetting(const std::string& line);

        Territory* addMainTerritory(const std::string& territoryName, const std::string& continentName, int x, int y);
        Territory* addConnectedTerritory(const std::string& territoryName);
        
        void connectContinents();
        // Map created from the file
        Map* map;
        // Number of sections in a map file
        const int NUMBER_OF_SECTIONS = 3;
};

#endif