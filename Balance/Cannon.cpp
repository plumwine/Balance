#include "Cannon.h"
#include "DxLib.h"
#include "Bullet.h"
#include "Enemy.h"
#include <typeinfo.h>
#include "Input.h"
#include "Player.h"


//�R���X�g���N�^�@����������
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
	centerPosX = 0;      //�ŏ���0�ŏ�����
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
	Move();
	m_pObjectManager->Update(deltaTime);
	m_pObjectManager->Draw();

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
	if (typeid(object) == typeid(Bullet)) return;

	CurrentPosition(object);  //�������������ւ̉����o��
	//���������̂��G�Ȃ�
	if (typeid(object) == typeid(Enemy))
	{
		isDeadFlag = true;
	} 
	

	//�������������������ŁA���A�����������̂�Player��Cannon
	if (_direction == Direction::Bottom &&
		( typeid(object) == typeid(Cannon) || typeid(object) == typeid(Player)))
	{

		
		_velocity.x = object.Velocity().x;
		//���G��Ă����烊�^�[��
		if (underTouch) return;
		underTouch = true;
		//centerPosX = (_position.x + _size.x / 2) - (object.Position().x + object.Size().x / 2);
	}
	


}
//�ړ�
void Cannon::Move()
{

	//�G�E�e�ȊO�̃I�u�W�F�N�g�̏�ɏ������
	if (_direction == Direction::Bottom)
	{
		gravity = 0;
	}
	else
	{
		underTouch = false;  //���ɉ����Ȃ�������false
		gravity = 2.0f;
	}


	_velocity.x += reaction;  //�������̈ړ��i�d�́j
	_velocity.y = gravity;   //�c�����ւ̈ړ�


	_position += _velocity;
	_velocity = Vector2(0, 0);
	reaction = 0;
}

void Cannon::Shot()
{
	//�Q�[���p�b�h�̉����ꂽ�{�^���ɍ��킹�Ĕ���������
	//��
	if (Input::Instance().GetButtonTrigger(XINPUT_BUTTON_LEFT_SHOULDER, DX_INPUT_PAD1))
	{
		reaction = -1;
		m_pObjectManager->Add(new Bullet(_position + Vector2(16, 16), Vector2(1, 0)));
	}

	//�E
	if (Input::Instance().GetButtonTrigger(XINPUT_BUTTON_RIGHT_SHOULDER, DX_INPUT_PAD1))
	{
		reaction = 1;
		m_pObjectManager->Add(new Bullet(_position + Vector2(16, 16), Vector2(-1, 0)));
	}
}