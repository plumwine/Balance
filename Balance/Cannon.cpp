#include "Cannon.h"
#include "DxLib.h"
#include "Bullet.h"
#include "Enemy.h"
#include <typeinfo.h>
#include "Music.h"
#include "Player.h"
#include "Ground.h"
#include "GamePlayManager.h"

//�R���X�g���N�^�@����������
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
	centerPosX = 0;      //�ŏ���0�ŏ�����
	shot_se = Music::Instance().LoadSound("../Music/boyon1.wav");
	nowNum = num;
	input = Input();
	Initialize();//������
}

Cannon::~Cannon()
{
}
//������
void Cannon::Initialize()
{
}
//�`��
void Cannon::Draw()
{
	//�ŏ��͉E����
	Render::Instance().RectDraw(*this, flipHorizontal);
}
//�X�V
void Cannon::Update(float deltaTime)
{
	Shot();
	Move(deltaTime);
}
//���
void Cannon::Release()
{
}
bool Cannon::IsDead()
{
	return isDeadFlag;
}
void Cannon::Hit(Object & object)
{
	//�e�Ɋւ��Ă͓����蔻������Ȃ�
	if (typeid(object) == typeid(Bullet))
	{
		return;
	}
	//���������̂��G�Ȃ�
	if (typeid(object) == typeid(Enemy) || typeid(object) == typeid(Ground))
	{
		GamePlayManager::Instance().DeadCannon();
		isDeadFlag = true;
		return;
	} 
	

	//�������������������ŁA���A�����������̂�Player��Cannon
	if (_direction == Direction::Bottom &&
		( typeid(object) == typeid(Cannon) || typeid(object) == typeid(Player)))
	{
		CurrentPosition(object);  //�������������ւ̉����o��
		nowNum = (int)((_position.y + _size.y / 2) - 496) / 32;
		_velocity.x = (0.8f * object.Velocity().x) / (10 / nowNum);
		//���G��Ă����烊�^�[��
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
//�ړ�
void Cannon::Move(float deltaTime)
{

	//�G�E�e�ȊO�̃I�u�W�F�N�g�̏�ɏ������
	if (_direction == Direction::Bottom)
	{
		gravity = 0;
	}
	else
	{
		gravity = 150.0f;
	}
	
	_velocity.x += reaction;  //�������̈ړ�
	_velocity.y = gravity;    //�c�����ւ̈ړ��i�d�́j


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

	//�Q�[���p�b�h�̉����ꂽ�{�^���ɍ��킹�Ĕ���������
	//��
	if (input.GetButtonTrigger(INPUT_BUTTON_LB, DX_INPUT_PAD1))
	{
		Music::Instance().SoundFileStart(shot_se);
		Vector2 kariPos = _position;
		flipHorizontal = true;
		reaction = (float)(15 *( 20 - nowNum));   //��C�̒���
		m_pObjectManager->Add(new Bullet(kariPos + Vector2(8, 8), Vector2(-1,0)));// enemyDir));
	}

	//�E
	if (input.GetButtonTrigger(INPUT_BUTTON_RB, DX_INPUT_PAD1))
	{
		//Music::Instance().SoundFileStart(shot_se);
		Vector2 kariPos = _position;
		flipHorizontal = false;
		reaction = (float)(-15 *( 20 - nowNum));  //��C�̒���
		m_pObjectManager->Add(new Bullet(kariPos + Vector2(8, 8), Vector2(1, 0)));//enemyDir));
	}
}