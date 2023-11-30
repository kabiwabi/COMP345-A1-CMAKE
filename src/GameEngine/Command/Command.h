#pragma once

#include "GameEngine/GameEngine.h"
#include "Logger/LogObserver.h"
#include <iostream>
#include <sstream>

class GameEngine;
class ILogObserver;

/**
 * @brief The Command class represents a game command with an associated effect.
 */
class Command : public Subject, ILoggable
{
private:
  std::string command;
  std::string effect;
  GameEngine *game = nullptr;

public:
  // Constructors
  /**
   * @brief Constructor for the Command class.
   *
   * @param _command The command string.
   * @param gameEngine Pointer to the GameEngine instance.
   */
  explicit Command(std::string _command, GameEngine *gameEngine);

  /**
   * @brief Copy constructor for the Command class.
   *
   * @param c Reference to another Command instance.
   */
  Command(const Command &c);

  /**
   * @brief Destructor for the Command class.
   */
  ~Command() override;

  // Getters & Setters
  /**
   * @brief Saves the effect associated with the command.
   *
   * @param effect The effect string.
   */
  void saveEffect(std::string effect);

  /**
   * @brief Gets the effect associated with the command.
   *
   * @return The effect string.
   */
  std::string getEffect();

  /**
   * @brief Gets the command string.
   *
   * @return The command string.
   */
  std::string getCommand();

  /**
   * @brief Sets the command string.
   *
   * @param _command The command string to set.
   */
  void setCommand(std::string _command);

  // Operator Overloading
  /**
   * @brief Overloaded stream insertion operator to output Command details.
   *
   * @param out Reference to the output stream.
   * @param c Reference to the Command instance.
   * @return Reference to the output stream.
   */
  friend std::ostream &operator<<(std::ostream &out, const Command &c);

  /**
   * @brief Overloaded assignment operator for the Command class.
   *
   * @param other Reference to another Command instance.
   * @return Reference to the modified Command instance.
   */
  Command &operator=(const Command &other);

  // Logging
  /**
   * @brief Converts the Command details to a log string.
   *
   * @return The log string.
   */
  std::string stringToLog() override;
};
