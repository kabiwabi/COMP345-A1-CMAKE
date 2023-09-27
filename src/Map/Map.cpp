#include <fstream>
#include <iostream>
#include <stack>

#include "Map.h"
#include "../Player/Player.h"
using namespace std;

// Returns a string containing x amount of tab characters
std::string string_tabs(int x)
{
    // Create the empty string
    string tabsString = "";

    // Add the tab characters to the string
    for(int i=0; i<x; i++)
    {
        tabsString += "\t";
    }

    return tabsString;
}

std::string remove_whitespace(std::string s)
{
    string s1="";
    string whitespace="";

    for(char c:s)
    {
        // c is a leading whitespace
        if(c==' ' && s1=="")
        {
            continue;
        }
        // c is not a leading whitespace
        else if (c==' ' && s1!="")
        {
            whitespace+=c;
        }
        // c is not a whitespace
        else if(c!=' ')
        {
            s1+=whitespace+c;
            whitespace="";
        }
    }

    return s1;
}

// ==============================================================================
// CONTINENT
// ==============================================================================
#pragma region Continent

// Constructor
Continent::Continent(const std::string& name, int bonus)
{
    this->name = name;
    this->bonus = bonus;
    this->index = -1;
    this->connectedContinents = std::vector<Continent *>();
}

// Destructor
Continent::~Continent()
{
    // Delete all the pointers to the connected continents
    for(auto& continent : this->connectedContinents)
    {
        delete continent;
    }
}

// Sets the name of the continent
void Continent::setName(std::string name)
{
    this->name=name;
}

// Set the bonus of the continent
void Continent::setBonus(int bonus)
{
    this->bonus=bonus;
}

// Adds an connected continent
void Continent::addConnectedContinent(Continent *continent)
{    
    // Check if the continent is already in the vector, if it is, return
    if(this->getConnectedContinent(continent->getName()) != nullptr)
    {
        return;
    }

    // If it isn't, add it to the connected continents
    this->connectedContinents.push_back(continent);
}

// Returns the name of the continent
std::string Continent::getName()
{
    return this->name;
}

// Returns the bonus of the continent
int Continent::getBonus()
{
    return this->bonus;
}

void Continent::setIndex(int index)
{
    this->index = index;
}

int Continent::getIndex()
{
    return this->index;
}

std::vector<int> Continent::getConnectedContinentIndexes()
{
    vector<int> indexes;
    for(auto& continent : this->connectedContinents)
    {
        indexes.push_back(continent->getIndex());
    }
    return indexes;
}

// Returns all connected continents
std::vector<Continent *> Continent::getConnectedContinents()
{
    return this->connectedContinents;
}

// Returns the continent with the given name, or nullptr if it doesn't exist
Continent *Continent::getConnectedContinent(std::string continentName)
{
    // Loop through all the connected continents
    for(auto& continent : this->connectedContinents)
    {
        // If the continent name matches the given name, return it
        if(continent->getName() == continentName)
        {
            return continent;
        }
    }

    // If it doesn't exist, return nullpt
    return nullptr;
}

// Returns a string representation of the continent
std::string Continent::to_string(int tabNum=0)
{
    string continentString = string_tabs(tabNum) + "Continent:\n";
    continentString += string_tabs(tabNum) + "{\n";
    continentString += string_tabs(tabNum) + "\tName: " + this->name + "\n";
    continentString += string_tabs(tabNum) + "\tBonus: "+ std::to_string(this->bonus) + "\n";    
    continentString += string_tabs(tabNum) + "\tConnected Continents: \n";
 
    // Show only the name of all the connected continents
    for(auto& continent : this->connectedContinents)
    {
        continentString += string_tabs(tabNum) + "\t\t- " + continent->getName() + "\n";
    }

    continentString += string_tabs(tabNum) + "}\n";

    return continentString;
}

#pragma endregion

// ==============================================================================
// TERRITORY
// ==============================================================================
#pragma region Territory

// Contructor
Territory::Territory(const std::string& name, Continent* continent, int x, int y)
{
    this->name = name;
    this->continent = continent;
    this->x = x;
    this->y = y;
    this->index=-1;
    this->connectedTerritories = std::vector<Territory *>();
    this->connectedTerritoriesCount=0;
}

// Constructor
Territory::Territory(const std::string &name)
{
    this->name=name;
    this->continent = nullptr;
    this->x = 0;
    this->y=0;
    this->connectedTerritories = std::vector<Territory *>();
    this->connectedTerritoriesCount=0;
}

// Destructor
Territory::~Territory() 
{
    // Delete all the pointers to the connected territories
    for(auto& territory : this->connectedTerritories)
    {
        delete territory;
    }

    // Delete pointer to the continent
    delete this->continent;
}

// Sets the name of the territory
void Territory::setName(std::string name)
{
    this->name = name;
}

// Set the continent of the territory
void Territory::setContinent(Continent *continent)
{
    this->continent = continent;
}

// Set the x coordinate of the territory
void Territory::setX(int x)
{
    this->x = x;
}

// Set the y coordinate of the territory
void Territory::setY(int y)
{
    this->y = y;
}

// Adds a connected territory
void Territory::addConnectedTerritory(Territory *territory)
{
    // Check if the territory connections limit has been reached
    if(this->connectedTerritoriesCount >= MAX_TERRITORY_CONNECTIONS)
    {
        // Show an error message and return
        cout << "Territory connections limit has been reached!" << endl;
        return;
    }

    // If it hasn't, add it to the connected territories
    this->connectedTerritories.push_back(territory);
    this->connectedTerritoriesCount++;
}

// Sets the index of the territory within a map
void Territory::setIndex(int index)
{
    this->index = index;
}

// Returns the index of the territory within a map
int Territory::getIndex()
{
    return this->index;
}

// Returns the name of the territory
std::string Territory::getName()
{
    return this->name;
}

// Returns the continent of the territory
Continent *Territory::getContinent()
{
    return this->continent;
}

// Returns the x coordinate of the territory
int Territory::getX()
{
    return this->x;
}

// Returns the y coordinate of the territory
int Territory::getY()
{
    return this->y;
}

// Returns all connected territories
std::vector<Territory *> Territory::getConnectedTerritories()
{
    return this->connectedTerritories;
}

std::vector<int> Territory::getConnectedTerritoryIndexes()
{
    vector<int> indexes;
    for(auto& territory : this->connectedTerritories)
    {
        indexes.push_back(territory->getIndex());
    }
    return indexes;
}

// Returns a string representation of the territory
std::string Territory::to_string(int tabNum=0)
{
    string territoryString = string_tabs(tabNum) + "Territory:\n";
    territoryString += string_tabs(tabNum) + "{\n";
    
    territoryString += string_tabs(tabNum) + "\tName: " + this->name + "\n";
    territoryString += string_tabs(tabNum) + "\tContinent: " + this->continent->getName() + "\n";
    territoryString += string_tabs(tabNum) + "\tX: " + std::to_string(this->x) + "\n";
    territoryString += string_tabs(tabNum) + "\tY: " + std::to_string(this->y) + "\n";
    territoryString += string_tabs(tabNum) + "\tConnected Territories: \n";
    
    for(auto& territory : this->connectedTerritories)
    {
        territoryString += string_tabs(tabNum) + "\t\t - " + territory->getName() + "\n";
    }

    territoryString += string_tabs(tabNum) + "\t}";

    return territoryString;
}

#pragma endregion

// ==============================================================================
// MAP
// ==============================================================================
#pragma region Map

// Constructor
Map::Map()
{
    this->author = "";
    this->image = "";
    this->scroll = "";
    this->warn = "";
    this->wrap = "";
    this->continents = std::vector<Continent *>();
    this->territories = std::vector<Territory *>();
    this->continentsCount = 0;
    this->territoriesCount = 0;
}

// Destructor
Map::~Map()
{
    // Delete all the territories pointers
    for(auto& territory : this->territories)
    {
        delete territory;
    }

    // Delete all the continents pointers
    for(auto& continent : this->continents)
    {
        delete continent;
    }
}

// Sets the author of the map
void Map::setAuthor(std::string author)
{
    this->author = author;
}

// Sets the image of the map
void Map::setImage(std::string image)
{
    this->image = image;
}

// Sets the scroll value of the map
void Map::setScroll(std::string scroll)
{
    this->scroll = scroll;
}

// Sets the warning value of the map
void Map::setWarn(std::string warn)
{
    this->warn = warn;
}

// Sets the wrap value of the map
void Map::setWrap(std::string wrap)
{
    this->wrap = wrap;
}

// Adds a continent to the map
void Map::addContinent(Continent *continent)
{
    // Check the maximum number of continents has not been reached
    if(this->continentsCount>=MAX_CONTINENTS)
    {
        // Show an error message and return
        cout << "Maximum number of continents reached!" << endl;
        return;
    }

    // If it hasn't, add it to the continents
    continent->setIndex(this->continentsCount);
    this->continents.push_back(continent);
    this->continentsCount++;
}

// Adds a territory to the map
void Map::addTerritory(Territory *territory)
{
    // Check the maximum number of territories has not been reached
    if(this->territoriesCount>=MAX_TERRITORIES)
    {
        // Show an error message and return
        cout << "Maximum number of territories reached!" << endl;
        return;
    }

    // If it hasn't, add it to the territories
    territory->setIndex(this->territoriesCount);
    this->territories.push_back(territory);
    this->territoriesCount++;
}

// Returns a continent by name
Continent *Map::getContinent(std::string name)
{
    // Iterate through each continent
    for(auto& continent : this->continents)
    {
        // If the name matches, return the continent
        if(continent->getName()==name)
        {
            return continent;
        }
    }    

    // If no continent was found, return a null pointer
    return nullptr;
}

// Returns a territory by name
Territory *Map::getTerritory(std::string name)
{
    // Iterate through each territory
    for(auto& territory : this->territories)
    {
        // If the name matches, return the territory
        if(territory->getName()==name)
        {
            return territory;
        }
    }
    // If no territory was found, return a null pointer
    return nullptr;
}

// Returns all the continents in the map
std::vector<Continent *> Map::getContinents()
{
    return this->continents;
}

// Returns all the territories in the map
std::vector<Territory *> Map::getTerritories()
{
    return this->territories;
}


bool Map::validate()
{
    // Check that the map is a connected graph
    // Check that continants are connected subgraphs
    // Check that each territory belongs to one and only one continent 
    
    return validateTerritoriesInContinents() && validateTerritoryConnections() && validateContinentConnections();
}


// Returns a string representation of the map
std::string Map::to_string(int tabNum=0)
{
    string mapString = string_tabs(tabNum) + "Map:\n";
    mapString += string_tabs(tabNum) + "{\n";
    mapString += string_tabs(tabNum) + "\tAuthor: " + this->author + "\n";
    mapString += string_tabs(tabNum) + "\tWrap: " + this->wrap  + "\n";
    mapString += string_tabs(tabNum) + "\tScroll: " + this->scroll + "\n";
    mapString += string_tabs(tabNum) + "\tImage: " + this->image + "\n";
    mapString += string_tabs(tabNum) + "\tWarn: " + this->warn + "\n";

    mapString += string_tabs(tabNum) + "\tContinents:";
    mapString += "\t{\n";
    for(auto& continent : this->continents)
    {
        mapString += continent->to_string(tabNum+1) + "\n"; 
    }
    mapString += string_tabs(tabNum) + "\t}\n";
    
    mapString += string_tabs(tabNum) + "\tTerritories:{\n";
    for(auto& territory : this->territories)    
    {
        mapString += territory->to_string(tabNum+1) + "\n";
    }
    mapString += string_tabs(tabNum) + "\t}\n";
    
    mapString += string_tabs(tabNum) + "\tNumber of Continents: " + std::to_string(this->continentsCount) + "\n";
    mapString += string_tabs(tabNum) + "\tNumber of Territories: " + std::to_string(this->territoriesCount) + "\n";
    mapString += string_tabs(tabNum) + "}";

    return mapString;
}

// Checks that all the territories are in a continent
bool Map::validateTerritoriesInContinents()
{
    // Check that all territories are in a continent
    for(auto& territory: this->territories)
    {
        // If the territory doesn't have a continent, return false
        if(dynamic_cast<Continent *>(territory->getContinent())==nullptr)
        {
            return false;
        }
    }

    return true;
}

bool Map::validateTerritoryConnections()
{
    // Tracks the visited territories
    vector<bool> visited(this->territories.size(), false);
    
    // Tracks the territories that have not yet been visited
    stack<int> territoryStack;

    // Tracks the current territory that is being visited
    int currentTerritoryIndex = 0;

    // Start with the first territory
    territoryStack.push(currentTerritoryIndex);

    // Loop until all territories have been visited
    while (!territoryStack.empty())
    {
        // Get the next territory to visit
        currentTerritoryIndex = territoryStack.top();
        territoryStack.pop();

        // Set the current territory as visited
        visited[currentTerritoryIndex] = true;

        // Add all the unvisited connected territories to the stack
        for(auto& connectedTerritoryIndex: this->territories[currentTerritoryIndex]->getConnectedTerritoryIndexes())
        {
            // If the connected territory has not been visited, add it to the stack
            if(!visited[connectedTerritoryIndex])
            {
                territoryStack.push(connectedTerritoryIndex);
            }
        }
    }
    
    // Validate that all territories have been visited, meaning that the graph is connected
    for(int i=0; i<visited.size(); i++)
    {
        if(!visited[i])
        {
            return false;
        }
    }

    return true;
}

bool Map::validateContinentConnections()
{
    // Tracks the visited continents
    vector<bool> visited(this->continents.size(), false);
    
    // Tracks the continents that have not yet been visited
    stack<int> continentStack;

    // Tracks the current continent that is being visited
    int currentContinentIndex = 0;

    // Start with the first continent
    continentStack.push(currentContinentIndex);

    // Loop until all continents have been visited
    while (!continentStack.empty())
    {
        // Get the next continent to visit
        currentContinentIndex = continentStack.top();
        continentStack.pop();

        // Set the current continent as visited
        visited[currentContinentIndex] = true;

        // Add all the unvisited connected continents to the stack
        for(auto& connectedContinentIndex: this->continents[currentContinentIndex]->getConnectedContinentIndexes())
        {
            // If the connected continent has not been visited, add it to the stack
            if(!visited[connectedContinentIndex])
            {
                continentStack.push(connectedContinentIndex);
            }
        }
    }
    
    // Validate that all continents have been visited, meaning that the graph is connected
    for(int i=0; i<visited.size(); i++)
    {
        if(!visited[i])
        {
            return false;
        }
    }

    return true;
}

#pragma endregion

// ==============================================================================
// MAP LOADER
// ==============================================================================
#pragma region Map Loader

// Constructor
MapLoader::MapLoader()
{
    this->map = new Map();
}

// Destructor
MapLoader::~MapLoader()
{
    // Delete the pointer to the map
    delete this->map;
}

// Creates a map object from a map file, given the path to the file
Map *MapLoader::loadMap(const std::string& mapFilePath)
{
    // Tracks the current line that is being read
    string line {};
    // Stream to read the file 
    ifstream mapFile (mapFilePath);
    // Tracks the current section of the file
    mapSections section = none;
    // Tracks the number of sections found in the file. It should be 3.
    int sectionsCount = 0;
    
    // Open the file
    if(mapFile.is_open())
    {
        // Iterate through each line of the file
        while (getline(mapFile, line))
        {
            // The Map section has been reached
            if(line=="[Map]")
            {
                section = mapSection;
                sectionsCount++;
            }
            // The Continents section has been reached
            else if(line=="[Continents]")
            {
                section = continentsSection;
                sectionsCount++;
            }
            // The Territories section has been reached
            else if(line=="[Territories]")
            {
                section = territoriesSection;
                sectionsCount++;
            }
            // Reading a line belonging to one of the 3 sections
            else if(line!="" && section!=none)
            {
                switch (section)
                {
                    // Extract the map settings from the Map section
                    case mapSection:
                        extractMapSetting(line);
                        break;
                    // Extract the continents from the Continents section
                    case continentsSection:
                        extractContinent(line);
                        break;
                    // Extract the territories from the Territories section
                    case territoriesSection:
                        extractTerritory(line);
                        break;
                    default:
                        break;
                }
            }   
        }
        // Close the file after reading it
        mapFile.close();
    }
    else
    {
        // Show an error message if the file is not found
        cout << "Unable to open file!"<<endl;
    }

    // Check if the file is a valid map file
    if(sectionsCount!=3 || section==none)
    {
        cout << "The file is not a valid map file!" << endl;
        return nullptr;
    }

    // For each continent, set their connected continents
    this->connectContinents();

    // Return a pointer to the map
    return this->map;
}

// Extracts the territory details represented by each line under the Territories section
void MapLoader::extractTerritory(const std::string &line)
{
    // Current territory
    Territory *territory;
    // Current connected territory
    Territory *connectedTerritory;

    // Current territory name, continent name, x and y coordinate
    string territoryName {};
    string continentName {};
    string x {};
    string y {};
    
    // Current connected territory name
    string connectedTerritoryName {};
    
    // Delimiter between values
    char delimiter = ',';
    
    // True when all values for the current territory are extracted
    bool isMainTerritory = false;

    // True when the delimiter has been encountered for the current value
    bool isNewVal = false;
    // Counts the number of values read. The first 4 values are reserved for the territory details
    int newValCounter = 0;
    
    // Iterate through each character of the line
    for(int i=0; i<line.length(); i++)
    {
        // Delimiter is found, move to next value
        if(line[i]==delimiter)
        {
            newValCounter++;
            isNewVal = true;
            continue;
        }

        switch (newValCounter)
        {
            // The current value belongs to the territory name
            case 0:
                territoryName += line[i];
                break;
            // The current value belongs to the x coordinate
            case 1:
                x+=line[i];
                break;
            // The current value belongs to the y coordinate
            case 2:
                y+=line[i];
                break;
            // The current value belongs to the continent name
            case 3:
                continentName+=line[i];
                isMainTerritory = true;
                break;
            default:
                // Add the Territory details to the map for which the current line refers to
                if(isMainTerritory)
                {
                    // Add the territory details to the map
                    territory = addMainTerritory(remove_whitespace(territoryName), remove_whitespace(continentName), stoi(x), stoi(y));

                    // Prevent the territory from being added twice
                    isMainTerritory=false;
                    isNewVal=false;
                }

                // Connect the connected territory to the main one
                if(isNewVal)
                {
                    // Get/Add the connected territory
                    connectedTerritory = addConnectedTerritory(remove_whitespace(connectedTerritoryName));
                    territory->addConnectedTerritory(connectedTerritory);

                    // Reset the territory name
                    connectedTerritoryName = "";
                    isNewVal=false;
                }

                connectedTerritoryName+=line[i];

                break;
        }
    }

    // Make sure to connect the last territory if needed
    if(connectedTerritoryName!="")
    {
        // Get/Add the connected territory
        connectedTerritory = addConnectedTerritory(remove_whitespace(connectedTerritoryName));

        // Connect the territories
        territory->addConnectedTerritory(connectedTerritory);
    }
}

// Extracts the continents represented by each line under the Continents section
void MapLoader::extractContinent(const std::string &line)
{
    // Extract the name and bonus from the line
    string continentName {};
    string continentBonus {};

    // delimiter between the name and bonus
    string delimiter = "=";
    
    // Find the delimiter index
    int  delimiterIndex = line.find(delimiter);

    // Iterate through each character of the line
    for(int i=0; i<line.length(); i++)
    {
        // Add the character to the continent name
        if(i<delimiterIndex)
        {
            continentName += line[i];
        }
        // Add the character to the continent bonus
        else if(i>delimiterIndex)
        {
            continentBonus += line[i];
        }
    }

    // Create a new continent and add it to the map
    this->map->addContinent(new Continent(remove_whitespace(continentName), stoi(continentBonus)));
}

// Extracts the settings represented by each line under the Map section
void MapLoader::extractMapSetting(const std::string &line)
{
    // Extract the key and value from the line
    string key {};
    string value {};

    // delimiter between the key and value
    string delimiter = "="; 
    
    // Find the delimiter index
    int delimiterIndex = line.find(delimiter);

    // Iterate through each character of the line
    for(int i=0; i<line.length(); i++)
    {
        // Add the character to the key
        if(i<delimiterIndex)
        {
            key += tolower(line[i]);
        }
        // Add the character to the value
        else if(i>delimiterIndex)
        {
            value += line[i];
        }
    }

    // Set the map setting value for the specified key
    if(key=="author")
    {
        this->map->setAuthor(value);
    }
    else if(key=="warn")
    {
        this->map->setWarn(value);
    }
    else if(key=="image")
    {
        this->map->setImage(value);
    }
    else if(key=="wrap")
    {
        this->map->setWrap(value);
    }
    else if(key=="scroll")
    {
        this->map->setScroll(value);
    }
}

// Adds/Modifies a territory, with its name, continent and position in the map
Territory* MapLoader::addMainTerritory(const std::string &territoryName, const std::string &continentName, int x, int y)
{
    // Get the continent to which the territory belongs
    Continent *continent = this->map->getContinent(continentName);  
    
    // Check if the territory already exists
    Territory *territory = this->map->getTerritory(territoryName);

    // If the territory does not exist, create a new one and add it to the map
    if(territory==nullptr)
    {
        territory = new Territory(territoryName, continent, x, y);
        this->map->addTerritory(territory);
    }
    // If the territory exists, update its position and continent
    else
    {
        territory->setContinent(continent);
        territory->setX(x);
        territory->setY(y);
    }

    // Return a pointer to the territory
    return territory;
}

// Adds/Modifies a connected territory, with its name 
Territory* MapLoader::addConnectedTerritory(const std::string &territoryName)
{
    // Check if the territory already exists
    Territory *territory = this->map->getTerritory(territoryName);

    // If the territory does not exist, create a new one and add it to the map
    if(territory==nullptr)
    {
        territory = new Territory(territoryName);
        this->map->addTerritory(territory);
    }
    
    // Return a pointer to the territory
    return territory;
}

// Connects the continents with each other
void MapLoader::connectContinents()
{
    // Current continent
    Continent *continent;
    // All territories
    std::vector<Territory*> territories = this->map->getTerritories();

    // Iterate through each territory
    for(int i=0; i<territories.size(); i++)
    {
        // Get the continent to which the current territory belongs
        continent = territories[i]->getContinent();
        
        // Iterate through each territory's connected territories
        for(auto& territory : territories[i]->getConnectedTerritories())
        {
            // If the connected territory's continent is not the current continent, add it to the current continent's connected continents
            if(territory->getContinent()->getName()!=continent->getName())
            {
                continent->addConnectedContinent(territory->getContinent());
            }
        }
    }
}

#pragma endregion
