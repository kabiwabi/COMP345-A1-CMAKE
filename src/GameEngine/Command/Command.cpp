#include "Command.h"
#include <iostream>
#include <utility>

using namespace std;

/**
 * @brief Constructor for the Command class.
 * @param _command The command string.
 * @param gameEngine Pointer to the GameEngine.
 */
Command::Command(string _command, GameEngine *gameEngine)
{
  this->game = gameEngine;
  command = std::move(_command);
  effect = "Command has not been executed yet";
  Subject::attach((ILogObserver *)game->getLogObserver());
}

/**
 * @brief Copy constructor for the Command class.
 * @param c The Command object to be copied.
 */
Command::Command(const Command &c) : Subject(c)
{
  game = c.game;
  command = c.command;
  effect = c.effect;
  Subject::attach((ILogObserver *)game->getLogObserver());
}

/**
 * @brief Save the effect of the command.
 * @param _effect The effect string to be saved.
 */
void Command::saveEffect(string _effect)
{
  effect = std::move(_effect);
  Subject::notify(this);
}

/**
 * @brief Get the saved effect of the command.
 * @return The effect string.
 */
string Command::getEffect()
{
  return effect;
}

/**
 * @brief Get the command string.
 * @return The command string.
 */
string Command::getCommand()
{
  return command;
}

/**
 * @brief Set the command string.
 * @param _command The new command string.
 */
void Command::setCommand(string _command)
{
  command = std::move(_command);
}

/**
 * @brief Overloaded stream insertion operator to print the Command object.
 * @param out The output stream.
 * @param c The Command object.
 * @return The output stream.
 */
ostream &operator<<(ostream &out, const Command &c)
{
  out << c.command << " : " << c.effect << endl;
  return out;
}

/**
 * @brief Assignment operator for the Command class.
 * @param other The Command object to be assigned.
 * @return A reference to the assigned Command object.
 */
Command &Command::operator=(const Command &other)
{
  if (this == &other)
  {
    return *this;
  }

  this->command = other.command;
  this->effect = other.effect;
  Subject::attach((ILogObserver *)game->getLogObserver());

  return *this;
}

/**
 * @brief Convert the command details to a log-friendly string.
 * @return The log string.
 */
std::string Command::stringToLog()
{
  std::stringstream ss;
  ss << "COMMAND: ";
  ss << "Saved Effect \"";
  ss << getEffect();
  ss << "\"";
  return ss.str();
}

/**
 * @brief Destructor for the Command class.
 * Detaches the game's log observer if game is not null.
 */
Command::~Command()
{
  if (game)
  {
    Subject::detach((ILogObserver *)game->getLogObserver());
  }
}