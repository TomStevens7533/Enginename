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

using namespace std;

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
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
	ComponentManager::GetInstance().RegisterComponent<TextureComponent>();
	ComponentManager::GetInstance().RegisterComponent<TextComponent>();
	ComponentManager::GetInstance().RegisterComponent<FPSComponent>();


}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();


	TextureComponent* texComp = new TextureComponent();
	texComp->SetTexture("background.jpg");
	go->AddComponent<TextureComponent>(texComp);
	auto fontfps = ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	TextComponent* textComponent = new TextComponent("fps: ", fontfps);
	textComponent->SetPosition(glm::vec2{ 10.f, 10.f });
	go->AddComponent<TextComponent>(textComponent);
	FPSComponent* fpsComponent = new FPSComponent();
	go->AddComponent<FPSComponent>(fpsComponent);

	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	texComp = new TextureComponent();
	texComp->SetTexture("logo.png");
	texComp->SetPosition(glm::vec2{ 216, 180 });
	go->AddComponent<TextureComponent>(texComp);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	textComponent = new TextComponent("Programming 4 assignment", font);
	textComponent->SetPosition(glm::vec2{ 80.f, 20.f });
	go->AddComponent<TextComponent>(textComponent);
	scene.Add(go);

}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{


		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& time = Time::GetInstance();


		// todo: this update loop could use some work.
		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		//FrameCounter


		float lag = 0.f;
		while (doContinue)
		{


			const auto start = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(start - lastTime).count();

			doContinue = input.ProcessInput();
			sceneManager.Update();
			time.Update();

			lag += deltaTime;
			while (lag >= m_FixedTimeStep)
			{
				sceneManager.LateUpdate();
				lag -= m_FixedTimeStep;
			}
			renderer.Render();
			lastTime = start;
		}
	}

	Cleanup();
}
