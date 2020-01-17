#include "Render.h"

////Render::Instance().���\�b�h��();�Ŏg����


//�C���X�^���X�������\�b�h
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
//�ʏ��`�`��
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

//��`�`��(���]�Ή�)
//TRUE�Ŕ��]
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


//pos=>�n�_���W extendPos=>�I�_���W
void Render::ExtendDraw(Vector2 pos, Vector2 extendPos, int grp)
{
	DrawExtendGraph(
		(int)pos.x, (int)pos.y,
		(int)extendPos.x, (int)extendPos.y,
		grp, TRUE
	);
}
//extend�ɉ��{�ɂ��邩�����
void Render::ExtendDraw(Vector2 pos, Vector2 size, Vector2 extend, int grp)
{
	DrawExtendGraph(
		(int)pos.x, (int)pos.y,
		(int)(pos.x + size.x * extend.x), (int)(pos.y + size.y * extend.y),
		grp, TRUE
	);
}
//extendPos�͏I�_�̍��W
void Render::ExtendDrawRefPos(Object & object, Vector2 extendPos)
{
	DrawExtendGraph(
		(int)object.Position().x, (int)object.Position().y,
		(int)extendPos.x, (int)extendPos.y,
		object.Grp(), TRUE
	);
}
//extend�͉��{��
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

//���̕`��
//1.�n�_�@2.�I�_�@3.�F
void Render::LineDraw(Vector2 start, Vector2 end, unsigned int color)
{
	DrawLine(
		(int)start.x, (int)start.y,
		(int)end.x, (int)end.y,
		color
	);
}

//�F�w��Ȃ������`��
void Render::StringDraw(Vector2 pos, const TCHAR* str)
{
	DrawString(
		(int)pos.x, (int)pos.y, str, 0);
}

//�F�w�肠�蕶���`��
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

//�������ɗh�炷
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

//�������ɗh�炷(���])
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

//�h�炵�Ă���ԌĂ�
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

//�h�炷�̂��~�߂�
void Render::ShakeStop()
{
	shake = 0;
}
