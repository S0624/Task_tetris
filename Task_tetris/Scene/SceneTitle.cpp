#include"DxLib.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include"UI/Pad.h"
#include"game.h"

namespace
{
	bool kCheckisTrigger = false;							//ボタンが押されたかチェックするために用意
	const char*  kNameTitle = "TETRIS";						//タイトル
	const char*  kNameGuide = "ボタンを押してください";		//ガイドの表示
}

SceneTitle::SceneTitle() :
	m_fadeSpeed(-5),										//フェード速度
	m_fadeColor(255)										//フェードカラー
{
}

void SceneTitle::Init()
{
}


SceneBase* SceneTitle::Update()
{
	Fead();
	
	if (m_fadeColor < 0)
	{
		m_fadeColor = 0;
	}
	if(m_fadeColor > 255)
	{
		m_fadeSpeed = 255;
		return(new SceneMain);
		kCheckisTrigger = false;
	}

	return this;
}
void SceneTitle::Fead()
{
	m_fadeColor += m_fadeSpeed;				//フェード処理
	if (kCheckisTrigger == false)			//フェードが終わるまで処理を止める
	{
		if (m_fadeColor > 0)
		{
			return;
		}
	}
	if (kCheckisTrigger == true)			//ボタンが押されたらフェードするまで操作を受け付けない
	{
		if (m_fadeColor <= 255)
		{
			return;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_1))		//ボタンが押されたらフェードを開始する
	{
		kCheckisTrigger = true;
		m_fadeSpeed *= -1;
	}
}
void SceneTitle::Draw()
{
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kNameTitle, -1)) / 2, 425, kNameTitle, GetColor(255, 255, 255));			//タイトル画面の表示
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kNameGuide, -1)) / 2, 500, kNameGuide, GetColor(255, 255, 255));			//タイトルガイドの表示

	SetDrawBlendMode(DX_BLENDMODE_MULA, m_fadeColor);				//フェード
	DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), true);				//かぶせる色
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);						//元に戻す
}