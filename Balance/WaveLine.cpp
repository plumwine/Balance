#include "WaveLine.h"
#include <typeinfo.h>
#include "Cannon.h"

//描画するだけで判定は別でやる
WaveLine::WaveLine(const Vector2 &position)
	:isTouch(false)
{
	_position = position;
	m_position = position;  //初期位置を覚えるため
	_grp = LoadGraph("../Texture/master/waveline.png");
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
	DrawExtendGraph(0, 500, 1980, 505, _grp, false);
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
//当たり判定はいらない
void WaveLine::Hit(Object & object)
{
//	//オブジェクトが当たったらTure;
//	if (typeid(object) == typeid(Cannon))
//	{
//		isTouch = true;
//	}
//	else
//	{
//		//触れていないときは
//		isTouch = false;
//	}
}

//触ったかどうか
bool WaveLine::GetTouch()
{
	return isTouch;
}
