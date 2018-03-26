#include "functions.cpp"

int main ( int argc, char** argv )
{
    atexit(stop);
    init_SDL();
    init_OpenGL();

    new_game();
    while(1){
        game_on();
        game_over();
    }

    return 0;
}
