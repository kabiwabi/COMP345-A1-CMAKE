#include "FileCommandProcessorAdapter.h"

/**
 * @brief Sets the FileLineReader that the adapter will use to read commands from a file.
 *
 * @param _flr Pointer to a FileLineReader object.
 */
void FileCommandProcessorAdapter::commandLineToFile(FileLineReader* _flr){
    flr = _flr;
}

/**
 * @brief Reads a command from a file using the FileLineReader.
 *
 * @return std::string The command read from the file.
 */
std::string FileCommandProcessorAdapter::readCommand(){
    return flr->readLineFromFile();
}

/**
 * @brief Constructs a FileCommandProcessorAdapter object.
 *
 * @param game Pointer to the GameEngine object.
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments array.
 */
FileCommandProcessorAdapter::FileCommandProcessorAdapter(GameEngine* game, int argc, char** argv)
        : CommandProcessor(game, argc, argv) {}

/**
 * @brief Overloaded stream insertion operator for FileCommandProcessorAdapter.
 *
 * @param out Reference to the ostream object.
 * @param fcpA The FileCommandProcessorAdapter object to output.
 * @return std::ostream& Reference to the updated ostream object.
 */
std::ostream & operator << (std::ostream &out, const FileCommandProcessorAdapter &fcpA){
    out << "Adapter connected to: " << fcpA.flr << std::endl;
    return out;
}

/**
 * @brief Overloaded assignment operator for FileCommandProcessorAdapter.
 *
 * @param other The FileCommandProcessorAdapter object to assign from.
 * @return FileCommandProcessorAdapter& Reference to the updated FileCommandProcessorAdapter object.
 */
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter& other){
    if(this == &other){
        return *this;
    }

    this->flr = other.flr;

    return *this;
}