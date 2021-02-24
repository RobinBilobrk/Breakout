#pragma once

#include "tinyxml2.h"
#include "Entity.h"
#include "WindowClass.h"



using namespace tinyxml2;
using namespace std;

class BricksnLevels {

	

public:
	BricksnLevels(const char* filename);
	XMLElement* getLevelInfo();
	XMLElement* getBrickInfo(char brickID);
	XMLElement* getLvlLayout();
private:
	XMLDocument file;
	XMLElement* currentLevel;

};

