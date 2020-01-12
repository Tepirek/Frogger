#include <stdio.h>
#include "SDL.h"
#include "Game.h"
#include "Frog.h"
#include "Obstacle.h"

int main(int argc, char** argv) {

	Game* game = new Game();
	game->init("Frogger 1.0", false);

	Frog* frog = new Frog(5);

	Obstacle** trucks = new Obstacle * [20];
	Obstacle** logs = new Obstacle * [20];

	for (int i = 0; i < 5; i++) {
		/*
		trucks[i] = new Obstacle(i * 256, 256, 96, 32, -0.3, "images/truck_head_left.bmp");
		trucks[i + 5] = new Obstacle(i * 288, 288, 64, 32, 0.7, "images/car_head_right.bmp");
		trucks[i + 10] = new Obstacle(i * 288, 320, 64, 32, -0.5, "images/car_head_left.bmp");
		trucks[i + 15] = new Obstacle(i * 256, 352, 96, 32, 0.1, "images/truck_head_right.bmp");

		logs[i] = new Obstacle(i * 256, 96, 96, 32, -0.1, "images/log_size_3.bmp");
		logs[i + 5] = new Obstacle(i * 288, 128, 64, 32, 0.5, "images/turtle_size_2.bmp");
		logs[i + 10] = new Obstacle(i * 288, 160, 96, 32, -0.7, "images/log_size_3.bmp");
		logs[i + 15] = new Obstacle(i * 256, 192, 64, 32, 0.3, "images/turtle_size_2.bmp");
		*/

		trucks[i] = new Obstacle(i * 256, 256, 96, 32, -0.1, "images/truck_head_left.bmp");
		trucks[i + 5] = new Obstacle(i * 288, 288, 64, 32, 0.1, "images/car_head_right.bmp");
		trucks[i + 10] = new Obstacle(i * 288, 320, 64, 32, -0.1, "images/car_head_left.bmp");
		trucks[i + 15] = new Obstacle(i * 256, 352, 96, 32, 0.1, "images/truck_head_right.bmp");

		logs[i] = new Obstacle(i * 256, 96, 96, 32, -0.1, "images/log_size_3.bmp");
		logs[i + 5] = new Obstacle(i * 288, 128, 64, 32, 0.1, "images/turtle_size_2.bmp");
		logs[i + 10] = new Obstacle(i * 288, 160, 96, 32, -0.1, "images/log_size_3.bmp");
		logs[i + 15] = new Obstacle(i * 256, 192, 64, 32, 0.1, "images/turtle_size_2.bmp");
	}

	int t1 = SDL_GetTicks();
	int t2 = 0;
	double delta = 0;
	double time = 0;
	char text[128];

	while (frog->isAlive() && !frog->endGame()) {
		// static output
		t2 = SDL_GetTicks();
		delta = (t2 - t1) * 0.001;
		time += delta;
		t1 = t2;
		game->handleEvents();
		game->update(frog->getLives());
		sprintf_s(text, "Remaining time: %02.02f", 50 - time);
		game->drawText(8, 436, text);
		if(time < 40) game->drawRectangle(8, 452, 624 - (time * 12.48), 24, game->green, game->green);
		else if(time > 40 && time < 50) game->drawRectangle(8, 456, 624 - (time * 12.48), 16, game->red, game->red);
		else {
			frog->reset();
			time = 0;
		}

		// movement
		for (int i = 0; i < 20; i++) {
			trucks[i]->move();
			logs[i]->move();
		}
		frog->move();

		// handling collisions
		if (frog->onRiver()) {
			bool dead = true;
			float speed;
			for (int i = 0; i < 20; i++) {
				if (frog->collision(logs[i])) {
					dead = false;
					speed = logs[i]->getSpeed();
				}
			}
			if (!dead) frog->move(speed);
			else {
				frog->reset();
				time = 0;
			}
		}
		else {
			for (int i = 0; i < 20; i++) {
				if (frog->collision(trucks[i])) {
					frog->reset();
					time = 0;
				}
			}
		}
		if (frog->touchdown()) {
			time = 0;
		}

		// drawing objects
		for (int i = 0; i < 20; i++) {
			trucks[i]->draw(game->getScreen());
			logs[i]->draw(game->getScreen());
		}
		frog->draw(game->getScreen());
		frog->drawBase(game->getScreen());

		game->render();
	}

	bool gameOver = true;
	SDL_Event event;
	while (gameOver) {
		SDL_FillRect(game->getScreen(), NULL, game->black);
		game->drawText(100, 100, "GAMEOVER");
		game->drawText(100, 120, "Czy zakończyć grę?");
		game->drawText(100, 140, "Wciśnij dowolny klawisz!");
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				gameOver = false;
			}
		}
		game->render();
	}

	game->clean();

	return 0;
}