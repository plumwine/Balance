#pragma once
#include <DxLib.h>
#include <string>
#include <map>
#include "Vector2.h"

#define INPUT_BUTTON_A 16
#define INPUT_BUTTON_B 32
#define INPUT_BUTTON_X 64
#define INPUT_BUTTON_Y 128
#define INPUT_BUTTON_LB 256
#define INPUT_BUTTON_RB 512
#define INPUT_BUTTON_START 2048
#define INPUT_BUTTON_BACK 1024
#define INPUT_BUTTON_UP 8
#define INPUT_BUTTON_DOWN 1
#define INPUT_BUTTON_RIGHT 4
#define INPUT_BUTTON_LEFT 2
#define INPUT_BUTTON_LEFT_UP 10
#define INPUT_BUTTON_LEFT_DOWN 3
#define INPUT_BUTTON_RIGHT_DOWN 5
#define INPUT_BUTTON_RIGHT_UP 12

class Input {

private:
	Input() {}
	Input(const Input&) {}
	Input& operator= (const Input&) {}

public:
	static Input& Instance();

	int GetInputState();
	int GetInputState(int inputType);

	Vector2 GetAnalog();
	Vector2 GetAnalog(int inputType);

	int GetAnalogX();
	int GetAnalogX(int inputType);

	void StartJoypadVibration(int Power, int Time);
	void StopJoypadVibration();
	void StartJoypadVibration(int Power, int Time, int inputType);
	void StopJoypadVibration(int inputType);

	bool GetButtonTrigger(int key, int inputType);
	bool GetButtonState(int key, int inputType);

private:
	std::map<int, int> triggerMap;
};