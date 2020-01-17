#include "Music.h"

#define STR(var) #var


//�C���X�^���X�������\�b�h
Music & Music::Instance()
{
	static std::unique_ptr<Music> instance(new Music());

	return *instance;
}

int Music::LoadSound(std::string filepath)
{
	int mem = LoadSoundMem(filepath.c_str());

	if (mem == -1)
	{
		return NULL;
	}

	return mem;
}


//���y���ŏ�����Đ�����
void Music::SoundFileStart(int mem)
{
	if (mem == NULL)
	{
		return;
	}
	PlaySoundMem(mem, DX_PLAYTYPE_NORMAL);
}

//���y���ŏ�����Đ�����
//(�������Ńm�[�}���A�o�b�N�O���E���h�A���[�v��؂�ւ�����)
void Music::SoundFileStart(int mem, int PlayType)
{
	if (mem == NULL)
	{
		return;
	}
	PlaySoundMem(mem, PlayType);
}

void Music::SoundFileStartMid(int mem)
{
	if (mem == NULL)
	{
		return;
	}
	PlaySoundMem(mem, DX_PLAYTYPE_NORMAL, FALSE);
}

void Music::SoundFileStartMid(int mem, int PlayType)
{
	if (mem == NULL)
	{
		return;
	}
	PlaySoundMem(mem, PlayType, FALSE);
}

void Music::SoundStop(int mem)
{
	if (mem == NULL)
	{
		return;
	}
	StopSoundMem(mem);
}

void Music::SoundChangeVolume(int volume, int mem)
{
	if (mem == NULL || volume > 255 || volume < 0)
	{
		return;
	}

	ChangeVolumeSoundMem(volume, mem);
}

bool Music::CheckSoundMem(int mem)
{
	int check = CheckSoundMem(mem);

	if (check == 1)
	{
		return true;
	}
	else if (check == 0)
	{
		return false;
	}
	else
	{
		return NULL;
	}
}

void Music::SoundDeleteMem(int mem)
{
	if (mem == NULL)
	{
		return;
	}
	DeleteSoundMem(mem);
}

void Music::SoundAllDeleteMem()
{
	InitSoundMem();
}