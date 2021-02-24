#include "Entity.h"
#include "SDL.h"
#include "SDL_image.h"

Entity::Entity(float p_x, float p_y, SDL_Texture* p_tex) 
{
	x = p_x;
	y = p_y;
	tex = (p_tex);

	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 40;
	currentFrame.h = 5;
}

Entity::Entity(float p_x, float p_y, float p_currentFrameW, float p_currentFrameH) {

	x = p_x;
	y = p_y;

	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = p_currentFrameW;
	currentFrame.h = p_currentFrameH;

}

Entity::Entity(float p_x, float p_y, SDL_Texture* p_tex, int hit_P, int score) {

	x = p_x;
	y = p_y;
	tex = (p_tex);

	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 20;
	currentFrame.h = 5;

	hitpoints = hit_P;
	hitscore = score;

}

void Entity::setX(float newX) {

	x += newX;
}

void Entity::setY(float newY) {

	y += newY;

}


float Entity::getX()
{
	return x;
}

float Entity::getY()
{
	return y;
}

SDL_Texture* Entity::getTexture()
{
	return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;

}


SDL_Rect Entity::getRectangle() {

	SDL_Rect object;

	object.x = x;
	object.y = y;
	object.w = currentFrame.w *2.5;
	object.h = currentFrame.h;


	return object;
}


bool Entity::getRender() {



	return renderThis;
}

void Entity::setRender() {

	renderThis = false;
	
}

int Entity::gethitscore() {


	return hitscore;


}

void Entity::setHitpoints() {

	hitpoints -= 1;

}

int Entity::getHitpoints() {


	return hitpoints;

}

void Entity::reset(float beginX, float beginY) {

	x = beginX;
	y = beginY;

}