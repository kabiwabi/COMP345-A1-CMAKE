#pragma once

#include <iostream>
#include <string>

#include "GameEngine.h"

/**
 * @brief Tests the various states of the game engine.
 *
 * Demonstrates and tests the different states the game can be in.
 * Calls various methods of the GameEngine based on the current state and user input.
 */
void testStartupPhase();

/**
 * @brief Tests the various states of the game engine.
 *
 * Demonstrates and tests the different states the game can be in.
 * Calls various methods of the GameEngine based on the current state and user input.
 */
void testGameStates();

/**
 * @brief Prints a message indicating that a given command is invalid.
 *
 * @param command The user's inputted command to be printed in the error message.
 */
void printInvalidCommand(const std::string& command);