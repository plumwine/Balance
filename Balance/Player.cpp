#include "Player.h"
#include "Cannon.h"
#include "DxLib.h"
#include "Input.h"
Player::Player(const Vector2 &position)
	:speed(5)
{
	_position = position;
	_size = Vector2(38,38);
	_grp = LoadGraph("../Texture/kari/player_A.png");
	Initialize();
}


Player::~Player()
{
}

void Player::Initialize()
{
}

void Player::Draw()
{
	Render::Instance().RectDraw(*this);
}

void Player::Update(float deltaTime)
{
	Move();
}

void Player::Release()
{
}

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
void Player::Move()
{
	//アナログパッドの入力情報
	GetJoypadAnalogInput(&input_x, &input_y, DX_INPUT_KEY_PAD1);
	
	float inputPercentage = (float)input_x / 1000;   //inputが-1000～1000を返すため1000で割って割合を出す
	_velocity.x = inputPercentage * speed;
	_position.x += _velocity.x;   //Playerは横移動しかしないため
	
}