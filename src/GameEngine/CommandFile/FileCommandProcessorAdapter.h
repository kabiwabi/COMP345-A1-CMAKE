#pragma once
#include <iostream>
#include "../Command/CommandProcessor.h"
#include "FileLineReader.h"

class FileCommandProcessorAdapter : public CommandProcessor
{

private:
    FileLineReader *flr = nullptr;

public:
    /**
     * @brief Constructor for FileCommandProcessorAdapter.
     *
     * @param game Pointer to the GameEngine.
     * @param argc Number of command line arguments.
     * @param argv Array of command line arguments.
     */
    FileCommandProcessorAdapter(GameEngine *game, int argc, char **argv);

    /**
     * @brief Copy constructor for FileCommandProcessorAdapter.
     *
     * @param fcpA Reference to the FileCommandProcessorAdapter to copy.
     */
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter &fcpA) = default;

    /**
     * @brief Destructor for FileCommandProcessorAdapter.
     */
    ~FileCommandProcessorAdapter() override = default;

    /**
     * @brief Overridden method to read commands from the file.
     *
     * @return A string representing the read command.
     */
    std::string readCommand() override;

    /**
     * @brief Overloaded << operator for FileCommandProcessorAdapter.
     *
     * @param out The output stream.
     * @param ffcpAr The FileCommandProcessorAdapter to output.
     * @return The output stream.
     */
    friend std::ostream &operator<<(std::ostream &out, const FileCommandProcessorAdapter &ffcpAr);

    /**
     * @brief Overloaded assignment operator for FileCommandProcessorAdapter.
     *
     * @param other The FileCommandProcessorAdapter to copy.
     * @return Reference to the assigned FileCommandProcessorAdapter.
     */
    FileCommandProcessorAdapter &operator=(const FileCommandProcessorAdapter &other);
};
