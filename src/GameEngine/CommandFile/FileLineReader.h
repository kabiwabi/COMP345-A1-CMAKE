#pragma once
#include <iostream>
#include <fstream>
#include <limits>
#include <utility>

class FileLineReader{

private:
    std::string fileName;       ///< The name of the file to be read.
    bool readComplete = false;  ///< Flag to indicate if the file read is complete.
    int currentLine = 1;        ///< Counter for the current line being read from the file.

public:

    /**
     * @brief Default constructor for FileLineReader.
     */
    FileLineReader() = default;

    /**
     * @brief Copy constructor for FileLineReader.
     * @param flr A FileLineReader object to copy from.
     */
    FileLineReader(const FileLineReader &flr);

    /**
     * @brief Reads a single line from the file.
     * @return A std::string representing the line read from the file.
     */
    virtual std::string readLineFromFile();

    /**
     * @brief Moves the file pointer to the specified line number.
     * @param file A reference to an ifstream object.
     * @param num The line number to go to.
     * @return A reference to the ifstream object.
     */
    std::ifstream& GotoLine(std::ifstream& file, unsigned int num);

    /**
     * @brief Calculates the maximum number of lines in the file.
     * @param _fileName The name of the file to be examined.
     * @return The total number of lines in the file.
     */
    int maxNumberOfLines(const std::string& _fileName);

    /**
     * @brief Sets the file to be read.
     * @param _fileName The name of the file to set.
     */
    void setFile(std::string _fileName);

    /**
     * @brief Checks if the file has been completely read.
     * @return True if reading is complete, otherwise false.
     */
    bool getReadComplete();

    /**
     * @brief Retrieves the current line number being read.
     * @return The current line number.
     */
    int getCurrentLine();

    /**
     * @brief Increments the current line counter.
     */
    void incrementCurrentLine();

    /**
     * @brief Overloaded output stream operator for FileLineReader.
     * @param out The ostream object to be written to.
     * @param flr The FileLineReader object whose state is to be output.
     * @return A reference to the ostream object.
     */
    friend std::ostream & operator << (std::ostream &out, const FileLineReader &flr);

    /**
     * @brief Overloaded assignment operator for FileLineReader.
     * @param other The FileLineReader object to assign from.
     * @return A reference to the assigned FileLineReader object.
     */
    FileLineReader& operator=(const FileLineReader& other);
};