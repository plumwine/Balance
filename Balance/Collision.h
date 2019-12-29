#pragma once
#include "Vector2.h"
#include "Object.h"

//	衝突判定クラス
class Collision
{
public:

	//	矩形対矩形の判定
	bool RectCollision(
		const Object& rectA,
		const Object& rectB);
};