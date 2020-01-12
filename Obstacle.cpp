#include "Obstacle.h"

Obstacle::Obstacle(float x, float y, float w, float h, float s, const char* path) {
	positionX = x;
	positionY = y;
	width = w;
	height = h;
	speed = s;
	if ((image = SDL_LoadBMP(path)) == NULL) {
		printf("SDL_LoadBMP(%s) error: %s\n", path, SDL_GetError());
	}
}

Obstacle::~Obstacle() {

}

float Obstacle::getX() {
	return positionX;
}

float Obstacle::getY() {
	return positionY;
}

float Obstacle::getWidth() {
	return width;
}

float Obstacle::getSpeed() {
	return speed;
}

void Obstacle::draw(SDL_Surface* screen) {
	SDL_Rect destination;
	destination.x = positionX;
	destination.y = positionY;
	SDL_BlitSurface(image, NULL, screen, &destination);
}

void Obstacle::move() {
	if (speed > 0) {
		if (positionX <= 640 * 2 + width) positionX += speed;
		else positionX = -width;
	}
	else if (speed < 0) {
		if (positionX >= -width) positionX += speed;
		else positionX = 640 * 2;
	}
}