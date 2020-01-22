#include "Player.h"
#include "Cannon.h"
#include "DxLib.h"
#include "Input.h"
#include "GraphFactory.h"
#include "GamePlayManager.h"

Player::Player(const Vector2 &position)
	:speed(250),
	maxAnimTime(2.0f),
	maxAnimNum(1)

{
	_position = position;
	_size = Vector2(104,128);
	_grp = LoadGraph("../Texture/master/PlayMove.png");
	Initialize();
}


Player::~Player()
{
	
}

void Player::Initialize()
{
	animNum = 0;
	animTime = 0;
}

void Player::Draw()
{
	//Render::Instance().RectParticle(_position,animNum,104,_grp);
	DrawRectGraph(
		(int)_position.x,
		(int)_position.y,
		animNum * _size.x,
		0,//particleNumber * particleSize,
		_size.x,
		_size.y,
		_grp, TRUE, false
	);
}

void Player::Update(float deltaTime)
{
	Move(deltaTime);

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

void Player::Release()
{
}
//プレイヤーは死なない
bool Player::IsDead()
{
	return false;
}
//当たった時の処理
void Player::Hit(Object & object)
{
	//CurrentPosition(object);  //当たった方向への押し出し
}

//移動
void Player::Move(float deltaTime)
{
	GamePlayManager::Instance().GetPlayerPos(_position);

	//アナログパッドの入力情報
	GetJoypadAnalogInput(&input_x, &input_y, DX_INPUT_KEY_PAD1);
	
	float inputPercentage = (float)input_x / 1000;   //inputが-1000～1000を返すため1000で割って割合を出す
	_velocity.x = inputPercentage * speed ;
	_position.x += _velocity.x * deltaTime;   //Playerは横移動しかしないため
	
}