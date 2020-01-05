#include "Player.h"
#include "Cannon.h"
#include "DxLib.h"

Player::Player(const Vector2 &position, GameObjectManager*objectManager)
	:speed(5)
{
	_position = position;
	_size = Vector2(38,38);
	m_pObjectManager = objectManager;
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
//�����������̏���
void Player::Hit(Object & object)
{
	//CurrentPosition(object);  //�������������ւ̉����o��
}


//�ړ�
void Player::Move()
{
	//�A�i���O�p�b�h�̓��͏��
	GetJoypadAnalogInput(&input_x, &input_y, DX_INPUT_KEY_PAD1);
	
	float inputPercentage = (float)input_x / 1000;   //input��-1000�`1000��Ԃ�����1000�Ŋ����Ċ������o��
	_position.x += inputPercentage * speed;   //Player�͉��ړ��������Ȃ�����
	
}

//������
void Player::Generate()
{
	m_pObjectManager->Add(new Cannon(Vector2(100, 100), m_pObjectManager, 0));
}
