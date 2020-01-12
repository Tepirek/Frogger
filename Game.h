#pragma once
#include <stdio.h>
#include "SDL.h"

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

class Game {

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* screen;
	SDL_Surface* map;
	SDL_Surface* charset;
	SDL_Texture* texture;

public:
	int black, green, red, blue;
	Game();
	~Game();
	void init(const char* title, bool fullscreen);
	void handleEvents();
	void update(int l);
	void render();
	void clean();
	void drawMap();
	SDL_Surface* getScreen();
	void drawText(int x, int y, const char* text);
	void drawPixel(int x, int y, Uint32 color);
	void drawLine (int x, int y, int l, int dx, int dy, Uint32 color);
	void drawRectangle(int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
};

