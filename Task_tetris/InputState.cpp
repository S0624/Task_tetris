#include "InputState.h"
#include"DxLib.h"
bool InputState::IsTrigger(InputType type) const
{
	if (type == InputType::next)
	{
		return !lastKeystate[PAD_INPUT_1] && keystate[PAD_INPUT_1];
	}
	else if (type == InputType::back)
	{
		return !lastKeystate[PAD_INPUT_2] && keystate[PAD_INPUT_2];
	}
	else if (type == InputType::pause)
	{
		return !lastKeystate[PAD_INPUT_8] && keystate[PAD_INPUT_8];
	}
    return false;
}

bool InputState::IsPressed(InputType type) const
{
	if (type == InputType::next)
	{
		return keystate[PAD_INPUT_1];
	}
    return false;
}

void InputState::Update()
{
	//現在のフレームのキー状況をコピー
	for (int i = 0; i < _countof(lastKeystate); ++i)
	{
		lastKeystate[i] = keystate[i];
	}
	GetHitKeyStateAll(keystate);
}

