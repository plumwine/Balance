#pragma once
#include "Vector2.h"
#include "Render.h"
#include <typeinfo.h>
#include "GraphFactory.h"



enum Direction
{
	Top, Bottom, Right, Left, None
};

//	ゲームオブジェクトクラス
class Object
{
public:
	//	コンストラクタ
	Object() : _position(0, 0), _size(0, 0) {};

	//	初期化
	virtual void Initialize() = 0;

	//	描画
	virtual void Draw() =0;

	//	更新
	virtual void Update(float deltaTime) = 0;

	//	解放
	virtual void Release() = 0;
	//死亡判定
	virtual bool IsDead() = 0;
	//当たった時の処理
	virtual void Hit(Object& object) = 0;

	virtual void AreaHit(Object& object) = 0;

#pragma region 元々の機能


	//当たった方向に押し出し
	void CurrentPosition(Object& other)
	{
		Direction dir = _direction;

		switch (dir)
		{
		case(Direction::Top):
			_position.y = other.Position().y + _size.y;
			break;
		case(Direction::Right):
			_position.x = other.Position().x + _size.x;
			break;
		case(Direction::Left):
			_position.x = other.Position().x - _size.x;
			break;
		case(Direction::Bottom):
			_position.y = other.Position().y - _size.y;
			break;

		}
	}
	//	矩形対矩形の判定
	bool RectCollision(const Object& rect)
	{
		if (&rect == nullptr)
		{
			return false;
		}
		Vector2 rectAPos = Position();
		Vector2 rectBPos = rect.Position();
		Vector2 rectASize = Size();
		Vector2 rectBSize = rect.Size();
		auto dx = (rectAPos.x + rectASize.x / 2) - (rectBPos.x + rectBSize.x / 2);
		auto dy = (rectAPos.y + rectASize.y / 2) - (rectBPos.y + rectBSize.y / 2);

		if (abs(dx) < (rectASize.x + rectBSize.x) / 2 && abs(dy) < (rectASize.y + rectBSize.y) / 2)
		{
			_direction = ColDirection(Vector2(dx, dy), rectBSize);
			return true;
		}
		_direction = None;
		return false;
	}
	//当たった方向を返す
	Direction ColDirection(Vector2 dir, Vector2 otherSize)
	{
		Vector2 AddSize = _size + otherSize;

		float x = dir.x / AddSize.x;
		float y = dir.y / AddSize.y;

		if (abs(x) > abs(y))
		{
			if (x < 0)
				return Left;
			else
				return Right;
		}
		else
		{
			if (y < 0)
				return Bottom;
			else
				return Top;
		}
		return None;
	}

#pragma endregion

	//	メンバ関数にconstを付与する事で
	//	その関数内でのメンバ変数の変更を禁止にする
	Vector2 Position() const { return _position; }
	Vector2 Size() const { return _size; }
	Vector2 Velocity() const { return _velocity; }
	int Grp() const { return _grp; }
	Direction Dir() const { return _direction; }
protected:
	Vector2 _position;		//	座標
	Vector2 _velocity;      //  移動方向
	Vector2 _size;			//	サイズ
	int _grp;				//  画像ID
	Direction _direction;   //  当たった方向

};