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
#include "ComponentManager.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "Time.h"
#include "RenderComponent.h"
#include "OpenGLContext.h"
#include "GLFW/glfw3.h"



using namespace std;
using namespace dae;

Minigin* Minigin::s_Instance = nullptr;


void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();
	s_Instance = this;


	float height = 480.f;
	float width = 640.f;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	if (!glfwInit())
		return;

	//m_Window = SDL_CreateWindow(
	//	"Programming 4 assignment",
	//	SDL_WINDOWPOS_CENTERED,
	//	SDL_WINDOWPOS_CENTERED,
	//	640,
	//	480,
	//	SDL_WINDOW_OPENGL
	//);
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

	//if (m_Window == nullptr) 
	//{
	//	throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	//}

	m_OpenGLContext->Init();
	ComponentManager::GetInstance().RegisterComponent<RenderComponent>();
	ComponentManager::GetInstance().RegisterComponent<TextureComponent>();
	ComponentManager::GetInstance().RegisterComponent<TextComponent>();
	ComponentManager::GetInstance().RegisterComponent<FPSComponent>();


	m_ImGuiLayer = new ImGuiLayer();
	PushLayer(m_ImGuiLayer);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//auto go = std::make_shared<dae::GameObject>();


	//auto texComp = std::make_shared<TextureComponent>();
	//texComp->SetTexture("background.jpg");
	//texComp->SetPosition({ 0,0 });

	//go->AddComponent<TextureComponent>(texComp);
	//auto fontfps = ResourceManager::GetInstance().GetFont("Lingua.otf", 15);
	//auto textComponent = std::make_shared<TextComponent>("fps: ", fontfps);
	//textComponent->SetPosition(glm::vec2{ 10, 10 });
	//go->AddComponent<TextComponent>(textComponent);
	//auto fpsComponent = std::make_shared<FPSComponent>();
	//go->AddComponent<FPSComponent>(fpsComponent);


	//auto goChild = std::make_shared<dae::GameObject>();
	//texComp = std::make_shared<TextureComponent>();
	//texComp->SetTexture("logo.png");
	//texComp->SetPosition(glm::vec2{ 216, 180 });
	//goChild->AddComponent<TextureComponent>(texComp);
	auto goChild = std::make_shared<dae::GameObject>();
	auto font = ResourceManager::GetInstance().GetFont("Lingua.otf", 36);

	auto textComponent = std::make_shared<TextComponent>("Programming 4 assignment", font);
	textComponent->SetPosition(glm::vec2{ 80.f, 20.f });
	textComponent->SetColor(glm::vec3{ 0.5f, 0.3f, 0.f });
	goChild->AddComponent<TextComponent>(textComponent);
	scene.Add(goChild);

	auto gopaka = std::make_shared<dae::GameObject>();


	textComponent = std::make_shared<TextComponent>("Programming 10 assignment", font);
	textComponent->SetPosition(glm::vec2{ 150.f, 80.f });
	textComponent->SetColor(glm::vec3{ 0.8f, 0.f, 0.1f });
	gopaka->AddComponent<TextComponent>(textComponent);
	scene.Add(gopaka);

}
void Minigin::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
	layer->OnAttach();
}


void dae::Minigin::Cleanup()
{
	glfwTerminate();
	SDL_Quit();

	delete m_OpenGLContext;
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


		// todo: this update loop could use some work.
		bool doContinue = true;
		//FrameCounter


		float lag = 0.f;
		while (doContinue)
		{

			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);



			/* Poll for and process events */
			glfwPollEvents();


			doContinue = input.ProcessInput();
			sceneManager.Update();

			sceneManager.Render();

			lag += time.GetDeltaTime();
			while (lag >= m_FixedTimeStep)
			{
				sceneManager.FixedUpdate();
				lag -= m_FixedTimeStep;
			}
			time.Update();


			m_ImGuiLayer->Begin();
			for (Layer* currentLayer : m_LayerStack)
				currentLayer->OnImGuiRender();
			m_ImGuiLayer->End();


			/* Swap front and back buffers */
			m_OpenGLContext->SwapBuffer();
		}
	}

	Cleanup();
}

