#include "LogObserver.h"

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Subject - (Observable)
//
// ----------------------------------------------------------------------------------------------------------------


/**
 * @brief Attaches an observer to the subject.
 *
 * @param observer The observer to attach.
 * @throw std::runtime_error if the observer is null.
 */
void Subject::attach(ILogObserver* observer) {
  if(observer == nullptr){ throw std::runtime_error("Observer is null."); }
  observers.push_back(observer);
}

/**
 * @brief Detaches an observer from the subject.
 *
 * @param observer The observer to detach.
 */
void Subject::detach(ILogObserver* observer) {
  for(auto it = observers.begin(); it != observers.end(); it++){
    if(*it == observer){
      observers.erase(it);
      return;
    }
  }
}

/**
 * @brief Notifies all observers with the given loggable object.
 *
 * @param loggable The loggable object to notify observers about.
 */
void Subject::notify(ILoggable* loggable) {
  for(auto& observer : observers){
    observer->update(loggable);
  }
}

/**
 * @brief Resets the list of observers attached to the subject.
 */
void Subject::resetObservers() {
  this->observers = std::vector<ILogObserver*>();
}

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                LogObserver
//
// ----------------------------------------------------------------------------------------------------------------

/**
 * @brief Default constructor for the LogObserver class.
 *
 * @param game Pointer to the GameEngine.
 * @throw std::runtime_error if the provided GameEngine pointer is null.
 */
LogObserver::LogObserver(GameEngine* game)
        :game(game)
{
    if(game == nullptr){throw std::runtime_error("LogObserver::Error | Cannot set observer Game Engine to null");}
}

/**
 * @brief Copy constructor for the LogObserver class.
 *
 * @param observer Pointer to the LogObserver to be copied.
 */
LogObserver::LogObserver(LogObserver *observer) {
    this->game = observer->game;
}

/**
 * @brief Updates the observer with the given loggable object.
 *
 * Appends the loggable information to the "gamelog.txt" file.
 *
 * @param loggable The loggable object to update the observer with.
 */
void LogObserver::update(ILoggable* loggable) {
    std::fstream file;
    try {
        file.open("gamelog.txt", std::fstream::out | std::fstream::app);
        file << loggable->stringToLog();
        file << '\n';
    }
    catch(const std::fstream::failure& e){
        std::cout << "Exception opening/writing to file" << std::endl;
    }
    file.close();
}

/**
 * @brief Overloaded stream insertion operator for LogObserver.
 *
 * @param out The output stream.
 * @param log The LogObserver object.
 * @return The output stream.
 */
std::ostream& operator << (std::ostream &out, const LogObserver &log)
{
  out << "I am a LogObserver" << std::endl;
  return out;
}

/**
 * @brief Copy assignment operator for the LogObserver class.
 *
 * @param other The LogObserver to copy from.
 * @return Reference to the current LogObserver.
 */
LogObserver& LogObserver::operator=(const LogObserver &other){
  if(this == &other){
    return *this;
  }

  this->game = other.game;

  return *this;
}

