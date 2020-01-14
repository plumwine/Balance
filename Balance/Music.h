#pragma once
#include <DxLib.h>
#include <string>



//âπÉfÅ[É^ñºóÒãì
enum MusicString
{

};

enum Type
{
	mp3,wav
};

class Music
{
private:
	Music() {}
	Music(const Music&) {}
	Music& operator= (const Music&) {}

public:
	static Music& Instance();

	int LoadSound(char *filePath);
	int LoadSound(MusicString music,Type dataType);
	void SoundFileStart(int mem);
	void SoundFileStart(int mem, int PlayType);
	void SoundFileStartMid(int mem);
	void SoundFileStartMid(int mem, int PlayType);
	void SoundStop(int mem);
	void SoundChangeVolume(int volume, int mem);

	bool CheckSoundMem(int mem);

	void SoundDeleteMem(int mem);
	void SoundAllDeleteMem();
};

