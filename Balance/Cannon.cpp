#include "Cannon.h"
#include "DxLib.h"
#include "Bullet.h"
#include "Enemy.h"
#include <typeinfo.h>
#include "Music.h"
#include "Player.h"
#include "Ground.h"
#include "GamePlayManager.h"
#include "WaveLine.h"

//コンストラクタ　初期化並び
Cannon::Cannon(const Vector2 &position, GameObjectManager* objectManager,int num)
	:underTouch(false),
	flipHorizontal(false),
	isDeadFlag(false),
	enemyDir(Vector2(1,0)),
	maxAnimTime(2.0f),
	maxAnimNum(1),
	shotWaitTime(0),
	maxShotWaitTime(9)
{
	_position = position;
	_size = Vector2(72, 96);
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
	DrawRectGraph(
		(int)_position.x,
		(int)_position.y,
		animNum * _size.x,
		0,
		_size.x,
		_size.y,
		_grp, TRUE, false
	);
}
//更新
void Cannon::Update(float deltaTime)
{
	Shot(deltaTime);
	Move(deltaTime);

	//アニメーション
	animTime += 0.1;
	if (animTime >= maxAnimTime)
	{
		animTime = 0;
		animNum++;
		if (animNum > maxAnimNum)
		{
			animNum = 0;
		}
	}
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
	//CurrentPosition(object);  //当たった方向への押し出し


	//当たった時方向が下で、かつ、当たったものがPlayerかCannon   (_direction == Direction::Bottom || _direction == Direction::Top)&&
	if ((_direction == Direction::Bottom || _direction == Direction::Top) && ( typeid(object) == typeid(Cannon) || typeid(object) == typeid(Player)))
	{


		CurrentPosition(object);  //当たった方向への押し出し
		nowNum = (int)((_position.y + _size.y / 2) + 248) / 96;

		if (nowNum <= 1)
		{
			nowNum = 1;
		}
		if (nowNum <= 3)
		{
			GamePlayManager::Instance().SetWaveClear();
		}

		_velocity.x = (0.2f * object.Velocity().x) / (10 / nowNum);
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
		gravity = 200.0f;
	}
	
	_velocity.x += reaction;  //横方向の移動
	_velocity.y = gravity;    //縦方向への移動（重力）

	_position += _velocity * deltaTime;
	
	

	_velocity = Vector2(0, 0);

	//ウィンドウ範囲外に出たら消す
	if (_position.x < 0 ||
		_position.x > WindowInfo::WindowWidth)
	{
		GamePlayManager::Instance().DeadCannon();
		isDeadFlag = true;
	}
	if (_position.y < -500 ||
		_position.y > WindowInfo::WindowHeight)
	{
		GamePlayManager::Instance().DeadCannon();
		isDeadFlag = true;
	}


	//大砲の完成の減速
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
//弾の発射
void Cannon::Shot(float deltaTime)
{
	if (!underTouch) return;


	shotWaitTime++;
	
	if (!(shotWaitTime >= maxShotWaitTime))
	{
		return;
	}
	else
	{
		shotWaitTime = maxShotWaitTime;
	}



	//ゲームパッドの押されたボタンに合わせて反動をつける
	//左
	if (input.GetButtonTrigger(INPUT_BUTTON_LB, DX_INPUT_PAD1))
	{
		shotWaitTime = 0;
		Music::Instance().SoundFileStart(shot_se);
		Vector2 kariPos = _position;
		flipHorizontal = true;
		reaction += (float)(25 *( 40 - nowNum*3));   //大砲の調節
		m_pObjectManager->Add(new Bullet(kariPos + Vector2(16, 16), Vector2(-1,0)));// enemyDir));
	}
	if (shotWaitTime == 0)
	{
		return;
	}


	//右
	if (input.GetButtonTrigger(INPUT_BUTTON_RB, DX_INPUT_PAD1))
	{
		shotWaitTime = 0;
		Music::Instance().SoundFileStart(shot_se);
		Vector2 kariPos = _position;
		flipHorizontal = false;
		reaction += (float)(- 25*( 40 - nowNum*3));  //大砲の調節
		m_pObjectManager->Add(new Bullet(kariPos + Vector2(16, 16), Vector2(1, 0)));//enemyDir));
	}
}