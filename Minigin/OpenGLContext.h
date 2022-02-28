#pragma once

struct GLFWwindow;
struct SDL_Window;

namespace dae
{


	class OpenGLContext 
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		 void Init();
		 void SwapBuffer();

	private:

		GLFWwindow* m_WindowHandle;
	};

}