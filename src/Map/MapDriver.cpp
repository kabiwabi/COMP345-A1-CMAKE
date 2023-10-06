#include <iostream>
#include <memory>

#include "Map/Map.h"

/**
 * @brief Tests the loading of various map files and validates them.
 *
 * Loads a set of predefined map files, both valid and invalid.
 * For each map file, it checks the validity and reports the results.
 * If a map file is in an invalid format or has errors, it catches the error and displays a message.
 */
void testLoadMaps() {

  std::vector<std::string> map_files {
    "map_resources/Africa.map",
    "map_resources/Alberta.map",
    "map_resources/AlbertaInvalid.map",
    "map_resources/Anatomy.map",
    "map_resources/TestMap1_valid.map",
    "map_resources/TestMap2_invalid.map",
    "map_resources/TestMap3_invalid.map",
    "map_resources/TestMap4_valid.map",
    "map_resources/TestMap5_invalid_format.map",
  };
  for(const std::string& p : map_files){
    GameEngine gameEngine = GameEngine();
    auto map = gameEngine.getMap();
    try {
      MapLoader::load(p, map);
      std::cout << "Map is valid: " << (map->validate() ? "True" : "False") << std::endl;
    } catch (const std::runtime_error& error) {
      std::cout << "Map Format is Invalid: " << error.what() << std::endl;
    }
  }
}
