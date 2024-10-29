#include "Game.h"

// Galaga with Zombies

int main(){
    Game::Start();

    while (Game::IsRunning()) {
        Game::Update();
    }

    return 0;
}