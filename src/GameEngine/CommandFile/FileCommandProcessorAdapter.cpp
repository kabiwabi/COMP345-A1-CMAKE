#include "FileCommandProcessorAdapter.h"

/**
 * @brief Connects a FileLineReader to the adapter for reading commands from a file.
 * @param _flr Pointer to the FileLineReader to be connected.
 * @return None.
 */
void FileCommandProcessorAdapter::commandLineToFile(FileLineReader *_flr)
{
    flr = _flr;
}

/**
 * @brief Reads a command from the connected FileLineReader.
 * @return A string containing the read command.
 */
std::string FileCommandProcessorAdapter::readCommand()
{
    return flr->readLineFromFile();
}

/**
 * @brief Initializes the FileCommandProcessorAdapter object with a GameEngine,
 *        argc, and argv, and calls the constructor of the base class CommandProcessor
 *        with these parameters.
 * @param game Pointer to the GameEngine instance.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 */
FileCommandProcessorAdapter::FileCommandProcessorAdapter(GameEngine *game, int argc, char **argv) : CommandProcessor(game, argc, argv) {}

/**
 * @brief Overloaded stream insertion operator for output.
 * @param out Reference to the output stream.
 * @param fcpA Reference to the FileCommandProcessorAdapter to be output.
 * @return Reference to the output stream.
 */
std::ostream &operator<<(std::ostream &out, const FileCommandProcessorAdapter &fcpA)
{
    out << "Adapter connected to: " << fcpA.flr << std::endl;
    return out;
}

/**
 * @brief Overloaded assignment operator for assigning the content of another
 *        FileCommandProcessorAdapter instance.
 * @param other Reference to the FileCommandProcessorAdapter to be copied.
 * @return Reference to the assigned FileCommandProcessorAdapter.
 */
FileCommandProcessorAdapter &FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter &other)
{
    if (this == &other)
    {
        return *this;
    }

    this->flr = other.flr;

    return *this;
}
