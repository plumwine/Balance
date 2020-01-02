#include "Input.h"

Input & Input::Instance()
{
	static std::unique_ptr<Input> instance(new Input());

	return *instance;
}

int Input::GetInputState()
{
	int key = GetJoypadInputState(DX_INPUT_PAD1);

	return key;
}
 
int Input::GetInputState(int inputType)
{
	int key = GetJoypadInputState(inputType);

	return key;
}
