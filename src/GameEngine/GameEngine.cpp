#include "GameEngine.h"
#include "Player/PlayerStrategies.h"
#include <random>
#include <iomanip>

/**
 * @brief Sets the current state of the game engine.
 * @param engineState The state to set.
 */
void GameEngine::setCurrentState(GameEngineState engineState)
{
  this->state = engineState;
  Subject::notify(this);
}

/**
 * @brief Gets the current state of the game engine.
 * @return The current state.
 */
GameEngineState GameEngine::getCurrentState()
{
  return this->state;
}

/**
 * @brief Constructor for the GameEngine class.
 * @param state Initial state of the game engine.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @param testing Boolean indicating whether the game is in testing mode.
 */
GameEngine::GameEngine(GameEngineState state, int argc, char **argv, bool testing)
{
  this->state = state;
  this->deck = new Deck(this);
  this->map = new Map(this);
  this->logObserver = new LogObserver(this);
  this->commandProcessor = new CommandProcessor(this, argc, argv);
  this->adapter = new FileCommandProcessorAdapter(this, argc, argv);
  this->flr = new FileLineReader();
  Subject::attach((ILogObserver *)logObserver);

  this->argc = argc;
  this->argv = argv;

  this->testing = testing;
}

/**
 * @brief Handles the startup phase of the game.
 * Prompts the user for commands and processes them until the "quit" command is entered.
 */
void GameEngine::startupPhase()
{
  Command *command;
  std::string strCommand;
  std::string effect;

  if (!commandProcessor)
  {
    throw std::runtime_error("GameEngine::startupPhase::ASSERT commandProcessor is null");
  }
  cout << "Welcome to the startup phase of the game!\n"
       << endl;
  printCommands();
  do
  {
    command = commandProcessor->getCommand();
    strCommand = command->getCommand();
    effect = command->getEffect();

    if (effect == "Game successfully restarted")
    {
      resetGame();
      startupPhase();
    }

    else if (effect == "Tournament started")
    {
      runTournament();
      strCommand = "quit";
    }

    else if (!isValid(effect) && strCommand != "quit")
    {
      cout << "The command or its argument is invalid" << endl;
      continue;
    }
  } while (strCommand != "quit");
}

/**
 * @brief Validates that the maximum number of players has not been exceeded.
 * Throws an exception if the condition is not met.
 */
void GameEngine::validateMaxPlayers()
{
  if (players.size() == 6)
  {
    throw std::runtime_error("Maximum number of players(6) reached! Game is ready to be started.");
  }
}

/**
 * @brief Validates that the minimum number of players has been reached.
 * Throws an exception if the condition is not met.
 */
void GameEngine::validateMinPlayers()
{
  if (players.size() < 2)
  {
    throw std::runtime_error("Please add at least one more player! Minimum number of players required is two(2).");
  }
}

/**
 * @brief Distributes territories among the players.
 * Territories are distributed based on the number of players and the total number of territories.
 */
void GameEngine::distributeTerritories()
{
  if (!map)
  {
    throw std::runtime_error("GameEngine::distributeTerritories::ASSERT Map is null");
  }
  std::vector<Territory *> *territories = map->getTerritories();
  int numPlayers = (int)players.size();
  int territoriesDistr[numPlayers];
  int terrPerPlayer = floor(territories->size() / numPlayers);
  int remainingTerr = (int)territories->size() - (numPlayers * terrPerPlayer);
  int currPlayer = 0;
  int tempTerr = 0;
  Player *player = players.at(currPlayer);

  for (int i = 0; i < numPlayers; i++)
  {
    territoriesDistr[i] = terrPerPlayer;
    if (remainingTerr > 0)
    {
      territoriesDistr[i] += 1;
      remainingTerr--;
    }
  }

  for (Territory *terr : *territories)
  {
    Territory *t = terr;
    if (tempTerr == (territoriesDistr[currPlayer]))
    {
      currPlayer++;
      player = players.at(currPlayer);
      tempTerr = 0;
    }
    player->addTerritory(*t);
    tempTerr++;
  }
}

/**
 * @brief Shuffles the order of players.
 */
void GameEngine::playerOrder()
{
  auto rng = std::default_random_engine{};
  std::shuffle(std::begin(players), std::end(players), rng);
}

/**
 * @brief Checks if a given command is valid based on its effect.
 * @param strCommand The effect of the command.
 * @return True if the command is valid, false otherwise.
 */
bool GameEngine::isValid(const std::string &strCommand) { return strCommand.find("Invalid") == string::npos; }

/**
 * @brief Prints the available commands to the console.
 */
void GameEngine::printCommands()
{
  cout << "Here are the commands available to you: " << endl;
  for (const string &cmd : commands)
  {
    cout << cmd << " ";
  }
  cout << "\n"
       << endl;
}

/**
 * @brief Converts the current game state to a string representation.
 * @return String representation of the current game state.
 * @throws std::runtime_error if the state is invalid.
 */
std::string GameEngine::getCurrentStateToString()
{
  switch (this->state)
  {
  case GE_Start:
    return "Start";
  case GE_Tournament:
    return "Tournament";
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
 * @brief Gets the vector of players.
 * @return A pointer to the vector of players.
 */
std::vector<Player *> *GameEngine::getPlayers()
{
  return &this->players;
}

/**
 * @brief Gets the player whose turn it currently is.
 * @return Pointer to the current player.
 */
Player *GameEngine::getCurrentPlayerTurn()
{
  return currentPlayerTurn;
}

/**
 * @brief Gets the deck associated with the game engine.
 * @return Pointer to the deck.
 */
Deck *GameEngine::getDeck()
{
  return this->deck;
}

/**
 * @brief Gets the map associated with the game engine.
 * @return Pointer to the map.
 */
Map *GameEngine::getMap()
{
  return this->map;
}

/**
 * @brief Gets the log observer associated with the game engine.
 * @return Pointer to the log observer.
 */
LogObserver *GameEngine::getLogObserver()
{
  return this->logObserver;
}

/**
 * @brief Gets the command processor associated with the game engine.
 * @return Pointer to the command processor.
 */
CommandProcessor *GameEngine::getCommandProcessor()
{
  return this->commandProcessor;
}

/**
 * @brief Adds a player to the game.
 * @param player Pointer to the player to be added.
 * @throws std::runtime_error if the player is null or the game is already in progress.
 */
void GameEngine::addPlayer(Player *player)
{
  if (player == nullptr)
  {
    throw std::runtime_error("GameEngine::Error | Cannot add player to game (nullptr)");
  }
  if (state > GE_Players_Added)
  {
    throw std::runtime_error("GameEngine::ASSERT | Cannot add player to game. Game is already in progress.");
  }
  this->players.push_back(player);
}

/**
 * @brief Destructor for the GameEngine class.
 * Frees memory allocated for players and other components.
 */
GameEngine::~GameEngine()
{
  for (auto player : players)
  {
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
 * @brief Constructor for the GameEngine class.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @param testing Boolean indicating whether the game is in testing mode.
 */
GameEngine::GameEngine(int argc, char **argv, bool testing)
{
  this->logObserver = new LogObserver(this);
  this->map = new Map(this);
  this->deck = new Deck(this);
  this->adapter = new FileCommandProcessorAdapter(this, argc, argv);
  this->flr = new FileLineReader();
  this->commandProcessor = new CommandProcessor(this, argc, argv);
  this->argc = argc;
  this->argv = argv;
  Subject::attach((ILogObserver *)logObserver);
  this->testing = testing;
}

/**
 * @brief Loads a map from a file.
 * @param path Path to the map file.
 */
void GameEngine::loadMap(const std::string &path)
{
  MapLoader::load(path, this->map);
}

/**
 * @brief Validates the loaded map.
 * @return True if the map is valid, false otherwise.
 * @throws std::runtime_error if the map is null.
 */
bool GameEngine::validateMap()
{
  if (map == nullptr)
  {
    throw runtime_error("ASSERT: Map is null.");
  }
  return map->validate();
}

/**
 * @brief Validates the parameters for the tournament mode.
 * Exits the program if any parameter is invalid.
 */
void GameEngine::validateTournament()
{
  if (allMaps.size() < 1 || allMaps.size() > 5)
  {
    std::cout << "GameEngine::validateTournament::Error | Number of maps must be between 1 to 5";
    exit(0);
  }
  if (allPlayerStrategies.size() < 2 || allPlayerStrategies.size() > 4)
  {
    std::cout << "GameEngine::validateTournament::Error | Number of player strategies must be between 2 to 4";
    exit(0);
  }
  if (numberOfGames < 1 || numberOfGames > 5)
  {
    std::cout << "GameEngine::validateTournament::Error | Number of games must be between 1 to 5";
    exit(0);
  }
  if (maxNumberOfTurns < 10 || maxNumberOfTurns > 50)
  {
    std::cout << "GameEngine::validateTournament::Error | Number of turns must be between 10 to 50";
    exit(0);
  }
  // validate strategy
  string strategies[5] = {"Aggressive", "Benevolent", "Neutral", "Cheater", "Human"};
  int invalidStrategyCounter = 0;

  for (int i = 0; i < allPlayerStrategies.size(); i++)
  {
    for (int j = 0; j < 5; j++)
    {
      if (allPlayerStrategies[i] == strategies[j])
      {
        break;
      }
      else if (allPlayerStrategies[i] != strategies[j] && j == 4)
      {
        cout << allPlayerStrategies[i] + " X NOT VALID" << endl;
        invalidStrategyCounter++;
      }
    }
  }
  if (invalidStrategyCounter > 0)
  {
    cout << invalidStrategyCounter;
    throw std::runtime_error("GameEngine::validateTournament::Error | Player strategies entered are not valid");
  }
}

/**
 * @brief Generates a string representation of the current game state for logging purposes.
 * @return String representation of the current game state.
 */
std::string GameEngine::stringToLog()
{
  std::stringstream ss;
  if (tournamentEnd)
    return getTournamentResults();
  ss << "GAME ENGINE: ";
  ss << "State transition to ";
  ss << getCurrentStateToString();
  return ss.str();
}

/**
 * @brief Executes the reinforcement phase of the game for each player.
 * Calculates and adds reinforcements for each player based on territories and continents owned.
 */
void GameEngine::reinforcementPhase()
{
  for (auto &player : players)
  {
    currentPlayerTurn = player;
    player->setPhase("Reinforcement");
    cout << "Player: " << player->getName() << "'s current Reinforcement Pool: " << player->getReinforcementPool() << endl;
    // Check for continents bonus before territories themselves.
    // Check if players owned number of territories matches a continent that holds n amount of territories to gain control bonus.
    int reinforcementsToAdd = 0;

    // Get continent bonus.
    reinforcementsToAdd += player->getContinentBonus();
    if (reinforcementsToAdd > 0)
    {
      cout << "Player: " << player->getName() << "'s continent bonus is: " << player->getReinforcementPool() << endl;
    }

    // Get territories reinforcement.
    reinforcementsToAdd += (int)(player->getTerritories()->size() / 3) * 3;

    // Check if they have the minimum reinforcements.
    if (reinforcementsToAdd < 3)
    {
      reinforcementsToAdd = 3;
    }

    player->addReinforcement(reinforcementsToAdd);

    cout << "Player: " << player->getName() << "'s updated Reinforcement Pool: " << player->getReinforcementPool() << endl;
  }
}

/**
 * @brief Executes the issue orders phase of the game for each player.
 * Players take turns issuing orders until all have issued their orders for the turn.
 */
void GameEngine::issueOrdersPhase()
{
  int phaseTurn = 0;
  vector<bool> completed(players.size());
  for (auto &player : players)
  {
    player->setPhase("Issue Orders");
  }

  while (!std::all_of(completed.begin(), completed.end(), [](bool v)
                      { return v; }))
  {
    if (completed[phaseTurn])
    {
      nextTurn(phaseTurn);
      continue;
    }
    currentPlayerTurn = players[phaseTurn];

    cout << "Player: " << currentPlayerTurn->getName() << "'s turn to issue an order!" << endl;

    auto human = dynamic_cast<Human *>(currentPlayerTurn->getStrategy());

    // When no more orders need to be issued.
    if (currentPlayerTurn->getDeployedArmiesThisTurn() >= currentPlayerTurn->getReinforcementPool() && human == nullptr)
    {
      completed[phaseTurn] = true;
      cout << "Player: " << currentPlayerTurn->getName() << " has no more orders to issue." << endl;
      continue;
    }

    if (human != nullptr && human->isTurnDone)
    {
      completed[phaseTurn] = true;
      cout << "Player: " << currentPlayerTurn->getName() << " has no more orders to issue." << endl;
      continue;
    }

    currentPlayerTurn->issueOrder();

    nextTurn(phaseTurn);
  }

  for (auto &player : players)
  {
    player->clearDeploymentArmies();
    // Clear the deployment troops for all human players.
    if (auto strategy = dynamic_cast<Human *>(player->getStrategy()))
    {
      strategy->reset();
    }
  }
}

/**
 * @brief Executes the execute orders phase of the game for each player.
 * Players take turns executing their orders until all orders have been executed for the turn.
 */
void GameEngine::executeOrdersPhase()
{
  int phaseTurn = 0;
  vector<bool> completed(players.size());
  for (auto &player : players)
  {
    player->setPhase("Execute Orders Phase");
  }

  while (!std::all_of(completed.begin(), completed.end(), [](bool v)
                      { return v; }))
  {
    if (completed[phaseTurn])
    {
      nextTurn(phaseTurn);
      continue;
    }
    currentPlayerTurn = players[phaseTurn];
    auto currentPlayerOrders = currentPlayerTurn->getOrdersListObject()->getList();

    // When no more orders need to be issued.
    if (currentPlayerOrders->empty())
    {
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

  // Reset player friendly.
  for (auto player : players)
  {
    player->clearFriendly();
  }
}

/**
 * @brief Main game loop that iterates through rounds until a win state is reached or a draw is declared.
 * @param maxRounds Maximum number of rounds before declaring a draw.
 */
void GameEngine::mainGameLoop(int maxRounds)
{
  if (players.empty())
  {
    throw std::runtime_error("GameEngine::mainGameLoop::Assert Player size is 0.");
  }
  Player *winner;
  // Check win state.
  int round = 0;
  isDraw = false;

  while ((winner = checkWinState()) == nullptr)
  {
    cout << "-----------------------------------------------------------------------" << endl;
    cout << "Round: " << round << "" << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    removePlayersWithNoTerritories();
    reinforcementPhase();
    issueOrdersPhase();
    executeOrdersPhase();
    round++;
    if (round > maxRounds)
    {
      cout << "This game is gonna take forever. Draw.." << endl;
      isDraw = true;
      break;
    }
  }

  if (!isDraw)
  {
    cout << "Congratulations " << winner->getName() << "!" << endl;
  }

  setCurrentState(GE_Win);
}

/**
 * @brief Checks if a win state has been reached by a player having all territories.
 * @return Pointer to the winning player or nullptr if no win state is reached.
 */
Player *GameEngine::checkWinState()
{
  if (map == nullptr)
  {
    throw std::runtime_error("checkWinState::Assert Map is null.");
  }

  int totalAmountOfTerritories = (int)map->getTerritories()->size();

  for (auto &player : players)
  {
    // Check if a player has all the territories.
    if (player->getTerritories()->size() == totalAmountOfTerritories)
    {
      return player;
    }
  }
  return nullptr;
}

/**
 * @brief Advances the turn to the next player's turn.
 * @param turn Reference to the current turn, which will be updated to the next turn.
 */
void GameEngine::nextTurn(int &turn)
{
  turn++;
  turn %= (int)players.size();
}

/**
 * @brief Sets the current player turn to the specified player.
 * @param player Pointer to the player whose turn it is to be set.
 */
void GameEngine::setCurrentPlayer(Player *player)
{
  currentPlayerTurn = player;
}

/**
 * @brief Removes players from the game who have no territories.
 */
void GameEngine::removePlayersWithNoTerritories()
{
  auto playersToBeDeleted = vector<Player *>();

  for (auto &player : players)
  {
    if (player->getTerritories()->empty())
    {
      playersToBeDeleted.push_back(player);
    }
  }

  // Remove from the game.
  players.erase(std::remove_if(players.begin(), players.end(), [&](Player *p)
                               { return p->getTerritories()->empty(); }),
                players.end());

  // Free memory.
  for (auto &player : playersToBeDeleted)
  {
    cout << player->getName() << " has been conquered!" << endl;
    delete player;
  }
}

/**
 * @brief Gets the FileLineReader object associated with the game engine.
 * @return Pointer to the FileLineReader object.
 */
FileLineReader *GameEngine::getFlir()
{
  return flr;
}

/**
 * @brief Gets the FileCommandProcessorAdapter object associated with the game engine.
 * @return Pointer to the FileCommandProcessorAdapter object.
 */
FileCommandProcessorAdapter *GameEngine::getFileCommandProcessorAdapter()
{
  return adapter;
}

/**
 * @brief Resets the game to its initial state.
 */
void GameEngine::resetGame()
{
  if (multipleTournaments)
  {
    allPlayerStrategies = {};
    numberOfGames = 0;
    maxNumberOfTurns = 0;
  }

  for (auto player : players)
  {
    delete player;
  }

  delete deck;
  delete map;
  delete adapter;
  delete flr;
  delete logObserver;

  this->players = vector<Player *>();
  this->currentPlayerTurn = nullptr;
  this->logObserver = new LogObserver(this);
  this->map = new Map(this);
  this->deck = new Deck(this);
  this->adapter = new FileCommandProcessorAdapter(this, argc, argv);
  this->flr = new FileLineReader();
  this->resetObservers();

  if (!multipleTournaments)
  {
    delete commandProcessor;
    this->commandProcessor = new CommandProcessor(this, argc, argv);
  }

  Subject::attach((ILogObserver *)logObserver);
}

/**
 * @brief Checks if the game is in testing mode.
 * @return True if the game is in testing mode, false otherwise.
 */
bool GameEngine::isTesting() const
{
  return testing;
}

/**
 * @brief Runs the tournament mode of the game, playing multiple games on multiple maps with different strategies.
 */
void GameEngine::runTournament()
{
  tournamentEnd = false;
  for (int i = 0; i < allMaps.size(); i++)
  {
    loadMap(allMaps[i]);
    std::vector<std::string> currMap{};
    currMap.push_back(allMaps.at(i));
    int localNumGames = numberOfGames;
    int localMaxTurns = maxNumberOfTurns;
    std::vector<std::string> localAllPlayerStrategies = allPlayerStrategies;
    if (validateMap())
    {
      for (int j = 0; j < localNumGames; j++)
      {
        generateRandomDeck();
        for (auto &allPlayerStrategie : localAllPlayerStrategies)
        {
          new Player(this, new Hand(), allPlayerStrategie, allPlayerStrategie);
        }
        assignCardsEvenly();
        distributeTerritories();
        mainGameLoop(localMaxTurns);
        currMap.push_back(isDraw ? "draw" : checkWinState()->getName());

        resetGame();
        state = GE_Tournament;
        loadMap(allMaps[i]);
      }
      resetGame();
    }
    else
    {
      std::cout << "" << std::endl;
      std::cout << "Map " + std::to_string(i + 1) + " is invalid" << std::endl;
      resetGame();
      state = GE_Tournament;
    }
    tournamentResults.push_back(currMap);
  }
  tournamentEnd = true;
  Subject::notify(this);
}

/**
 * @brief Generates a string representation of the tournament results.
 * @return String representation of the tournament results.
 */
std::string GameEngine::getTournamentResults()
{
  std::stringstream str;
  const char separator = ' ';
  const int mapNameWidth = 25;
  const int nameWidth = 15;
  str << "Tournament Mode: " << endl;
  str << "M: ";
  for (int i = 0; i < tournamentResults.size(); i++)
  {
    str << (tournamentResults.at(i))[0] << ((i != tournamentResults.size() - 1) ? ',' : ' ');
  }
  str << endl
      << "P: ";
  for (int i = 0; i < allPlayerStrategies.size(); i++)
  {
    str << (allPlayerStrategies.at(i)) << ((i != allPlayerStrategies.size() - 1) ? ',' : ' ');
  }
  str << endl
      << "G: " << numberOfGames << endl
      << "D: " << maxNumberOfTurns << endl;
  str << std::left << std::setw(mapNameWidth) << std::setfill(separator) << "Map Name";

  for (int s = 1; s <= numberOfGames; s++)
  {
    str << std::left << std::setw(nameWidth) << std::setfill(separator) << ("Game " + std::to_string(s));
  }
  str << endl;

  for (auto &tournamentResult : tournamentResults)
  {
    str << std::left << std::setw(mapNameWidth) << std::setfill(separator) << tournamentResult.at(0);

    for (int j = 1; j < tournamentResult.size(); j++)
    {
      str << std::left << std::setw(nameWidth) << std::setfill(separator) << tournamentResult.at(j);
    }
    str << endl;
  }
  return str.str();
}

/**
 * @brief Generates a random deck for the game with a specified deck size.
 * @param deckSize Size of the deck to be generated.
 */
void GameEngine::generateRandomDeck(int deckSize)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distribution(0, 4);

  CardType cardOptions[5] = {
      CT_Bomb,
      CT_Reinforcement,
      CT_Blockade,
      CT_Airlift,
      CT_Diplomacy};

  for (int i = 0; i < deckSize; i++)
  {
    int randomNum = distribution(gen);
    deck->addCardToDeck(new Card(cardOptions[randomNum], this));
  }
}

/**
 * @brief Assigns cards evenly to each player at the beginning of the game.
 */
void GameEngine::assignCardsEvenly()
{
  for (auto &player : players)
  {
    player->getHand()->addToHand(new Card(CardType::CT_Reinforcement, this));
    player->getHand()->addToHand(new Card(CardType::CT_Blockade, this));
    player->getHand()->addToHand(new Card(CardType::CT_Bomb, this));
    player->getHand()->addToHand(new Card(CardType::CT_Diplomacy, this));
    player->getHand()->addToHand(new Card(CardType::CT_Airlift, this));
  }
}
