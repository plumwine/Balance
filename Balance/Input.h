#pragma once
#include <DxLib.h>
#include <string>
#include "Vector2.h"

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
};