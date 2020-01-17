#pragma once
#include <DxLib.h>
#include <string>

#include "Object.h"
#include "Vector2.h"

class Object;

class Render
{
private:
	Render() {}
	Render(const Render&) {}
	Render& operator= (const Render&) {}

public:
	static Render& Instance();

	void Draw(Vector2 pos, Vector2 size, int grp);
	void FlagDraw(Vector2 pos, Vector2 size, int grp, bool dr, int alpha);
	void RectDraw(Object& object);
	void RectDraw(Object& object, bool reverse);
	void AlphaDraw(Object& object, int alpha);
	void AlphaDraw(Object& object, bool reverse, int alpha);
	void FlagDraw(Object& object, bool dr, int alpha);

	void ExtendDraw(Vector2 pos, Vector2 extendPos, int grp);
	void ExtendDraw(Vector2 pos, Vector2 size, Vector2 extend, int grp);
	void ExtendDrawRefPos(Object& object, Vector2 extendPos);
	void ExtendDrawRefMul(Object& object, Vector2 extend);

	void RectParticle(Vector2 pos, int particleNumber, int particleSize, int grp);
	void RectParticle(Vector2 pos, int particleNumber, int particleSize, int grp, bool reverse);
	void LineDraw(Vector2 start, Vector2 end, unsigned int color);
	void StringDraw(Vector2 pos, const TCHAR* str);
	void StringDraw(Vector2 pos, const TCHAR* str, unsigned int color);
	void NumberDraw(Vector2 pos, int number, int grp);


	void DrawShake(Object& object);
	void DrawShake(Object& object, bool reverse);
	void ShakeChange();
	void ShakeStop();

private:
	int shake = 0;
	bool change = false;
};