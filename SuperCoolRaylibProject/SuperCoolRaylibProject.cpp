#include <iostream>
#include "raylib.h"
#include "Game.h"

// TODO - Component System?

int main() {
	Game* game = new Game();
	game->Init();

	while (!WindowShouldClose()) {
		game->Tick();
		game->Draw();
	}
	
	CloseWindow();
	delete game;
}