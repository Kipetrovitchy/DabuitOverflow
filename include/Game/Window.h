#ifndef __OPERATINGSYSTE_H__
#define __OPERATINGSYSTE_H__

#include "GameMgr.h"
#include <SDL2/SDL.h>

#define FPS 60.0f

namespace Game
{
	typedef Game::GameMgr			GameMgr;
	
	class Window
	{
	private:
		GameMgr		_simulation;
		SDL_Window*	_window;

	public:
		Window();
		~Window();

		void	init(uint width, uint height);
		void	reshape(uint width, uint height);
		void	setFullscreen(bool fullscreen);

		void	getMousePos( float& x, float& y );
		bool	getMouseButton(int button);
		void	showCursor(bool value);

		SDL_Window* getWindow() { return _window; };
		GameMgr& simulation() { return _simulation; }
	};
}

#endif
