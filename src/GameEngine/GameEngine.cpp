#include "GameEngine.h"

/**
 * @brief Sets the current state of the game and notifies observers.
 * @param engineState The new state to set the game to.
 */
void GameEngine::setCurrentState(GameEngineState engineState) {
  this->state = engineState;
  Subject::notify(this);
}

/**
 * @brief Gets the current state of the game.
 * @return The current state of the game.
 */
GameEngineState GameEngine::getCurrentState() {
  return this->state;
}

/**
 * @brief Constructor for GameEngine, initializes the game with the provided arguments.
 * @param state Initial state of the game engine.
 * @param argc Argument count from the command line.
 * @param argv Argument vector from the command line.
 */
GameEngine::GameEngine(GameEngineState state, int argc, char** argv) {
  this->state = state;
  this->deck = new Deck(this);
  this->map = new Map(this);
  this->logObserver = new LogObserver(this);
  this->commandProcessor = new CommandProcessor(this, argc, argv);
  this->adapter = new FileCommandProcessorAdapter(this, argc, argv);
  this->flr = new FileLineReader();
  Subject::attach((ILogObserver*)logObserver);
}

/**
 * @brief Conducts the startup phase of the game where initial setup is done.
 */
void GameEngine::startupPhase() {
    Command* command;
    std::string strCommand;
    std::string effect;

    if(!commandProcessor){ throw std::runtime_error("GameEngine::startupPhase::ASSERT commandProcessor is null"); }
    cout << "Welcome to the startup phase of the game!\n"<< endl;
    printCommands();
    do{
        command = commandProcessor->getCommand();
        strCommand = command->getCommand();
        effect = command->getEffect();

        if(effect == "Game successfully restarted") {
          resetGame();
          startupPhase();
        }

        else if(!isValid(effect) && strCommand != "quit"){
            cout << "The command or its argument is invalid" << endl;
            continue;
        }
    } while(strCommand != "quit" );
}

/**
 * @brief Validates if the maximum number of players has been reached.
 */
void GameEngine::validateMaxPlayers() {
  if(players.size() == 6){
    throw std::runtime_error("Maximum number of players(6) reached! Game is ready to be started.");
  }
}

/**
 * @brief Validates if the minimum number of players required to start the game is present.
 */
void GameEngine::validateMinPlayers() {
  if(players.size() < 2){
    throw std::runtime_error("Please add at least one more player! Minimum number of players required is two(2).");
  }
}


/**
 * @brief Distributes territories among players at the start of the game.
 */
void GameEngine::distributeTerritories(){
  if(!map){ throw std::runtime_error("GameEngine::distributeTerritories::ASSERT Map is null"); }
  std::vector<Territory*>* territories = map->getTerritories();
  int numPlayers = (int)players.size();
  int territoriesDistr[numPlayers];
  int terrPerPlayer = floor(territories->size() / numPlayers);
  int remainingTerr = (int)territories->size() - (numPlayers * terrPerPlayer);
  int currPlayer = 0;
  int tempTerr = 0;
  Player* player = players.at(currPlayer);

  for(int i = 0; i < numPlayers; i++){
      territoriesDistr[i] = terrPerPlayer;
      if(remainingTerr > 0){
              territoriesDistr[i] +=1;
              remainingTerr--;
      }
  }

  for(Territory *terr : *territories){
      Territory* t = terr;
      if(tempTerr == (territoriesDistr[currPlayer])){
          currPlayer++;
          player = players.at(currPlayer);
          tempTerr = 0;
      }
      player->addTerritory(*t);
      tempTerr++;
  }
}

/**
 * @brief Randomizes the order of players.
 */
void GameEngine::playerOrder(){
  auto rng = std::default_random_engine {};
  std::shuffle(std::begin(players), std::end(players), rng);
}

/**
 * @brief Checks if a given command string is valid.
 * @param strCommand The command string to validate.
 * @return True if valid, false otherwise.
 */
bool GameEngine::isValid(const std::string& strCommand){return strCommand.find("Invalid") == string::npos;}

/**
 * @brief Prints the available commands to the console.
 */
void GameEngine::printCommands() {
    cout<< "Here are the commands available to you: "<<endl;
    for (const string& cmd: commands) {
        cout << cmd << " ";
    }
    cout << "\n" << endl;
}

/**
 * @brief Returns the current state of the game as a string.
 * @return A string representing the current game state.
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
 * @brief Gets the players participating in the game.
 * @return A pointer to the vector of players.
 */
std::vector<Player *> *GameEngine::getPlayers() {
  return &this->players;
}

/**
 * @brief Gets the current player's turn.
 * @return A pointer to the current player.
 */
Player* GameEngine::getCurrentPlayerTurn() {
  return currentPlayerTurn;
}

/**
 * @brief Retrieves the deck associated with the game engine.
 * @return A pointer to the Deck object.
 */
Deck* GameEngine::getDeck() {
  return this->deck;
}

/**
 * @brief Retrieves the map associated with the game engine.
 * @return A pointer to the Map object.
 */
Map* GameEngine::getMap() {
  return this->map;
}

/**
 * @brief Retrieves the log observer associated with the game engine.
 * @return A pointer to the LogObserver object.
 */
LogObserver* GameEngine::getLogObserver() {
    return this->logObserver;
}

/**
 * @brief Retrieves the command processor associated with the game engine.
 * @return A pointer to the CommandProcessor object.
 */
CommandProcessor* GameEngine::getCommandProcessor() {
    return this->commandProcessor;
}

/**
 * @brief Adds a new player to the game engine.
 * @param player A pointer to the Player object to add.
 * @throw std::runtime_error If the player pointer is nullptr or if the game state does not allow adding a new player.
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
 * @brief Destructor for the GameEngine, responsible for cleaning up resources.
 */
GameEngine::~GameEngine() {
  for(auto player : players){
    delete player;
  }

  delete deck;
  delete map;
  delete adapter;
  delete flr;
  delete logObserver;
  delete commandProcessor;
}

/**
 * @brief Overloaded constructor for GameEngine, used for setting up the game environment.
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 */
GameEngine::GameEngine(int argc, char** argv) {
  this->logObserver = new LogObserver(this);
  this->map = new Map(this);
  this->deck = new Deck(this);
  this->adapter = new FileCommandProcessorAdapter(this, argc, argv);
  this->flr = new FileLineReader();
  this->commandProcessor = new CommandProcessor(this, argc, argv);
  this->argc = argc;
  this->argv = argv;
  Subject::attach((ILogObserver*)logObserver);
}

/**
 * @brief Loads a map from a given file path.
 * @param path Path to the map file.
 */
void GameEngine::loadMap(const std::string& path) {
  MapLoader::load(path, this->map);
}

/**
 * @brief Validates the loaded map.
 * @return True if the map is valid, otherwise false.
 * @throw runtime_error if the map pointer is null.
 */
bool GameEngine::validateMap() {
  if(map == nullptr){ throw runtime_error("ASSERT: Map is null."); }
  return map->validate();
}


/**
 * @brief Converts the current state of the game engine into a string for logging.
 * @return A string representing the current state for logging purposes.
 */
std::string GameEngine::stringToLog() {
  std::stringstream ss;
  ss << "GAME ENGINE: ";
  ss << "State transition to ";
  ss << getCurrentStateToString();
  return ss.str();
}

/**
 * @brief The reinforcement phase of the game where players receive and place their reinforcements.
 */
void GameEngine::reinforcementPhase()
{
  for (auto& player : players)
  {
    currentPlayerTurn = player;
    player->setPhase("Reinforcement");
    cout << "Player: " << player->getName() << "'s current Reinforcement Pool: "<< player->getReinforcementPool() << endl;
    int reinforcementsToAdd = 0;

    reinforcementsToAdd += player->getContinentBonus();
    if(reinforcementsToAdd > 0){cout << "Player: " << player->getName() << "'s continent bonus is: "<< player->getReinforcementPool() << endl;}

    reinforcementsToAdd += (int)(player->getTerritories()->size() / 3) * 3;

    if(reinforcementsToAdd < 3){ reinforcementsToAdd = 3;}

    player->addReinforcement(reinforcementsToAdd);

    cout << "Player: " << player->getName() << "'s updated Reinforcement Pool: "<< player->getReinforcementPool() << endl;
  }
}


/**
 * @brief The phase where players issue their orders.
 */
void GameEngine::issueOrdersPhase() {
  int phaseTurn = 0;
  vector<bool> completed(players.size());
  for(auto& player : players){ player->setPhase("Issue Orders"); }

  while(!std::all_of(completed.begin(), completed.end(), [](bool v) { return v; })){
    if(completed[phaseTurn]){ nextTurn(phaseTurn); continue; }
    currentPlayerTurn = players[phaseTurn];

    cout << "Player: " << currentPlayerTurn->getName() << "'s turn to issue an order!" << endl;

    if(currentPlayerTurn->getDeployedArmiesThisTurn() >= currentPlayerTurn->getReinforcementPool()){
      cout << "Player: " << currentPlayerTurn->getName() << " has no more orders to issue." << endl;
      completed[phaseTurn] = true;
      continue;
    }

    currentPlayerTurn->issueOrder();

    nextTurn(phaseTurn);
  }

  for(auto& player : players){
    player->clearDeploymentArmies();
  }
}

/**
 * @brief The phase where the players' orders are executed.
 */
void GameEngine::executeOrdersPhase() {
  int phaseTurn = 0;
  vector<bool> completed(players.size());
  for(auto& player : players){ player->setPhase("Execute Orders Phase"); }

  while(!std::all_of(completed.begin(), completed.end(), [](bool v) { return v; })){
    if(completed[phaseTurn]){nextTurn(phaseTurn); continue; }
    currentPlayerTurn = players[phaseTurn];
    auto currentPlayerOrders = currentPlayerTurn->getOrdersListObject()->getList();

    if(currentPlayerOrders->empty()){
      cout << "Player: " << currentPlayerTurn->getName() << " has no more orders to execute." << endl;
      completed[phaseTurn] = true;
      continue;
    }

    auto topOrder = currentPlayerOrders->at(0);
    cout << "Player: " << currentPlayerTurn->getName() << "'s order: " + topOrder->getLabel() + " is being executed." << endl;
    topOrder->execute();
    currentPlayerOrders->erase(currentPlayerOrders->cbegin());

    delete topOrder;

    nextTurn(phaseTurn);
  }

  for(auto player : players){
    player->clearFriendly();
  }
}

/**
 * @brief The main game loop that continues until there is a winner.
 */
void GameEngine::mainGameLoop() {
  if(players.empty()){throw std::runtime_error("GameEngine::mainGameLoop::Assert Player size is 0.");}
  Player* winner;
  // check win state
  int round = 0;
  while((winner = checkWinState()) == nullptr){
    cout << "-----------------------------------------------------------------------" << endl;
    cout << "Round: " << round << "" << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    reinforcementPhase();
    issueOrdersPhase();
    executeOrdersPhase();
    removePlayersWithNoTerritories();
    round++;
  }
  cout << "Congratulations " << winner->getName() << "!" << endl;
  setCurrentState(GE_Win);
}

/**
 * @brief Checks if a player has won the game.
 * @return A pointer to the winning player if there is one, otherwise nullptr.
 * @throw runtime_error if the map pointer is null.
 */
Player* GameEngine::checkWinState() {
  if(map == nullptr){throw std::runtime_error("checkWinState::Assert Map is null.");}

  int totalAmountOfTerritories = (int) map->getTerritories()->size();

  for(auto& player: players){
    if(player->getTerritories()->size() == totalAmountOfTerritories){
      return player;
    }
  }
  return nullptr;
}

/**
 * @brief Advances the turn to the next player.
 * @param turn The current turn index, to be updated to the next player's index.
 */
void GameEngine::nextTurn(int &turn) {
  turn++;
  turn %= (int)players.size();
}

/**
 * @brief Sets the current player's turn.
 * @param player Pointer to the player whose turn is to be set.
 */
void GameEngine::setCurrentPlayer(Player* player) {
  currentPlayerTurn = player;
}

/**
 * @brief Removes players who have no territories left.
 */
void GameEngine::removePlayersWithNoTerritories() {
  auto playersToBeDeleted = vector<Player*>();

  for(auto& player : players){
    if(player->getTerritories()->empty()){
      playersToBeDeleted.push_back(player);
    }
  }

  players.erase(std::remove_if(players.begin(), players.end(), [&](Player* p) {
                  return p->getTerritories()->empty();
                }), players.end());


  for(auto& player : playersToBeDeleted){
    cout << player->getName() << " has been conquered!" << endl;
    delete player;
  }
}

/**
 * @brief Gets the FileLineReader object.
 * @return A pointer to the FileLineReader.
 */
FileLineReader* GameEngine::getFlir() {
  return flr;
}

/**
 * @brief Gets the FileCommandProcessorAdapter object.
 * @return A pointer to the FileCommandProcessorAdapter.
 */
FileCommandProcessorAdapter *GameEngine::getFileCommandProcessorAdapter() {
  return adapter;
}

/**
 * @brief Resets the game to its initial state.
 */
void GameEngine::resetGame() {

  for(auto player : players){
    delete player;
  }

  delete deck;
  delete map;
  delete adapter;
  delete flr;
  delete logObserver;
  delete commandProcessor;

  this->players = vector<Player*>();
  this->currentPlayerTurn = nullptr;

  this->logObserver = new LogObserver(this);
  this->map = new Map(this);
  this->deck = new Deck(this);
  this->adapter = new FileCommandProcessorAdapter(this, argc, argv);
  this->flr = new FileLineReader();
  this->commandProcessor = new CommandProcessor(this, argc, argv);
  this->resetObservers();

  Subject::attach((ILogObserver*)logObserver);

}
