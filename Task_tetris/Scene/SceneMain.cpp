#include"DxLib.h"
#include "SceneMain.h"
#include"UI/Pad.h"
#include"game.h"

namespace
{
	constexpr int kwaitTime = 30;
	const char* kNameTitle = "Main���";
	const char* kNameGuide = "������";
}

SceneMain::SceneMain()
{

}

void SceneMain::Init()
{
}


SceneBase* SceneMain::Update()
{
	return this;
}
void SceneMain::Draw()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), ":%d", kwaitTime);
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kNameTitle, -1)) / 2, 425, kNameTitle, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kNameGuide, -1)) / 2, 500, kNameGuide, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��
}