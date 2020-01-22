#include "EnemyGenerateManager.h"
#include <fstream>
#include <sstream>
#include "Enemy.h"
#include "WindowInfo.h"
#include "GamePlayManager.h"


EnemyGenerateManager::EnemyGenerateManager()
{
}


EnemyGenerateManager::~EnemyGenerateManager()
{
}

void EnemyGenerateManager::Initialize(GameObjectManager *objectManager)
{

	m_pGameObjectManager = objectManager;
	//�}�b�v��ǂݍ���
	std::ifstream ifs("data\\generateTime.csv");

	//�t�@�C���̓ǂݍ��݂ɐ���������
	
	if (ifs)
	{
		std::string s;
		while (!ifs.eof())
		{
			std::getline(ifs, s);
			_generateTime.push_back(atoi(s.c_str()));
		}
	}
}

void EnemyGenerateManager::SetCSV(std::string filePath)
{//�}�b�v��ǂݍ���
	std::ifstream ifs(filePath);

	//�t�@�C���̓ǂݍ��݂ɐ���������

	if (ifs)
	{
		std::string s;
		while (!ifs.eof())
		{
			std::getline(ifs, s);
			_generateTime.push_back(atoi(s.c_str()));
		}
	}
}

void EnemyGenerateManager::Update(float nowTime, int cannonCnt)
{
	cannonCount = cannonCnt;

	if (cannonCount == 0 || _generateTime.empty())
	{
		return;
	}

	float time = _generateTime.front();
	if (time < nowTime)
	{
		Generate(cannonCount);
		_generateTime.pop_front();
	}
}

void EnemyGenerateManager::Generate(int cannonCnt)
{
	///�����_��(0�`�����̐����܂ސ�)()�̒��Ɖ��̍�����̓G�̔�r���Z�q�̉E�ӂ̐��l��ς��邱�ƂŔ䗦��ύX�ł���
	int randSpawnX = GetRand(5);

	//�����甭�˂����G
	if (randSpawnX <= 1)
	{
		Vector2 generatePos = Vector2(
			0,
			WindowInfo::WindowHeight - GROUNDHEIGHT - PLAYERTEXTUREY - ((GetRand(cannonCnt - 1) + 1) * CANNONTEXTURESIZEY) + (CANNONTEXTURESIZEY / 2 - THISTEXTURESIZEY / 2));
		m_pGameObjectManager->Add(new Enemy(generatePos, Vector2(1, 0), GamePlayManager::Instance().GetWave(),true));
	}
	//�E���甭�˂����G
	else
	{
		Vector2 generatePos = Vector2(
			WindowInfo::WindowWidth,
			WindowInfo::WindowHeight - GROUNDHEIGHT - PLAYERTEXTUREY - ((GetRand(cannonCnt - 1) + 1) * CANNONTEXTURESIZEY) + (CANNONTEXTURESIZEY / 2 - THISTEXTURESIZEY / 2));
		m_pGameObjectManager->Add(new Enemy(generatePos, Vector2(-1, 0),GamePlayManager::Instance().GetWave(),false));
	}
}

void EnemyGenerateManager::Generate(int cannonCnt, int R0L1)
{
	//�����甭�˂����G
	if (R0L1 == 1)
	{
		Vector2 generatePos = Vector2(
			0,
			//�@��ʏc���@�@�@�@�@�@ - �@�n�ʂ̍��� - �v���C���[�̍��� - �����_���̖C��̈ʒu        *  �C��̍���         +  �i�C��̍����@/�@2�@-�@�G�̍����@/�@2�j�@�����W���킹�̂��Ƃ̒��S���킹
			WindowInfo::WindowHeight - GROUNDHEIGHT - PLAYERTEXTUREY - ((GetRand(cannonCnt - 1) + 1) * CANNONTEXTURESIZEY) + (CANNONTEXTURESIZEY / 2 - THISTEXTURESIZEY / 2));
		m_pGameObjectManager->Add(new Enemy(generatePos, Vector2(1, 0), GamePlayManager::Instance().GetWave(),true));
	}
	//�E���甭�˂����G
	else
	{
		Vector2 generatePos = Vector2(
			WindowInfo::WindowWidth,
			WindowInfo::WindowHeight - GROUNDHEIGHT - PLAYERTEXTUREY - ((GetRand(cannonCnt - 1) + 1) * CANNONTEXTURESIZEY) + (CANNONTEXTURESIZEY / 2 - THISTEXTURESIZEY / 2));
		m_pGameObjectManager->Add(new Enemy(generatePos, Vector2(-1, 0), GamePlayManager::Instance().GetWave(),false));
	}
}
