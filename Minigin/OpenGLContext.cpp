#include "OpenGLContext.h"
#include <assert.h>

namespace Eu
{
	OpenGLRenderer::OpenGLRenderer(SDL_Window* windowhandle)
		:m_WindowHandle(windowhandle)
	{
		assert(windowhandle, "Graphics Context is null")

	}

	void OpenGLRenderer::Init()
	{

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EU_CORE_ASSERT(status, "Failed to initialize!");

		EU_CORE_INFO("OpenGL Renderer: {0} {1} {2}", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));

	}

	void OpenGLRenderer::SwapBuffer()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}