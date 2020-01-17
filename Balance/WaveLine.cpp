#include "WaveLine.h"
#include <typeinfo.h>
#include "Cannon.h"


WaveLine::WaveLine(const Vector2 &position)
	:isTouch(false)
{
	_position = position;
	m_position = position;  //�����ʒu���o���邽��
}


WaveLine::~WaveLine()
{
}

void WaveLine::Initialize()
{
	//����������Ƃ������ʒu���o����
	_position = m_position;
	isTouch = false;
}

void WaveLine::Draw()
{
	Render::Instance().RectDraw(*this);
}

void WaveLine::Update(float deltaTime)
{
}

void WaveLine::Release()
{
}

bool WaveLine::IsDead()
{
	return false;
}

void WaveLine::Hit(Object & object)
{
	//�I�u�W�F�N�g������������Ture;
	if (typeid(object) == typeid(Cannon))
	{
		isTouch = true;
	}
	else
	{
		//�G��Ă��Ȃ��Ƃ���
		isTouch = false;
	}
}

//�G�������ǂ���
bool WaveLine::GetTouch()
{
	return isTouch;
}
