#include "Render.h"

////Render::Instance()::���\�b�h��();�Ŏg����


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
		object.Position().x,
		object.Position().y,
		0, 0,
		object.Size().x,
		object.Size().y,
		object.Grp(), TRUE
	);
}

//��`�`��(���]�Ή�)
//TRUE�Ŕ��]
void Render::RectDraw(Object& object, bool reverse)
{
	DrawRectGraph(
		object.Position().x,
		object.Position().y,
		0, 0,
		object.Size().x,
		object.Size().y,
		object.Grp(), TRUE, reverse
	);
}

//���̕`��
//1.�n�_�@2.�I�_�@3.�F
void Render::LineDraw(Vector2 start, Vector2 end, unsigned int color)
{
	DrawLine(
		start.x, start.y,
		end.x, end.y,
		color
	);
}

//�F�w��Ȃ������`��
void Render::StringDraw(Vector2 pos, const TCHAR* str)
{
	DrawString(
		pos.x, pos.y, str, 0);
}

//�F�w�肠�蕶���`��
void Render::StringDraw(Vector2 pos, const TCHAR* str, unsigned int color)
{
	DrawString(
		pos.x, pos.y, str, color);
}