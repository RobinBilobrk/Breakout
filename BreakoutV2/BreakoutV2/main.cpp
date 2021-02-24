#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "WindowClass.h"
#include "objects.h"
#include <vector>
#include "time.h"
#include "SDL_ttf.h"
#include <string>
using namespace std;

void selectLevel(int levelnum, Windows &thiswindow);
SDL_Surface* updateScore(int score, TTF_Font* font, SDL_Color color);
SDL_Surface* updateLife(int life, TTF_Font* font, SDL_Color color);
vector<Entity> actualLevel;

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		cout << "SDL Initialization has failed" << SDL_GetError() << endl;
	}

	if (SDL_Init(SDL_INIT_AUDIO) > 0) {
		 
		cout << "SDL audio has failed" << SDL_GetError() << endl;
	}
	TTF_Init();

	SDL_AudioSpec wavSpec, wavSpec2;
	Uint32 wavLength;
	Uint8* wavBuffer;

	SDL_LoadWAV("pop.wav", &wavSpec, &wavBuffer, &wavLength);
	SDL_LoadWAV("explosion.wav", &wavSpec2, &wavBuffer, &wavLength);

	SDL_AudioDeviceID firstSound = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
	SDL_AudioDeviceID secondSound = SDL_OpenAudioDevice(NULL, 0, &wavSpec2, NULL, 0);

	float board_x = 640;
	float board_y = 670;
	float ball_x = 640;
	float ball_y = 360;
	float ball_W = 5;
	float ball_H = 5;
	float pillar1_X = 40;
	float pillar1_Y = 10;
	float pillar2_X = 1220;
	float pillar2_Y = 10;
	float pillar_w = 10;
	float pillar_h = 700;
	bool pillar1set = false;
	bool pillar2set = false;
	bool setLevel = false;
	float directionY = 0.25;
	float directionX = 0.25;
	int score = 0;
	int brickCount = 0;
	int life = 3;
	int level = 0;
	Windows newWindow("Breakout", 1280, 720);
	SDL_bool collision1, collision, collision2, collision3, collision4, collision5;
	SDL_Rect ballRect, boardRect, checkRect, pillar1, pillar2, scorerect, liferect;
	SDL_Texture* boards = newWindow.loadTexture("Boards.bmp");
	SDL_Texture* pillars = newWindow.loadTexture("BGrass.bmp");
	Entity board(board_x, board_y, boards);
	Entity ball(ball_x, ball_y, ball_W, ball_H);
	scorerect.x = 55; scorerect.y = 660; scorerect.w = 100; scorerect.h = 50;
	liferect.x = 160; liferect.y = 660; liferect.w = 100; liferect.h = 50;

	TTF_Font* onlyfont = TTF_OpenFont("OpenSans-Bold.ttf", 24);
	SDL_Color fontColor = {225, 225, 225};
	

	selectLevel(level, newWindow);

	bool gameIsRUnning = true;

	SDL_Event event;

	while (gameIsRUnning) {

		if (brickCount > 98) {

			level += 1;
			brickCount = 0;
			selectLevel(level, newWindow);
		}

		if (life <=0) {

			gameIsRUnning = false;

		}

		SDL_Surface* scoreSurface = updateScore(score, onlyfont, fontColor);
		SDL_Surface* livesSurface = updateLife(life, onlyfont, fontColor);

		ball.setY(directionY);
		ball.setX(directionX);
		ballRect = ball.getRectangle();
		boardRect = board.getRectangle();
		collision1 = SDL_HasIntersection(&ballRect, &boardRect);
		
		if (pillar1set) {
			collision2 = SDL_HasIntersection(&ballRect, &pillar1);
			collision4 = SDL_HasIntersection(&pillar1, &boardRect);

			if (collision2) {

				directionX = 0.25;
				int success = SDL_QueueAudio(firstSound, wavBuffer, wavLength);
				SDL_PauseAudioDevice(firstSound, 0);
			}

			if (collision4) {

				board.reset(41, 670);
				int success = SDL_QueueAudio(firstSound, wavBuffer, wavLength);
				SDL_PauseAudioDevice(firstSound, 0);
			}

		}

		if (pillar2set) {
			collision3 = SDL_HasIntersection(&ballRect, &pillar2);
			collision5 = SDL_HasIntersection(&pillar2, &boardRect);
			if (collision3) {

				directionX = -0.25;
				int success = SDL_QueueAudio(firstSound, wavBuffer, wavLength);
				SDL_PauseAudioDevice(firstSound, 0);
			}

			if (collision5) {

				board.reset(1120, 670);
				int success = SDL_QueueAudio(firstSound, wavBuffer, wavLength);
				SDL_PauseAudioDevice(firstSound, 0);

			}
		}



		if (ball.getRectangle().y < 5) {

			directionY = 0.25;
		}

		if (ball.getRectangle().y > 700) {
			ball.reset(ball_x, ball_y);
			life -= 1;
		}


		if (collision1) {
			directionY *= -1;
			int success = SDL_QueueAudio(firstSound, wavBuffer, wavLength);
			SDL_PauseAudioDevice(firstSound, 0);
		}


		
		//ball.setY(direction*(-1));
		
		
		for (int i = 0; i < actualLevel.size(); i++) {

			checkRect = actualLevel[i].getRectangle();

			collision = SDL_HasIntersection(&checkRect, &ballRect);

			if (collision && actualLevel[i].getRender()) {
				
				directionY = 0.25;

				actualLevel[i].setHitpoints();

				int success = SDL_QueueAudio(firstSound, wavBuffer, wavLength);
				SDL_PauseAudioDevice(firstSound, 0);

				if (actualLevel[i].getHitpoints() == 0) {

					actualLevel[i].setRender();
					score += actualLevel[i].gethitscore();
					brickCount += 1;

					int success = SDL_QueueAudio(secondSound, wavBuffer, wavLength);
					SDL_PauseAudioDevice(firstSound, 0);

				}

			}

		}



		while (SDL_PollEvent(&event)) {

			switch (event.type) {
			case SDL_QUIT:
				gameIsRUnning = false; break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_LEFT: board.setX(-15);  break;
				case SDLK_RIGHT:board.setX(15);  break;
				case SDLK_k: brickCount = 100; break;
				}
			}
		}


		newWindow.clear();
		newWindow.render(board);
		newWindow.drawEntity(ball);
		newWindow.renderText(scorerect, scoreSurface);
		newWindow.renderText(liferect, livesSurface);

		if (!pillar1set && !pillar2set) {

			pillar1 = newWindow.drawTiles(pillar1_X, pillar1_Y, pillar_w, pillar_h);
			pillar2 = newWindow.drawTiles(pillar2_X, pillar2_Y, pillar_w, pillar_h);

			pillar1set = true;
			pillar2set = true;
		}

		newWindow.drawTiles(pillar1_X, pillar1_Y, pillar_w, pillar_h);
		newWindow.drawTiles(pillar2_X, pillar2_Y, pillar_w, pillar_h);

		

			for (int i = 0; i < actualLevel.size(); i++) {


				if (actualLevel[i].getRender()) {

					newWindow.render(actualLevel[i]);

				}


			}
		


		newWindow.display();

		//cout << timess::recordTime() << endl;
	}

	newWindow.cleanWindow();

	return 0;
}


void selectLevel(int levelnum, Windows& thiswindow) {

	 actualLevel = thiswindow.drawLevel(levelnum);

}

SDL_Surface* updateScore(int score, TTF_Font* onlyfont, SDL_Color fontColor) {

	string scorestring = "Score: " + to_string(score);
	const char* scoreChar = scorestring.c_str();

	SDL_Surface* scoreSuface = TTF_RenderText_Solid(onlyfont, scoreChar, fontColor);

	return scoreSuface;
}

SDL_Surface* updateLife(int life, TTF_Font* onlyfont, SDL_Color fontColor) {

	string scorestring = "Lives: " + to_string(life);
	const char* scoreChar = scorestring.c_str();

	SDL_Surface* scoreSuface = TTF_RenderText_Solid(onlyfont, scoreChar, fontColor);

	return scoreSuface;
}

