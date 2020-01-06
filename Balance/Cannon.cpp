#include "Cannon.h"
#include "DxLib.h"
#include "Bullet.h"
#include "Enemy.h"
#include <typeinfo.h>
#include "Input.h"
#include "Player.h"


//コンストラクタ　初期化並び
Cannon::Cannon(const Vector2 &position, GameObjectManager* objectManager, int listNum)
	:mListNum(listNum),
	underTouch(false),
	flipHorizontal(false),
	isDeadFlag(false)
{
	_position = position;
	_size = Vector2(32, 32);
	m_pObjectManager = objectManager;
	_grp = LoadGraph("../Texture/kari/battery_A.png");
	centerPosX = 0;      //最初は0で初期化
	Initialize();//初期化
}

Cannon::~Cannon()
{
}
//初期化
void Cannon::Initialize()
{
}
//描画
void Cannon::Draw()
{
	//最初は右方向
	Render::Instance().RectDraw(*this, flipHorizontal);
}
//更新
void Cannon::Update(float deltaTime)
{
	Shot();
	Move();
	m_pObjectManager->Update(deltaTime);
	m_pObjectManager->Draw();

}
//解放
void Cannon::Release()
{
}
bool Cannon::IsDead()
{
	return isDeadFlag;
}
void Cannon::Hit(Object & object)
{
	//弾に関しては当たり判定を取らない
	if (typeid(object) == typeid(Bullet)) return;

	CurrentPosition(object);  //当たった方向への押し出し
	//当たったのが敵なら
	if (typeid(object) == typeid(Enemy))
	{
		isDeadFlag = true;
	} 
	

	//当たった時方向が下で、かつ、当たったものがPlayerかCannon
	if (_direction == Direction::Bottom &&
		( typeid(object) == typeid(Cannon) || typeid(object) == typeid(Player)))
	{

		
		_velocity.x = object.Velocity().x;
		//一回触れていたらリターン
		if (underTouch) return;
		underTouch = true;
		//centerPosX = (_position.x + _size.x / 2) - (object.Position().x + object.Size().x / 2);
	}
	


}
//移動
void Cannon::Move()
{

	//敵・弾以外のオブジェクトの上に乗ったら
	if (_direction == Direction::Bottom)
	{
		gravity = 0;
	}
	else
	{
		underTouch = false;  //下に何もなかったらfalse
		gravity = 2.0f;
	}


	_velocity.x += reaction;  //横方向の移動（重力）
	_velocity.y = gravity;   //縦方向への移動


	_position += _velocity;
	_velocity = Vector2(0, 0);
	reaction = 0;
}

void Cannon::Shot()
{
	//ゲームパッドの押されたボタンに合わせて反動をつける
	//左
	if (Input::Instance().GetButtonTrigger(XINPUT_BUTTON_LEFT_SHOULDER, DX_INPUT_PAD1))
	{
		reaction = -1;
		m_pObjectManager->Add(new Bullet(_position + Vector2(16, 16), Vector2(1, 0)));
	}

	//右
	if (Input::Instance().GetButtonTrigger(XINPUT_BUTTON_RIGHT_SHOULDER, DX_INPUT_PAD1))
	{
		reaction = 1;
		m_pObjectManager->Add(new Bullet(_position + Vector2(16, 16), Vector2(-1, 0)));
	}
}