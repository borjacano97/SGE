#include "RendererSDL.h"
#include <SDL2/SDL.h>

void RendererSDL::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Motor bien perron", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void RendererSDL::BeginFrame()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
}

void RendererSDL::EndFrame()
{
	SDL_RenderPresent(renderer);
}

void RendererSDL::Cleanup()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void RendererSDL::DrawRect(Vec2f tl_corner, float width, float height)
{
	SDL_FRect rect = {tl_corner.x, tl_corner.y, width, height};
	SDL_RenderDrawRectF(renderer, &rect);
}

void RendererSDL::DrawRect(Vec2f tl_corner, float width, float height, Color color)
{
	SetRenderColor(color);
	DrawRect(tl_corner, width, height);
}

void RendererSDL::DrawLine(Vec2f from, Vec2f to)
{
	SDL_RenderDrawLineF(renderer, from.x, from.y, to.x, to.y);
}

void RendererSDL::DrawLine(Vec2f from, Vec2f to, Color color)
{
	SetRenderColor(color);
	DrawLine(from, to);
}

void RendererSDL::SetRenderColor(Color new_color)
{
	if (new_color != render_color) 
	{
		render_color = new_color;
		SDL_SetRenderDrawColor(renderer, render_color.r, render_color.g, render_color.b, render_color.a);
	}
}
