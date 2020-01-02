#pragma once
#include <DxLib.h>
#include <string>

class Input {

private:
	Input() {}
	Input(const Input&) {}
	Input& operator= (const Input&) {}

public:
	static Input& Instance();

	int GetInputState();
	int GetInputState(int inputType);

};