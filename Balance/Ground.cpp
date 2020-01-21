#include "Ground.h"
#include <typeinfo.h>
#include "Cannon.h"
#include "GamePlayManager.h"

Ground::Ground(const Vector2 &position)
	:isGameEnd(false)
{
	_position = position; 
	_size = Vector2(1920, 144);
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
}

void Ground::Update(float deltaTime)
{
}

void Ground::Release()
{
}

//�����͏I���t���O�͂���Ȃ�
bool Ground::IsDead()
{
	return false;
}

void Ground::Hit(Object & object)
{
	//��C���G�ꂽ��Q�[�����I��
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
