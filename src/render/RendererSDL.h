#pragma once
#include "../math/Vec2.hpp"

struct SDL_Window;
struct SDL_Renderer;

union Color
{
	int32_t abgr;
	struct { char a, b, g, r; };

	bool operator==(const Color& rhs) const noexcept
	{
		return abgr == rhs.abgr;
	}
	bool operator!=(const Color& rhs) const noexcept
	{
		return abgr != rhs.abgr;
	}
};


class RendererSDL
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	bool initialized;
	Color render_color;
public:
	void Init();
	void BeginFrame();
	void EndFrame();
	void Cleanup();

	// Utility functions. TODO: REMOVE THIS

	void DrawRect(Vec2f tl_corner, float width, float height);
	void DrawRect(Vec2f tl_corner, float width, float height, Color color);
	void DrawLine(Vec2f from, Vec2f to);
	void DrawLine(Vec2f from, Vec2f to, Color color);
private:
	void SetRenderColor(Color new_color);
};
