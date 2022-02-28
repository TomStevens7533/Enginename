#pragma once

struct GLFWwindow;
struct SDL_Window;

namespace Eu
{


	class OpenGLRenderer 
	{
	public:
		OpenGLRenderer(SDL_Window* windowHandle);
		 void Init();
		 void SwapBuffer();

	private:

		SDL_Window* m_WindowHandle;
	};

}