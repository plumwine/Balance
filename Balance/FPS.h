#pragma once
#include <DxLib.h>
#include "WindowInfo.h"

class Fps {
	int startTime;         //����J�n����
	int count;             //�J�E���^
	float fps;             //fps
	static const int N = 60;//���ς����T���v����
	static const int FPS = 60;	//�ݒ肵��FPS

	int backTime; //1�t���[���O�̎���
	float deltaTime;
	float time;

	bool timeFlag;

public:
	Fps() {
		startTime = 0;
		count = 0;
		fps = 60;
		backTime = GetNowCount();
		deltaTime = 0;
		time = 0;
		timeFlag = false;
	}

	bool Update() {
		int nowTime = GetNowCount();

		deltaTime = (nowTime - backTime) / 1000.0;

		backTime = nowTime;
		if (count == 0) { //1�t���[���ڂȂ玞�����L��
			startTime = nowTime;
		}
		if (count == N) { //60�t���[���ڂȂ畽�ς��v�Z����
			int t = nowTime;
			fps = 1000.f / ((t - startTime) / (float)N);
			count = 0;
			startTime = t;
		}

		if (!timeFlag)
		{
			time += deltaTime;
		}
		count++;
		return true;
	}

	void Draw() {
#ifdef _DEBUG_
		DrawFormatString(20, 20, GetColor(255, 255, 255), "FPS : %.0f", fps);
#endif
	}

	void Wait() {
		int tookTime = GetNowCount() - startTime;	//������������
		int waitTime = count * 1000 / FPS - tookTime;	//�҂ׂ�����
		if (waitTime > 0) {
			Sleep(waitTime);	//�ҋ@
		}
	}

	float DeltaTime() {
		return deltaTime;
	}

	float GetTime() {
		return time;
	}

	void TimeStop() {
		timeFlag = true;
	}

	void TimeStart() {
		timeFlag = false;
	}
};