#include "Render.h"

////Render::Instance().���\�b�h��();�Ŏg����


//�C���X�^���X�������\�b�h
Render & Render::Instance()
{
	static std::unique_ptr<Render> instance(new Render());

	return *instance;
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
