#pragma once
#include <DxLib.h>
#include "WindowInfo.h"

class Fps {
	int startTime;         //測定開始時刻
	int count;             //カウンタ
	float fps;             //fps
	static const int N = 60;//平均を取るサンプル数
	static const int FPS = 60;	//設定したFPS

	int backTime; //1フレーム前の時間
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
		if (count == 0) { //1フレーム目なら時刻を記憶
			startTime = nowTime;
		}
		if (count == N) { //60フレーム目なら平均を計算する
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
		int tookTime = GetNowCount() - startTime;	//かかった時間
		int waitTime = count * 1000 / FPS - tookTime;	//待つべき時間
		if (waitTime > 0) {
			Sleep(waitTime);	//待機
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