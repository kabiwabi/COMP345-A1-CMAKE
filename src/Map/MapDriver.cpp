#include "Map.h"
#include <iostream>
#include <filesystem>
#include <string>


using namespace std;


void testLoadMap(string path,string fileName)
{
    auto* loader = new MapLoader();
    Map* map = loader->loadMap(path + fileName);

    if(map->validate())
    {
        cout<<fileName<<" is valid"<<endl;
    }
    else
    {
        cout<<fileName<<" is invalid"<<endl;
    }
}

void testLoadMaps() {

    // test commit
    // All map files in the maps directory
    vector<string> files = {"Africa.map", "Alberta.map", "Anatomy.map", "AlbertaInvalid.map"};
    string path;
    // change to your absolute path when running
    path = R"(C:\Users\Wang\CLionProjects\A1Cmake\src\maps\)";

    testLoadMap(path, files[0]);
    testLoadMap(path, files[1]);
    testLoadMap(path, files[2]);
    testLoadMap(path, files[3]);
}