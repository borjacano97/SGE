#pragma once
#include <SDL2/SDL.h>

#include "../math/Vec2.hpp"

struct Player
{
	Vec2f pos {0.0f,0.0f};
	Vec2f dir {0.0f,0.0f};
	float vel = 0.0f;

	int w = 0, h = 0;
};

const size_t window_width = 720;
const size_t window_height = 640;

class App 
{
	bool running;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Player player;
	size_t current_color;
public:
	void Init();
	void Start();
	void Stop();
private:
	void HandleEvents();
	void Update();
	void Cleanup();
};
