#include "Map.h"

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Map
//
// ----------------------------------------------------------------------------------------------------------------

/**
 * @brief Validates the map by checking if it is strongly connected and each continent has at least one territory.
 *
 * @return True if the map is valid, false otherwise.
 */
bool Map::validate()
{
  return isMapStronglyConnected() && isTerritories1to1Continents();
}

/**
 * @brief Performs Depth-First Search (DFS) on the given territory to check if it is strongly connected.
 *
 * @param territory The starting territory for DFS.
 * @param visited Vector to store visited territories during DFS.
 */
void Map::DFS(Territory *territory, std::vector<Territory *> &visited)
{
  visited.push_back(territory);
  for (auto adjacent : *territory->getAdjacentTerritories())
  {
    if (std::find(visited.begin(), visited.end(), adjacent) == visited.end())
    {
      DFS(adjacent, visited);
    }
  }
}

/**
 * @brief Checks if a specific territory is strongly connected to all other territories in the map.
 *
 * @param territory The territory to check for strong connectivity.
 * @return True if the territory is strongly connected, false otherwise.
 */
bool Map::isTerritoryStronglyConnected(Territory *territory)
{
  std::vector<Territory *> visited{};
  DFS(territory, visited);
  return visited.size() == territories.size();
}

/**
 * @brief Checks if the entire map is strongly connected by applying the isTerritoryStronglyConnected function to each territory.
 *
 * @return True if the entire map is strongly connected, false otherwise.
 */
bool Map::isMapStronglyConnected()
{
  return std::all_of(territories.begin(), territories.end(), [this](Territory *t)
                     { return isTerritoryStronglyConnected(t); });
}

/**
 * @brief Checks if each continent has at least one territory.
 *
 * @return True if each continent has at least one territory, false otherwise.
 */
bool Map::isTerritories1to1Continents()
{
  return std::all_of(continents.begin(), continents.end(), [](Continent *c)
                     { return !c->getTerritories()->empty(); });
}

/**
 * @brief Adds a continent to the map.
 *
 * @param continent The continent to be added.
 */
void Map::addContinent(Continent *continent)
{
  this->continents.push_back(continent);
}

/**
 * @brief Adds a territory to the map.
 *
 * @param territory The territory to be added.
 */
void Map::addTerritory(Territory *territory)
{
  this->territories.push_back(territory);
}

// --------------------------------------------------
// Getters
// --------------------------------------------------

/**
 * @brief Gets the name of the map.
 *
 * @return The name of the map.
 */
std::string Map::getName()
{
  return this->name;
}

/**
 * @brief Gets the image associated with the map.
 *
 * @return The image file name or path.
 */
std::string Map::getImage()
{
  return this->image;
}

/**
 * @brief Gets the author of the map.
 *
 * @return The author's name.
 */
std::string Map::getAuthor()
{
  return this->author;
}

/**
 * @brief Checks if the map has wrapping enabled.
 *
 * @return True if wrapping is enabled, false otherwise.
 */
bool Map::getWrap() const
{
  return this->wrap;
}

/**
 * @brief Checks if scrolling is enabled for the map.
 *
 * @return True if scrolling is enabled, false otherwise.
 */
bool Map::getScroll() const
{
  return this->scroll;
}

/**
 * @brief Checks if warnings are enabled for the map.
 *
 * @return True if warnings are enabled, false otherwise.
 */
bool Map::getWarn() const
{
  return this->warn;
}

/**
 * @brief Gets a pointer to the vector of territories in the map.
 *
 * @return Pointer to the vector of territories.
 */
std::vector<Territory *> *Map::getTerritories()
{
  return &this->territories;
}

/**
 * @brief Gets a pointer to the vector of continents in the map.
 *
 * @return Pointer to the vector of continents.
 */
std::vector<Continent *> *Map::getContinents()
{
  return &this->continents;
}

// --------------------------------------------------
// setters
// --------------------------------------------------

/**
 * @brief Sets the name of the map.
 *
 * @param _name The name to set for the map.
 */
void Map::setName(std::string _name)
{
  this->name = std::move(_name);
}

/**
 * @brief Sets the image associated with the map.
 *
 * @param _image The image file name or path to set.
 */
void Map::setImage(std::string _image)
{
  this->image = std::move(_image);
}

/**
 * @brief Sets the author of the map.
 *
 * @param _author The author's name to set.
 */
void Map::setAuthor(std::string _author)
{
  this->author = std::move(_author);
}

/**
 * @brief Sets whether the map has wrapping enabled.
 *
 * @param _wrap True if wrapping is enabled, false otherwise.
 */
void Map::setWrap(bool _wrap)
{
  this->wrap = _wrap;
}

/**
 * @brief Sets whether scrolling is enabled for the map.
 *
 * @param _scroll True if scrolling is enabled, false otherwise.
 */
void Map::setScroll(bool _scroll)
{
  this->scroll = _scroll;
}

/**
 * @brief Sets whether warnings are enabled for the map.
 *
 * @param _warn True if warnings are enabled, false otherwise.
 */
void Map::setWarn(bool _warn)
{
  this->warn = _warn;
}

// --------------------------------------------------
// Destructors + Constructors + Operator Overloads
// --------------------------------------------------

/**
 * @brief Destructor for Map. Deletes all territories and continents associated with the map.
 */
Map::~Map()
{
  for (auto t : territories)
  {
    delete t;
  }

  for (auto c : continents)
  {
    delete c;
  }
}

/**
 * @brief Overloaded stream insertion operator for Map.
 *
 * @param stream The output stream.
 * @param other The Map object to be printed.
 * @return The output stream.
 */
std::ostream &operator<<(std::ostream &stream, const Map &other)
{
  stream << "Map Name: " << other.name << '\n'
         << "Map Author: " << other.author << '\n'
         << "Map Image: " << other.image << '\n'
         << "Map Wrap: " << (other.wrap ? "True" : "False") << '\n'
         << "Map Scroll: " << (other.scroll ? "Horizontal" : "Vertical") << '\n'
         << "Map Warn: " << (other.warn ? "True" : "False") << '\n';

  stream << "Map Continents: " << '\n';
  for (auto c : other.continents)
  {
    stream << *c << '\n';
  }

  stream << "Map Territories: " << '\n';
  for (auto t : other.territories)
  {
    stream << *t << '\n';
  }

  return stream;
}

/**
 * @brief Copy constructor for Map.
 *
 * @param other The Map object to be copied.
 */
Map::Map(const Map &other)
    : name(other.name), author(other.author), warn(other.warn), scroll(other.scroll), image(other.image), wrap(other.wrap), game(other.game)
{
  // Deep copy
  for (auto t : territories)
  {
    this->addTerritory(new Territory(*t));
  }
  // Deep copy
  for (auto c : continents)
  {
    this->addContinent(new Continent(*c));
  }
}

/**
 * @brief Copy assignment operator for Map.
 *
 * @param other The Map object to be assigned.
 * @return Reference to the assigned Map object.
 */
Map &Map::operator=(const Map &other)
{
  if (this == &other)
  {
    return *this;
  }

  this->name = other.name;
  this->image = other.image;
  this->author = other.author;

  this->wrap = other.wrap;
  this->scroll = other.scroll;
  this->warn = other.warn;

  this->continents = other.continents;
  this->territories = other.territories;

  this->game = other.game;

  return *this;
}

/**
 * @brief Constructor for Map that takes a GameEngine pointer.
 *
 * @param game The GameEngine pointer associated with the map.
 */
Map::Map(GameEngine *game)
    : game(game)
{
  if (game == nullptr)
  {
    throw std::runtime_error("Map::Error | Cannot set map Game Engine to null");
  }
}

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Territory
//
// ----------------------------------------------------------------------------------------------------------------

/**
 * @brief Constructor for Territory.
 *
 * @param name The name of the territory.
 */
Territory::Territory(std::string name)
    : name(std::move(name)), continent(nullptr), player(nullptr)
{
}

/**
 * @brief Adds an adjacent territory to the current territory.
 *
 * @param territory The adjacent territory to add.
 */
void Territory::addAdjacentTerritory(Territory *territory)
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
std::vector<Territory *> *Territory::getAdjacentTerritories()
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
 * @return Pointer to the continent of the territory.
 */
Continent *Territory::getContinent()
{
  return this->continent;
}

/**
 * @brief Sets the continent to which the territory belongs.
 *
 * @param c Pointer to the continent to set.
 */
void Territory::setContinent(Continent *c)
{
  this->continent = c;
}

/**
 * @brief Copy constructor for Territory.
 *
 * @param other The Territory object to be copied.
 */
Territory::Territory(const Territory &other) = default;

/**
 * @brief Copy assignment operator for Territory.
 *
 * @param other The Territory object to be assigned.
 * @return Reference to the assigned Territory object.
 */
Territory &Territory::operator=(const Territory &other)
{
  if (this == &other)
  {
    return *this;
  }

  this->name = other.name;
  this->continent = other.continent;
  this->player = other.player;

  this->armies = other.armies;

  this->x = other.x;
  this->y = other.y;

  this->adjacentTerritories = other.adjacentTerritories;
  return *this;
}

/**
 * @brief Overloaded stream insertion operator for Territory.
 *
 * @param stream The output stream.
 * @param other The Territory object to be printed.
 * @return The output stream.
 */
std::ostream &operator<<(std::ostream &stream, const Territory &other)
{
  stream << "Territory Name: " << other.name << '\n'
         << "Territory Coordinates: " << '(' << other.x << ", " << other.y << ')' << '\n';
  return stream;
}

/**
 * @brief Gets the number of armies in the territory.
 *
 * @return The number of armies in the territory.
 */
int Territory::getArmies() const
{
  return this->armies;
}

/**
 * @brief Sets the number of armies in the territory.
 *
 * @param army_units The number of army units to set.
 */
void Territory::setArmies(int army_units)
{
  this->armies = army_units;
}

/**
 * @brief Removes a specified number of army units from the territory.
 *
 * @param removed The number of army units to remove.
 * @return The total number of armies remaining in the territory.
 */
int Territory::removeArmyUnits(int removed)
{
  if (removed < 0)
  {
    throw std::runtime_error("Cannot remove a negative amount of army units.");
  }
  int total = this->armies - removed;
  if (total < 0)
  {
    throw std::runtime_error("Cannot remove more armies than the territory currently has.");
  }
  this->armies = total;
  return total;
}

/**
 * @brief Adds a specified number of army units to the territory.
 *
 * @param added The number of army units to add.
 * @return The total number of armies in the territory.
 */
int Territory::addArmyUnits(int added)
{
  if (added < 0)
  {
    throw std::runtime_error("Cannot add a negative amount of army units.");
  }
  int total = this->armies + added;
  this->armies = total;
  return total;
}

/**
 * @brief Gets the player that owns the territory.
 *
 * @return Pointer to the player that owns the territory.
 */
Player *Territory::getPlayer()
{
  return this->player;
}

/**
 * @brief Sets the player that owns the territory.
 *
 * @param p Pointer to the player to set.
 */
void Territory::setPlayer(Player *p)
{
  this->player = p;
}

/**
 * @brief Checks if a territory is adjacent to another territory.
 *
 * @param pTerritory The territory to check for adjacency.
 * @return True if the territories are adjacent, false otherwise.
 */
bool Territory::isAdjacent(Territory *&pTerritory)
{
  for (auto t : this->adjacentTerritories)
  {
    if (t == pTerritory)
    {
      return true;
    }
  }
  return false;
}

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Continent
//
// ----------------------------------------------------------------------------------------------------------------

/**
 * @brief Constructor for Continent.
 *
 * @param name The name of the continent.
 * @param bonus The bonus associated with the continent.
 */
Continent::Continent(std::string name, int bonus)
{
  this->name = std::move(name);
  this->bonus = bonus;
}

/**
 * @brief Adds a territory to the continent.
 *
 * @param territory The territory to add.
 */
void Continent::addTerritory(Territory *territory)
{
  this->territories.push_back(territory);
}

/**
 * @brief Gets the name of the continent.
 *
 * @return The name of the continent.
 */
std::string Continent::getName()
{
  return this->name;
}

/**
 * @brief Gets the bonus associated with the continent.
 *
 * @return The bonus of the continent.
 */
int Continent::getBonus() const
{
  return this->bonus;
}

/**
 * @brief Gets a pointer to the vector of territories in the continent.
 *
 * @return Pointer to the vector of territories in the continent.
 */
std::vector<Territory *> *Continent::getTerritories()
{
  return &this->territories;
}

/**
 * @brief Overloaded stream insertion operator for Continent.
 *
 * @param stream The output stream.
 * @param other The Continent object to be printed.
 * @return The output stream.
 */
std::ostream &operator<<(std::ostream &stream, const Continent &other)
{
  stream << "Continent Name: " << other.name << '\n'
         << "Continent Bonus: " << other.bonus << '\n';

  stream << "Continent Territories: " << '\n';
  for (auto t : other.territories)
  {
    stream << (*t) << '\n';
  }
  return stream;
}

/**
 * @brief Copy assignment operator for Continent.
 *
 * @param other The Continent object to be assigned.
 * @return Reference to the assigned Continent object.
 */
Continent &Continent::operator=(const Continent &other)
{
  if (&other == this)
  {
    return *this;
  }
  this->name = other.name;
  this->bonus = other.bonus;
  this->territories = other.territories;

  return *this;
}

/**
 * @brief Copy constructor for Continent.
 *
 * @param other The Continent object to be copied.
 */
Continent::Continent(const Continent &other) = default;

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                MapLoader
//
// ----------------------------------------------------------------------------------------------------------------

/**
 * @brief Loads a map from a file.
 *
 * @param path The path to the file.
 * @param out_map The map object to load the data into.
 */
void MapLoader::load(const std::string &path, Map *out_map)
{
  std::ifstream input_file(path, std::ios::in);
  std::string line;

  // check if file is open
  if (!input_file.is_open())
  {
    throw std::runtime_error("Could not open file: " + path);
  }

  MapLoaderState state;

  std::string map_name = path.substr(path.find_last_of('/') + 1);
  out_map->setName(map_name);

  while (getline(input_file, line))
  {
    line = trim(line);
    if (line.empty())
    {
      continue;
    }

    parseLine(line, out_map, state);
  }

  state.parseState = ReadingState_Idle;
  input_file.close();
}

/**
 * @brief Parses a line of the map file.
 *
 * @param line The line to parse.
 * @param map The map object.
 * @param mapLoaderState The state of the map loader.
 */
void MapLoader::parseLine(std::string &line, Map *map, MapLoaderState &mapLoaderState)
{
  switch (mapLoaderState.parseState)
  {
  case ReadingState_Idle:
    if (line == "[Map]")
    {
      mapLoaderState.parseState = ReadingState_Map;
    }
    else
    {
      throw std::runtime_error("Invalid map file");
    }
    break;

  case ReadingState_Map:
    if (line == "[Continents]")
    {
      mapLoaderState.parseState = ReadingState_Continents;
    }
    else
    {
      std::string delimiter = "=";
      if (line.find(delimiter) != std::string::npos)
      {
        std::string key = line.substr(0, line.find(delimiter));
        std::string value = line.substr(line.find(delimiter) + 1, line.length());
        if (key == "author")
        {
          map->setAuthor(value);
        }
        else if (key == "image")
        {
          map->setImage(value);
        }
        else if (key == "wrap")
        {
          map->setWrap(value == "yes");
        }
        else if (key == "scroll")
        {
          map->setScroll(value == "horizontal");
        }
        else if (key == "warn")
        {
          map->setWarn(value == "yes");
        }
      }
    }
    break;

  case ReadingState_Continents:
    if (line == "[Territories]")
    {
      mapLoaderState.parseState = ReadingState_Territories;
    }
    else
    {
      // parse continents
      std::string delimiter = "=";
      if (line.find(delimiter) != std::string::npos)
      {
        std::string name = line.substr(0, line.find(delimiter));
        std::string value = line.substr(line.find(delimiter) + 1, line.length());
        Continent *continent;
        try
        {
          continent = new Continent(name, std::stoi(value));
        }
        catch (std::invalid_argument &e)
        {
          throw std::runtime_error("Map Formatting Error: Invalid Continent Bonus.");
        }
        catch (std::out_of_range &e)
        {
          throw std::runtime_error("Map Formatting Error: Continent Bonus Coordinate Out Of Range.");
        }

        map->addContinent(continent);
        mapLoaderState.continents[name] = continent;
      }
    }
    break;

  case ReadingState_Territories:
    // parse territories
    parseTerritoryLine(line, map, mapLoaderState);
    break;
  }
}

/**
 * @brief Parses a line of territory information.
 *
 * @param line The line to parse.
 * @param map The map object.
 * @param mapLoaderState The state of the map loader.
 */
void MapLoader::parseTerritoryLine(std::string &line, Map *map, MapLoaderState &mapLoaderState)
{
  std::string delimiter = ",";
  // Territory
  Territory *territory = nullptr;

  if (line.find(delimiter) != std::string::npos)
  {
    std::string name = line.substr(0, line.find(delimiter));
    line = line.substr(line.find(delimiter) + 1, line.length());

    // check if territory exists in territoriesToCreate before creating a new one
    if (mapLoaderState.territoriesToCreate.find(name) != mapLoaderState.territoriesToCreate.end())
    {
      territory = mapLoaderState.territoriesToCreate[name];
      // remove from territoriesToCreate
      mapLoaderState.territoriesToCreate.erase(name);
    }
    else
    {
      territory = new Territory(name);
    }
  }

  // parse the rest of the line
  while (!line.empty())
  {
    auto delimiter_location = line.find(delimiter);
    std::string value = line.substr(0, delimiter_location);
    line = delimiter_location == std::string::npos ? "" : line.substr(delimiter_location + 1, line.length());

    // x
    if (territory->getX() == -1)
    {
      try
      {
        territory->setX(std::stoi(value));
      }
      catch (std::invalid_argument &e)
      {
        throw std::runtime_error("Map Formatting Error: Invalid X Coordinate.");
      }
      catch (std::out_of_range &e)
      {
        throw std::runtime_error("Map Formatting Error: X Coordinate Out Of Range.");
      }
      continue;
    }
    // y
    else if (territory->getY() == -1)
    {
      try
      {
        territory->setY(std::stoi(value));
      }
      catch (std::invalid_argument &e)
      {
        throw std::runtime_error("Map Formatting Error: Invalid Y Coordinate.");
      }
      catch (std::out_of_range &e)
      {
        throw std::runtime_error("Map Formatting Error: Y Coordinate Out Of Range.");
      }
      continue;
    }
    // continent
    else if (territory->getContinent() == nullptr)
    {
      // check if continents exists in hashmap
      if (mapLoaderState.continents.find(value) == mapLoaderState.continents.end())
      {
        throw std::runtime_error("Invalid continent: " + value);
      }
      else
      {
        territory->setContinent(mapLoaderState.continents[value]);
        mapLoaderState.continents[value]->addTerritory(territory);
      }
      continue;
    }
    // adjacent territories
    else
    {
      // check if territory exists in hashmap
      if (mapLoaderState.territories.find(value) != mapLoaderState.territories.end())
      {
        territory->addAdjacentTerritory(mapLoaderState.territories[value]);
      }
      else
      {
        Territory *adjacentTerritory;
        // check inside territories to create
        if (mapLoaderState.territoriesToCreate.find(value) != mapLoaderState.territoriesToCreate.end())
        {
          // use previously created
          adjacentTerritory = mapLoaderState.territoriesToCreate[value];
        }
        else
        {
          // create new territory
          adjacentTerritory = new Territory(value);
        }
        territory->addAdjacentTerritory(adjacentTerritory);
        // add to territoriesToCreate
        mapLoaderState.territoriesToCreate[value] = adjacentTerritory;
      }
    }
  }
  mapLoaderState.territories[territory->getName()] = territory;
  map->addTerritory(territory);
}

/**
 * @brief Trims leading whitespaces from a string.
 *
 * @param s The string to trim.
 * @return The trimmed string.
 */
std::string MapLoader::ltrim(const std::string &s)
{
  size_t start = s.find_first_not_of(" \n\r\t\f\v");
  return (start == std::string::npos) ? "" : s.substr(start);
}

/**
 * @brief Trims trailing whitespaces from a string.
 *
 * @param s The string to trim.
 * @return The trimmed string.
 */
std::string MapLoader::rtrim(const std::string &s)
{
  size_t end = s.find_last_not_of(" \n\r\t\f\v");
  return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

/**
 * @brief Trims leading and trailing whitespaces from a string.
 *
 * @param s The string to trim.
 * @return The trimmed string.
 */
std::string MapLoader::trim(const std::string &s)
{
  return rtrim(ltrim(s));
}