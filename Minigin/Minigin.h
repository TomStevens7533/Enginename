#pragma once
#include "OpenGLContext.h"
struct SDL_Window;
namespace dae
{
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		const float m_FixedTimeStep = 0.25f;
		dae::OpenGLContext* m_OpenGLContext; //TODO change to unique ptr
		SDL_Window* m_Window{};

	};
}