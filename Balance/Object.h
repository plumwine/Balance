#pragma once
#include "Vector2.h"

//	ゲームオブジェクトクラス
class Object
{
public:
	//	コンストラクタ
	Object(Vector2 position, Vector2 size, int grNum);

	//	初期化
	virtual void Initialize();

	//	描画
	virtual void Draw();

	//	更新
	virtual void Update();

	//	解放
	virtual void Release();


	//	矩形対矩形の判定
	bool RectCollision(const Object& rect)
	{
		Vector2 rectAPos = Position();
		Vector2 rectBPos = rect.Position();
		Vector2 rectASize = Size();
		Vector2 rectBSize = rect.Size();
		auto dx = abs((rectAPos.x + rectASize.x / 2) - (rectBPos.x + rectBSize.x / 2));
		auto dy = abs((rectAPos.y + rectASize.y / 2) - (rectBPos.y + rectBSize.y / 2));

		return (dx < (rectASize.x + rectBSize.x) / 2 && dy < (rectASize.y + rectBSize.y) / 2);
	}

	//	メンバ関数にconstを付与する事で
	//	その関数内でのメンバ変数の変更を禁止にする
	Vector2 Position() const { return _position; }
	Vector2 Size() const { return _size; }
	int Grp() const { return _grp; }

protected:
	Vector2 _position;		//	座標
	Vector2 _size;			//	サイズ
	int _grp;				//  画像ID
};