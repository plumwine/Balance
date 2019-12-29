#include "Collision.h"
#include <math.h>

//	‹éŒ`‘Î‹éŒ`‚Ì”»’è
bool Collision::RectCollision(const Object& rectA, const Object& rectB)
{
	Vector2 rectAPos = rectA.Position();
	Vector2 rectBPos = rectB.Position();
	Vector2 rectASize = rectA.Size();
	Vector2 rectBSize = rectB.Size();
	auto dx = abs((rectAPos.x + rectASize.x / 2) - (rectBPos.x + rectBSize.x / 2));
	auto dy = abs((rectAPos.y + rectASize.y / 2) - (rectBPos.y + rectBSize.y / 2));

	return (dx < (rectASize.x + rectBSize.x) / 2 && dy < (rectASize.y + rectBSize.y) / 2);
}
