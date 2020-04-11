#include "../include/main.h"

int main(int argc, char* argv[])
{
    Game* mainGame = new Game();

    mainGame->gameLoop();

    return EXIT_SUCCESS;
}//main
