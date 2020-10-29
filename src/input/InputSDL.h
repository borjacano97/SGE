#pragma once

#include <vector>
#include <unordered_map>

#include "../math/Vec2.hpp"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>

enum Key 
{
	UNKNOWN  = SDLK_UNKNOWN,

	RETURN  = SDLK_RETURN,
	ESCAPE  = SDLK_ESCAPE,
	BACKSPACE  = SDLK_BACKSPACE,
	TAB  = SDLK_TAB,
	SPACE  = SDLK_SPACE,
	EXCLAIM  = SDLK_EXCLAIM,
	QUOTEDBL  = SDLK_QUOTEDBL,
	HASH  = SDLK_HASH,
	PERCENT  = SDLK_PERCENT,
	DOLLAR  = SDLK_DOLLAR,
	AMPERSAND  = SDLK_AMPERSAND,
	QUOTE  = SDLK_QUOTE,
	LEFTPAREN  = SDLK_LEFTPAREN,
	RIGHTPAREN  = SDLK_RIGHTPAREN,
	ASTERISK  = SDLK_ASTERISK,
	PLUS  = SDLK_PLUS,
	COMMA  = SDLK_COMMA,
	MINUS  = SDLK_MINUS,
	PERIOD  = SDLK_PERIOD,
	SLASH  = SDLK_SLASH,
	KEY_0  = SDLK_0,
	KEY_1  = SDLK_1,
	KEY_2  = SDLK_2,
	KEY_3  = SDLK_3,
	KEY_4  = SDLK_4,
	KEY_5  = SDLK_5,
	KEY_6  = SDLK_6,
	KEY_7  = SDLK_7,
	KEY_8  = SDLK_8,
	KEY_9  = SDLK_9,
	COLON  = SDLK_COLON,
	SEMICOLON  = SDLK_SEMICOLON,
	LESS  = SDLK_LESS,
	EQUALS  = SDLK_EQUALS,
	GREATER  = SDLK_GREATER,
	QUESTION  = SDLK_QUESTION,
	AT  = SDLK_AT,

	LEFTBRACKET ,
	BACKSLASH  = SDLK_BACKSLASH,
	RIGHTBRACKET  = SDLK_RIGHTBRACKET,
	CARET  = SDLK_CARET,
	UNDERSCORE  = SDLK_UNDERSCORE,
	BACKQUOTE  = SDLK_BACKQUOTE,
	a  = SDLK_a,
	b  = SDLK_b,
	c  = SDLK_c,
	d  = SDLK_d,
	e  = SDLK_e,
	f  = SDLK_f,
	g  = SDLK_g,
	h  = SDLK_h,
	i  = SDLK_i,
	j  = SDLK_j,
	k  = SDLK_k,
	l  = SDLK_l,
	m  = SDLK_m,
	n  = SDLK_n,
	o  = SDLK_o,
	p  = SDLK_p,
	q  = SDLK_q,
	r  = SDLK_r,
	s  = SDLK_s,
	t  = SDLK_t,
	u  = SDLK_u,
	v  = SDLK_v,
	w  = SDLK_w,
	x  = SDLK_x,
	y  = SDLK_y,
	z  = SDLK_z,

	CAPS_LOCK = SDLK_CAPSLOCK,

	F1  = SDLK_F1,
	F2  = SDLK_F2,
	F3  = SDLK_F3,
	F4  = SDLK_F4,
	F5  = SDLK_F5,
	F6  = SDLK_F6,
	F7  = SDLK_F7,
	F8  = SDLK_F8,
	F9  = SDLK_F9,
	F10 = SDLK_F10,
	F11 = SDLK_F11,
	F12 = SDLK_F12,

	RIGHT= SDLK_RIGHT,
	LEFT= SDLK_LEFT,
	DOWN= SDLK_DOWN,
	UP= SDLK_UP
};

enum KeyMod 
{
	NONE	= KMOD_NONE,
	LSHIFT  = KMOD_LSHIFT,
	RSHIFT  = KMOD_RSHIFT,
	LCTRL	= KMOD_LCTRL,
	RCTRL	= KMOD_RCTRL,
	LALT	= KMOD_LALT,
	RALT	= KMOD_RALT,
	LGUI	= KMOD_LGUI,
	RGUI	= KMOD_RGUI,
	NUM		= KMOD_NUM,
	CAPS	= KMOD_CAPS,
	MODE	= KMOD_MODE,
	RESERVED= KMOD_RESERVED,

	ALT		= LALT | RALT,
	GUI		= LGUI | RGUI,
	CTRL	= LCTRL	| RCTRL,
	SHIFT	= LSHIFT| RSHIFT
};
enum MouseButton
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputSDL
{
	std::unordered_map<Key, bool> keys_status;
	bool mouse_buttons[3];
	Vec2f mpos;
	bool mouse_moved;
public:
	bool KeyDown(Key key) const;
	bool KeyUp(Key key) const;

	bool MouseButtonUp(MouseButton mb) const;
	bool MouseButtonDown(MouseButton mb) const;

	Vec2f MousePosition() const;
	bool MouseMoved() const;
private:
	friend class App;
	void Init();
	void Update();
	void InitKeyState();
};