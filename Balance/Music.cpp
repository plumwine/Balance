#include "Music.h"

#define STR(var) #var


//インスタンス生成メソッド
Music & Music::Instance()
{
	static std::unique_ptr<Music> instance(new Music());

	return *instance;
}

int Music::LoadSound(char * filePath)
{
	int mem = LoadSoundMem(filePath);

	if (mem == -1)
	{
		return NULL;
	}

	return mem;
}

int Music::LoadSound(MusicString music, Type dataType)
{
	std::string filePath = "../Music/";

	std::string name = STR(music);
	name = name.substr(13);
	filePath.append(name);

	filePath.append(".");

	name = STR(dataType);
	name = name.substr(6);
	filePath.append(name);

	int mem = LoadSoundMem(filePath.data());

	if (mem == -1)
	{
		return NULL;
	}

	return mem;
}

//音楽を最初から再生する
void Music::SoundFileStart(int mem)
{
	if (mem == NULL)
	{
		return;
	}
	PlaySoundMem(mem, DX_PLAYTYPE_NORMAL);
}

//音楽を最初から再生する
//(第二引数でノーマル、バックグラウンド、ループを切り替えられる)
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