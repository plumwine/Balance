#pragma once
#include "Vector2.h"
#include "Object.h"

//	�Փ˔���N���X
class Collision
{
public:

	//	��`�΋�`�̔���
	bool RectCollision(
		const Object& rectA,
		const Object& rectB);
};