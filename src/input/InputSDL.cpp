#include "InputSDL.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

bool InputSDL::KeyDown(Key key) const
{
	return !keys_status.at(key);
}

bool InputSDL::KeyUp(Key key) const
{
	return keys_status.at(key);
}

bool InputSDL::MouseButtonUp(MouseButton mb) const
{
	return !mouse_buttons[(size_t)mb];
}

bool InputSDL::MouseButtonDown(MouseButton mb) const
{
	return mouse_buttons[(size_t)mb];
}

Vec2f InputSDL::MousePosition() const
{
	return mpos;
}

bool InputSDL::MouseMoved() const
{
	return mouse_moved;
}


void InputSDL::InitKeyState()
{
	keys_status.reserve(84);

	keys_status.insert({Key::UNKNOWN, false});
	keys_status.insert({Key::RETURN, false});
	keys_status.insert({Key::ESCAPE, false});
	keys_status.insert({Key::BACKSPACE, false});
	keys_status.insert({Key::TAB, false});
	keys_status.insert({Key::SPACE, false});
	keys_status.insert({Key::EXCLAIM, false});
	keys_status.insert({Key::QUOTEDBL, false});
	keys_status.insert({Key::HASH, false});
	keys_status.insert({Key::PERCENT, false});
	keys_status.insert({Key::DOLLAR, false});
	keys_status.insert({Key::AMPERSAND, false});
	keys_status.insert({Key::QUOTE, false});
	keys_status.insert({Key::LEFTPAREN, false});
	keys_status.insert({Key::RIGHTPAREN, false});
	keys_status.insert({Key::ASTERISK, false});
	keys_status.insert({Key::PLUS, false});
	keys_status.insert({Key::COMMA, false});
	keys_status.insert({Key::MINUS, false});
	keys_status.insert({Key::PERIOD, false});
	keys_status.insert({Key::SLASH, false});
	keys_status.insert({Key::KEY_0, false});
	keys_status.insert({Key::KEY_1, false});
	keys_status.insert({Key::KEY_2, false});
	keys_status.insert({Key::KEY_3, false});
	keys_status.insert({Key::KEY_4, false});
	keys_status.insert({Key::KEY_5, false});
	keys_status.insert({Key::KEY_6, false});
	keys_status.insert({Key::KEY_7, false});
	keys_status.insert({Key::KEY_8, false});
	keys_status.insert({Key::KEY_9, false});
	keys_status.insert({Key::COLON, false});
	keys_status.insert({Key::SEMICOLON, false});
	keys_status.insert({Key::LESS, false});
	keys_status.insert({Key::EQUALS, false});
	keys_status.insert({Key::GREATER, false});
	keys_status.insert({Key::QUESTION, false});
	keys_status.insert({Key::AT, false});
	keys_status.insert({Key::BACKSLASH, false});
	keys_status.insert({Key::RIGHTBRACKET, false});
	keys_status.insert({Key::CARET, false});
	keys_status.insert({Key::UNDERSCORE, false});
	keys_status.insert({Key::BACKQUOTE, false});
	keys_status.insert({Key::a, false});
	keys_status.insert({Key::b, false});
	keys_status.insert({Key::c, false});
	keys_status.insert({Key::d, false});
	keys_status.insert({Key::e, false});
	keys_status.insert({Key::f, false});
	keys_status.insert({Key::g, false});
	keys_status.insert({Key::h, false});
	keys_status.insert({Key::i, false});
	keys_status.insert({Key::j, false});
	keys_status.insert({Key::k, false});
	keys_status.insert({Key::l, false});
	keys_status.insert({Key::m, false});
	keys_status.insert({Key::n, false});
	keys_status.insert({Key::o, false});
	keys_status.insert({Key::p, false});
	keys_status.insert({Key::q, false});
	keys_status.insert({Key::r, false});
	keys_status.insert({Key::s, false});
	keys_status.insert({Key::t, false});
	keys_status.insert({Key::u, false});
	keys_status.insert({Key::v, false});
	keys_status.insert({Key::w, false});
	keys_status.insert({Key::x, false});
	keys_status.insert({Key::y, false});
	keys_status.insert({Key::z, false});
	keys_status.insert({Key::CAPS_LOCK, false});
	keys_status.insert({Key::F1, false});
	keys_status.insert({Key::F2, false});
	keys_status.insert({Key::F3, false});
	keys_status.insert({Key::F4, false});
	keys_status.insert({Key::F5, false});
	keys_status.insert({Key::F6, false});
	keys_status.insert({Key::F7, false});
	keys_status.insert({Key::F8, false});
	keys_status.insert({Key::F9, false});
	keys_status.insert({Key::F10, false});
	keys_status.insert({Key::F11, false});
	keys_status.insert({Key::F12, false});
	keys_status.insert({Key::RIGHT, false});
	keys_status.insert({Key::LEFT, false});
	keys_status.insert({Key::DOWN, false});
}

void InputSDL::Init()
{
	SDL_Init(SDL_INIT_EVENTS);
	mouse_moved = false;
	memset(mouse_buttons, false, 3 * sizeof(bool));
	mpos = { 0,0 };
	InitKeyState();
}

void InputSDL::Update()
{
	SDL_Event e;
	mouse_moved = false;
	while (SDL_PollEvent(&e)) 
	{
		switch (e.type)
		{
		case SDL_QUIT:
			break;
		case SDL_APP_TERMINATING:
			break;
		case SDL_APP_LOWMEMORY:
			break;
		case SDL_APP_WILLENTERBACKGROUND:
			break;
		case SDL_APP_DIDENTERBACKGROUND:
			break;
		case SDL_APP_WILLENTERFOREGROUND:
			break;
		case SDL_APP_DIDENTERFOREGROUND:
			break;
		case SDL_DISPLAYEVENT:
			break;
		case SDL_WINDOWEVENT:
			break;
		case SDL_SYSWMEVENT:
			break;
		case SDL_KEYDOWN:
			keys_status[(Key)e.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			keys_status[(Key)e.key.keysym.sym] = false;
			break;
		case SDL_TEXTEDITING:
			break;
		case SDL_TEXTINPUT:
			break;
		case SDL_KEYMAPCHANGED:
			break;
		case SDL_MOUSEMOTION:
			mpos = { e.motion.x, e.motion.y };
			mouse_moved = true;
			break;
		case SDL_MOUSEBUTTONDOWN: [[fallthrough]]
		case SDL_MOUSEBUTTONUP:
			const bool mb_down = e.button.type == SDL_MOUSEBUTTONDOWN;
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouse_buttons[MouseButton::LEFT] = mb_down;
				break;
			case SDL_BUTTON_MIDDLE:
				mouse_buttons[MouseButton::MIDDLE] = mb_down;
				break;
			case SDL_BUTTON_RIGHT:
				mouse_buttons[MouseButton::RIGHT] = mb_down;
				break;
			case SDL_BUTTON_X1:
				break;
			case SDL_BUTTON_X2:
				break;
			default: break;
			}
			break;
		case SDL_MOUSEWHEEL:
			break;
		case SDL_JOYAXISMOTION:
			break;
		case SDL_JOYBALLMOTION:
			break;
		case SDL_JOYHATMOTION:
			break;
		case SDL_JOYBUTTONDOWN:
			break;
		case SDL_JOYBUTTONUP:
			break;
		case SDL_JOYDEVICEADDED:
			break;
		case SDL_JOYDEVICEREMOVED:
			break;
		case SDL_CONTROLLERAXISMOTION:
			break;
		case SDL_CONTROLLERBUTTONDOWN:
			break;
		case SDL_CONTROLLERBUTTONUP:
			break;
		case SDL_CONTROLLERDEVICEADDED:
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			break;
		case SDL_CONTROLLERDEVICEREMAPPED:
			break;
		case SDL_FINGERDOWN:
			break;
		case SDL_FINGERUP:
			break;
		case SDL_FINGERMOTION:
			break;
		case SDL_DOLLARGESTURE:
			break;
		case SDL_DOLLARRECORD:
			break;
		case SDL_MULTIGESTURE:
			break;
		case SDL_CLIPBOARDUPDATE:
			break;
		case SDL_DROPFILE:
			break;
		case SDL_DROPTEXT:
			break;
		case SDL_DROPBEGIN:
			break;
		case SDL_DROPCOMPLETE:
			break;
		case SDL_AUDIODEVICEADDED:
			break;
		case SDL_AUDIODEVICEREMOVED:
			break;
		case SDL_SENSORUPDATE:
			break;
		case SDL_RENDER_TARGETS_RESET:
			break;
		default:
			break;
		}
	}
}