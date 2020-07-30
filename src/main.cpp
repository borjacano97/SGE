#include <cstdio>
#include <iostream>
#include <cstdint>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "math/Vec2.hpp"

struct Player
{
	Vec2f pos;
	Vec2f dir;
	float vel;
	
	int w, h;
};

const size_t window_width = 720;
const size_t window_height= 640;

int main(int argc, const char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window		= SDL_CreateWindow("Motor bien perron", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, 0);
	SDL_Renderer* renderer	= SDL_CreateRenderer(window,-1, 0);
	
	bool run = true;

	union Color
	{
		int32_t abgr;
		struct { char a, b, g, r; };
	};

	
	Color colors[] = 
	{
		{0xff0000ffu},
		{0x00ff00ffu},
		{0x0000ffffu},
		{0xff00ffffu}
	};
	const size_t n_colors = sizeof(colors) / sizeof(*colors);
	size_t current_color = 0;
	char n = 0;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	Player player
	{
		{window_width / 2 - 50, window_height / 2 - 50},
		{1, 0},
		50,
		50, 50
	};
	auto last_time = SDL_GetTicks();
	while (run)
	{
		const auto now = SDL_GetTicks();
		const auto delta_time = (now - last_time) * 0.001;
		last_time = now;
		
		// Handle events
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT) run = false;
			else if (e.type == SDL_KEYDOWN)
			{
				const auto sym = e.key.keysym.sym;
				if ((sym >= SDLK_0 && sym <= SDLK_9)
				||  (sym >= SDLK_a && sym <= SDLK_z))
				{
					std::cout << static_cast<char>(sym);
				}
				else if(sym == SDLK_SPACE)
				{
					current_color = (current_color + 1) % n_colors;
				}
				bool dirty = false;
				if (sym == SDLK_UP)
				{
					dirty = true;
					player.dir.y = -1;
				}
				else if (sym == SDLK_DOWN)
				{
					dirty = true;
					player.dir.y = 1;
				}
				if (sym == SDLK_RIGHT)
				{
					dirty = true;
					player.dir.x = 1;
				}
				else if (sym == SDLK_LEFT)
				{
					dirty = true;
					player.dir.x = -1;
				}
				if (dirty) player.dir.normalize();
			}
			else if(e.type == SDL_KEYUP)
			{
				const auto sym = e.key.keysym.sym;
				bool dirty = false;
				if ((sym == SDLK_UP && player.dir.y < 0) || (sym == SDLK_DOWN && player.dir.y > 0))
				{
					player.dir.y = 0;
					dirty = true;
				}
				if ((sym == SDLK_RIGHT && player.dir.x > 0) || (sym == SDLK_LEFT && player.dir.x < 0))
				{	
					player.dir.x = 0;
					dirty = true;
				}
				if (dirty) player.dir.normalize();
			}
		}
		// Update
		Vec2f next_pos = player.pos + player.dir * player.vel * delta_time;
		if (next_pos.x + player.w / 2 > window_width)
			player.dir.x *= -1;
		else if (next_pos.x - player.w / 2 < 0)
			player.dir.x *= -1;
		
		player.pos = next_pos;
		
		// Render
		SDL_Rect rect
		{
			(int)player.pos.x - (player.w/2),
			(int)player.pos.y - (player.h/2),
			player.w,
			player.h
		};
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &rect);

		const float ray_len = 100;
		const Vec2f dir_ray = player.pos + player.dir * ray_len;
		SDL_RenderDrawLine(renderer, player.pos.x, player.pos.y, dir_ray.x, dir_ray.y);
		SDL_RenderPresent(renderer);
	}
	
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}