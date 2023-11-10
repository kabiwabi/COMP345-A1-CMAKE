#include "Map.h"

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Map
//
// ----------------------------------------------------------------------------------------------------------------

/**
 * @brief Validates the map by checking if it is strongly connected and territories are associated with continents.
 *
 * @return True if the map is valid, otherwise false.
 */
bool Map::validate()
{
  return isMapStronglyConnected() && isTerritories1to1Continents();
}

/**
 * @brief Performs depth-first search (DFS) on the given territory.
 *
 * @param territory The starting territory for DFS.
 * @param visited Reference to the vector of visited territories.
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
 * @brief Checks if a territory is strongly connected by performing DFS.
 *
 * @param territory The territory to check.
 * @return True if the territory is strongly connected, otherwise false.
 */
bool Map::isTerritoryStronglyConnected(Territory* territory)
{
  std::vector<Territory *> visited{};
  DFS(territory, visited);
  return visited.size() == territories.size();
}

/**
 * @brief Checks if the entire map is strongly connected by checking each territory.
 *
 * @return True if the map is strongly connected, otherwise false.
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
 * @brief Checks if each continent has at least one territory associated with it.
 *
 * @return True if each continent has at least one territory, otherwise false.
 */
bool Map::isTerritories1to1Continents()
{
  return std::all_of(continents.begin(), continents.end(), [](Continent *c){return !c->getTerritories()->empty();});
}

/**
 * @brief Adds a continent to the map.
 *
 * @param continent The continent to add.
 */
void Map::addContinent(Continent *continent)
{
  this->continents.push_back(continent);
}

/**
 * @brief Adds a territory to the map.
 *
 * @param territory The territory to add.
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
 * @return The image file name.
 */
std::string Map::getImage()
{
    return this->image;
}

/**
 * @brief Gets the author of the map.
 *
 * @return The name of the map's author.
 */
std::string Map::getAuthor()
{
    return this->author;
}

/**
 * @brief Gets the wrap setting of the map.
 *
 * @return True if wrap is enabled, otherwise false.
 */
bool Map::getWrap() const
{
    return this->wrap;
}

/**
 * @brief Gets the scroll setting of the map.
 *
 * @return True if scroll is horizontal, otherwise false.
 */
bool Map::getScroll() const
{
    return this->scroll;
}

/**
 * @brief Gets the warn setting of the map.
 *
 * @return True if warning is enabled, otherwise false.
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
std::vector<Territory*>* Map::getTerritories()
{
    return &this->territories;
}

/**
 * @brief Gets a pointer to the vector of continents in the map.
 *
 * @return Pointer to the vector of continents.
 */
std::vector<Continent*>* Map::getContinents()
{
    return &this->continents;
}

// --------------------------------------------------
// setters
// --------------------------------------------------

/**
 * @brief Sets the name of the map.
 *
 * @param _name The new name of the map.
 */
void Map::setName(std::string _name)
{
    this->name = std::move(_name);
}

/**
 * @brief Sets the image file name associated with the map.
 *
 * @param _image The new image file name.
 */
void Map::setImage(std::string _image)
{
    this->image = std::move(_image);
}

/**
 * @brief Sets the author of the map.
 *
 * @param _author The new author of the map.
 */
void Map::setAuthor(std::string _author)
{
    this->author = std::move(_author);
}

/**
 * @brief Sets the wrap setting of the map.
 *
 * @param _wrap The new wrap setting.
 */
void Map::setWrap(bool _wrap)
{
    this->wrap = _wrap;
}

/**
 * @brief Sets the scroll setting of the map.
 *
 * @param _scroll The new scroll setting.
 */
void Map::setScroll(bool _scroll)
{
    this->scroll = _scroll;
}

/**
 * @brief Sets the warn setting of the map.
 *
 * @param _warn The new warn setting.
 */
void Map::setWarn(bool _warn)
{
    this->warn = _warn;
}

/**
 * @brief Destructor for the Map class.
 * Deletes all territories and continents associated with the map.
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
 * @brief Stream insertion operator for the Map class.
 *
 * @param stream The output stream.
 * @param other The Map object.
 * @return The output stream.
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
 * @brief Copy constructor for the Map class.
 *
 * @param other The Map object to copy.
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
 * @brief Copy assignment operator for the Map class.
 *
 * @param other The Map object to copy.
 * @return Reference to the assigned Map object.
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
 * @brief Constructor for the Map class with a GameEngine pointer.
 *
 * @param game Pointer to the GameEngine associated with the map.
 * @throw std::runtime_error if the game pointer is null.
 */
Map::Map(GameEngine* game)
  :game(game)
{
  if(game == nullptr){throw std::runtime_error("Map::Error | Cannot set map Game Engine to null");}
}

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
 * @param territory The adjacent territory to add.
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
 * @brief Gets the X-coordinate of the territory.
 *
 * @return The X-coordinate of the territory.
 */
int Territory::getX() const
{
  return this->x;
}

/**
 * @brief Gets the Y-coordinate of the territory.
 *
 * @return The Y-coordinate of the territory.
 */
int Territory::getY() const
{
  return this->y;
}

/**
 * @brief Sets the X-coordinate of the territory.
 *
 * @param _x The new X-coordinate.
 */
void Territory::setX(int _x)
{
  this->x = _x;
}

/**
 * @brief Sets the Y-coordinate of the territory.
 *
 * @param _y The new Y-coordinate.
 */
void Territory::setY(int _y)
{
  this->y = _y;
}

/**
 * @brief Gets the continent associated with the territory.
 *
 * @return Pointer to the continent associated with the territory.
 */
Continent* Territory::getContinent()
{
  return this->continent;
}

/**
 * @brief Sets the continent associated with the territory.
 *
 * @param c Pointer to the new continent.
 */
void Territory::setContinent(Continent* c)
{
  this->continent = c;
}

/**
 * @brief Default copy constructor for the Territory class.
 */
Territory::Territory(const Territory &other)= default;

/**
 * @brief Copy assignment operator for the Territory class.
 *
 * @param other The Territory object to copy.
 * @return Reference to the assigned Territory object.
 */
Territory& Territory::operator=(const Territory &other) {
  if(this == &other){
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
 * @param army_units The new number of armies.
 */
void Territory::setArmies(int army_units) {
  this->armies = army_units;
}

/**
 * @brief Removes a specified number of army units from the territory.
 *
 * @param removed The number of armies to remove.
 * @return The remaining number of armies in the territory.
 * @throw std::runtime_error if the specified number of armies is negative or exceeds the current number of armies.
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
 * @param added The number of armies to add.
 * @return The total number of armies in the territory after addition.
 * @throw std::runtime_error if the specified number of armies is negative.
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
 * @param p Pointer to the new owner player.
 */
void Territory::setPlayer(Player* p) {
  this->player = p;
}

/**
 * @brief Constructor for the Continent class.
 *
 * @param name The name of the continent.
 * @param bonus The bonus value associated with the continent.
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
void Continent::addTerritory(Territory* territory)
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
 * @brief Gets the bonus value associated with the continent.
 *
 * @return The bonus value.
 */
int Continent::getBonus() const
{
  return this->bonus;
}

/**
 * @brief Gets a pointer to the vector of territories in the continent.
 *
 * @return Pointer to the vector of territories.
 */
std::vector<Territory*>* Continent::getTerritories()
{
  return &this->territories;
}

/**
 * @brief Stream insertion operator for the Continent class.
 *
 * @param stream The output stream.
 * @param other The Continent object.
 * @return The output stream.
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
 * @brief Copy assignment operator for the Continent class.
 *
 * @param other The Continent object to copy.
 * @return Reference to the assigned Continent object.
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
 */
Continent::Continent(const Continent &other) = default;

/**
 * @brief Loads a map from a file.
 *
 * @param path The file path of the map file.
 * @param out_map Pointer to the Map object to store the loaded map.
 * @throw std::runtime_error if the file cannot be opened.
 */
void MapLoader::load(const std::string& path, Map* out_map)
{
  std::ifstream input_file(path, std::ios::in);
  std::string line;

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
 * @brief Parses a line from the map file and updates the map accordingly.
 *
 * @param line The line to parse.
 * @param map Pointer to the Map object.
 * @param mapLoaderState Reference to the MapLoaderState object.
 * @throw std::runtime_error if the map file is invalid or if there are formatting errors.
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
    case ReadingState_Territories:

      std::string delimiter = ",";
      Territory* territory = nullptr;

      if (line.find(delimiter) != std::string::npos)
      {
        std::string name = line.substr(0, line.find(delimiter));
        line = line.substr(line.find(delimiter) + 1, line.length());

        if (mapLoaderState.territoriesToCreate.find(name) != mapLoaderState.territoriesToCreate.end())
        {
          territory = mapLoaderState.territoriesToCreate[name];
          mapLoaderState.territoriesToCreate.erase(name);
        }
        else
        {
          territory = new Territory(name);
        }
      }

      while (!line.empty())
      {
        auto delimiter_location = line.find(delimiter);
        std::string value = line.substr(0, delimiter_location);
        line = delimiter_location == std::string::npos ? "" : line.substr(delimiter_location + 1, line.length());

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
        else if (territory->getContinent() == nullptr)
        {
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
        else
        {
          if (mapLoaderState.territories.find(value) != mapLoaderState.territories.end())
          {
            territory->addAdjacentTerritory(mapLoaderState.territories[value]);
          }
          else
          {
            Territory* adjacentTerritory;
            if(mapLoaderState.territoriesToCreate.find(value) != mapLoaderState.territoriesToCreate.end()){
              adjacentTerritory = mapLoaderState.territoriesToCreate[value];
            } else {
              adjacentTerritory = new Territory(value);
            }
            territory->addAdjacentTerritory(adjacentTerritory);
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
 * @brief Removes leading whitespaces from a string.
 *
 * @param s The input string.
 * @return The string with leading whitespaces removed.
 */
std::string MapLoader::ltrim(const std::string &s)
{
  size_t start = s.find_first_not_of(" \n\r\t\f\v");
  return (start == std::string::npos) ? "" : s.substr(start);
}

/**
 * @brief Removes trailing whitespaces from a string.
 *
 * @param s The input string.
 * @return The string with trailing whitespaces removed.
 */
std::string MapLoader::rtrim(const std::string &s)
{
  size_t end = s.find_last_not_of(" \n\r\t\f\v");
  return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

/**
 * @brief Removes leading and trailing whitespaces from a string.
 *
 * @param s The input string.
 * @return The string with leading and trailing whitespaces removed.
 */
std::string MapLoader::trim(const std::string &s) {
  return rtrim(ltrim(s));
}