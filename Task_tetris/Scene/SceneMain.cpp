#include"DxLib.h"
#include "SceneMain.h"
#include"UI/Pad.h"
#include"game.h"

namespace
{
	constexpr int kwaitTime = 30;
	const char* kNameTitle = "Main画面";
	const char* kNameGuide = "未実装";
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
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kNameTitle, -1)) / 2, 425, kNameTitle, GetColor(255, 255, 255));			//タイトル画面の表示
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kNameGuide, -1)) / 2, 500, kNameGuide, GetColor(255, 255, 255));			//タイトル画面の表示
}