#include "LogObserver.h"

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Subject - (Observable)
//
// ----------------------------------------------------------------------------------------------------------------

/**
 * @brief Attaches an observer to the subject.
 * @param observer The observer to attach.
 */
void Subject::attach(ILogObserver *observer)
{
  if (observer == nullptr)
  {
    throw std::runtime_error("Observer is null.");
  }
  observers.push_back(observer);
}

/**
 * @brief Detaches an observer from the subject.
 * @param observer The observer to detach.
 */
void Subject::detach(ILogObserver *observer)
{
  for (auto it = observers.begin(); it != observers.end(); it++)
  {
    if (*it == observer)
    {
      observers.erase(it);
      return;
    }
  }
}

/**
 * @brief Notifies all attached observers with an update from a loggable entity.
 * @param loggable The loggable entity.
 */
void Subject::notify(ILoggable *loggable)
{
  for (auto &observer : observers)
  {
    observer->update(loggable);
  }
}

/**
 * @brief Resets the list of observers.
 */
void Subject::resetObservers()
{
  this->observers = std::vector<ILogObserver *>();
}

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                LogObserver
//
// ----------------------------------------------------------------------------------------------------------------

/**
 * @brief Default constructor for LogObserver.
 * @param game The associated GameEngine.
 */
LogObserver::LogObserver(GameEngine *game)
    : game(game)
{
  if (game == nullptr)
  {
    throw std::runtime_error("LogObserver::Error | Cannot set observer Game Engine to null");
  }
}

/**
 * @brief Copy constructor for LogObserver.
 * @param observer The LogObserver to copy.
 */
LogObserver::LogObserver(LogObserver *observer)
{
  this->game = observer->game;
}

/**
 * @brief Updates the LogObserver with information from a loggable entity.
 * @param loggable The loggable entity.
 */
void LogObserver::update(ILoggable *loggable)
{
  std::fstream file;
  try
  {
    file.open("gamelog.txt", std::fstream::out | std::fstream::app);
    file << loggable->stringToLog();
    file << '\n';
  }
  catch (const std::fstream::failure &e)
  {
    std::cout << "Exception opening/writing to file" << std::endl;
  }
  file.close();
}

/**
 * @brief Overloaded stream insertion operator for LogObserver.
 * @param out The output stream.
 * @param log The LogObserver.
 * @return The output stream.
 */
std::ostream &operator<<(std::ostream &out, const LogObserver &log)
{
  out << "I am a LogObserver" << std::endl;
  return out;
}

/**
 * @brief Overloaded assignment operator for LogObserver.
 * @param other The LogObserver to copy.
 * @return A reference to the assigned LogObserver.
 */
LogObserver &LogObserver::operator=(const LogObserver &other)
{
  if (this == &other)
  {
    return *this;
  }

  this->game = other.game;

  return *this;
}
