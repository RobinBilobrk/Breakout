#pragma once

#include "SDL.h"
#include "Entity.h"
#include <vector>

using namespace std;

class Windows
{

public:
	Windows(const char* tittle, int width, int height);
	void cleanWindow();
	void clear();
	void display();
	SDL_Rect drawTiles(int x, int y, int w, int h);
	void drawEntity(Entity& entity);
	void render(Entity& entity);
	void renderText(SDL_Rect whereSquare, SDL_Surface* whattorender);
	void renderNotSCale(Entity& entity);
	vector<Entity> drawLevel(int whichLevel);
	SDL_Texture* loadTexture(const char* filename);
private:
	SDL_Window* createdWindow;
	SDL_Renderer* windowRenderer;
	const char* levels[3] = {"Levels.xml","Level2.xml","level3.xml"};
};