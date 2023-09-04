#include "PlayerPaddle.h"
#include "Input.h"
#include "CollisionManager.h"
#include "TimerModule.h"
/*
Khởi tạo trạng thái ban đầu cho paddle của người chơi 
*/
void PlayerPaddle::Place() {
	
	m_Player.Place(Vector2(30, 300), Vector2(15, 60));

	CollisionManager::AddCollider(&m_Player, "player");
}

/*
Render thanh paddle
*/
void PlayerPaddle::Render() {
	m_Player.RenderRect(255, 255, 255, 255);
}
/*
Update tọa độ của thanh paddle theo sự kiện nhấn phím của người chơi
*/
void PlayerPaddle::Update() {

	if (Input::Keydown(SDL_SCANCODE_UP) || Input::Keydown(SDL_SCANCODE_W)) {
		m_Player.Move(Vector2(0, -300) * TimerModule::GetDelta());
	}

	if (Input::Keydown(SDL_SCANCODE_DOWN) || Input::Keydown(SDL_SCANCODE_S)) {
		m_Player.Move(Vector2(0, 300) * TimerModule::GetDelta());
	}

	//Boundary check
	if (m_Player.GetRect().y <= 0) {
		m_Player.GetRect().y = 0;
	}

	if (m_Player.GetRect().y + m_Player.GetRect().h >= 600) {
		m_Player.GetRect().y = 600 - m_Player.GetRect().h;
	}
}

Shape2D& PlayerPaddle::GetPlayerPaddleCollider() {
	return m_Player;
}