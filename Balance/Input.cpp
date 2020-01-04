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

Vector2 Input::GetAnalog()
{
	int* x;
	int* y;
	GetJoypadAnalogInput(x, y, DX_INPUT_PAD1);

	Vector2 Analog = Vector2(*x, *y);

	return Analog;
}

Vector2 Input::GetAnalog(int inputType)
{
	int* x;
	int* y;
	GetJoypadAnalogInput(x, y, inputType);

	Vector2 Analog = Vector2(*x, *y);

	return Analog;
}

int Input::GetAnalogX()
{
	int* x;
	int* y;
	GetJoypadAnalogInput(x, y, DX_INPUT_PAD1);


	return *x;
}

int Input::GetAnalogX(int inputType)
{
	int* x;
	int* y;
	GetJoypadAnalogInput(x, y, inputType);


	return *x;
}

void Input::StartJoypadVibration(int Power, int Time)
{
	StartJoypadVibration(DX_INPUT_PAD1, Power, Time);
}

void Input::StopJoypadVibration()
{
	StopJoypadVibration(DX_INPUT_PAD1);
}

void Input::StartJoypadVibration(int Power, int Time, int inputType)
{
	StartJoypadVibration(inputType, Power, Time);
}

void Input::StopJoypadVibration(int inputType)
{
	StopJoypadVibration(inputType);
}
