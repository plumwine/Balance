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

	void RectDraw(Object& object);
	void RectDraw(Object& object, bool reverse);
	void LineDraw(Vector2 start, Vector2 end, unsigned int color);
	void StringDraw(Vector2 pos, const TCHAR* str);
	void StringDraw(Vector2 pos, const TCHAR* str, unsigned int color);
};