#pragma once
#include <DxLib.h>
#include <string>



//âπÉfÅ[É^ñºóÒãì
enum MusicString
{

};


class Music
{
private:
	Music() {}
	Music(const Music&) {}
	Music& operator= (const Music&) {}

public:
	static Music& Instance();

	int LoadSound(std::string filePath);
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

