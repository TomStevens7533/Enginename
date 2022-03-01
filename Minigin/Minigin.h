#pragma once
#include "ImGuiLayer.h"
#include "LayerStack.h"
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

		void PushLayer(Layer* layer);

		inline static Minigin& Get() { return *s_Instance; }
		inline OpenGLContext& GetContext() const { return *m_OpenGLContext; };

	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		const float m_FixedTimeStep = 0.25f;
		OpenGLContext* m_OpenGLContext; //TODO change to unique ptr
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;


		static Minigin* s_Instance;


	};
}