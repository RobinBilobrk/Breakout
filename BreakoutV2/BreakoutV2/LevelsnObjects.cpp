#include "SDL.h"
#include <iostream>
#include "objects.h"
#include "tinyxml2.h"


using namespace std;
using namespace tinyxml2;

BricksnLevels::BricksnLevels(const char* filename ) {

	file.LoadFile(filename);
}


XMLElement* BricksnLevels::getLevelInfo() {
	
	XMLElement* currentElement = file.FirstChildElement();
	
	if (!currentElement) {
		return 0;
	}

	return currentElement;	
}

XMLElement* BricksnLevels::getBrickInfo(char brickID) {

	//cout << brickID;

	string currentID = string(1,brickID);

	XMLElement* currentElement = file.FirstChildElement("Level")->FirstChildElement("BrickTypes")->FirstChildElement();

	while (string(currentElement->Attribute("Id")) != currentID && currentElement->NextSiblingElement() != NULL) {

		currentElement = currentElement->NextSiblingElement();
	}

	if (currentElement == NULL) {

		cout << "Element is NULL" << endl;
	}
	return currentElement;

}

XMLElement* BricksnLevels::getLvlLayout() {

	XMLElement* currentElement = file.FirstChildElement("Level")->FirstChildElement("BrickLayout");


	cout << currentElement->GetText() << endl;

	return currentElement;
}

