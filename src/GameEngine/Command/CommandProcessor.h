#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include "Logger/LogObserver.h"

class Command;

/**
 * @class CommandProcessor
 * @brief Processes user or file input commands for a game engine.
 *
 * The CommandProcessor is responsible for reading, validating, and storing commands. It also logs commands and notifies observers upon command changes.
 */
class CommandProcessor: public Subject, ILoggable {

private:
    std::vector<Command*> commandCollection; ///< Collection of pointers to Command objects that have been processed.
    GameEngine* game; ///< Pointer to the GameEngine associated with this CommandProcessor.
    std::vector<std::string> rawCommands; ///< Original raw string commands provided through argv.

private:

    /**
     * @brief Reads a command from the user input.
     * @return std::string The command entered by the user.
     */
    virtual std::string readCommand();

    /**
     * @brief Saves a command to the command collection.
     * @param c Pointer to the Command to be saved.
     */
    void saveCommand(Command* c);

    /**
     * @brief Validates a user input string and converts it to a Command object if valid.
     * @param _userInput The user input string to validate.
     * @return Command* Pointer to the validated and constructed Command object.
     */
    Command* validate(const std::string& _userInput);

public:

    /**
     * @brief Constructs a new Command Processor object.
     * @param game Pointer to the GameEngine object.
     * @param argc The number of command line arguments.
     * @param argv The command line arguments.
     */
    explicit CommandProcessor(GameEngine*, int argc,char* argv[]);

    /**
     * @brief Copy constructor for the Command Processor.
     * @param c The CommandProcessor object to copy from.
     */
    CommandProcessor(const CommandProcessor &c);

    /**
     * @brief Destructor for the Command Processor.
     */
    ~CommandProcessor() override;

    /**
     * @brief Gets the next Command object by reading user input and validating it.
     * @return Command* The next Command object.
     */
    Command* getCommand();

    /**
     * @brief Gets the current state of the game engine.
     * @return int The current state of the game.
     */
    int getCurrentState();

    /**
     * @brief Gets the raw command strings that were passed in via command line arguments.
     * @return std::vector<std::string>* Pointer to the vector of raw command strings.
     */
    std::vector<std::string>* getRawCommands();

    /**
     * @brief Prints all commands in the command collection.
     * @param collection A reference to the vector containing Command pointers.
     */
    void printCommandCollection(const std::vector<Command *> &collection);

    /**
     * @brief Gets the collection of Command objects.
     * @return std::vector<Command*> The collection of Command pointers.
     */
    std::vector<Command*> getCommandCollection();

    /**
     * @brief Converts the current state of the game to a string representation.
     * @return std::string The string representation of the current game state.
     */
    std::string StateToString();

    /**
     * @brief Overloads the stream insertion operator to output the state of the CommandProcessor.
     * @param out Reference to the ostream object.
     * @param c The CommandProcessor object to be output.
     * @return std::ostream& Reference to the updated ostream object.
     */
    friend std::ostream & operator << (std::ostream &out, const CommandProcessor &c);

    /**
     * @brief Overloads the assignment operator.
     * @param other The CommandProcessor object to assign from.
     * @return CommandProcessor& Reference to the updated CommandProcessor object.
     */
    CommandProcessor& operator=(const CommandProcessor& other);

    /**
     * @brief Generates a string representation of the last logged command for logging purposes.
     * @return std::string The formatted log string.
     */
    std::string stringToLog() override;

};