#include "RoomBuilder.h"
#include "_Room.h"
#include "declarations.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void RoomBuilder:: buildRoom(char filename[])
{
    //************* Read ***************

	// open file for reading
    char filepath[100] = "Maps/";
    strcat_s(filepath, filename);
    ifstream myfile(filepath);

    //check file not found
    if(!myfile){ 
		cout << "Room File " << filepath << " not found!\n";
		system("pause");
		exit(1);
	}

    //read width, height
     int mapWidth, mapHeight;
	myfile >> mapWidth >> mapHeight;
	myfile.ignore();
	_Room::currentRoom->initDimensionsAndCollisionSections(mapWidth, mapHeight);
	
	// read and build map
	for (int i=mapHeight-1; i>=0; i--){
	    string line;
	    getline(myfile, line);
	    for(int j = 0; j < mapWidth; j++){
		   char cha = line[j];
		   float x, y;
		   x = (float) j * TILE_WIDTH;
		   y = (float) i * TILE_HEIGHT;
		   _Room::currentRoom->createEntityFromChar(cha, x, y);
	    }

	}
     myfile.close();
}