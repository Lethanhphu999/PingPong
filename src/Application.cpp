#include "Application.h"
#include "Input.h"
#include "States/SplashMenu.h"
#include "CollisionManager.h"
#include "TimerModule.h"
#include <iostream>

Application* Application::s_Instance = nullptr;
SDL_Event Application::s_Event;
bool Application::m_Running;

/*Khởi tạo instance cho ứng dụng*/
Application* Application::Instance() {

	if (s_Instance == nullptr) {
		s_Instance = new Application();
	}
	
	return s_Instance;
}

Application::Application() {
	m_Running = true;

	m_Graphics = Graphics::Instance();
	if (!m_Graphics->Initialized()) {
		m_Running = false;
	}

	TimerModule::UpdateDelta();

	_StateMachine.addState(SplashMenu::GetInstance());
}

Application::~Application() {

	m_Graphics->DestroyInstance();
	m_Graphics = nullptr;
	
	_StateMachine.KillAllStates();
}

void Application::DestroyInstance() {
	delete s_Instance;
	s_Instance = nullptr;
}
/*
Main của chương trình
Mọi thứ sẽ được diễn render tại đây
*/
void Application::MainLoop() {
	while (m_Running)
	{

		TimerModule::UpdateDelta();

		while (SDL_PollEvent(&s_Event) != 0) {
			//std::cout << "Trong vong lap cua debug 1:  " << debug1++ << "\n";
			if (s_Event.type == SDL_QUIT) {
				m_Running = false;
			}
			
			switch (s_Event.window.event) 
			{                           
			case SDL_WINDOWEVENT_MINIMIZED:
				while (SDL_WaitEvent(&s_Event))
				{
					if (s_Event.window.event == SDL_WINDOWEVENT_RESTORED)
					{
						break;
					}
				}
				break;
			}
			break;
			
		}
		std::cout << "Debugger of Application:  " << "\n";
		Input::InputUpdate(s_Event);
		CollisionManager::Update();


		m_Graphics->Update();
		_StateMachine.Update();

	

		_StateMachine.Render();



		m_Graphics->Render();

		SDL_Delay(10); 
	}
}

void Application::ShutDown() {
	m_Running = false;
}

SDL_Event Application::GetEvent() {
	return s_Event;
}