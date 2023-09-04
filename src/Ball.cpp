#include <random>

#include "Ball.h"
#include "PlayerPaddle.h"
#include "AIPaddle.h"
#include "CollisionManager.h"
#include "TimerModule.h"

/*
Khởi tạo tráng thái ban đầu cho trái bóng
*/
void Ball::Place(){

	m_StartingPosition.x = 400;
	m_StartingPosition.y = 300;

	m_Ball.Place(m_StartingPosition, Vector2(20, 20));

	m_BallVelocity.x = 200;
	m_BallVelocity.y = 150;

	CollisionManager::AddCollider(&m_Ball, "ball");
}

void Ball::Render() {
	m_Ball.RenderRect(255, 255, 255);

}
/*
Update trạng thái của trái bóng
Khi xảy ra va đập hướng vector mới của trái bóng sẽ được ramdom
*/
void Ball::Update() {

	std::random_device randomizer; 
	std::mt19937 gen(randomizer()); 
	std::uniform_real_distribution<float> dist(-300.0f, 300.0f); //gioi hạn kết quả từ -6 đến 6

	//Player collision
	if (CollisionManager::CheckGroupCollision("ball", "player")) {
		m_BallVelocity.x *= -1;
		m_BallVelocity.y = dist(gen);
	}

	//AI collision
	if (CollisionManager::CheckGroupCollision("ball", "ai")) {
		m_BallVelocity.x *= -1;
		m_BallVelocity.y = dist(gen);
	}

	//Boundary check
	if (m_Ball.GetRect().x + m_Ball.GetRect().w >= 800) { //kiểm tra tường bên phải
		m_BallVelocity.x *= -1;
	}

	if (m_Ball.GetRect().x <= 0) { //kiểm tra tường bên trái
		m_BallVelocity.x *= -1;
	}

	if (m_Ball.GetRect().y <= 0) { //kiểm tra tường bên trên
		m_BallVelocity.y *= -1;
	}

	if (m_Ball.GetRect().y + m_Ball.GetRect().h >= 600) { // kiểm tra trường bên dưới
		m_BallVelocity.y *= -1;
	}

	m_Ball.Move(m_BallVelocity * TimerModule::GetDelta());
	
}

void Ball::ResetPosition() {
	m_Ball.Place(m_StartingPosition, Vector2(20, 20));
}

void Ball::Reset() {
	m_Ball.Place(m_StartingPosition, Vector2(20, 20));
}