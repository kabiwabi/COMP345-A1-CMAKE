#include "Command.h"
#include <iostream>
#include <utility>

using namespace std;

/**
 * @brief Construct a new Command object.
 *
 * @param _command The command string to be executed.
 * @param gameEngine Pointer to the GameEngine that will execute the command.
 */
Command::Command(string _command, GameEngine* gameEngine){
    this->game = gameEngine;
    command = std::move(_command);
    effect = "Command has not been executed yet";
    Subject::attach((ILogObserver*)game->getLogObserver());
}

/**
 * @brief Copy constructor.
 *
 * @param c The Command object to be copied.
 */
Command::Command(const Command &c) : Subject(c) {
    game = c.game;
    command = c.command;
    effect = c.effect;
    Subject::attach((ILogObserver*)game->getLogObserver());
}

/**
 * @brief Save the effect of the command.
 *
 * @param _effect The effect string to be saved.
 */
void Command::saveEffect(string _effect){
    effect = std::move(_effect);
    Subject::notify(this);
}

/**
 * @brief Get the effect of the command.
 *
 * @return string The effect string.
 */
string Command::getEffect(){
    return effect;
}

/**
 * @brief Get the command string.
 *
 * @return string The command string.
 */
string Command::getCommand(){
    return command;
}

/**
 * @brief Set the command string.
 *
 * @param _command The command string to be set.
 */
void Command::setCommand(string _command){
    command = std::move(_command);
}

/**
 * @brief Overloaded stream insertion operator to print the Command.
 *
 * @param out Reference to ostream object.
 * @param c The Command object to be printed.
 * @return ostream& The ostream object.
 */
ostream & operator << (ostream &out, const Command &c)
{
    out << c.command << " : " << c.effect << endl;
    return out;
}

/**
 * @brief Overloaded assignment operator.
 *
 * @param other The Command object to assign from.
 * @return Command& A reference to the updated object.
 */
Command& Command::operator=(const Command &other) {
    if(this == &other){
        return *this;
    }

    this->command = other.command;
    this->effect = other.effect;
    Subject::attach((ILogObserver*)game->getLogObserver());

    return *this;
}

/**
 * @brief Convert the command's effect to a string suitable for logging.
 *
 * @return std::string The string to log.
 */
std::string Command::stringToLog() {
    std::stringstream ss;
    ss << "COMMAND: ";
    ss << "Saved Effect \"";
    ss << getEffect();
    ss << "\"";
    return ss.str();
}

/**
 * @brief Destroy the Command object.
 */
Command::~Command() {
    if(game){
        Subject::detach((ILogObserver* )game->getLogObserver());
    }
}
