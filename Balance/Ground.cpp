#include "Ground.h"
#include <typeinfo.h>
#include "Cannon.h"
#include "GamePlayManager.h"

Ground::Ground(const Vector2 &position)
	:isGameEnd(false)
{
	_position = position; 
	_size = Vector2(1920, 150);
	//_grp = LoadGraph("../Texture/master/kusa.png");
	Initialize();
}


Ground::~Ground()
{
}

void Ground::Initialize()
{
}

void Ground::Draw()
{
	//DrawExtendGraph(_position.x, _position.y, 1920, 1080, _grp, false);
}

void Ground::Update(float deltaTime)
{
}

void Ground::Release()
{
}

//こいつは終了フラグはいらない
bool Ground::IsDead()
{
	return false;
}

void Ground::Hit(Object & object)
{
	//大砲が触れたらゲームを終了
	if (typeid(object) == typeid(Cannon))
	{
		isGameEnd = true;
		GamePlayManager::Instance().endGame();
	}
}
bool Ground::IsGameSet()
{
	return isGameEnd;
}
