#include "EnemyGenerateManager.h"
#include <fstream>
#include <sstream>
#include "Enemy.h"
#include "WindowInfo.h"


EnemyGenerateManager::EnemyGenerateManager()
{
}


EnemyGenerateManager::~EnemyGenerateManager()
{
}

void EnemyGenerateManager::Initialize(GameObjectManager *objectManager)
{
	generateFlag = true;

	m_pGameObjectManager = objectManager;
	//�}�b�v��ǂݍ���
	std::ifstream ifs("data\\generateTime.csv");

	//�t�@�C���̓ǂݍ��݂ɐ���������
	
	if (ifs)
	{
		//���������s���ǂݍ���
		std::string line;
		while (getline(ifs, line))
		{
			//�ǂݍ��񂾕�������J���}��؂�ŕ���
			std::vector<float> data = Split(line);

			//�}�b�v�����i�[
			_generateTime.push_back(data);
		}

		_generateItr = _generateTime.begin();

		_generate = *_generateItr;
	}
}

void EnemyGenerateManager::Update(float nowTime, int cannonCnt)
{
	cannonCount = cannonCnt;

	if (cannonCount == 0 || _generateTime.empty() || !generateFlag)
	{
		return;
	}

	auto itr = _generate.begin();

	if (*itr > nowTime)
	{
		return;
	}

	itr++;

	for (auto i = 0; i < *itr; i++)
	{
		Generate(cannonCount);
	}

	if (_generateItr == _generateTime.end())
	{
		generateFlag = false;
		return;
	}

	_generateItr++;
	_generate = *_generateItr;
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
			WindowInfo::WindowHeight - GROUNDHEIGHT - PLAYERTEXTUREY - ((GetRand(cannonCnt - 1) + 1) * TEXTURESIZEY));
		m_pGameObjectManager->Add(new Enemy(generatePos, Vector2(1, 0)));
	}
	//�E���甭�˂����G
	else
	{
		Vector2 generatePos = Vector2(
			WindowInfo::WindowWidth,
			WindowInfo::WindowHeight - GROUNDHEIGHT - PLAYERTEXTUREY - ((GetRand(cannonCnt - 1) + 1) * TEXTURESIZEY));
		m_pGameObjectManager->Add(new Enemy(generatePos, Vector2(-1, 0)));
	}
}


std::vector<float> EnemyGenerateManager::Split(const std::string & str, char delim)
{
	//�����񑀍���s�����ߕ�����X�g���[����錾
	std::stringstream iss(str);
	std::string tmp;
	std::vector<float> enemyRow;

	//��������J���}��؂�œǂݍ���
	while (getline(iss, tmp, delim))
	{//atoi->������𐔎���
		enemyRow.push_back(std::atoi(tmp.c_str()));
	}

	return enemyRow;
}
