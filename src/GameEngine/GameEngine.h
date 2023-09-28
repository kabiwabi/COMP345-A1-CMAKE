#pragma once

#include <string>
#include <stdexcept>
#include <vector>
#include "Player/Player.h"
#include "Map/Map.h"

class Player;
class Map;
class Deck;

/**
 * @enum GameEngineState
 * @brief Represents the different states the game engine can be in.
 */
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
 * @class GameEngine
 * @brief Represents the game engine which manages the state of the game.
 */
class GameEngine {
private:
  /// current state
  GameEngineState state = GE_Start;
  /// Players
  unsigned int playerTurn = 0;
  std::vector<Player*> players;
  /// Deck
  Deck* deck = nullptr;
  /// Map
  Map* map = nullptr;
public:
    /**
     * @brief Default constructor for the GameEngine class.
     */
  GameEngine();
    /**
     * @brief Constructor for the GameEngine class that sets an initial state.
     *
     * @param state Initial state for the game engine.
     */
  explicit GameEngine(GameEngineState state);

  // ----------------------------------------
  // Modifiers & Setters
  // ----------------------------------------
    /**
     * @brief Sets the current state of the game engine.
     *
     * @param engineState State to set the game engine to.
     */
  void setCurrentState(GameEngineState engineState);

    /**
     * @brief Destructor for the GameEngine class.
     */
  ~GameEngine();

    /**
     * @brief Adds a player to the game.
     *
     * @param player Pointer to the player to add.
     */
  void addPlayer(Player* player);

    /**
     * @brief Loads a map for the game.
     *
     * @param path String indicating the path to the map file.
     */
  void loadMap(const std::string& path);

    /**
     * @brief Gets a string representation of the current game engine state.
     *
     * @return std::string String representation of the current state.
     */
  std::string getCurrentStateToString();

private:
    /**
     * @brief Advances the game to the next player's turn.
     */
  void nextPlayerTurn();

public:
    /**
     * @brief Retrieves the players in the game.
     *
     * @return std::vector<Player*>* Pointer to the vector of players.
     */
  std::vector<Player*>* getPlayers();
    /**
     * @brief Gets the player whose turn it currently is.
     *
     * @return Player* Pointer to the current player.
     */
  Player* getCurrentPlayerTurn();
    /**
     * @brief Retrieves the game's deck.
     *
     * @return Deck* Pointer to the game's deck.
     */
  Deck* getDeck();
    /**
    * @brief Retrieves the game's map.
    *
    * @return Map* Pointer to the game's map.
    */
  Map* getMap();
    /**
     * @brief Retrieves the current state of the game engine.
     *
     * @return GameEngineState The current state of the game engine.
     */
  GameEngineState getCurrentState();
};