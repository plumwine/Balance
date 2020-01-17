#include "Cannon.h"
#include "DxLib.h"
#include "Bullet.h"
#include "Enemy.h"
#include <typeinfo.h>
#include "Music.h"
#include "Player.h"
#include "Ground.h"
#include "GamePlayManager.h"

//コンストラクタ　初期化並び
Cannon::Cannon(const Vector2 &position, GameObjectManager* objectManager,int num)
	:underTouch(false),
	flipHorizontal(false),
	isDeadFlag(false),
	enemyDir(Vector2(1,0))

{
	_position = position;
	_size = Vector2(32, 32);
	m_pObjectManager = objectManager;
	_grp = LoadGraph("../Texture/master/Hiyoko.png");
	centerPosX = 0;      //最初は0で初期化
	shot_se = Music::Instance().LoadSound("../Music/boyon1.wav");
	nowNum = num;
	input = Input();
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
	Move(deltaTime);
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
	if (typeid(object) == typeid(Bullet))
	{
		return;
	}
	//当たったのが敵なら
	if (typeid(object) == typeid(Enemy) || typeid(object) == typeid(Ground))
	{
		GamePlayManager::Instance().DeadCannon();
		isDeadFlag = true;
		return;
	} 
	

	//当たった時方向が下で、かつ、当たったものがPlayerかCannon
	if (_direction == Direction::Bottom &&
		( typeid(object) == typeid(Cannon) || typeid(object) == typeid(Player)))
	{
		CurrentPosition(object);  //当たった方向への押し出し
		nowNum = (int)((_position.y + _size.y / 2) - 496) / 32;
		_velocity.x = (0.8f * object.Velocity().x) / (10 / nowNum);
		//一回触れていたらリターン
		if (underTouch) return;
		underTouch = true;
	}

}
int Cannon::GetNowNum()
{
	return nowNum;
}
void Cannon::GetObj(Object * obj)
{
	if (obj == nullptr) return;
	m_pObj = obj;
	enemyDir =  m_pObj->Position() - _position;
	enemyDir.Normalized();
}
//移動
void Cannon::Move(float deltaTime)
{

	//敵・弾以外のオブジェクトの上に乗ったら
	if (_direction == Direction::Bottom)
	{
		gravity = 0;
	}
	else
	{
		gravity = 150.0f;
	}
	
	_velocity.x += reaction;  //横方向の移動
	_velocity.y = gravity;    //縦方向への移動（重力）


	_position += _velocity * deltaTime;
	
	_velocity = Vector2(0, 0);

	if (reaction >11)
	{
		reaction -= 10;
	}
	if (reaction < -11)
	{
		reaction += 10;
	}
	if (reaction >= -10 && reaction <= 10)
	{
		reaction = 0;
	}
}

void Cannon::Shot()
{
	if (!underTouch) return;

	//ゲームパッドの押されたボタンに合わせて反動をつける
	//左
	if (input.GetButtonTrigger(INPUT_BUTTON_LB, DX_INPUT_PAD1))
	{
		Music::Instance().SoundFileStart(shot_se);
		Vector2 kariPos = _position;
		flipHorizontal = true;
		reaction = (float)(15 *( 20 - nowNum));   //大砲の調節
		m_pObjectManager->Add(new Bullet(kariPos + Vector2(8, 8), Vector2(-1,0)));// enemyDir));
	}

	//右
	if (input.GetButtonTrigger(INPUT_BUTTON_RB, DX_INPUT_PAD1))
	{
		//Music::Instance().SoundFileStart(shot_se);
		Vector2 kariPos = _position;
		flipHorizontal = false;
		reaction = (float)(-15 *( 20 - nowNum));  //大砲の調節
		m_pObjectManager->Add(new Bullet(kariPos + Vector2(8, 8), Vector2(1, 0)));//enemyDir));
	}
}