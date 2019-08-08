// OpenGL.cpp : Defines the entry point for the console application.
#include "Window.h"

#undef main SDL_main

int main()
{
	Game::Window window;
	window.init( 1024, 600 );
	
    return 0;
}
