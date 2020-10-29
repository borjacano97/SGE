#include "App.h"

#include <iostream>
#include <fmt/format.h>
#include <SDL2/SDL.h>

#include "Time.h"


static const Color colors[] =
{
	{0xff0000ffu},
	{0x00ff00ffu},
	{0x0000ffffu},
	{0xff00ffffu}
};
static const size_t n_colors = sizeof(colors) / sizeof(*colors);

void App::Init()
{
	Time::StartTime();
	renderer.Init();

	player = {
		{window_width / 2 - 50, window_height / 2 - 50},
		{1, 0},
		50,
		50, 50
	};

}

void App::Start()
{
	running = true;
	while (running)
	{
		Time::StartFrame();
		HandleEvents();
		Update();
	}
	Cleanup();
}

void App::Stop()
{
	running = false;
}

void App::HandleEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			Stop();

		else if (e.type == SDL_KEYDOWN)
		{
			const auto sym = e.key.keysym.sym;
			if ((sym >= SDLK_0 && sym <= SDLK_9)
				|| (sym >= SDLK_a && sym <= SDLK_z))
			{
				std::cout << static_cast<char>(sym);
			}
			else if (sym == SDLK_SPACE)
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
		else if (e.type == SDL_KEYUP)
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
}

void App::Update()
{
	// Update
	Vec2f next_pos = player.pos + player.dir * player.vel * Time::DeltaTime();
	//Vec2f next_pos = player.pos + player.dir * player.vel * .0001;
	fmt::print("Player pos: ({}, {}) Dt: {}\n", next_pos.x, next_pos.y, Time::DeltaTime());
	if (next_pos.x + player.w / 2 > window_width)
		player.dir.x *= -1;
	else if (next_pos.x - player.w / 2 < 0)
		player.dir.x *= -1;

	player.pos = next_pos;

	// Render
	
	renderer.BeginFrame();

	Vec2f player_center = { player.pos.x - (player.w / 2), player.pos.y - (player.h / 2) };

	renderer.DrawRect(player_center, player.w, player.h);

	const float ray_len = 100;
	const Vec2f dir_ray = player.pos + player.dir * ray_len;
	renderer.DrawLine({ player.pos.x, player.pos.y }, { dir_ray.x, dir_ray.y });

	renderer.EndFrame();
}

void App::Cleanup()
{
	renderer.Cleanup();
}
