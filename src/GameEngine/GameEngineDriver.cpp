#include "GameEngineDriver.h"
#include "GameEngine.h"

/**
 * @brief Tests the game's startup phase by demonstrating the correct implementation of initial setup steps.
 */
void testStartupPhase() {
    GameEngine gameEngine;
    gameEngine.startupPhase();
}

/**
 * @brief Print an error message for an invalid command.
 *
 * @param command The incorrect command entered by the user.
 */
void printInvalidCommand(const std::string& command){
  std::cout << "Incorrect Command: \"" << command << "\". Please input a correct command." << std::endl;
}


/**
 * @brief Test function to demonstrate the game state transitions.
 *
 * This function simulates the various states of the game engine and the transitions
 * between them based on user input.
 */
void testGameStates(){
  /// Creates an instance of game_engine
  GameEngine gameEngine;
  /// Get user input (a command)
  std::string input;
  /// Game runs while true
  while(true){
    std::cout << "Current Game State: " << gameEngine.getCurrentStateToString() << std::endl;
    std::cout << "Please enter an action: ";
    std::cin >> input;

    switch(gameEngine.getCurrentState()){
      case GE_Start:
        if(input == "loadmap"){ gameEngine.setCurrentState(GameEngineState::GE_Map_Loaded); }
        else { printInvalidCommand(input); }
        break;
      case GE_Map_Loaded:
        if(input == "loadmap"){ continue; }
        else if(input == "validatemap"){ gameEngine.setCurrentState(GameEngineState::GE_Map_Validated); }
        else { printInvalidCommand(input); }
        break;
      case GE_Map_Validated:
        if(input == "addplayer"){ gameEngine.setCurrentState(GameEngineState::GE_Players_Added); }
        else { printInvalidCommand(input); }
        break;
      case GE_Players_Added:
        if(input == "addplayer"){ continue; }
        else if(input == "assigncountries"){ gameEngine.setCurrentState(GameEngineState::GE_Reinforcement); }
        else { printInvalidCommand(input); }
        break;
      case GE_Reinforcement:
        if(input == "issueorder"){ gameEngine.setCurrentState(GameEngineState::GE_Issue_Orders); }
        else { printInvalidCommand(input); }
        break;
      case GE_Issue_Orders:
        if(input == "issueorder"){ continue; }
        else if(input == "endissueorders"){ gameEngine.setCurrentState(GameEngineState::GE_Execute_Orders); }
        else { printInvalidCommand(input); }
        break;
      case GE_Execute_Orders:
        if(input == "execorder"){ continue; }
        else if(input == "execorders"){ gameEngine.setCurrentState(GameEngineState::GE_Reinforcement); }
        else if(input == "win"){ gameEngine.setCurrentState(GameEngineState::GE_Win); }
        else { printInvalidCommand(input); }
        break;
      case GE_Win:
        if(input == "play"){ gameEngine.setCurrentState(GameEngineState::GE_Start); }
        else if(input == "end"){ return; }
        else { printInvalidCommand(input); }
        break;
    }
    std:: cout << "------------------------------" << std::endl;
  }
}
