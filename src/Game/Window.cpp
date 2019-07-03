#include "Window.h"

#include <GL/glew.h>

namespace Game
{

	Window::Window()
	{
		_simulation.setRenderWindow(this);
	}

	Window::~Window()
	{
	}

	void	Window::init(uint width, uint height)
	{
		SDL_GLContext	context;

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			return;

		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE))
    	    std::cout << "Could not set core profile" << std::endl;
    	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4))
    	    std::cout << "Could not set GL major version" << std::endl;
    	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3))
    	    std::cout << "Could not set GL minor version" << std::endl;

		/* Turn on double buffering with a 24bit Z buffer.
		* You may need to change this to 16 or 32 for your system */
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		_window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)width, (int)height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (_window == nullptr)
		{
			return;
		}

		context = SDL_GL_CreateContext(_window);
		if (SDL_GL_SetSwapInterval(1) < 0)
			return;

		if (GLEW_OK != glewInit())
			return;

		showCursor(true);

		if (_simulation.init(width, height))
		{
			Uint64 currentTime = SDL_GetPerformanceCounter();
			Uint64 lastTime = 0;
			float frameTime = 0.0;

			while (!_simulation.needQuit())
			{
				
				lastTime = currentTime;
				currentTime = SDL_GetPerformanceCounter();

				Uint64 deltaTime = (currentTime - lastTime);
				frameTime = (float)deltaTime / SDL_GetPerformanceFrequency();

				//Make sure frametime isn't too big
				if (frameTime > 0.1)
					frameTime = 0.1;

				_simulation.update(frameTime);

				SDL_GL_SwapWindow(_window);
			}
		}

		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(_window);
		SDL_Quit();
	}

	void	Window::reshape(uint width, uint height)
	{
		SDL_SetWindowSize(_window, width, height);
		SDL_SetWindowPosition(_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		_simulation.resize(width, height);
	}

	void Window::setFullscreen(bool fullscreen)
	{
		if (fullscreen)
			SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		else
			SDL_SetWindowFullscreen(_window, 0);
	}

	void	Window::getMousePos(float& x, float& y)
	{
		int _x, _y;
		SDL_GetMouseState(&_x, &_y);
		//y = _height - y;

		x = (float)_x;
		y = (float)_y;
	}

	bool	Window::getMouseButton(int button)
	{
		int flag = 0;
		switch (button)
		{
		case 0:	flag = SDL_BUTTON_LEFT; break;
		case 1: flag = SDL_BUTTON_MIDDLE; break;
		case 2: flag = SDL_BUTTON_RIGHT; break;
		}

		return ((SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(flag)) != 0);
	}

	void	Window::showCursor(bool value)
	{
		if (!value)
			SDL_ShowCursor(SDL_DISABLE);
		else
			SDL_ShowCursor(SDL_ENABLE);
	}
}
