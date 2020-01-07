#include "Ground.h"
#include <typeinfo.h>
#include "Cannon.h"


Ground::Ground(const Vector2 &position)
	:isGameEnd(false)
{
	_position = position; 
	_size = Vector2(1920, 150);
	_grp = LoadGraph("../Texture/kari/ground_A.png");
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
	Render::Instance().RectDraw(*this);
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
	}
}

bool Ground::IsGameSet()
{
	return isGameEnd;
}
