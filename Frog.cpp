#include "Frog.h"

#define STARTING_POSITION_X 288
#define STARTING_POSITION_Y 384

Frog::Frog(int l) {
	positionX = STARTING_POSITION_X;
	positionY = STARTING_POSITION_Y;
	width = 32;
	height = 32;
	speed = 32;
	lives = l;
	int base[6] = { 0 };
	if ((image = SDL_LoadBMP("images/frog2.bmp")) == NULL) {
		printf("image = SDL_LoadBMP(\"images/frog2.bmp\") error: %s\n", SDL_GetError());
	}
}

Frog::~Frog() {

}

void Frog::draw(SDL_Surface* screen) {
	SDL_Rect destination;
	destination.x = positionX;
	destination.y = positionY;
	SDL_BlitSurface(image, NULL, screen, &destination);
}

void Frog::drawBase(SDL_Surface* screen) {
	for (int i = 0; i < 6; i++) {
		if (base[i]) {
			SDL_Rect destination;
			destination.x = 64 + (i * 96);
			destination.y = 64;
			SDL_BlitSurface(image, NULL, screen, &destination);
		}
	}
}

void Frog::move() {
	SDL_Event event; 
	const Uint8* state = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) {
				if (positionY - speed >= 64) positionY -= speed;
			}
			if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) {
				if (positionY + speed <= 384) positionY += speed;
			}
			if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
				if (positionX - speed >= 0) positionX -= speed;
			}
			if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) {
				if (positionX + speed <= 624) positionX += speed;
			}
		}
	}
}

void Frog::move(float s) {
	if (positionX < -width || positionX > 640) reset();
	else positionX += s;
}

bool Frog::onRiver() {
	return (positionY >= 96 && positionY <= 192);
}

void Frog::reset() {
	positionX = STARTING_POSITION_X;
	positionY = STARTING_POSITION_Y;
	lives--;
}

bool Frog::isAlive() {
	return (lives > 0);
}

int Frog::getLives() {
	return lives;
}

bool Frog::collision(Obstacle* other) {
	return !(positionX + width <= other->getX() || positionX >= other->getX() + other->getWidth() || positionY + 32 <= other->getY() || positionY >= other->getY() + 32);
}

void Frog::touchdown() {
	if (positionY == 64) {
		for (int i = 0; i < 6; i++) {
			if (positionX >= 64 + (i * 96) - 8 && positionX <= 96 + (i * 96) + 8 && !base[i]) {
				base[i] = 1;
				positionX = STARTING_POSITION_X;
				positionY = STARTING_POSITION_Y;
				return;
			}
		}
		for (int i = 0; i < 6; i++) {
			if (positionX >= 64 + (i * 96) - 8 && positionX <= 96 + (i * 96) + 8 && !base[i]) {
				base[i] = 1;
				positionX = STARTING_POSITION_X;
				positionY = STARTING_POSITION_Y;
				return;
			}
			else {
				reset();
				return;
			}
		}
	}
}

bool Frog::endGame() {
	int counter = 0;
	for (int i = 0; i < 6; i++) {
		if (base[i]) counter++;
	}
	if (counter == 6) return true;
	else return false;
}