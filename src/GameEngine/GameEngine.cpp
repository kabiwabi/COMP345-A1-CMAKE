#include "GameEngine.h"

/**
 * @brief Sets the current state of the GameEngine.
 *
 * @param engineState The state to set the GameEngine to.
 */
void GameEngine::setCurrentState(GameEngineState engineState) {
  this->state = engineState;
}

/**
 * @brief Retrieves the current state of the GameEngine.
 *
 * @return GameEngineState The current state of the GameEngine.
 */
GameEngineState GameEngine::getCurrentState() {
  return this->state;
}

/**
 * @brief Constructs a GameEngine object with an initial state.
 *
 * @param state The initial state of the GameEngine.
 */
GameEngine::GameEngine(GameEngineState state) {
  this->state = state;
  this->deck = new Deck(this);
  this->map = new Map(this);
}

/**
 * @brief Converts the current state of the GameEngine to its string representation.
 *
 * @return std::string The string representation of the GameEngine's state.
 * @exception std::runtime_error If the GameEngine's state is invalid.
 */
std::string GameEngine::getCurrentStateToString() {
  switch (this->state) {
    case GE_Start:
      return "Start";
    case GE_Map_Loaded:
      return "Map Loaded";
    case GE_Map_Validated:
      return "Map Validated";
    case GE_Players_Added:
      return "Players Added";
    case GE_Reinforcement:
      return "Assign Reinforcement";
    case GE_Issue_Orders:
      return "Issue Orders";
    case GE_Execute_Orders:
      return "Execute Orders";
    case GE_Win:
      return "Win";
  }

  throw std::runtime_error("Invalid State");
}


/**
 * @brief Progresses to the next player's turn.
 */
void GameEngine::nextPlayerTurn() {
  playerTurn++;
  playerTurn %= players.size();
}

/**
 * @brief Retrieves the list of players in the game.
 *
 * @return std::vector<Player *> * Pointer to the list of players.
 */
std::vector<Player *> *GameEngine::getPlayers() {
  return &this->players;
}

/**
 * @brief Gets the player whose turn it currently is.
 *
 * @return Player* Pointer to the current player.
 */
Player* GameEngine::getCurrentPlayerTurn() {
  return players.at(playerTurn);
}

/**
 * @brief Retrieves the game's deck.
 *
 * @return Deck* Pointer to the game's deck.
 */
Deck *GameEngine::getDeck() {
  return this->deck;
}

/**
 * @brief Retrieves the game's map.
 *
 * @return Map* Pointer to the game's map.
 */
Map* GameEngine::getMap() {
  return this->map;
}


/**
 * @brief Adds a new player to the game.
 *
 * @param player Pointer to the player to be added.
 * @exception std::runtime_error If the player is a nullptr or if trying to add a player after the game has started.
 */
void GameEngine::addPlayer(Player* player) {
  if(player == nullptr){
    throw std::runtime_error("GameEngine::Error | Cannot add player to game (nullptr)");
  }
  if(state > GE_Players_Added){
    throw std::runtime_error("GameEngine::ASSERT | Cannot add player to game. Game is already in progress.");
  }
  this->players.push_back(player);
}

/**
 * @brief Destructor for the GameEngine class.
 *
 * Deletes memory allocations for deck, map, and players.
 */
GameEngine::~GameEngine() {
  delete deck;
  delete map;

  for(auto player : players){
    delete player;
  }
}

/**
 * @brief Default constructor for the GameEngine class.
 */
GameEngine::GameEngine() {
  this->map = new Map(this);
  this->deck = new Deck(this);
}

/**
 * @brief Loads a map file into the game.
 *
 * @param path Path to the map file to be loaded.
 */
void GameEngine::loadMap(const std::string& path) {
  MapLoader::load(path, this->map);
}
