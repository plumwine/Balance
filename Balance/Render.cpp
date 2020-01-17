#include "Render.h"

////Render::Instance().メソッド名();で使える


//インスタンス生成メソッド
Render & Render::Instance()
{
	static std::unique_ptr<Render> instance(new Render());

	return *instance;
}

void Render::Draw(Vector2 pos, Vector2 size, int grp)
{
	DrawRectGraph(
		(int)pos.x,
		(int)pos.y,
		0, 0,
		(int)size.x,
		(int)size.y,
		grp, TRUE
	);
}

void Render::FlagDraw(Vector2 pos, Vector2 size, int grp, bool dr, int alpha = 255)
{
	if (dr)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawRectGraph(
			(int)pos.x,
			(int)pos.y,
			0, 0,
			(int)size.x,
			(int)size.y,
			grp, TRUE
		);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
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

void Render::AlphaDraw(Object & object, int alpha = 255)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawRectGraph(
		(int)object.Position().x,
		(int)object.Position().y,
		0, 0,
		(int)object.Size().x,
		(int)object.Size().y,
		object.Grp(), TRUE
	);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Render::AlphaDraw(Object & object, bool reverse, int alpha = 255)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawRectGraph(
		(int)object.Position().x,
		(int)object.Position().y,
		0, 0,
		(int)object.Size().x,
		(int)object.Size().y,
		object.Grp(), TRUE, reverse
	);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Render::FlagDraw(Object & object, bool dr, int alpha = 255)
{
	if (dr)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawRectGraph(
			(int)object.Position().x,
			(int)object.Position().y,
			0, 0,
			(int)object.Size().x,
			(int)object.Size().y,
			object.Grp(), TRUE
		);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}


//pos=>始点座標 extendPos=>終点座標
void Render::ExtendDraw(Vector2 pos, Vector2 extendPos, int grp)
{
	DrawExtendGraph(
		(int)pos.x, (int)pos.y,
		(int)extendPos.x, (int)extendPos.y,
		grp, TRUE
	);
}
//extendに何倍にするか入れる
void Render::ExtendDraw(Vector2 pos, Vector2 size, Vector2 extend, int grp)
{
	DrawExtendGraph(
		(int)pos.x, (int)pos.y,
		(int)(pos.x + size.x * extend.x), (int)(pos.y + size.y * extend.y),
		grp, TRUE
	);
}
//extendPosは終点の座標
void Render::ExtendDrawRefPos(Object & object, Vector2 extendPos)
{
	DrawExtendGraph(
		(int)object.Position().x, (int)object.Position().y,
		(int)extendPos.x, (int)extendPos.y,
		object.Grp(), TRUE
	);
}
//extendは何倍か
void Render::ExtendDrawRefMul(Object & object, Vector2 extend)
{
	DrawExtendGraph(
		(int)object.Position().x, (int)object.Position().y,
		(int)(object.Position().x + object.Size().x * extend.x), (int)(object.Position().y + object.Size().y * extend.y),
		object.Grp(), TRUE
	);
}


void Render::BrightDraw(Vector2 pos, Vector2 size, int grp, int BrightColorR = 255, int BrightColorG = 255, int BrightColorB = 255, bool reverse = FALSE)
{
	SetDrawBright(BrightColorR, BrightColorG, BrightColorB);

	DrawRectGraph(
		(int)pos.x,
		(int)pos.y,
		0, 0,
		(int)size.x,
		(int)size.y,
		grp, TRUE, reverse
	);

	SetDrawBright(255, 255, 255);
}

void Render::BrightDraw(Object & object, int BrightColorR, int BrightColorG, int BrightColorB, bool reverse = FALSE)
{
	SetDrawBright(BrightColorR, BrightColorG, BrightColorB);

	DrawRectGraph(
		(int)object.Position().x,
		(int)object.Position().y,
		0, 0,
		(int)object.Size().x,
		(int)object.Size().y,
		object.Grp(), TRUE, reverse
	);

	SetDrawBright(255, 255, 255);
}

void Render::RectParticle(Vector2 pos, int particleNumber, int particleSize, int grp)
{
	DrawRectGraph(
		(int)pos.x,
		(int)pos.y,
		particleNumber * particleSize,
		0,//particleNumber * particleSize,
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
		0,//particleNumber * particleSize,
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
	if (number == 0)
	{
		DrawRectGraph(
			pos.x,
			pos.y,
			0,
			0,
			16,
			16,
			grp, TRUE
		);
	}
	int count = 0;
	while (number != 0)
	{
		DrawRectGraph(
			pos.x + (count * 16),
			pos.y,
			(number % 10) * 16,
			0,
			16,
			16,
			grp, TRUE
		);
		number /= 10;
		count++;
	}
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
