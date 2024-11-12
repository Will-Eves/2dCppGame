#include "Game.h"

// Galaga with Zombies

int main() {
    Game game;

    game.Start();

    while (game.IsRunning()) {
        game.Update();
    }

    return 0;
}