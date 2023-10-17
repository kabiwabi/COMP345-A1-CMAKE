#include <iostream>
#include <fstream>

#include "CommandProcessingDriver.h"
#include "CommandProcessing.h"

using namespace std;

/**
 * @brief Tests the Command Processor.
 */
void testCommandProcessor(){

    // Create test Command file.
    string filename = "cmdTestFile.txt";
    fstream cmdFile(filename);
    cmdFile << "loaDmap fakemap.map\n";
    cmdFile << "validatemap\n";
    cmdFile << "addplayer joe\n";
    cmdFile << "addplayer\n";
    cmdFile << "gamestart\n";
    cmdFile << "replay\n";
    cmdFile << "quit\n";
    cmdFile.close();

    GameEngineState states[7]={GE_Start,GE_Map_Loaded,GE_Map_Validated,GE_Players_Added,GE_Players_Added,GE_Win,GE_Map_Validated};

    // Command Processors
    Command* cmd;
    CommandProcessor* consoleCmdProc = new CommandProcessor();
    CommandProcessor* fileCmdProc = new FileCommandProcessorAdapter(filename);

    // Test File Command Processor
    cout << "TESTING COMMAND PROCESSOR FROM FILE" << endl;
    cout << "====================================="<< endl;

    for(int i = 0; i<7; i++){
        cout << "Getting Command from file:" << endl;
        cmd = fileCmdProc->getCommand();
        cout << *cmd << endl;
        cout << "Is command valid for game engine state #"+to_string((states[i]))+": "+(CommandProcessor::validate(*cmd,states[i])?"True":"False") << endl;
        cout << "---------------------------------------------------------"<<endl;
    }

    // Test Console Command Processor
    cout << "TESTING COMMAND PROCESSOR FROM CONSOLE" << endl;
    cout << "====================================="<< endl;

    for(int i = 0; i<7; i++){
        cout << "Getting Command from (state #"+to_string((states[i]))+"):" << endl;
        cmd = consoleCmdProc->getCommand();
        cout << *cmd << endl;
        cout << "Is command valid for game engine state #"+to_string((states[i]))+": "+(CommandProcessor::validate(*cmd,states[i])?"True":"False") << endl;
        cout << "---------------------------------------------------------"<<endl;
    }

    delete fileCmdProc;
    delete consoleCmdProc;
}