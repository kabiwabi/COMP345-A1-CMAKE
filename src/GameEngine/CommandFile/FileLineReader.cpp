#include "FileLineReader.h"
#include <string>

/**
 * @brief Copy constructor for FileLineReader.
 * @param flr The FileLineReader instance to be copied.
 */
FileLineReader::FileLineReader(const FileLineReader &flr)
{
  fileName = flr.fileName;
  readComplete = flr.readComplete;
}

/**
 * @brief Reads a line from the file and updates the current line pointer.
 * @return A string containing the read line.
 * @throws std::runtime_error if the file cannot be opened.
 */
std::string FileLineReader::readLineFromFile()
{

  std::ifstream fileInputStream(fileName);
  int maxLines = maxNumberOfLines(fileName);
  std::string line;

  if (fileInputStream.is_open() && !readComplete)
  {
    GotoLine(fileInputStream, getCurrentLine());
    getline(fileInputStream, line);
    if (getCurrentLine() == maxLines)
    {
      this->readComplete = true;
    }
    incrementCurrentLine();
    return line;
  }
  else
  {
    throw std::runtime_error("Could not open file");
  }

  return "";
}

/**
 * @brief Positions the file cursor to the specified line number.
 * @param file Reference to the input file stream.
 * @param num Line number to move the cursor to.
 * @return Reference to the modified input file stream.
 */
std::ifstream &FileLineReader::GotoLine(std::ifstream &file, unsigned int num)
{
  file.seekg(std::ios::beg);
  for (int i = 0; i < num - 1; ++i)
  {
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return file;
}

/**
 * @brief Determines the maximum number of lines in the given file.
 * @param _fileName The name of the file to analyze.
 * @return The maximum number of lines in the file.
 */
int FileLineReader::maxNumberOfLines(const std::string &_fileName)
{
  std::ifstream temp(_fileName);
  int lines_count = 0;
  std::string line;
  while (std::getline(temp, line))
  {
    lines_count++;
  }
  return lines_count;
}

/**
 * @brief Sets the file to be read.
 * @param _fileName The name of the file to be set.
 */
void FileLineReader::setFile(std::string _fileName)
{
  fileName = std::move(_fileName);
}

/**
 * @brief Checks if reading from the file is complete.
 * @return True if reading is complete, false otherwise.
 */
bool FileLineReader::getReadComplete()
{
  return this->readComplete;
}

/**
 * @brief Gets the current line number being read from the file.
 * @return The current line number.
 */
int FileLineReader::getCurrentLine()
{
  return this->currentLine;
}

/**
 * @brief Increments the current line number.
 */
void FileLineReader::incrementCurrentLine()
{
  currentLine++;
}

/**
 * @brief Overloaded stream insertion operator for output.
 * @param out Reference to the output stream.
 * @param flr Reference to the FileLineReader to be output.
 * @return Reference to the output stream.
 */
std::ostream &operator<<(std::ostream &out, const FileLineReader &flr)
{
  out << "Current file: " << flr.fileName << std::endl;
  return out;
}

/**
 * @brief Overloaded assignment operator for assigning the content of another
 *        FileLineReader instance.
 * @param other Reference to the FileLineReader to be copied.
 * @return Reference to the assigned FileLineReader.
 */
FileLineReader &FileLineReader::operator=(const FileLineReader &other)
{
  if (this == &other)
  {
    return *this;
  }

  this->fileName = other.fileName;
  this->readComplete = other.readComplete;

  return *this;
}
