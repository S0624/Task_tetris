#include"DxLib.h"
#include "SceneMain.h"
#include"UI/Pad.h"
#include"game.h"

namespace
{
	const char* kNameTitle = "Main���";
	const char* kNameGuide = "������";
}

SceneMain::SceneMain()
{

}

void SceneMain::Init()
{
	int field[10][20];
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			field[j][i] = 0;
		}
	}
}


SceneBase* SceneMain::Update()
{

	return this;
}
void SceneMain::Draw()
{
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kNameTitle, -1)) / 2, 425, kNameTitle, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kNameGuide, -1)) / 2, 500, kNameGuide, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��



	for (int i = 0; i <= 20; i++)
	{
		DrawFormatString(100, 0 + (i * 25), GetColor(255, 255, 255), " %d", i);
		for (int j = 0; j <= 10; j++)
		{
			DrawFormatString(100 + (j * 25), 0, GetColor(255, 255, 255), " %d", j);
		}
	}
}