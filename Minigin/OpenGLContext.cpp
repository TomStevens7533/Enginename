#include "OpenGLContext.h"
#include <assert.h>
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace dae
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowhandle)
		:m_WindowHandle(windowhandle)
	{
		assert(windowhandle);

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
