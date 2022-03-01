#include "OpenGLContext.h"
#include <assert.h>
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace dae
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle, float width, float height) : m_Width{width}, m_Height{height}
		, m_WindowHandle(windowHandle)
	{
		assert(windowHandle);

	}

	void OpenGLContext::Init()
	{

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		assert(status != 0);
		std::cout << "OpenGL Initialized\n";
	}

	void OpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
