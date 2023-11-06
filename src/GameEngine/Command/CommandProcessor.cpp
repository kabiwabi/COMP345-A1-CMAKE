#include "CommandProcessor.h"
#include "../GameEngine.h"

using namespace std;

regex regexRuleLoadMap("loadmap .+.map$");
regex regexRulePlayerAdd("addplayer .+");

/**
 * @brief Construct a new Command Processor object
 *
 * @param game Pointer to the GameEngine object
 * @param argc Count of command-line arguments
 * @param argv Array of command-line argument strings
 */
CommandProcessor::CommandProcessor(GameEngine* game, int argc, char** argv) : game(game) {
    commandCollection = {};
    for(int i = 0; i < argc; i++){ rawCommands.emplace_back(argv[i]); }
    Subject::attach((ILogObserver*)game->getLogObserver());
}

/**
 * @brief Copy constructor for Command Processor
 *
 * @param c The CommandProcessor object to copy from
 */
CommandProcessor::CommandProcessor(const CommandProcessor &c) : Subject(c) {
    commandCollection = {};
    for(auto i : c.commandCollection){
        commandCollection.push_back(new Command(*i));
    }
    this->rawCommands = c.rawCommands;
    this->game = c.game;
    Subject::attach((ILogObserver*)game->getLogObserver());
}

/**
 * @brief Get a Command object after reading and validating user input
 *
 * @return Command* Pointer to the newly created Command object
 */
Command* CommandProcessor::getCommand(){
    string userInput = readCommand();
    Command* currentCommand = validate(userInput);
    saveCommand(currentCommand);
    return currentCommand;
}

/**
 * @brief Read a command from the user input
 *
 * @return string The user input string
 */
string CommandProcessor::readCommand(){
    string userInput;
    cout << "Please enter a command: ";
    getline(cin, userInput);
    std::cout << std::endl;
    return userInput;
}

/**
 * @brief Save the Command object in the command collection
 *
 * @param _currentCommand Pointer to the Command object to save
 */
void CommandProcessor::saveCommand(Command* _currentCommand){
    commandCollection.push_back(_currentCommand);
    Subject::notify(this);
}

/**
 * @brief Get the current state of the game
 *
 * @return int The current state as an integer
 */
int CommandProcessor::getCurrentState(){
    return game->getCurrentState();
}

/**
 * @brief Validate the user input and create a Command object if valid
 *
 * @param _userInput The user input string to validate
 * @return Command* Pointer to the newly created Command object
 */
Command* CommandProcessor::validate(const string& _userInput){

    auto currentCommandObj = new Command(_userInput, game);
    GameEngineState current_game_state = game->getCurrentState();
    std::string strCommand = currentCommandObj->getCommand();

    switch(current_game_state){
        case GE_Start:
            if (std::regex_match(_userInput, regexRuleLoadMap)){
              size_t pos = strCommand.find(' ');
              std::string mapName = "res/" + MapLoader::trim(strCommand.substr(pos));
              try {
                game->loadMap(mapName);
              }
              catch(std::runtime_error& err){
                cout<< err.what() << endl;
                break;
              }
              game->setCurrentState(GE_Map_Loaded);
              currentCommandObj->saveEffect("Map successfully loaded");
              cout << currentCommandObj->getEffect() << endl;
              return currentCommandObj;
            }
            break;

        case GE_Map_Loaded:
            if (_userInput == "validatemap"){

              try{
                game->validateMap();
              }
              catch(std::runtime_error& err){
                cout<< err.what() << endl;
                game->setCurrentState(GE_Start);
                break;
              }

              game->setCurrentState(GE_Map_Validated);
              currentCommandObj->saveEffect("Map successfully validated");
              cout << currentCommandObj->getEffect() << endl;
              return currentCommandObj;
            }
            else if (std::regex_match(_userInput, regexRuleLoadMap)){
                cout << "Map already loaded" << endl;
            }
            break;

        case GE_Map_Validated:
            if (std::regex_match(_userInput, regexRulePlayerAdd)){

                size_t pos = strCommand.find(' ');
                std::string playerName = strCommand.substr(pos);
                new Player(game, new Hand(), playerName);
                currentCommandObj->saveEffect("Player" + playerName + " has been added successfully");
                game->setCurrentState(GE_Players_Added);
                cout << currentCommandObj->getEffect() << endl;
                return currentCommandObj;
            }
            break;

        case GE_Players_Added:
            if (std::regex_match(_userInput, regexRulePlayerAdd)){

              try {
                game->validateMaxPlayers();
              }
              catch(std::runtime_error& err){
                cout << err.what() << endl;
                break;
              }

              size_t pos = strCommand.find(' ');
              std::string playerName = strCommand.substr(pos);
              new Player(game, new Hand(), playerName);
              currentCommandObj->saveEffect("Player" + playerName + " has been added successfully");
              cout << currentCommandObj->getEffect() << endl;
              return currentCommandObj;
            }
            else if(_userInput == "gamestart"){

              try {
                game->validateMinPlayers();
              }
              catch(std::runtime_error& err){
                cout << err.what() << endl;
                break;
              }

              game->distributeTerritories();
              cout<< "Territories distributed."<<endl;

              game->playerOrder();
              cout<< "Order of play of players determined."<<endl;

              game->getDeck()->create_deck();

              try{
                for(Player* player : *game->getPlayers()){
                  player->setReinforcementPool(50);
                  game->setCurrentPlayer(player);
                  Hand &hand = *player->getHand();
                  game->getDeck()->draw(hand);
                  game->getDeck()->draw(hand);
                }
              }
              catch(std::runtime_error& err){
                cout << err.what() <<endl;
                break;
              }

              game->setCurrentState(GE_Reinforcement);
              currentCommandObj->saveEffect("Game successfully started");
              cout << currentCommandObj->getEffect() << endl;
              game->mainGameLoop();
              return currentCommandObj;
            }
            break;

        case GE_Win:
            if (_userInput == "replay"){
                game->setCurrentState(GE_Start);
                currentCommandObj->saveEffect("Game successfully restarted");
                cout << currentCommandObj->getEffect() << "!\n" << endl;
                return currentCommandObj;
            }
            else if(_userInput == "quit"){
                cout << "Quitting game";
                exit(0);
            }
            break;
        case GE_Reinforcement:
          throw std::runtime_error("CommandProcessor::GE_Reinforcement Not Implemented Yet");
        case GE_Issue_Orders:
          throw std::runtime_error("CommandProcessor::GE_Issue_Orders Not Implemented Yet");
        case GE_Execute_Orders:
          throw std::runtime_error("CommandProcessor::GE_Execute_Orders Not Implemented Yet");
    }

    currentCommandObj->saveEffect("Invalid Command");
    return currentCommandObj;

}


/**
 * @brief Print all commands in the command collection
 *
 * @param collection A collection of Command pointers
 */
void CommandProcessor::printCommandCollection(const std::vector<Command*>& collection){
    for(auto & i : collection){
        cout << (*i) << endl;
    }
    cout << "Current Game State: " << StateToString() << endl;
}

/**
 * @brief Get the command collection
 *
 * @return vector<Command*> The collection of Command pointers
 */
vector<Command*> CommandProcessor::getCommandCollection(){
    return commandCollection;
}

/**
 * @brief Convert the current state of the game to a string representation
 *
 * @return string The string representation of the current game state
 */
string CommandProcessor::StateToString() {
  switch (game->getCurrentState()) {
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
    case GE_Win:
        return "Win";
    case GE_Issue_Orders:
      return "Issue Orders";
    case GE_Execute_Orders:
      return "Execute Orders";
  }
  throw std::runtime_error("CommandProcessor::StateToString Assert:Invalid State");
}

/**
 * @brief Overloaded stream insertion operator for CommandProcessor
 *
 * @param out Reference to ostream object
 * @param c The CommandProcessor object to insert into the stream
 * @return ostream& Reference to the updated ostream object
 */
ostream & operator << (ostream &out, const CommandProcessor &c)
{
  out << "Overloaded << operator for Command Processor?" << endl;
  return out;
}

/**
 * @brief Overloaded assignment operator for CommandProcessor
 *
 * @param other The CommandProcessor object to assign from
 * @return CommandProcessor& Reference to the updated CommandProcessor object
 */
CommandProcessor& CommandProcessor::operator=(const CommandProcessor &other) {
  if(this == &other){
      return *this;
  }

  this->commandCollection = other.commandCollection;
  Subject::attach((ILogObserver*)game->getLogObserver());
  return *this;
}

/**
 * @brief Convert the last command's effect to a string suitable for logging
 *
 * @return string The formatted log string
 */
std::string CommandProcessor::stringToLog() {
  std::stringstream ss;
  ss << "COMMAND PROCESSOR: ";
  ss << "Saved command \"";
  ss << commandCollection.back()->getEffect();
  ss << "\"";
  return ss.str();
}

/**
 * @brief Get the raw command arguments
 *
 * This function provides access to the raw command line arguments that were provided to the CommandProcessor.
 *
 * @return std::vector<std::string>* Pointer to the vector containing the raw command strings.
 */
std::vector<std::string> *CommandProcessor::getRawCommands() {
  return &rawCommands;
}

/**
 * @brief Destructor for CommandProcessor
 *
 * Cleans up the CommandProcessor object, ensuring that the observer is properly detached from the subject.
 */
CommandProcessor::~CommandProcessor() {
  if(game){
    Subject::detach((ILogObserver* )game->getLogObserver());
  }
}
