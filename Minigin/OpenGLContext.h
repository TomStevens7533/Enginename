#pragma once
#include "Singleton.h"

struct GLFWwindow;
struct SDL_Window;

namespace dae
{


	class OpenGLContext 
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle, float width, float height);
		 void Init();
		 void SwapBuffer();
		 inline  GLFWwindow* const GetRawWindowHandle() const { return m_WindowHandle; };
		 inline float GetHeight() const { return  m_Height; }
		 inline float GetWidth() const { return  m_Width; }


	private:
		float m_Height = 0;
		float m_Width = 0;
		GLFWwindow* m_WindowHandle;
	};

}