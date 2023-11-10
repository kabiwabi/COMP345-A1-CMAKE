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
class ILoggable {
public:

    /**
 * @brief Converts the object to a loggable string.
 *
 * @return The loggable string representation.
 */
  virtual std::string stringToLog() = 0;

    /**
   * @brief Virtual destructor for ILoggable.
   */
  virtual ~ILoggable()= default;
};

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                ISubject
//
// ----------------------------------------------------------------------------------------------------------------

/**
 * @brief Interface for subjects (observables).
 */
class ISubject {
public:
   /**
   * @brief Virtual destructor for ISubject.
   */
    virtual ~ISubject() = default;

    /**
     * @brief Attaches an observer to the subject.
     *
     * @param observer The observer to attach.
     */
    virtual void attach(ILogObserver* observer) = 0;

    /**
     * @brief Detaches an observer from the subject.
     *
     * @param observer The observer to detach.
     */
    virtual void detach(ILogObserver* observer) = 0;

    /**
     * @brief Notifies all observers with the given loggable object.
     *
     * @param loggable The loggable object to notify observers about.
     */
    virtual void notify(ILoggable*) = 0;

    /**
     * @brief Resets the list of observers attached to the subject.
     */
    virtual void resetObservers() = 0;
};

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Subject
//
// ----------------------------------------------------------------------------------------------------------------

/**
 * @brief Concrete implementation of the subject (observable) interface.
 */
class Subject : ISubject {
private:
  std::vector<ILogObserver*> observers;
public:
   /**
   * @brief Default constructor for the Subject class.
   */
    Subject() = default;

    /**
     * @brief Virtual destructor for the Subject class.
     */
    ~Subject() override = default;

    /**
     * @brief Attaches an observer to the subject.
     *
     * @param observer The observer to attach.
     */
    void attach(ILogObserver* observer) override;

    /**
     * @brief Detaches an observer from the subject.
     *
     * @param observer The observer to detach.
     */
    void detach(ILogObserver* observer) override;

    /**
     * @brief Notifies all observers with the given loggable object.
     *
     * @param loggable The loggable object to notify observers about.
     */
    void notify(ILoggable*) override;

    /**
     * @brief Resets the list of observers attached to the subject.
     */
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
class ILogObserver {
public:
    /**
     * @brief Virtual destructor for ILogObserver.
     */
    virtual ~ILogObserver() = default;

    /**
     * @brief Updates the observer with the given loggable object.
     *
     * @param loggable The loggable object to update the observer with.
     */
    virtual void update(ILoggable*) = 0;
};


// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                LogObserver
//
// ----------------------------------------------------------------------------------------------------------------

/**
 * @brief Concrete implementation of the log observer interface.
 */
class LogObserver : ILogObserver {
private:
    // Object Owner
    GameEngine* game;

public:
    /**
     * @brief Constructor for the LogObserver class.
     *
     * @param game Pointer to the GameEngine.
     * @throw std::runtime_error if the provided GameEngine pointer is null.
     */
    explicit LogObserver(GameEngine*);

    /**
     * @brief Virtual destructor for the LogObserver class.
     */
    ~LogObserver() override = default;

    /**
     * @brief Copy constructor for the LogObserver class.
     *
     * @param observer Pointer to the LogObserver to be copied.
     */
    explicit LogObserver(LogObserver*);

    /**
     * @brief Updates the observer with the given loggable object.
     *
     * Appends the loggable information to the "gamelog.txt" file.
     *
     * @param loggable The loggable object to update the observer with.
     */
    void update(ILoggable*) override;

    /**
     * @brief Overloaded stream insertion operator for LogObserver.
     *
     * @param out The output stream.
     * @param log The LogObserver object.
     * @return The output stream.
     */
    friend std::ostream &operator << (std::ostream &out, const LogObserver &log);

    /**
     * @brief Copy assignment operator for the LogObserver class.
     *
     * @param other The LogObserver to copy from.
     * @return Reference to the current LogObserver.
     */
    LogObserver& operator=(const LogObserver &other);
};
