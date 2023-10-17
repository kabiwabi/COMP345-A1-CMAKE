#pragma once

#include <string>
#include <vector>
#include <stack>
#include "GameEngine/GameEngine.h"

class Command;
class FileLineReader;

/// Command Classifications/Types.
enum CommandType{
    CMD_Loadmap = 0,
    CMD_Validatemap,
    CMD_Addplayer,
    CMD_Gamestart,
    CMD_Replay,
    CMD_Quit
};

/// Processes Commands from Console.
class CommandProcessor{
private:
    /// Number of Command Types currently in the game.
    const int COMMANDS_COUNT=6;
    /// Regex pattern for each command.
    const std::string REGEX_PATTERNS[6] = {"(^\\s*[lL][oO][aA][dD][mM][aA][pP]\\s*\\S+\\s*$)",
                                           "(^\\s*[vV][aA][lL][iI][dD][aA][tT][eE][mM][aA][pP]\\s*$)",
                                           "(^\\s*[aA][dD][dD][pP][lL][aA][yY][eE][rR]\\s*\\S+\\s*$)",
                                           "(^\\s*[gG][aA][mM][eE][sS][tT][aA][rR][tT]\\s*$)",
                                           "(^\\s*[rR][eE][pP][lL][aA][yY]\\s*$)",
                                           "(^\\s*[qQ][uU][iI][tT]\\s*$)"};
    /// Transition effect for each command.
    const std::string TRANSITION_EFFECTS[6] = {"maploaded",
                                               "mapvalidaed",
                                               "playersadded",
                                               "assignreinforcement",
                                               "start",
                                               "exit program"};
    /// Stack of commands that have been called.
    std::stack<Command*> commands;
    /// Reads a Command from the console.
    virtual std::string readCommand();
    /// Saves/Returns a Command from a command string.
    Command* saveCommand(std::string& commandStr);
public:
    /// Constructor.
    CommandProcessor();
    /// Destructor.
    ~CommandProcessor();
    /// Gets a Command from the console.
    Command* getCommand();
    /// Validates if a Command is valid in a certain state.
    static bool validate(Command &command, GameEngineState &curState);
};

/// Processes Commands from File.
class FileCommandProcessorAdapter: public CommandProcessor{
private:
    /// Handles reading commands from file.
    FileLineReader* fileLineReader;
    /// Overrides the virtual method from CommandProcessor.
    std::string readCommand() override;
public:
    /// Constructor.
    explicit FileCommandProcessorAdapter(const std::string &filename);
    /// Destructor.
    ~FileCommandProcessorAdapter();
};

/// Represents a Command.
class Command{
private:
    /// Command string.
    std::string command;
    /// Effect of command
    std::string effect;
    /// Command type.
    CommandType type;
public:
    /// Constructor.
    explicit Command(const std::string &commandStr,const std::string &effectStr, CommandType cmdType);
    /// Destructor.
    ~Command();
    /// Saves an effect for the command.
    void saveEffect(const std::string &effectStr);
    /// Gets the command type.
    CommandType getType();
    /// Gets the Map file name if possible, otherwise returns an empty string.
    std::string getMapFile();
    /// Gets the player name if possible, otherwise returns an empty string.
    std::string getPlayerName();
    /// Stream operator overload.
    friend std::ostream& operator<<(std::ostream& stream, const Command& other);
};

/// Handles reading commands from a file.
class FileLineReader{
private:
    /// Name of the file containing the commands.
    std::string filename;
    /// Index to line at which the current command is located.
    int currentLine;
public:
    /// Constructor.
    explicit FileLineReader(const std::string& filename);
    /// Destructor.
    ~FileLineReader();
    /// Reads/Returns the current line from the file.
    std::string readLineFromFile();
};