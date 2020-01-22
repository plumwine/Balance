#pragma once
#include <DxLib.h>
#include <string>

#include "Object.h"
#include "Vector2.h"

class Object;

#define NUMBER_SIZE 64

class Render
{
private:
	Render() {}
	Render(const Render&) {}
	Render& operator= (const Render&) {}

public:
	static Render& Instance();

	void Draw(Vector2 pos, Vector2 size, int grp);
	void FlagDraw(Vector2 pos, Vector2 size, int grp, bool dr, int alpha = 255);
	void RectDraw(Object& object, bool reverse = FALSE);
	void AlphaDraw(Object& object, bool reverse = FALSE, int alpha = 255);
	void FlagDraw(Object& object, bool dr, int alpha = 255);

	void ExtendDraw(Vector2 pos, Vector2 extendPos, int grp);
	void ExtendDraw(Vector2 pos, Vector2 size, Vector2 extend, int grp);
	void ExtendDrawRefPos(Object& object, Vector2 extendPos);
	void ExtendDrawRefMul(Object& object, Vector2 extend);

	void RotaDraw(Vector2 centerPos, float extend, float angle, int grp, bool reverse = FALSE);

	void BrightDraw(Vector2 pos, Vector2 size, int grp, int BrightColorR = 255, int BrightColorG = 255, int BrightColorB = 255, bool reverse = FALSE);

	void BrightDraw(Object & object, int BrightColorR, int BrightColorG, int BrightColorB, bool reverse = FALSE);

	void RectParticle(Vector2 pos, int particleNumber, int particleSize, int grp, bool reverse = FALSE);
	void LineDraw(Vector2 start, Vector2 end, unsigned int color);
	void StringDraw(Vector2 pos, const TCHAR* str);
	void StringDraw(Vector2 pos, const TCHAR* str, unsigned int color);
	void NumberDraw(Vector2 pos, int number, int grp, bool TRlFLr = TRUE);
	void NumberDraw_Small (Vector2 pos, int number, int grp);


	void DrawShake(Object& object, bool reverse = 255);
	void ShakeChange();
	void ShakeStop();

	int Digit(int digit);

private:
	int shake = 0;
	bool change = false;
};