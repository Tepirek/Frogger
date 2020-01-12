#pragma once
#include <stdio.h>
#include "SDL.h"
#include "Obstacle.h"

class Frog {

	float positionX;
	float positionY;
	float width;
	float height;
	float speed;
	int lives;
	int base[6];
	SDL_Surface* image;

public:
	Frog(int l);
	~Frog();
	void draw(SDL_Surface* screen);
	void drawBase(SDL_Surface* screen);
	void move();
	void move(float s);
	bool onRiver();
	void reset();
	bool isAlive();
	int getLives();
	bool collision(Obstacle* other);
	bool touchdown();
	bool endGame();
};

