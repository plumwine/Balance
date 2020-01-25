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

//�R���X�g���N�^�@����������
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
//�X�V
void Cannon::Update(float deltaTime)
{
	Shot(deltaTime);
	Move(deltaTime);

	//�A�j���[�V����
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
	//CurrentPosition(object);  //�������������ւ̉����o��


	//�������������������ŁA���A�����������̂�Player��Cannon   (_direction == Direction::Bottom || _direction == Direction::Top)&&
	if ((_direction == Direction::Bottom || _direction == Direction::Top) && ( typeid(object) == typeid(Cannon) || typeid(object) == typeid(Player)))
	{


		CurrentPosition(object);  //�������������ւ̉����o��
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
		gravity = 200.0f;
	}
	
	_velocity.x += reaction;  //�������̈ړ�
	_velocity.y = gravity;    //�c�����ւ̈ړ��i�d�́j

	_position += _velocity * deltaTime;
	
	

	_velocity = Vector2(0, 0);

	//�E�B���h�E�͈͊O�ɏo�������
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


	//��C�̊����̌���
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
//�e�̔���
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



	//�Q�[���p�b�h�̉����ꂽ�{�^���ɍ��킹�Ĕ���������
	//��
	if (input.GetButtonTrigger(INPUT_BUTTON_LB, DX_INPUT_PAD1))
	{
		shotWaitTime = 0;
		Music::Instance().SoundFileStart(shot_se);
		Vector2 kariPos = _position;
		flipHorizontal = true;
		reaction += (float)(25 *( 40 - nowNum*3));   //��C�̒���
		m_pObjectManager->Add(new Bullet(kariPos + Vector2(16, 16), Vector2(-1,0)));// enemyDir));
	}
	if (shotWaitTime == 0)
	{
		return;
	}


	//�E
	if (input.GetButtonTrigger(INPUT_BUTTON_RB, DX_INPUT_PAD1))
	{
		shotWaitTime = 0;
		Music::Instance().SoundFileStart(shot_se);
		Vector2 kariPos = _position;
		flipHorizontal = false;
		reaction += (float)(- 25*( 40 - nowNum*3));  //��C�̒���
		m_pObjectManager->Add(new Bullet(kariPos + Vector2(16, 16), Vector2(1, 0)));//enemyDir));
	}
}