#pragma once
#include <stdio.h>
#include "SDL.h"

class Obstacle {

	float positionX;
	float positionY;
	float width;
	float height;
	float speed;
	SDL_Surface* image;

public:
	Obstacle(float x, float y, float w, float h, float s, const char* path);
	~Obstacle();

	float getX();
	float getY();
	float getWidth();
	float getSpeed();

	void draw(SDL_Surface* screen);
	void move();
};

