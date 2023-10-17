#include <iostream>
#include <regex>
#include <fstream>
#include "CommandProcessing.h"


// ==========================================================
// COMMAND PROCESSOR
// ==========================================================

/**
 * @brief Constructor.
 */
CommandProcessor::CommandProcessor() = default;

/**
 * @brief Destructor.
 */
CommandProcessor::~CommandProcessor(){
    // Delete the Commands
    while(!commands.empty()){
        Command* cmd = commands.top();
        commands.pop();
        delete cmd;
    }
}

/**
 * @brief Reads command from console.
 * @return command as a string.
 */
std::string CommandProcessor::readCommand() {
    // Read command from CMD Line and returns its value
    std::string commandStr;
    std::getline(std::cin,commandStr);
    return commandStr;
}

/**
 * @brief Validates/Saves/Returns command from command string.
 * @param commandStr command as string.
 * @return A Command object from the command string.
 */
Command *CommandProcessor::saveCommand(string &commandStr) {
    // Validate Command String

    int index=-1;
    // Check if Command String matches a valid command
    for (int i = 0; i < COMMANDS_COUNT; i++) {
        if(regex_match(commandStr,regex(REGEX_PATTERNS[i]))){
            index=i;
            break;
        }
    }

    // Create Command Object
    Command* cmd = ((index<0) ?
            new Command(commandStr,"Invalid Command.",(CommandType)index):
            new Command(commandStr,"Transitions to "+TRANSITION_EFFECTS[index]+" state.",(CommandType)index));

    // Add Command to list
    commands.push(cmd);

    // Return Command
    return cmd;
}

/**
 * @brief Gets a Command from the console.
 * @return Command.
 */
Command *CommandProcessor::getCommand() {
    // Read the command
    std::string commandStr = this->readCommand();

    // Save the command
    Command* command = this->saveCommand(commandStr);

    // Return the command
    return command;
}

/**
 * @brief Validates the command within the current state
 * @param command current command.
 * @param curState current game engine state.
 * @return True if command is valid, otherwise false.
 */
bool CommandProcessor::validate(Command &command, GameEngineState &curState) {
    bool isValid=false;

    switch(command.getType()){
        case CMD_Loadmap:
            isValid = (curState==GE_Start || curState == GE_Map_Loaded);
            break;
        case CMD_Validatemap:
            isValid = (curState == GE_Map_Loaded);
            break;
        case CMD_Addplayer:
            isValid = (curState==GE_Map_Validated || curState == GE_Players_Added);
            break;
        case CMD_Gamestart:
            isValid = (curState==GE_Players_Added);
            break;
        case CMD_Replay: case CMD_Quit:
            isValid = (curState==GE_Win);
            break;
    }

    if(!isValid)
        command.saveEffect("Command not valid in current state.");

    return isValid;
}

// ==========================================================
// COMMAND
// ==========================================================

/**
 * @brief Constructor
 * @param commandStr Command as a string.
 * @param effectStr Effect of the command.
 * @param cmdType Type of the command as a CommandType Enum.
 */
Command::Command(const string &commandStr, const string &effectStr, CommandType cmdType) {
    this->command=commandStr;
    this->effect=effectStr;
    this->type=cmdType;
}

/**
 * @brief Destructor.
 */
Command::~Command() = default;

/**
 * @brief Updates the effect string for the command.
 * @param effectStr new effect string.
 */
void Command::saveEffect(const string &effectStr) {
    this->effect=effectStr;
}

/**
 * @brief Gets the command type.
 * @return CommandType enum.
 */
CommandType Command::getType() {
    return this->type;
}

/**
 * @brief Gets the map name if possible, otherwise returns an empty string.
 * @return Map name if possible, otherwise empty string.
 */
std::string Command::getMapFile() {
    std::string filename;
    if(this->type == CMD_Loadmap){
        filename = this->command.substr(this->command.find(' ')+1, this->command.length());
    }
    return filename;
}

/**
 * @brief Gets the player name if possible, otherwise returns an empty string.
 * @return Player name if possible, otherwise empty string.
 */
std::string Command::getPlayerName() {
    std::string playerName;
    if(this->type == CMD_Addplayer){
        playerName = this->command.substr(this->command.find(' ') + 1, this->command.length());
    }
    return playerName;
}

/**
 * @brief Shows Command.
 * @param stream Stream.
 * @param other Command.
 * @return new Stream.
 */
std::ostream &operator<<(ostream &stream, const Command &other) {
    stream << "Command String: " << other.command << '\n'
            << "Command Effect: " << other.effect;
    return stream;
}

// ==========================================================
// FILE LINE READER
// ==========================================================

/**
 * @brief Constructor.
 * @param filename File name to be read.
 */
FileLineReader::FileLineReader(const std::string& filename) {
    // Keep filename
    this->filename=filename;
    this->currentLine=0;

    // Check if the file actually exists
    std::ifstream file(filename);
    if(!file.good()){
        throw std::runtime_error("FileLineReader::Error | Provided filename does not exist");
    }
    file.close();
}

/**
 * @brief Reads/Returns the current line from the file.
 * @return Current line as a string.
 */
std::string FileLineReader::readLineFromFile() {
    // Open the file
    ifstream file(this->filename);

    // Read from file
    std::string cmdString = {};
    int i = this->currentLine;

    // Reach the current command
    while(getline(file,cmdString)){
        // Command found, so leave loop
        if(i==0){
            this->currentLine++;
            break;
        }
        i--;
    }

    // Close the file
    file.close();

    // Check if the wanted command was found
    if(i!=0){
        throw std::runtime_error("FileLineReader::Error | Command not found");
    }

    // Return string value
    return cmdString;
}

/**
 * @brief Destructor.
 */
FileLineReader::~FileLineReader() = default;

// ==========================================================
// FILE COMMAND PROCESSOR ADAPTER
// ==========================================================

/**
 * @brief Constructor.
 * @param filename Name of the file that contains the commands.
 */
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const std::string &filename) {
    this->fileLineReader = new FileLineReader(filename);
}

/**
 * @brief Reads a command from a file.
 * @return A command as a string.
 */
std::string FileCommandProcessorAdapter::readCommand() {
    // Read command from File and return its value
    std::string commandStr = this->fileLineReader->readLineFromFile();
    return commandStr;
}

/**
 *  @brief Destructor.
 */
FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    delete this->fileLineReader;
}


