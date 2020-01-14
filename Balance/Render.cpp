#include "Render.h"

////Render::Instance().メソッド名();で使える


//インスタンス生成メソッド
Render & Render::Instance()
{
	static std::unique_ptr<Render> instance(new Render());

	return *instance;
}

//通常矩形描画
void Render::RectDraw(Object& object)
{
	DrawRectGraph(
		(int)object.Position().x,
		(int)object.Position().y,
		0, 0,
		(int)object.Size().x,
		(int)object.Size().y,
		object.Grp(), TRUE
	);
}

//矩形描画(反転対応)
//TRUEで反転
void Render::RectDraw(Object& object, bool reverse)
{
	DrawRectGraph(
		(int)object.Position().x,
		(int)object.Position().y,
		0, 0,
		(int)object.Size().x,
		(int)object.Size().y,
		object.Grp(), TRUE, reverse
	);
}

void Render::RectParticle(Vector2 pos, int particleNumber, int particleSize, int grp)
{
	DrawRectGraph(
		(int)pos.x,
		(int)pos.y,
		particleNumber * particleSize,
		particleNumber * particleSize,
		particleSize,
		particleSize,
		grp, TRUE
	);
}

void Render::RectParticle(Vector2 pos, int particleNumber, int particleSize, int grp, bool reverse)
{
	DrawRectGraph(
		(int)pos.x,
		(int)pos.y,
		particleNumber * particleSize,
		particleNumber * particleSize,
		particleSize,
		particleSize,
		grp, TRUE, reverse
	);
}

//線の描画
//1.始点　2.終点　3.色
void Render::LineDraw(Vector2 start, Vector2 end, unsigned int color)
{
	DrawLine(
		(int)start.x, (int)start.y,
		(int)end.x, (int)end.y,
		color
	);
}

//色指定なし文字描画
void Render::StringDraw(Vector2 pos, const TCHAR* str)
{
	DrawString(
		(int)pos.x, (int)pos.y, str, 0);
}

//色指定あり文字描画
void Render::StringDraw(Vector2 pos, const TCHAR* str, unsigned int color)
{
	DrawString(
		(int)pos.x, (int)pos.y, str, color);
}

void Render::NumberDraw(Vector2 pos, int number, int grp)
{
	DrawRectGraph(
		pos.x,
		pos.y,
		number * 16,
		0,
		16,
		16,
		grp, TRUE
	);
}

//横方向に揺らす
void Render::DrawShake(Object & object)
{
	DrawRectGraph(
		(int)object.Position().x + shake,
		(int)object.Position().y,
		0, 0,
		(int)object.Size().x,
		(int)object.Size().y,
		object.Grp(), TRUE
	);
}

//横方向に揺らす(反転)
void Render::DrawShake(Object & object, bool reverse)
{
	DrawRectGraph(
		(int)object.Position().x + shake,
		(int)object.Position().y,
		0, 0,
		(int)object.Size().x,
		(int)object.Size().y,
		object.Grp(), TRUE, reverse
	);
}

//揺らしている間呼ぶ
void Render::ShakeChange()
{
	if (shake > 20)
	{
		change = false;
	}
	else if (shake < -20)
	{
		change = true;
	}

	if (!change)
	{
		shake -= 15;
	}
	else
	{
		shake += 15;
	}
}

//揺らすのを止める
void Render::ShakeStop()
{
	shake = 0;
}
