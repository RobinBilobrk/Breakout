#pragma once

#include "SDL.h"
#include "SDL_image.h"


class Entity {

public:
	Entity(float p_x, float p_y, float p_currentFrameW, float p_currentFrameH);
	Entity(float p_x, float p_y, SDL_Texture* p_tex);
	Entity(float p_x, float p_y, SDL_Texture* p_tex, int hit_P, int score);
	float getX();
	float getY();
	bool getRender();
	int gethitscore();
	int getHitpoints();
	void setHitpoints();
	void setRender();
	void setX(float newX);
	void setY(float newY);
	void reset(float beginX, float beginY);
	SDL_Texture* getTexture();
	SDL_Rect getCurrentFrame(); 
	SDL_Rect getRectangle();
private:
	float x, y;
	int hitpoints, hitscore;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
	bool renderThis = true;

};