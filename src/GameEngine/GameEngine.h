#pragma once
#include <string>
#include <stdexcept>
#include <vector>
#include "../Player/Player.h"
#include "Map/Map.h"
#include "Logger/LogObserver.h"
#include "CommandFile/FileCommandProcessorAdapter.h"
#include "CommandFile/FileLineReader.h"
#include "Command/Command.h"

class Player;
class Map;
class Deck;

enum GameEngineState {
  GE_Start = 0,
  GE_Map_Loaded,
  GE_Map_Validated,
  GE_Players_Added,
  GE_Reinforcement,
  GE_Issue_Orders,
  GE_Execute_Orders,
  GE_Win
};

/**
 * @brief This class represents the game engine for a board game, handling the game states, players, and main game loop.
 */
class GameEngine : public Subject, ILoggable {
private:
    // Current state of the game engine.
    GameEngineState state = GE_Start;
    // Filename for saving/loading game.
    std::string fileName;
    // Pointer to the current player's turn.
    Player* currentPlayerTurn = nullptr;
    // List of players in the game.
    std::vector<Player*> players;
    // List of available commands.
    std::vector<std::string> commands = {"loadmap <filename>", "validatemap", "addplayer <playername>", "gamestart", "replay", "quit"};
    // Pointer to the deck of cards.
    Deck* deck = nullptr;
    // Pointer to the game map.
    Map* map = nullptr;
    // Pointer to the log observer.
    LogObserver* logObserver = nullptr;
    // Pointer to the command processor.
    CommandProcessor* commandProcessor = nullptr;
    // Pointer to the file command processor adapter.
    FileCommandProcessorAdapter* adapter = nullptr;
    // Pointer to the file line reader.
    FileLineReader* flr = nullptr;
    // Argument count.
    int argc;
    // Argument vector.
    char** argv;

    // Checks for win state and returns the winning player, if any.
    Player* checkWinState();
    // Advances to the next player's turn.
    void nextTurn(int& turn);
    // Removes players who no longer control any territories.
    void removePlayersWithNoTerritories();
    // Prints the list of commands to the console.
    void printCommands();
    // Validates if the provided command string is valid.
    static bool isValid(const std::string& strCommand);
    // Converts the current state to a string for logging.
    std::string getCurrentStateToString();

public:
    // Constructor with command line arguments.
    GameEngine(int argc, char** argv);
    // Constructor with specified game state and command line arguments.
    explicit GameEngine(GameEngineState state, int argc, char** argv);
    // Destructor.
    ~GameEngine() override;
    // Sets the current state of the game engine.
    void setCurrentState(GameEngineState engineState);
    // Loads the map from a file.
    void loadMap(const std::string& path);
    // Validates the loaded game map.
    bool validateMap();
    // Returns a string representation of the current state for logging.
    std::string stringToLog() override;
    // Executes the startup phase of the game.
    void startupPhase();
    // Executes the reinforcement phase of the game.
    void reinforcementPhase();
    // Executes the issue orders phase of the game.
    void issueOrdersPhase();
    // Executes the orders.
    void executeOrdersPhase();
    // Distributes territories among players.
    void distributeTerritories();
    // Determines the order of players.
    void playerOrder();
    // Gets the deck of cards.
    Deck* getDeck();
    // Gets the game map.
    Map* getMap();
    // Main game loop.
    void mainGameLoop();
    // Gets the log observer.
    LogObserver* getLogObserver();
    // Gets the current player's turn.
    Player* getCurrentPlayerTurn();
    // Validates the maximum number of players.
    void validateMaxPlayers();
    // Validates the minimum number of players.
    void validateMinPlayers();
    // Adds a new player to the game.
    void addPlayer(Player* player);
    // Resets the game to initial state.
    void resetGame();
    // Gets the list of players.
    std::vector<Player*>* getPlayers();
    // Gets the current state of the game engine.
    GameEngineState getCurrentState();
    // Gets the command processor.
    CommandProcessor* getCommandProcessor();
    // Gets the file line reader.
    FileLineReader* getFlir();
    // Gets the file command processor adapter.
    FileCommandProcessorAdapter* getFileCommandProcessorAdapter();
    // Sets the current player's turn.
    void setCurrentPlayer(Player* player);
};