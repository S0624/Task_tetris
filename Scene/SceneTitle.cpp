#include "SceneTitle.h"
#include"DxLib.h"

SceneTitle::SceneTitle()// :
	//m_isEnd(false)
{

}


void SceneTitle::update()
{

}
void SceneTitle::draw()
{
	//DrawFormatString(0, 0, GetColor(255, 0, 0), "title");
	DrawString(0, 0, "Title", GetColor(255, 255, 255));
}