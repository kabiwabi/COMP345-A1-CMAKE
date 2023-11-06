#include "FileLineReader.h"

/**
 * @brief Copy constructor for FileLineReader.
 *
 * @param flr The FileLineReader object to copy from.
 */
FileLineReader::FileLineReader(const FileLineReader &flr){
    fileName = flr.fileName;
    readComplete = flr.readComplete;
}

/**
 * @brief Reads a single line from the file.
 *
 * This function reads the next line from the file and advances the file pointer.
 * If the end of the file is reached, it sets the readComplete flag to true.
 *
 * @return std::string The line read from the file.
 * @throw std::runtime_error If the file cannot be opened.
 */
std::string FileLineReader::readLineFromFile(){

    std::ifstream fileInputStream(fileName);
    int maxLines = maxNumberOfLines(fileName);
    std::string line;
    
    if (fileInputStream.is_open() && !readComplete){
      GotoLine(fileInputStream, getCurrentLine());
      getline(fileInputStream, line);
      if (getCurrentLine() == maxLines){
        this->readComplete = true;
      }
      incrementCurrentLine();
      return line;
    } else {
      throw std::runtime_error("Could not open file");
    }
    
    return "";
}

/**
 * @brief Seeks to the specified line number in a file.
 *
 * @param file The file stream to manipulate.
 * @param num The line number to seek to.
 * @return std::ifstream& The file stream after seeking.
 */
std::ifstream& FileLineReader::GotoLine(std::ifstream& file, unsigned int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

/**
 * @brief Counts the number of lines in the file.
 *
 * @param _fileName The name of the file.
 * @return int The total number of lines in the file.
 */
int FileLineReader::maxNumberOfLines(const std::string& _fileName){
  std::ifstream temp(_fileName);
  int lines_count = 0;
  std::string line;
  while (std::getline(temp , line)){
    lines_count++;
  }
  return lines_count;
}

/**
 * @brief Sets the file to be read.
 *
 * @param _fileName The name of the file.
 */
void FileLineReader::setFile(std::string _fileName){
  fileName = std::move(_fileName);
}

/**
 * @brief Checks if the reading of the file is complete.
 *
 * @return true If all lines have been read.
 * @return false If there are still lines to be read.
 */
bool FileLineReader::getReadComplete(){
  return this->readComplete;
}

/**
 * @brief Gets the current line number being read from the file.
 *
 * @return int The current line number.
 */
int FileLineReader::getCurrentLine(){
  return this->currentLine;
}

/**
 * @brief Increments the counter for the current line number.
 */
void FileLineReader::incrementCurrentLine(){
  currentLine++;
}

/**
 * @brief Overloaded stream insertion operator for FileLineReader.
 *
 * @param out The ostream object.
 * @param flr The FileLineReader object whose state is to be output.
 * @return std::ostream& The ostream object with the FileLineReader state appended.
 */
std::ostream & operator << (std::ostream &out, const FileLineReader &flr)
{
    out << "Current file: " << flr.fileName << std::endl;
    return out;
}

/**
 * @brief Overloaded assignment operator for FileLineReader.
 *
 * @param other The FileLineReader object to assign from.
 * @return FileLineReader& The FileLineReader object after assignment.
 */
FileLineReader& FileLineReader::operator=(const FileLineReader &other) {
  if(this == &other){
    return *this;
  }

  this->fileName = other.fileName;
  this->readComplete = other.readComplete;

  return *this;
}