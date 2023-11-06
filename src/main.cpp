#include "GameEngine/GameEngineDriver.h"
#include "Orders/OrdersDriver.h"
#include "GameEngine/Command/CommandProcessingDriver.h"
#include "Logger/LoggingObserverDriver.h"

using namespace std;

int main(int argc, char** argv)
{
//    testCommandProcessor(argc, argv);
//    testStartupPhase(argc, argv);
    testMainGameLoop(argc, argv);
//    testOrderExecution();
//    testLoggingObserver(argc, argv);
  return 0;
}

