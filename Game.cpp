#include "Game.h"

Game::Game() {
	window = nullptr;
	renderer = nullptr;
	screen = nullptr;
	map = nullptr;
	charset = nullptr;
	texture = nullptr;
	black = 0;
	green = 0;
	red = 0;
	blue = 0;
}

Game::~Game() {

}

void Game::init(const char* title, bool fullscreen) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init(SDL_INIT_EVERYTHING) error: %s\n", SDL_GetError());
		return;
	}
	int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
	if ((window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, flags)) == NULL) {
		printf("SDL_CreateWindow(%s, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_HEIGHT, SCREEN_WIDTH, flags) error: %s\n", title, SDL_GetError());
		return;
	}
	if ((renderer = SDL_CreateRenderer(window, -1, 0)) == NULL) {
		printf("SDL_CreateRenderer(window, -1, 0) error: %s\n", SDL_GetError());
		return;
	}
	if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear") == SDL_FALSE) {
		printf("SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, \"linear\") error: %s\n", SDL_GetError());
	};
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0) {
		printf("SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) error: %s\n", SDL_GetError());
		return;
	}
	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_ShowCursor(SDL_ENABLE);
	if ((charset = SDL_LoadBMP("images/charset.bmp")) == NULL) {
		printf("SDL_LoadBMP(\"images/charset.bmp\") error: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(charset, true, 0x000000);
	if ((map = SDL_LoadBMP("images/map.bmp")) == NULL) {
		printf("SDL_LoadBMP(\"images/map.bmp\") error: %s\n", SDL_GetError());
		return;
	}

	black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
}

void Game::handleEvents() {

}

void Game::update(int l) {
	drawMap();
	char text[64];
	sprintf_s(text, "Lives: %d", l);
	drawText(4, 4, text);
}

void Game::render() {
	SDL_UpdateTexture(texture, NULL, screen->pixels, screen->pitch);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);	
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(texture);
	SDL_Quit();
}

void Game::drawMap() {
	SDL_Rect destination;
	destination.x = 0;
	destination.y = 0;
	SDL_BlitSurface(map, NULL, screen, &destination);
}

SDL_Surface* Game::getScreen() {
	return screen;
}

void Game::drawText(int x, int y, const char* text) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	}
}

void Game::drawPixel(int x, int y, Uint32 color) {
	int bpp = screen->format->BytesPerPixel;
	Uint8* p = (Uint8*)screen->pixels + y * screen->pitch + x * bpp;
	*(Uint32*)p = color;
};

void Game::drawLine(int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		drawPixel(x, y, color);
		x += dx;
		y += dy;
	}
}

void Game::drawRectangle(int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
	int i;
	drawLine(x, y, k, 0, 1, outlineColor);
	drawLine(x + l - 1, y, k, 0, 1, outlineColor);
	drawLine(x, y, l, 1, 0, outlineColor);
	drawLine(x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++) drawLine(x + 1, i, l - 2, 1, 0, fillColor);
};