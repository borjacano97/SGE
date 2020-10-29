#include <cstdio>
#include <iostream>
#include <cstdint>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "math/Vec2.hpp"
#include "core/App.h"

int main(int argc, const char* argv[])
{
	App app;
	app.Init();
	app.Start();
	return 0;
}