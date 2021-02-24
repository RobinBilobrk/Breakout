#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "WindowClass.h"
#include "Entity.h"
#include "objects.h"
#include <vector>
#include <sstream>

using namespace std;


Windows::Windows(const char* tittle, int width, int height)
	:createdWindow(NULL), windowRenderer(NULL)
{

	createdWindow = SDL_CreateWindow(tittle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);


	if (createdWindow == NULL) {

		cout << "WIndow failed" << SDL_GetError() << endl;
	
	}

	windowRenderer = SDL_CreateRenderer(createdWindow, -1, SDL_RENDERER_ACCELERATED);

}


void Windows::cleanWindow() {


	SDL_DestroyWindow(createdWindow);

}

void Windows::clear() {

	SDL_RenderClear(windowRenderer);

}

void Windows::display() {

	SDL_RenderPresent(windowRenderer);
}

void Windows::renderText(SDL_Rect whereSquare, SDL_Surface* whattorender) {

	SDL_Rect where = whereSquare;
	SDL_Texture* squareTex = SDL_CreateTextureFromSurface(windowRenderer, whattorender);

	SDL_RenderCopy(windowRenderer, squareTex, NULL, &where);


}

void Windows::render(Entity& entity)
{

	SDL_Rect src;

	src.x = entity.getCurrentFrame().x;
	src.y = entity.getCurrentFrame().y;
	src.w = entity.getCurrentFrame().w * 2.7;
	src.h = entity.getCurrentFrame().h * 2.7;

	SDL_Rect dst;

	dst.x = entity.getX();
	dst.y = entity.getY();
	dst.w = entity.getCurrentFrame().w * 2.7 ;
	dst.h = entity.getCurrentFrame().h * 2.7 ;


	SDL_RenderCopy(windowRenderer, entity.getTexture(), &src, &dst);


}

void Windows::renderNotSCale(Entity& entity) {

	SDL_Rect src;

	src.x = entity.getCurrentFrame().x;
	src.y = entity.getCurrentFrame().y;
	src.w = entity.getCurrentFrame().w ;
	src.h = entity.getCurrentFrame().h ;

	SDL_Rect dst;

	dst.x = entity.getX();
	dst.y = entity.getY();
	dst.w = entity.getCurrentFrame().w ;
	dst.h = entity.getCurrentFrame().h ;


	SDL_RenderCopy(windowRenderer, entity.getTexture(), &src, &dst);


}

SDL_Rect Windows::drawTiles(int x, int y, int w, int h) {

	SDL_Rect pillar;

	pillar.x = x;
	pillar.y = y;
	pillar.w = w;
	pillar.h = h;

	SDL_SetRenderDrawColor(windowRenderer, 100, 100, 100, 255);
	SDL_RenderFillRect(windowRenderer, &pillar);
	SDL_SetRenderDrawColor(windowRenderer, 0, 0, 0, 150);

	return pillar;
}

SDL_Texture* Windows::loadTexture(const char* filename) {

	SDL_Surface* image = SDL_LoadBMP(filename);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(windowRenderer, image);

	//texture = IMG_LoadTexture(windowRenderer, filename);

	if (texture == NULL) {

		cout << "texture failed" <<SDL_GetError() << endl;

	}

	

	return texture;
}

vector<Entity> Windows::drawLevel(int whichlevel) {

	bool newrow = true;

	vector<Entity> LevelLayout;
	cout << levels[whichlevel];

	BricksnLevels newLevel(levels[whichlevel]);

	XMLElement* layout = newLevel.getLvlLayout();

	string level = string(layout->GetText());

	float x = 55;
	float y = 100;

	for (int i = 0; i < level.size(); i++) {

		int b = i + 1;

		if (!isspace(level[i])) {

			XMLElement* currentBrick = newLevel.getBrickInfo(level[i]);		
			//cout << level[i];
			//cout << currentBrick->Attribute("Id") << endl;

			int hits = stoi(string(currentBrick->Attribute("Hitpoints")));
			int score = stoi(string(currentBrick->Attribute("BreakScore")));

			Entity tile(x, y, loadTexture(currentBrick->Attribute("Texture")), hits, score);

			LevelLayout.push_back(tile);

			x += 58;

			newrow = false;
		}

		if (level[b]) {

			if (isspace(level[i]) && isspace(level[b]) && newrow == false) {

				x = 55;
				y += 20;
				newrow = true;
				//cout << "new row happened";
			}
		}
	}
	return LevelLayout;
}


void Windows::drawEntity(Entity& entity) {

	SDL_Rect ball;


	ball.x = entity.getX();
	ball.y = entity.getY();
	ball.w = entity.getCurrentFrame().w;
	ball.h = entity.getCurrentFrame().h;

	SDL_SetRenderDrawColor(windowRenderer, 200, 200, 100, 255);
	SDL_RenderFillRect(windowRenderer, &ball);
	SDL_SetRenderDrawColor(windowRenderer, 0, 0, 0, 255);



}