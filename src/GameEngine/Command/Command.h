#pragma once
#include "GameEngine/GameEngine.h"
#include "Logger/LogObserver.h"
#include <iostream>
#include <sstream>

class GameEngine;
class ILogObserver;

/**
 * @class Command
 * @brief The Command class encapsulates a game command and its effect within a game engine.
 *
 * It inherits from Subject to implement the Observer pattern and ILoggable for logging purposes.
 */
class Command: public Subject, ILoggable {

private:
    std::string command; ///< Command string to be executed
    std::string effect;  ///< Resulting effect of the command after execution

    GameEngine* game = nullptr; ///< Pointer to the associated GameEngine

public:

    /**
     * @brief Construct a new Command object with a command string and pointer to the GameEngine.
     * @param _command Command string to be executed
     * @param gameEngine Pointer to the GameEngine that will process the command
     */
    explicit Command(std::string _command, GameEngine* gameEngine);

    /**
     * @brief Copy constructor for the Command object.
     * @param c Reference to the Command object to be copied
     */
    Command(const Command &c);

    /**
     * @brief Destroy the Command object and detach from the subject.
     */
    ~Command() override;

    // Getters & Setters

    /**
     * @brief Save the effect of the command.
     * @param effect The effect string to be saved
     */
    void saveEffect(std::string effect);

    /**
     * @brief Get the effect of the command.
     * @return std::string The effect string
     */
    std::string getEffect();

    /**
     * @brief Get the command string.
     * @return std::string The command string
     */
    std::string getCommand();

    /**
     * @brief Set the command string.
     * @param _command The command string to be set
     */
    void setCommand(std::string _command);

    // Operator Overloading

    /**
     * @brief Overload the stream insertion operator to output the Command object.
     * @param out Reference to the ostream object
     * @param c Reference to the Command object to be output
     * @return std::ostream& Reference to the updated ostream object
     */
    friend std::ostream & operator << (std::ostream &out, const Command &c);

    /**
     * @brief Overload the assignment operator for the Command object.
     * @param other Reference to the Command object to assign from
     * @return Command& Reference to the updated Command object
     */
    Command& operator=(const Command& other);

    // Logging

    /**
     * @brief Convert the command's effect to a string suitable for logging.
     * @return std::string The formatted log string
     */
    std::string stringToLog() override;
};