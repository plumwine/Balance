#include "WaveLine.h"
#include <typeinfo.h>
#include "Cannon.h"

//描画するだけで判定は別でやる
WaveLine::WaveLine(const Vector2 &position)
	:isTouch(false)
{
	_position = position;
	m_position = position;  //初期位置を覚えるため
	_grp = LoadGraph("../Texture/master/Gline.png");
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
//当たり判定はいらない
void WaveLine::Hit(Object & object)
{
}

//触ったかどうか
bool WaveLine::GetTouch()
{
	return isTouch;
}
