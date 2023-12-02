#include <cstring>
#include "GameEngine/GameEngineDriver.h"
#include "Orders/OrdersDriver.h"
#include "GameEngine/Command/CommandProcessingDriver.h"
#include "Logger/LoggingObserverDriver.h"
#include "GameEngine/TournamentDriver.h"
#include "Player/PlayerDriver.h"
#include "Player/PlayerStrategiesDriver.h"

using namespace std;

int main(int argc, char** argv)
{
    bool runTests = false;

    // Check if the -test argument is passed
    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-test") == 0)
        {
            runTests = true;
            break;
        }
    }

    if(runTests)
    {
        // Run the tests
        testTournament(argc, argv);
        testPlayerStrategies();
    }
    else
    {
        // Run the game normally
        auto gameEngine = GameEngine(argc, argv);
        gameEngine.startupPhase();
    }

    return 0;
}