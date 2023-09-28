#include "Map.h"

/**
 * @brief Validates the map by checking if it is strongly connected and if each territory belongs to a continent.
 *
 * @return true If the map is valid.
 * @return false Otherwise.
 */
bool Map::validate()
{
    return isMapStronglyConnected() && isTerritories1to1Continents();
}

/**
 * @brief Performs Depth First Search (DFS) on a given territory to check for connectivity.
 *
 * @param territory The starting territory for DFS.
 * @param visited Vector storing the visited territories.
 */
void Map::DFS(Territory* territory, std::vector<Territory*> &visited)
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
 * @brief Checks if a territory is strongly connected to all other territories.
 *
 * @param territory The territory to check.
 * @return true If the territory is strongly connected.
 * @return false Otherwise.
 */
bool Map::isTerritoryStronglyConnected(Territory* territory)
{
    std::vector<Territory *> visited{};
    DFS(territory, visited);
    return visited.size() == territories.size();
}

/**
 * @brief Checks if the map as a whole is strongly connected.
 *
 * @return true If the map is strongly connected.
 * @return false Otherwise.
 */
bool Map::isMapStronglyConnected()
{
    return std::all_of(territories.begin(), territories.end(), [this](
            Territory* t)
    {
        auto val = isTerritoryStronglyConnected(t);
        return val;
    });
}

/**
 * @brief Checks if each territory is assigned to a continent.
 *
 * @return true If all territories are assigned.
 * @return false Otherwise.
 */
bool Map::isTerritories1to1Continents()
{
    return std::all_of(continents.begin(), continents.end(), [](Continent *c){return !c->getTerritories()->empty();});
}

/**
 * @brief Adds a continent to the map.
 *
 * @param continent Pointer to the continent to be added.
 */
void Map::addContinent(Continent *continent)
{
    this->continents.push_back(continent);
}

/**
 * @brief Adds a territory to the map.
 *
 * @param territory Pointer to the territory to be added.
 */
void Map::addTerritory(Territory *territory)
{
    this->territories.push_back(territory);
}

// --------------------------------------------------
// Getters
// --------------------------------------------------
/**
 * @brief Get the name of the Map.
 *
 * @return std::string The name of the Map.
 */
std::string Map::getName()
{
    return this->name;
}

/**
 * @brief Get the image associated with the Map.
 *
 * @return std::string The image of the Map.
 */
std::string Map::getImage()
{
    return this->image;
}

/**
 * @brief Get the author of the Map.
 *
 * @return std::string The author of the Map.
 */
std::string Map::getAuthor()
{
    return this->author;
}

/**
 * @brief Get the wrap setting of the Map.
 *
 * @return bool The wrap setting of the Map.
 */
bool Map::getWrap() const
{
    return this->wrap;
}

/**
 * @brief Get the scroll setting of the Map.
 *
 * @return bool The scroll setting of the Map.
 */
bool Map::getScroll() const
{
    return this->scroll;
}

/**
 * @brief Get the warn setting of the Map.
 *
 * @return bool The warn setting of the Map.
 */
bool Map::getWarn() const
{
    return this->warn;
}

/**
 * @brief Get the territories of the Map.
 *
 * @return std::vector<Territory*>* Pointer to the vector of territories.
 */
std::vector<Territory*>* Map::getTerritories()
{
    return &this->territories;
}

/**
 * @brief Get the continents of the Map.
 *
 * @return std::vector<Continent*>* Pointer to the vector of continents.
 */
std::vector<Continent*>* Map::getContinents()
{
    return &this->continents;
}

// --------------------------------------------------
// Setters
// --------------------------------------------------

/**
 * @brief Set the name of the Map.
 *
 * @param _name New name for the Map.
 */
void Map::setName(std::string _name)
{
    this->name = std::move(_name);
}

/**
 * @brief Set the image for the Map.
 *
 * @param _image New image for the Map.
 */
void Map::setImage(std::string _image)
{
    this->image = std::move(_image);
}

/**
 * @brief Set the author of the Map.
 *
 * @param _author New author for the Map.
 */
void Map::setAuthor(std::string _author)
{
    this->author = std::move(_author);
}

/**
 * @brief Set the wrap setting of the Map.
 *
 * @param _wrap New wrap setting.
 */
void Map::setWrap(bool _wrap)
{
    this->wrap = _wrap;
}

/**
 * @brief Set the scroll setting of the Map.
 *
 * @param _scroll New scroll setting.
 */
void Map::setScroll(bool _scroll)
{
    this->scroll = _scroll;
}

/**
 * @brief Set the warn setting of the Map.
 *
 * @param _warn New warn setting.
 */
void Map::setWarn(bool _warn)
{
    this->warn = _warn;
}

// --------------------------------------------------
// Destructors + Constructors + Operator Overloads
// --------------------------------------------------


/**
 * Destructor for the Map class.
 * Responsible for releasing memory for territories and continents.
 */
Map::~Map() {
  for(auto t : territories){
    delete t;
  }

  for(auto c : continents){
    delete c;
  }
}


/**
 * Overloaded insertion operator for the Map class.
 * @param stream The output stream.
 * @param other The Map object to be displayed.
 * @return Modified output stream.
 */
std::ostream &operator<<(std::ostream &stream, const Map &other) {
  stream << "Map Name: " << other.name << '\n'
  << "Map Author: " << other.author << '\n'
  << "Map Image: " << other.image << '\n'
  << "Map Wrap: " << (other.wrap ? "True":"False") << '\n'
  << "Map Scroll: " << (other.scroll ? "Horizontal":"Vertical") << '\n'
  << "Map Warn: " << (other.warn ? "True":"False") << '\n';

  stream << "Map Continents: " << '\n';
  for(auto c : other.continents){
    stream << *c << '\n';
  }

  stream << "Map Territories: " << '\n';
  for(auto t : other.territories){
    stream << *t << '\n';
  }

  return stream;
}

/**
 * Copy constructor for the Map class.
 * Performs a deep copy.
 * @param other The Map object to be copied.
 */
Map::Map(const Map &other)
: name(other.name), author(other.author), warn(other.warn), scroll(other.scroll), image(other.image), wrap(other.wrap), game(other.game)
{
  // deep copy
  for(auto t : territories){
    this->addTerritory(new Territory(*t));
  }
  // deep copy
  for(auto c : continents){
    this->addContinent(new Continent(*c));
  }

}

/**
 * Overloaded assignment operator for the Map class.
 * @param other The Map object on the right of the assignment.
 * @return A reference to the current Map after assignment.
 */
Map &Map::operator=(const Map &other) {
  if(this == &other){
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
 * Constructor for the Map class.
 * Initializes a Map with a GameEngine.
 * @param game Pointer to the GameEngine.
 * @throws std::runtime_error If the GameEngine pointer is null.
 */
Map::Map(GameEngine* game)
  :game(game)
{
  if(game == nullptr){throw std::runtime_error("Map::Error | Cannot set map Game Engine to null");}
}

/**
 * Constructor for the Territory class.
 * Initializes a Territory with a name.
 * @param name The name of the territory.
 */
Territory::Territory(std::string name)
    : name(std::move(name)), continent(nullptr), player(nullptr)
{}

/**
 * Adds an adjacent territory.
 * @param territory Pointer to the Territory to be added as adjacent.
 */
void Territory::addAdjacentTerritory(Territory* territory)
{
  this->adjacentTerritories.push_back(territory);
}

/**
 * @brief Get the name of the Territory.
 *
 * @return std::string - Name of the Territory.
 */
std::string Territory::getName()
{
    return this->name;
}

/**
 * @brief Get the adjacent territories to the current Territory.
 *
 * @return std::vector<Territory *>* - Pointer to a vector containing adjacent territories.
 */
std::vector<Territory *>* Territory::getAdjacentTerritories()
{
    return &this->adjacentTerritories;
}

/**
 * @brief Get the X-coordinate of the Territory.
 *
 * @return int - X-coordinate of the Territory.
 */
int Territory::getX() const
{
    return this->x;
}

/**
 * @brief Get the Y-coordinate of the Territory.
 *
 * @return int - Y-coordinate of the Territory.
 */
int Territory::getY() const
{
    return this->y;
}

/**
 * @brief Set the X-coordinate of the Territory.
 *
 * @param _x X-coordinate value.
 */
void Territory::setX(int _x)
{
    this->x = _x;
}

/**
 * @brief Set the Y-coordinate of the Territory.
 *
 * @param _y Y-coordinate value.
 */
void Territory::setY(int _y)
{
    this->y = _y;
}

/**
 * @brief Get the Continent to which the Territory belongs.
 *
 * @return Continent* - Pointer to the Continent object.
 */
Continent* Territory::getContinent()
{
    return this->continent;
}

/**
 * @brief Assign the Territory to a Continent.
 *
 * @param c Pointer to the Continent object.
 */
void Territory::setContinent(Continent* c)
{
    this->continent = c;
}

/**
 * @brief Default copy constructor for the Territory class.
 *
 * @param other The Territory object to be copied from.
 */
Territory::Territory(const Territory &other)= default;

/**
 * @brief Overloaded assignment operator for deep copying of the Territory class.
 *
 * Checks for self-assignment, and if not, copies all attributes from the provided Territory to the current instance.
 *
 * @param other The Territory object to be assigned from.
 * @return Territory& - Reference to the current instance post-assignment.
 */
Territory& Territory::operator=(const Territory &other) {
  if(this == &other){
    return *this;
  }

  this->name = other.name;
  this->continent = other.continent;
  this->player = other.player;

  this->armies = other.armies;
  this->ownerId = other.ownerId;

  this->x = other.x;
  this->y = other.y;

  this->adjacentTerritories = other.adjacentTerritories;
  return *this;
}

/**
 * @brief Overloaded stream insertion operator for Territory.
 *
 * @param stream Output stream.
 * @param other Territory object.
 * @return std::ostream& - Reference to the modified stream.
 */
std::ostream &operator<<(std::ostream &stream, const Territory &other) {
  stream << "Territory Name: " << other.name << '\n'
         << "Territory Coordinates: " << '(' << other.x << ", " << other.y << ')' << '\n'
         << "Territory Continent: " << other.continent << '\n';
  return stream ;
}

/**
 * @brief Set the ID of the owner of the Territory.
 *
 * @param id Owner's ID.
 */
void Territory::setOwnerId(int id) {
  this->ownerId = id;
}

/**
 * @brief Get the owner's ID for the Territory.
 *
 * @return int - Owner's ID.
 */
int Territory::getOwnerId() const {
  return this->ownerId;
}

/**
 * @brief Get the number of armies in the Territory.
 *
 * @return int - Number of armies.
 */
int Territory::getArmies() const {
  return this->armies;
}

/**
 * @brief Set the number of armies in the Territory.
 *
 * @param army_units Number of armies.
 */
void Territory::setArmies(int army_units) {
  this->armies = army_units;
}

/**
 * @brief Removes a specified number of army units from the territory.
 *
 * @param removed The number of army units to remove.
 * @return int The total number of army units after removal.
 * @exception std::runtime_error If trying to remove a negative number of units or more units than present.
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
 * @return int The total number of army units after addition.
 * @exception std::runtime_error If trying to add a negative number of units.
 */
int Territory::addArmyUnits(int added) {
  if(added < 0){ throw std::runtime_error("Cannot add a negative amount of army units."); }
  int total = this->armies + added;
  this->armies = total;
  return total;
}

/**
 * @brief Get the player who owns the territory.
 *
 * @return Player* Pointer to the owning player.
 */
Player *Territory::getPlayer() {
  return this->player;
}

/**
 * @brief Assign a player as the owner of the territory.
 *
 * @param p Pointer to the player object.
 */
void Territory::setPlayer(Player* p) {
  this->player = p;
}

/**
 * @brief Continent constructor initializing the continent with a name and bonus.
 *
 * @param name Name of the continent.
 * @param bonus Army bonus provided by the continent.
 */
Continent::Continent(std::string name, int bonus)
{
  this->name = std::move(name);
  this->bonus = bonus;
}


/**
 * @brief Add a territory to the continent's list of territories.
 *
 * @param territory Pointer to the territory to add.
 */
void Continent::addTerritory(Territory* territory)
{
  this->territories.push_back(territory);
}

/**
 * @brief Get the name of the continent.
 *
 * @return std::string The name of the continent.
 */
std::string Continent::getName()
{
  return this->name;
}

/**
 * @brief Get the army bonus provided by the continent.
 *
 * @return int Army bonus value.
 */
int Continent::getBonus() const
{
  return this->bonus;
}

/**
 * @brief Get a list of territories belonging to the continent.
 *
 * @return std::vector<Territory*>* Pointer to the list of territories.
 */
std::vector<Territory*>* Continent::getTerritories()
{
  return &this->territories;
}

/**
 * @brief Overloaded stream insertion operator for displaying continent details.
 *
 * @param stream The output stream.
 * @param other The continent object to display.
 * @return std::ostream& Reference to the modified output stream.
 */
std::ostream &operator<<(std::ostream &stream, const Continent &other) {
  stream << "Continent Name: " << other.name << '\n'
         << "Continent Bonus: " << other.bonus << '\n';

  stream << "Continent Territories: " << '\n';
  for(auto t: other.territories){
    stream << (*t) << '\n';
  }
  return stream;
}

/**
 * @brief Overloaded assignment operator for deep copying of the Continent class.
 *
 * @param other The Continent object to be assigned from.
 * @return Continent& - Reference to the current instance post-assignment.
 */
Continent &Continent::operator=(const Continent &other) {
  if(&other == this){
    return *this;
  }
  this->name = other.name;
  this->bonus = other.bonus;
  this->territories = other.territories;

  return *this;
}

/**
 * @brief Default copy constructor for the Continent class.
 *
 * @param other The Continent object to be copied from.
 */
Continent::Continent(const Continent &other) = default;

/**
 * @brief Loads a map from a file into a Map object.
 *
 * @param path Path to the map file.
 * @param out_map Pointer to the Map object to populate with data.
 * @exception std::runtime_error If the map file cannot be opened or there are issues during reading.
 */
void MapLoader::load(const std::string& path, Map* out_map)
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
    if(line.empty()) { continue; }

    parseLine(line, out_map, state);
  }

  state.parseState = ReadingState_Idle;
  input_file.close();
}

/**
 * @brief Parse a line from the map file and update the map data accordingly.
 *
 * @param line The line from the map file.
 * @param map Pointer to the Map object to update.
 * @param mapLoaderState Current state of the map loader.
 * @exception std::runtime_error If there are formatting or parsing issues in the map file.
 */
void MapLoader::parseLine(std::string &line, Map* map, MapLoaderState& mapLoaderState)
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
          Continent* continent;
          try {
            continent = new Continent(name, std::stoi(value));
          } catch (std::invalid_argument& e){
            throw std::runtime_error("Map Formatting Error: Invalid Continent Bonus.");
          } catch (std::out_of_range& e) {
            throw std::runtime_error("Map Formatting Error: Continent Bonus Coordinate Out Of Range.");
          }

          map->addContinent(continent);
          mapLoaderState.continents[name] = continent;
        }
      }
      break;
      // FORMAT: Territory name, x, y, continent, adjacent territories
    case ReadingState_Territories:

      // parse territories
      std::string delimiter = ",";
      // Territory
      Territory* territory = nullptr;

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
          try{
            territory->setX(std::stoi(value));
          } catch (std::invalid_argument& e){
            throw std::runtime_error("Map Formatting Error: Invalid X Coordinate.");
          } catch (std::out_of_range& e) {
            throw std::runtime_error("Map Formatting Error: X Coordinate Out Of Range.");
          }
          continue;
        }
          // y
        else if (territory->getY() == -1)
        {
          try{
            territory->setY(std::stoi(value));
          } catch (std::invalid_argument& e){
            throw std::runtime_error("Map Formatting Error: Invalid Y Coordinate.");
          } catch (std::out_of_range& e) {
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
            Territory* adjacentTerritory;
            // check inside territories to create
            if(mapLoaderState.territoriesToCreate.find(value) != mapLoaderState.territoriesToCreate.end()){
              // use previously created
              adjacentTerritory = mapLoaderState.territoriesToCreate[value];
            } else {
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
      break;
  }
}

/**
 * @brief Utility function to trim leading whitespace from a string.
 *
 * @param s Input string.
 * @return std::string Trimmed string.
 */
std::string MapLoader::ltrim(const std::string &s)
{
  size_t start = s.find_first_not_of(" \n\r\t\f\v");
  return (start == std::string::npos) ? "" : s.substr(start);
}

/**
 * @brief Utility function to trim trailing whitespace from a string.
 *
 * @param s Input string.
 * @return std::string Trimmed string.
 */
std::string MapLoader::rtrim(const std::string &s)
{
  size_t end = s.find_last_not_of(" \n\r\t\f\v");
  return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

/**
 * @brief Utility function to trim both leading and trailing whitespace from a string.
 *
 * @param s Input string.
 * @return std::string Trimmed string.
 */
std::string MapLoader::trim(const std::string &s) {
  return rtrim(ltrim(s));
}