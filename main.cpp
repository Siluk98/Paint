#include "lib/Engine/hpp/game.hpp"
#include <iostream>
#include "lib/UI/hpp/ui.hpp"
#include "hpp/FirstState.hpp"

int main()
{
    Game game;
    game.pushState(new FirstState);
    game.run();
    return 0;
}
