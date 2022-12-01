#include"DxLib.h"
#include "SceneTitle.h"
#include"game.h"

namespace
{
	constexpr int kwaitCount = 30;
	const char*  kNameTitle = "TETRIS";
	const char*  kNameGuide = "ボタンを押してください";
}

SceneTitle::SceneTitle() :
	m_freamCount()
	//m_isEnd(false)
{

}


void SceneTitle::update()
{
	if (m_freamCount > 0)
	{
		m_freamCount--;
		return;
	}
}
void SceneTitle::draw()
{

	DrawFormatString(0, 0, GetColor(255, 255, 255), ":%d", m_freamCount);
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kNameTitle, -1)) / 2, 425, kNameTitle, GetColor(255, 255, 255));			//タイトル画面の表示
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kNameGuide, -1)) / 2, 500, kNameGuide, GetColor(255, 255, 255));			//タイトル画面の表示
}