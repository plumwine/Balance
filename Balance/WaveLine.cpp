#include "WaveLine.h"
#include <typeinfo.h>
#include "Cannon.h"

//�`�悷�邾���Ŕ���͕ʂł��
WaveLine::WaveLine(const Vector2 &position)
	:isTouch(false)
{
	_position = position;
	m_position = position;  //�����ʒu���o���邽��
	_grp = LoadGraph("../Texture/master/Gline.png");
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
	DrawExtendGraph(_position.x, _position.y, 1980, _position.y +20, _grp, false);
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
//�����蔻��͂���Ȃ�
void WaveLine::Hit(Object & object)
{
}

//�G�������ǂ���
bool WaveLine::GetTouch()
{
	return isTouch;
}
