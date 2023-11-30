#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include "Logger/LogObserver.h"

class Command;

class CommandProcessor : public Subject, ILoggable
{

private:
  // Store all user commands
  std::vector<Command *> commandCollection;

  // Object Owner
  GameEngine *game;

  // Command line arguments
  std::vector<std::string> rawCommands;

private:
  /**
   * @brief Reads a command from the user.
   *
   * @return The user-inputted command.
   */
  virtual std::string readCommand();

  /**
   * @brief Saves a command to the collection.
   *
   * @param c The command to save.
   */
  void saveCommand(Command *c);

  /**
   * @brief Validates user input to create a command.
   *
   * @param _userInput The user input to validate.
   * @return A validated Command object.
   */
  Command *validate(const std::string &_userInput);

public:
  /**
   * @brief Processes input for a file-based tournament.
   *
   * @param input The input for the file-based tournament.
   */
  void FileTournamentFunctionInput(std::string input);

  /**
   * @brief Processes input for a tournament.
   *
   * @param input The input for the tournament.
   */
  void TournamentFunctionInput(std::string);

  // Constructors
  /**
   * @brief Constructor for CommandProcessor.
   *
   * @param gameEngine The associated GameEngine.
   * @param argc The number of command line arguments.
   * @param argv The array of command line arguments.
   */
  explicit CommandProcessor(GameEngine *, int argc, char *argv[]);

  /**
   * @brief Copy constructor for CommandProcessor.
   *
   * @param c The CommandProcessor to copy.
   */
  CommandProcessor(const CommandProcessor &c);

  /**
   * @brief Destructor for CommandProcessor.
   */
  ~CommandProcessor() override;

  // Getters and setters
  /**
   * @brief Gets the current command.
   *
   * @return The current command.
   */
  Command *getCommand();

  /**
   * @brief Gets the current state.
   *
   * @return The current state.
   */
  int getCurrentState();

  /**
   * @brief Gets the raw command arguments.
   *
   * @return A pointer to the vector of raw command arguments.
   */
  std::vector<std::string> *getRawCommands();

  /**
   * @brief Validates the input for a tournament.
   *
   * @return True if the input is valid for a tournament, false otherwise.
   */
  bool validateTournament();

  // Functions for CommandProcessorDriver.cpp
  /**
   * @brief Prints the command collection.
   *
   * @param collection The collection of commands to print.
   */
  void printCommandCollection(const std::vector<Command *> &collection);

  /**
   * @brief Gets the command collection.
   *
   * @return The vector of commands.
   */
  std::vector<Command *> getCommandCollection();

  /**
   * @brief Converts the current state to a string.
   *
   * @return The string representation of the current state.
   */
  std::string StateToString();

  // Operator Overloading
  /**
   * @brief Overloaded << operator for CommandProcessor.
   *
   * @param out The output stream.
   * @param c The CommandProcessor to output.
   * @return The output stream.
   */
  friend std::ostream &operator<<(std::ostream &out, const CommandProcessor &c);

  /**
   * @brief Overloaded assignment operator for CommandProcessor.
   *
   * @param other The CommandProcessor to copy.
   * @return A reference to the current CommandProcessor.
   */
  CommandProcessor &operator=(const CommandProcessor &other);

  // Logging
  /**
   * @brief Converts the object to a loggable string.
   *
   * @return The loggable string representation of the object.
   */
  std::string stringToLog() override;
};
