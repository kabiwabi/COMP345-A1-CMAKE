#pragma once

#include <string>
#include <stdexcept>
#include <vector>
#include "Player/Player.h"
#include "Map/Map.h"
#include "Logger/LogObserver.h"
#include "CommandFile/FileCommandProcessorAdapter.h"
#include "CommandFile/FileLineReader.h"
#include "Command/Command.h"

class Player;
class Map;
class Deck;

// ----------------------------------------
// Public GameEngine State Enum
// ----------------------------------------
enum GameEngineState {
  GE_Start = 0,
  GE_Tournament,
  GE_Map_Loaded,
  GE_Map_Validated,
  GE_Players_Added,
  GE_Reinforcement,
  GE_Issue_Orders,
  GE_Execute_Orders,
  GE_Win
};

/**
 * @brief Main class representing the game engine.
 */
class GameEngine : public Subject, ILoggable {
private:
  // current state
  GameEngineState state = GE_Start;

  // Players
  std::string fileName;
  Player* currentPlayerTurn = nullptr;
  std::vector<Player*> players;
  std::vector<std::vector<std::string>> tournamentResults;

  bool isDraw = false;
  bool tournamentEnd = false;
  std::vector<std::string> commands = {"tournament -M <mapFiles> -P <playerStrategies> -G <numGames> -D <maxTurns>", "loadmap <filename>", "validatemap", "addplayer <playername>", "gamestart", "replay", "quit"};

  // Deck
  Deck* deck = nullptr;

  // Map
  Map* map = nullptr;

  // Logger
  LogObserver* logObserver = nullptr;

  // Command Processor
  CommandProcessor* commandProcessor = nullptr;
  FileCommandProcessorAdapter* adapter = nullptr;
  FileLineReader* flr = nullptr;

  // CL Args
  int argc;
  char** argv;

  // testing
  bool testing = false;

public:
  std::vector <std::string> allMaps;
  std::vector <std::string> allPlayerStrategies;
  int numberOfGames = 0;
  int maxNumberOfTurns = 0;
  bool multipleTournaments = false;
  
  // ----------------------------------------
  // Constructors
  // ----------------------------------------
  GameEngine(int argc, char** argv, bool testing = false);
  explicit GameEngine(GameEngineState state, int argc, char** argv, bool testing = false);

  /**
   * @brief Sets the current state of the GameEngine.
   *
   * @param engineState The new state to set.
   */
  void setCurrentState(GameEngineState engineState);

  // ----------------------------------------
  // Destructor
  // ----------------------------------------
  ~GameEngine() override;

  /**
   * @brief Validates the tournament settings.
   */
  void validateTournament();

  /**
   * @brief Loads a game map from a file.
   *
   * @param path The path to the map file.
   */
  void loadMap(const std::string& path);

  /**
   * @brief Validates the loaded game map.
   *
   * @return True if the map is valid, false otherwise.
   */
  bool validateMap();

  /**
   * @brief Converts the current state to a string representation.
   *
   * @return The string representation of the current state.
   */
  std::string stringToLog() override;

  /**
   * @brief Retrieves the tournament results.
   *
   * @return The string representation of tournament results.
   */
  std::string getTournamentResults();

  // ----------------------------------------
  // Initiates startup phase for commands read from the console
  // ----------------------------------------
  void startupPhase();

  // ----------------------------------------
  // Reinforcement phase
  // ----------------------------------------
  void reinforcementPhase();

  // ----------------------------------------
  // Issuing Orders Phase
  // ----------------------------------------
  void issueOrdersPhase();

  // ----------------------------------------
  // Execute Orders Phase
  // ----------------------------------------
  void executeOrdersPhase();

  // ----------------------------------------
  // Distributes all territories evenly between the players
  // ----------------------------------------
  void distributeTerritories();

  // ----------------------------------------
  // Determines a random order of play for players
  // ----------------------------------------
  void playerOrder();

  /**
   * @brief Retrieves the game's deck.
   *
   * @return The game's deck.
   */
  Deck* getDeck();

  /**
   * @brief Retrieves the game's map.
   *
   * @return The game's map.
   */
  Map* getMap();

  /**
   * @brief Runs the main game loop.
   *
   * @param maxRounds Maximum number of rounds to play.
   */
  void mainGameLoop(int maxRounds = 500);

  /**
   * @brief Retrieves the game's logger observer.
   *
   * @return The game's logger observer.
   */
  LogObserver* getLogObserver();

  /**
   * @brief Checks if the game is in testing mode.
   *
   * @return True if the game is in testing mode, false otherwise.
   */
  bool isTesting() const;

  /**
   * @brief Retrieves the current player's turn.
   *
   * @return The current player's turn.
   */
  Player* getCurrentPlayerTurn();

  /**
   * @brief Validates the maximum number of players.
   */
  void validateMaxPlayers();

  /**
   * @brief Validates the minimum number of players.
   */
  void validateMinPlayers();

  /**
   * @brief Adds a player to the game.
   *
   * @param player The player to add.
   */
  void addPlayer(Player* player);

  /**
   * @brief Resets the game to its initial state.
   */
  void resetGame();

  /**
   * @brief Runs a tournament.
   */
  void runTournament();

  /**
   * @brief Generates a random deck.
   *
   * @param deckSize The size of the deck.
   */
  void generateRandomDeck(int deckSize = 15);

  /**
   * @brief Assigns cards evenly among players.
   */
  void assignCardsEvenly();

  // ----------------------------------------
  // Getters
  // ----------------------------------------

  /**
   * @brief Retrieves the vector of players.
   *
   * @return The vector of players.
   */
  std::vector<Player*>* getPlayers();

  /**
   * @brief Retrieves the current state of the GameEngine.
   *
   * @return The current state of the GameEngine.
   */
  GameEngineState getCurrentState();

  /**
   * @brief Retrieves the game's command processor.
   *
   * @return The game's command processor.
   */
  CommandProcessor* getCommandProcessor();

  /**
   * @brief Retrieves the game's file line reader.
   *
   * @return The game's file line reader.
   */
  FileLineReader* getFlir();

  /**
   * @brief Retrieves the game's file command processor adapter.
   *
   * @return The game's file command processor adapter.
   */
  FileCommandProcessorAdapter* getFileCommandProcessorAdapter();

  // ----------------------------------------
  // Setters
  // ----------------------------------------

  /**
   * @brief Sets the current player's turn.
   *
   * @param player The player whose turn it is.
   */
  void setCurrentPlayer(Player* player);

private:
  /**
   * @brief Checks the win state of the game.
   *
   * @return The winning player if there is one, nullptr otherwise.
   */
  Player* checkWinState();

  /**
   * @brief Moves on to the next turn.
   *
   * @param turn The current turn.
   */
  void nextTurn(int& turn);

  // ----------------------------------------
  // Remove players with no territories
  // ----------------------------------------
  void removePlayersWithNoTerritories();

private:
  // ----------------------------------------
  // Prints all the commands available for the user to use
  // ----------------------------------------
  void printCommands();

  // ----------------------------------------
  // Checks whether a command is valid or not
  // ----------------------------------------
  static bool isValid(const std::string& strCommand);

  // ----------------------------------------
  // Convert current state to string
  // ----------------------------------------
  std::string getCurrentStateToString();

  /**
   * @brief Retrieves the string representation of a player type.
   *
   * @return The string representation of a player type.
   */
  std::string getPlayerTypeToString();
};
