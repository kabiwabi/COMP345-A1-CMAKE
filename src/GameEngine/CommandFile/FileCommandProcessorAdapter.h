#pragma once
#include <iostream>
#include "../Command/CommandProcessor.h"
#include "FileLineReader.h"

/**
 * @class FileCommandProcessorAdapter
 * @brief Adapter class to use a FileLineReader with a CommandProcessor.
 *
 * This class adapts the CommandProcessor to read commands from a file instead of the standard input, leveraging the FileLineReader class.
 */
class FileCommandProcessorAdapter : public CommandProcessor {

private:
    FileLineReader *flr; ///< Pointer to the FileLineReader object.

public:
    /**
     * @brief Sets the FileLineReader that this adapter will use.
     * @param _flr Pointer to the FileLineReader object.
     */
    void commandLineToFile(FileLineReader* _flr);

    /**
     * @brief Reads a command from a file.
     * @return std::string The next command from the file.
     */
    std::string readCommand() override;

    /**
     * @brief Destructor for FileCommandProcessorAdapter.
     */
    ~FileCommandProcessorAdapter() override = default;

    /**
     * @brief Constructs a FileCommandProcessorAdapter object.
     * @param game Pointer to the GameEngine object.
     * @param argc The number of command-line arguments.
     * @param argv The command-line arguments array.
     */
    FileCommandProcessorAdapter(GameEngine* game, int argc, char** argv);

    /**
     * @brief Copy constructor for FileCommandProcessorAdapter.
     * @param fcpA The FileCommandProcessorAdapter object to copy from.
     */
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter &fcpA) = default;

    //Operator Overloading
    /**
     * @brief Overloaded stream insertion operator for FileCommandProcessorAdapter.
     * @param out Reference to the ostream object.
     * @param fcpA The FileCommandProcessorAdapter object to output.
     * @return std::ostream& Reference to the updated ostream object.
     */
    friend std::ostream & operator << (std::ostream &out, const FileCommandProcessorAdapter &fcpA);

    /**
     * @brief Overloaded assignment operator for FileCommandProcessorAdapter.
     * @param other The FileCommandProcessorAdapter object to assign from.
     * @return FileCommandProcessorAdapter& Reference to the updated FileCommandProcessorAdapter object.
     */
    FileCommandProcessorAdapter& operator=(const FileCommandProcessorAdapter& other);
};