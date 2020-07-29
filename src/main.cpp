#include <cstdio>
#include <iostream>
#include <cstdint>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

int main(int argc, const char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = SDL_CreateWindow("Motor bien perron", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 640, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1, 0);
	
	bool run = true;

	union Color
	{
		int32_t abgr;
		struct { char a, b, g, r; };
	};

	
	Color colors[] = 
	{
		{0xff0000ff},
		{0x00ff00ff},
		{0x0000ffff},
		{0xff00ffff}
	};
	const size_t n_colors = sizeof(colors) / sizeof(*colors);
	size_t current_color = 0;
	while (run)
	{
		// Handle events
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT) run = false;
			else if (e.type == SDL_KEYDOWN)
			{
				const auto sym = e.key.keysym.sym;
				char c;
				if ((sym >= SDLK_0 && sym <= SDLK_9)
				||  (sym >= SDLK_a && sym <= SDLK_z))
				{
					std::cout << (char)sym;
				}
				else if(sym == SDLK_SPACE)
				{
					current_color = (current_color + 1) % n_colors;
				}
			}
		}
		// Update
		const auto render_color = colors[current_color];
		// Render
		SDL_SetRenderDrawColor(renderer, render_color.r, render_color.g, render_color.b, render_color.a);
		SDL_RenderClear(renderer);


		SDL_RenderPresent(renderer);
	}
	
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}