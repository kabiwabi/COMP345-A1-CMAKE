#include "TournamentDriver.h"
#include "GameEngine.h"
#include <iostream>

/**
 * @brief Tests the tournament mode of the game engine.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 */
void testTournament(int argc, char *argv[])
{
  auto gameEngine = new GameEngine(argc, argv);
  std::string option = "1";

  // Prompt user for tournament mode selection
  std::cout << "Do you want to enter tournament mode via console or via file?" << std::endl;
  std::cout << "1. Console" << std::endl;
  std::cout << "2. File" << std::endl;
  std::cout << "-> ";
  getline(std::cin, option);

  if (option == "1")
  {
    // Start the tournament in console mode
    gameEngine->startupPhase();
  }
  else if (option == "2")
  {
    // Prompt user for the file name and start the tournament in file mode
    std::string fileName;
    std::cout << "Enter the file name: ";
    std::cin >> fileName;
    gameEngine->getCommandProcessor()->FileTournamentFunctionInput(fileName);
  }
  else
  {
    // Exit the program if an invalid option is selected
    exit(0);
  }
}
