#include "Minigin.h"

#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include <chrono>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "Time.h"
#include "RenderComponent.h"
#include "OpenGLContext.h"
#include "ThrashCachLayer.h"
#include "GLFW/glfw3.h"



using namespace std;
using namespace dae;

Minigin* Minigin::s_Instance = nullptr;


void dae::Minigin::Initialize()
{
	assert(s_Instance == nullptr); //if not nullptr
	s_Instance = this;


	float height = 480.f;
	float width = 640.f;

	if (!glfwInit())
		return;

	GLFWwindow* window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), "Hello World", NULL, NULL);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	m_OpenGLContext = new OpenGLContext(window, width, height);

	if(!window)
	{
		glfwTerminate();
		throw std::runtime_error(std::string("glfwCreateWindow Error: "));
	}


	m_OpenGLContext->Init();

	m_ImGuiLayer = new ImGuiLayer();
	m_ImGuiLayer->OnAttach();

}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	Layer* thrashLayer = new Thrashlayer();
	scene.PushLayer(thrashLayer);
	
	auto goChild = std::make_shared<dae::GameObject>();
	auto font = ResourceManager::GetInstance().GetFont("Lingua.otf", 36);

	auto textComponent = std::make_shared<TextComponent>("Programming 4 assignment", font);
	textComponent->SetPosition(glm::vec2{ 80.f, 20.f });
	textComponent->SetColor(glm::vec3{ 0.5f, 0.3f, 0.f });
	goChild->AddComponent<TextComponent>(textComponent);

	auto gopaka = std::make_shared<dae::GameObject>();


	textComponent = std::make_shared<TextComponent>("Programming 10 assignment", font);
	textComponent->SetPosition(glm::vec2{ 150.f, 80.f });
	textComponent->SetColor(glm::vec3{ 0.8f, 0.f, 0.1f });
	gopaka->AddComponent<TextComponent>(textComponent);
	thrashLayer->Add(gopaka);
	auto comp = gopaka->GetComponent<TextComponent>();
	auto textttComponent = std::make_shared<TextComponent>("Programming 4 assignment", font);

	gopaka->AddChild(goChild);
	//gopaka->RemoveComponent<TextComponent>();

}



void dae::Minigin::Cleanup()
{
	glfwTerminate();

	delete m_OpenGLContext;
	delete m_ImGuiLayer;
}

void dae::Minigin::Run()
{
	Initialize();


	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{

		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& time = Time::GetInstance();

		float lag = 0.f;
		while (m_IsRunning)
		{

			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);



			/* Poll for and process events */
			glfwPollEvents();


			m_IsRunning = input.ProcessInput();

			m_ImGuiLayer->Begin();


			sceneManager.Update();


			sceneManager.Render();

			m_ImGuiLayer->End();


			lag += time.GetDeltaTime();
			while (lag >= m_FixedTimeStep)
			{
				sceneManager.FixedUpdate();
				lag -= m_FixedTimeStep;
			}
			time.Update();


	


			/* Swap front and back buffers */
			m_OpenGLContext->SwapBuffer();
		}
	}

	Cleanup();
}

void Minigin::Close()
{
	m_IsRunning = false;

}

