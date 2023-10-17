#include "Map/MapDriver.h"
#include "GameEngine/GameEngineDriver.h"
#include "Orders/OrdersDriver.h"
#include "Cards/CardsDriver.h"
#include "Player/PlayerDriver.h"
#include "CommandProcessing/CommandProcessingDriver.h"
#include <regex>
using namespace std;

int main(int argc, char** argv)
{
    bool runTests = false;
    bool useFileCmd = false;
    string cmdFilename = "";

    for (int i = 0; i < argc; ++i) {
        if (regex_match((std::string)argv[i],regex ("^-[tT][eE][sS][tT]\\s*$")))
            runTests = true;
        if (regex_match((std::string)argv[i],regex ("^-[fF][iI][lL][eE]\\s*$"))){
            useFileCmd=true;
            cmdFilename = ((std::string)argv[i+1]);
        }
    }


    if(runTests){
        testCommandProcessor();
        testLoadMaps();
        testGameStates();
        testOrdersLists();
        testCards();
        testPlayers();
    }

    return 0;
}

