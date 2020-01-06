#include "WaveLine.h"
#include <typeinfo.h>
#include "Cannon.h"


WaveLine::WaveLine(const Vector2 &position)
	:isTouch(false)
{
	_position = position;
	m_position = position;  //初期位置を覚えるため
}


WaveLine::~WaveLine()
{
}

void WaveLine::Initialize()
{
	//初期化するとき初期位置を覚える
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
	//オブジェクトが当たったらTure;
	if (typeid(object) == typeid(Cannon))
	{
		isTouch = true;
	}
	else
	{
		//触れていないときは
		isTouch = false;
	}
}

//触ったかどうか
bool WaveLine::GetTouch()
{
	return isTouch;
}
