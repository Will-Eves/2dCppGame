#include "Game.h"

/*

LU Software Development Club - Game Development Team (2024)

Created by the Game Development team in the Software Development club to
learn how to use SFML and create simple games with it.

Led by Will Eves.

*/

int main() {
    Game::Start();

    while (Game::IsRunning()) {
        Game::Update();
    }

    return 0;
}