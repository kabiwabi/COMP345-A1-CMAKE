#include <iostream>
#include <memory>

#include "Map/Map.h"

/**
 * @brief Test function to load and validate multiple map files.
 */
void testLoadMaps()
{

  // Available map files
  std::vector<std::string> map_files{
      "res/TestMap1_valid.map",
      "res/TestMap2_invalid.map",
      "res/TestMap3_invalid.map",
      "res/TestMap4_valid.map",
      "res/TestMap5_invalid_format.map"};

  // Mocking argc and argv
  int argc = 1;
  char *argv[] = {(char *)"-console"};

  // Let's load all the maps and check if they are valid.
  for (const std::string &map_file : map_files)
  {
    // Create a GameEngine instance for each map
    GameEngine gameEngine = GameEngine(argc, argv);
    auto map = gameEngine.getMap();

    // We make sure to catch our own std::runtime errors for invalid maps
    try
    {
      // Load the map using MapLoader
      MapLoader::load(map_file, map);

      // Check if the map is valid and print the result
      std::cout << "Map is valid: " << (map->validate() ? "True" : "False") << std::endl;
    }
    catch (const std::runtime_error &error)
    {
      // Handle runtime errors for invalid maps
      std::cout << "Map Format is Invalid: " << error.what() << std::endl;
    }
  }
}
