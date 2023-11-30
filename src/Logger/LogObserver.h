#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>

class ILogObserver;
class GameEngine;

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Loggable
//
// ----------------------------------------------------------------------------------------------------------------

/**
 * @brief Interface for objects that can be logged.
 */
class ILoggable
{
public:
  virtual std::string stringToLog() = 0;
  virtual ~ILoggable() = default;
};

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                ISubject
//
// ----------------------------------------------------------------------------------------------------------------

/**
 * @brief Interface for the subject in the observer pattern.
 */
class ISubject
{
public:
  virtual ~ISubject() = default;
  virtual void attach(ILogObserver *observer) = 0;
  virtual void detach(ILogObserver *observer) = 0;
  virtual void notify(ILoggable *) = 0;
  virtual void resetObservers() = 0;
};

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Subject
//
// ----------------------------------------------------------------------------------------------------------------

/**
 * @brief Concrete implementation of the subject in the observer pattern.
 */
class Subject : ISubject
{
private:
  std::vector<ILogObserver *> observers;

public:
  Subject() = default;
  ~Subject() override = default;

  void attach(ILogObserver *observer) override;
  void detach(ILogObserver *observer) override;
  void notify(ILoggable *) override;
  void resetObservers() override;
};

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                ILogObserver
//
// ----------------------------------------------------------------------------------------------------------------

/**
 * @brief Interface for log observers.
 */
class ILogObserver
{
public:
  virtual ~ILogObserver() = default;
  virtual void update(ILoggable *) = 0;
};

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                LogObserver
//
// ----------------------------------------------------------------------------------------------------------------

/**
 * @brief Concrete implementation of a log observer.
 */
class LogObserver : ILogObserver
{
private:
  // Object Owner
  GameEngine *game;

public:
  // Constructors
  explicit LogObserver(GameEngine *);
  ~LogObserver() override = default;
  explicit LogObserver(LogObserver *);

  void update(ILoggable *) override;

  // Stream Operator
  friend std::ostream &operator<<(std::ostream &out, const LogObserver &log);

  // Assignment Operator
  LogObserver &operator=(const LogObserver &other);
};
