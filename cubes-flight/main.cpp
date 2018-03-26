#include "functions.cpp"

int main(int, char**)
{
    atexit(stop);
    init_SDL();
    init_OpenGL();
    init_cubes();

    while(1){
        new_game();
        game_on();
        game_over();
    }

    return 0;
}
