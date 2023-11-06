#include "CommandProcessingDriver.h"

/**
 * @brief Test function for command processing.
 *
 * This function tests the command processing functionality by either accepting commands from the console or reading from a file based on the command line arguments provided.
 * It creates instances of GameEngine, FileCommandProcessorAdapter, and CommandProcessor to manage the commands and their processing.
 *
 * @param argc The count of command line arguments.
 * @param argv The command line arguments array.
 */
void testCommandProcessor(int argc, char* argv[]) {
    // Initialize the game engine with command line arguments
    auto gameEngine = new GameEngine(argc, argv);

    // Loop control for console command input
    bool moreCommands = true;
    std::string moreCommandsDecision;

    // Adapter for processing file commands
    FileCommandProcessorAdapter adapter(gameEngine, argc, argv);

    // Processor for managing command input and execution
    CommandProcessor cpr = CommandProcessor(gameEngine, argc, argv);

    // Retrieve raw commands inputted
    auto inputCommandsRaw = cpr.getRawCommands();

    // Check for minimum number of arguments for mode selection
    if(inputCommandsRaw->size() < 2){
        std::cout << "You must choose between -console or -file <filename>" << std::endl;
        exit(0);
    }

    // Handle console command input
    if (inputCommandsRaw->at(1) == "-console"){
        do {
            cpr.getCommand();
            cpr.printCommandCollection(cpr.getCommandCollection());
            std::cout << "Do you want to enter a command? (y/n): ";
            getline(std::cin, moreCommandsDecision);
            std::cout << std::endl;
            if (!(moreCommandsDecision == "y")){
                moreCommands = false;
            }
        } while(moreCommands);

        // Handle file command input
    } else if (inputCommandsRaw->at(1) == "-file"){

        // Ensure a file name is provided
        if(inputCommandsRaw->size() < 3) {
            std::cout << "You must give a file as an argument" << std::endl;
            exit(0);
        }

        // Set the file for reading commands
        gameEngine->getFlir()->setFile(inputCommandsRaw->at(2));

        // Process commands from the file
        adapter.commandLineToFile(gameEngine->getFlir());

        // Read commands until the end of file
        while(!gameEngine->getFlir()->getReadComplete()){
            adapter.getCommand();
        }

        // Print out the processed commands
        adapter.printCommandCollection(adapter.getCommandCollection());

    } else {
        // Throw an error if the command line argument is invalid
        throw std::runtime_error("Invalid Command line arguments");
    }
}