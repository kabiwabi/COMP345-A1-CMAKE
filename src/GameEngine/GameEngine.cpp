#include <sstream>
#include "GameEngine.h"

/**
 * @brief Method to initiate the game's startup phase by allowing user input.
 */
void GameEngine::startupPhase() {
    std::string input;
    std::vector<std::string> maps = {"Africa", "Alberta", "Anatomy", "AlbertaInvalid"};
    int totalPlayers = 0;
    while (true) {
        std::cout << "Current Game State: " << getCurrentStateToString() << std::endl;
        std::cout << "Please enter an action: " ;

        std::getline(std::cin, input);

        std::istringstream iss(input);
        std::string command, varName;

        // Read the first word as the command
        iss >> command;

        switch (getCurrentState()) {
            // Game Start Phase
            case GE_Start:
                if (command == "loadmap" ) {
                    iss >> varName;
                    if (input.substr(0,6) == "loadmap")
                    std::string varName = input.substr(7);
                    // Map name is validated
                    if (std::find(maps.begin(), maps.end(), varName) != maps.end()) {
                        loadMap("map_resources/" + varName + ".map");
                        std::cout << "Loaded Map: " << varName << std::endl;
                        setCurrentState(GE_Map_Loaded);
                    }
                    // User prompted to enter a valid map name
                    else {
                        std::cout << "Invalid map name. Choose any of the following maps: \nAfrica\nAlberta\nAnatomy\nAlbertaInvalid\n";
                    }
                } else {
                    printInvalidCommand(input);
                }
                break;

            // Map loaded phase
            case GE_Map_Loaded:
                if (input == "validatemap") {
                    if (map->validate() == true){
                        std::cout << "Map is valid. "  << std::endl;
                        setCurrentState(GE_Map_Validated);}
                    else {
                        std::cout << "Map is invalid. Returning to previous game state." << std::endl;
                        map->resetMap();
                        varName="";
                        setCurrentState(GE_Start);
                    }
                } else {
                    printInvalidCommand(input);
                }
                break;

            case GE_Map_Validated:
                if (command == "gamestart" && totalPlayers > 1 ){
                    setCurrentState(GE_Players_Added);
                    continue;
                }
                if (command == "addplayer") {
                    iss >> varName;

                    if (varName.size() < 1) {
                        std::cout << "Player name must contain at least 1 character.\n";
                        continue;
                    }

                    if (totalPlayers < 7) {
                        addPlayer(new Player(this, new Hand(), varName));
                        totalPlayers++;

                        if (totalPlayers < 2) {
                            std::cout << "Player " << totalPlayers << ", " << varName << ", added. Minimum of 2 players are required to start the game.\n";
                        } else {
                            std::cout << "Player " << totalPlayers << ", " << varName << ", added.\n";
                        }
                    }  else {
                        std::cout << "Maximum of 6 players reached. Cannot add more players.\n";
                    }

                } else {
                    printInvalidCommand(input);
                }
                break;
            case GE_Players_Added:
                if (input == "gamestart") {
                    // a) Fairly distribute territories to players
                    int currentPlayerIndex = 0;
                    for (Territory* territory : *map->getTerritories()) {
                        Player* currentPlayer = players[currentPlayerIndex];
                        currentPlayer->addTerritory(*territory);
                        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
                    }

                    // b) Randomize play order
                    randomizePlayerOrder();
                    std::cout << "Player Order After Randomization:" << std::endl;
                    for (size_t i = 0; i < totalPlayers; ++i) {
                        std::cout << "Player " << i + 1 << ": " << players[i]->getName() << std::endl;
                    }

                    // c) Give 50 initial army units to each player in their reinforcement pool
                    for (size_t i = 0; i < totalPlayers; ++i) {
                        std::cout << "Player " << i + 1; // Update the output to display the correct player number
                        players[i]->addToReinforcementPool(50);
                        std::cout << " Reinforcement size: " << players[i]->getReinforcementPool() << std::endl;
                    }

                    // d) Let each player draw 2 initial cards from the deck
                    for (Player *player: players) {
                        for (int i = 0; i < 1; i++) {
                            deck->draw(*player->getHand());
                        }}

                    auto playerTwoHand = players[1]->getHand()->getHandCards();
                    for (auto handCard : *playerTwoHand) {
                        cout << "Player Cards for " << players[1]->getName() << "; " << *handCard;
                    }

                    // e) Switch the game to the play phase
                    setCurrentState(GE_Reinforcement);

                }else {
                        printInvalidCommand(input);
                    }

                }


        if (getCurrentState() == GE_Reinforcement) {
            std::cout << "Game setup completed. Moving to the Reinforcement play phase." << std::endl;
            break; // Exit the loop and start the game
        }
        std::cout << "------------------------------" << std::endl;
    }
}

/**
 * @brief Print an error message for an invalid command.
 *
 * @param command The incorrect command entered by the user.
 */
void GameEngine::printInvalidCommand(const std::string& command) {
    std::cout << "Incorrect Command: \"" << command << "\". Please input a correct command." << std::endl;
}

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

    // Adding 30 different cards to the deck during initialization
    for (int i = 0; i < 30; i++) {
        CardType cardType = static_cast<CardType>(i % 5);
        this->deck->addCardToDeck(new Card(cardType, this));
    }

    // Shuffle the deck after adding cards
    this->deck->shuffleDeck();
}

/**
 * @brief Loads a map file into the game.
 *
 * @param path Path to the map file to be loaded.
 */
void GameEngine::loadMap(const std::string& path) {
  MapLoader::load(path, this->map);
}

/**
 * @brief Randomizes the player order.
 */
void GameEngine::randomizePlayerOrder() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(players.begin(), players.end(), gen);
}
