#pragma once
#include <iostream>
#include <fstream>
#include <limits>
#include <utility>

class FileLineReader
{

private:
    std::string fileName;      /**< The name of the file being read. */
    bool readComplete = false; /**< Flag indicating whether the file reading is complete. */
    int currentLine = 1;       /**< The current line being read in the file. */

public:
    /**
     * @brief Default constructor for FileLineReader.
     */
    FileLineReader() = default;

    /**
     * @brief Copy constructor for FileLineReader.
     *
     * @param flr Reference to the FileLineReader to copy.
     */
    FileLineReader(const FileLineReader &flr);

    /**
     * @brief Reading a line from the file.
     *
     * @return A string representing the read line.
     */
    virtual std::string readLineFromFile();

    /**
     * @brief Jump to a specified line number in the file.
     *
     * @param file Reference to the input file stream.
     * @param num The line number to jump to.
     * @return Reference to the modified input file stream.
     */
    std::ifstream &GotoLine(std::ifstream &file, unsigned int num);

    /**
     * @brief Get the maximum number of lines in the specified file.
     *
     * @param _fileName The name of the file to get the maximum lines for.
     * @return The maximum number of lines in the file.
     */
    int maxNumberOfLines(const std::string &_fileName);

    /**
     * @brief Set the file to be read.
     *
     * @param _fileName The name of the file to be set.
     */
    void setFile(std::string _fileName);

    /**
     * @brief Get the status of file reading completion.
     *
     * @return True if file reading is complete, false otherwise.
     */
    bool getReadComplete();

    /**
     * @brief Get the current line being read in the file.
     *
     * @return The current line number.
     */
    int getCurrentLine();

    /**
     * @brief Increment the current line number.
     */
    void incrementCurrentLine();

    /**
     * @brief Overloaded << operator for FileLineReader.
     *
     * @param out The output stream.
     * @param flr The FileLineReader to output.
     * @return The output stream.
     */
    friend std::ostream &operator<<(std::ostream &out, const FileLineReader &flr);

    /**
     * @brief Overloaded assignment operator for FileLineReader.
     *
     * @param other The FileLineReader to copy.
     * @return Reference to the assigned FileLineReader.
     */
    FileLineReader &operator=(const FileLineReader &other);
};
