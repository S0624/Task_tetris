#include"DxLib.h"
#include "SceneMain.h"
#include"UI/Pad.h"
#include"game.h"

namespace
{
	constexpr int kFieldHeight = 0;				//fieldの大きさ
	constexpr int kFieldWindth = 0;				//fieldの大きさ
	//constexpr int kFieldHeight = 75;
	//constexpr int kFieldWindth = 100;
	constexpr int kBlocHeight = 20;				//fieldの高さ
	constexpr int kBlocWindht = 10;				//fieldの横幅
	constexpr int kFieldFloor = 570;			//fieldの下

	constexpr int kFrameTimer = 50;
	constexpr int kMinoTimer = 10;

	int field[kBlocHeight][kBlocWindht];
	
	int m_coordinateX = 0;
	int m_coordinateY = 0;

	const char* kNameTitle = "Main画面";
	const char* kNameGuide = "未実装";
}

SceneMain::SceneMain():
	m_frametimer(),								//フレームタイマー
	m_pos(),									//ミノのポジション
	m_size(),									//ミノのサイズ
	m_gravity(),								//ミノの重力
	m_speed(),									//ミノの落下スピード
	m_placed(false),
	m_minotimer()
{
	MinoInit();
}

void SceneMain::Init()
{
	m_frametimer = kFrameTimer;					//タイマーを設定
	m_minotimer = kMinoTimer;
	for (int i = 0; i < kBlocHeight; i++)
	{
		for (int j = 0; j < kBlocWindht; j++)
		{
			field[j][i] = 0;
		}
	}
}


void SceneMain::MinoInit()
{
	m_pos.x = 150;								//初期位置
	m_pos.y = 0;								//初期位置
	m_size.x = 30;								//初期サイズ
	m_size.y = 30;								//初期サイズ
	m_gravity = m_size.y / 2;								//重力
	m_speed = 2.5f;								//スピード
	m_placed = false;
}

void SceneMain::MoveUpdate()
{
	m_coordinateY = m_pos.y / m_size.y;
	m_coordinateX = m_pos.x / m_size.x;

	if (m_pos.y == kFieldFloor)								//
	{
		MinoInit();
		if (m_minotimer > 0)
		{
			m_minotimer--;
			return;
		}
		if (m_minotimer <= 0)
		{
			m_placed = true;
			field[m_coordinateY][m_coordinateX] = 1;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_LEFT))				//左の移動処理、移動制限
	{
		m_pos.x -= m_size.x;						//キーが押されたら押された方向に動く
		if (m_pos.x < 0)
		{
			m_pos.x = 0;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_RIGHT))			//右の移動処理、移動制限
	{
		m_pos.x += m_size.x;						//キーが押されたら押された方向に動く
		if (m_pos.x > 270)
		{
			m_pos.x = 270;
		}
	}

	if (m_pos.y >= 570)								//field下から出ないように設定
	{
		m_pos.y = 570;
	}
	if (Pad::isTrigger(PAD_INPUT_UP))				//上の移動処理
	{
		m_pos.y = kFieldFloor;						//キーが押されたら一瞬で下まで
		m_placed = true;
	}

	if (Pad::isPress(PAD_INPUT_DOWN))				//下の移動処理
	{
		m_pos.y += m_speed;							//キーが押されたら押された方向に動く
		return;										//押されている間はフレームタイマーの処理をスキップする
	}

	if (m_frametimer > 0)							//下キーが押されていないときはタイマーの数を減らす
	{
		m_frametimer--;
	}
	if (m_frametimer == 0)							//タイマーがゼロになったら落下させる
	{
		m_pos.y += m_gravity;
		m_frametimer = kFrameTimer;					//落下させたらタイマーの数値を元に戻す
	}
}

SceneBase* SceneMain::Update()
{
	if (m_placed == false)
	{
		MoveUpdate();									//ミノの移動処理
	}
	return this;
}
void SceneMain::Draw()
{
	if (Placed())
	{
		DrawBox(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),						//ミノの表示
			static_cast<int>(m_pos.x + m_size.x), static_cast<int>(m_pos.y + m_size.y),
			GetColor(255, 0, 0), false);
	}

	if (!Placed())
	{
		DrawBox(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),						//ミノの表示
		static_cast<int>(m_pos.x + m_size.x), static_cast<int>(m_pos.y + m_size.y),
		GetColor(0, 255, 255), false);
	}

	DrawBox(kFieldWindth - 2, kFieldHeight - 2, 300 + 2, 600 + 2, GetColor(255, 255, 255), false);					//fieldの枠




	///////////////////////////////////////
	///        確認用の数値表示         ///
	///////////////////////////////////////


	for (int i = 0; i < kBlocHeight; i++)
	{
		//DrawFormatString(kFieldWindth, kFieldHeight + (i * 30), GetColor(255, 255, 255), " %d", i);
		DrawFormatString(kFieldWindth, kFieldHeight + (i * 30), GetColor(255, 255, 255), " %d", i);
		for (int j = 0; j < kBlocWindht; j++)
		{
			DrawFormatString(kFieldWindth + (j * 30), kFieldHeight, GetColor(255, 255, 255), " %d", j);
		}
	}

	//DrawFormatString(500, 0, GetColor(255, 255, 255), " %d", m_frametimer);
	DrawFormatString(600, 0, GetColor(255, 255, 255), " {x %d,y %d}", static_cast<int>(m_pos.x / 30), static_cast<int>(m_pos.y / 30));		//座標
	DrawFormatString(600, 75, GetColor(255, 255, 255), " {x %d,y %d}", static_cast<int>(m_coordinateX), static_cast<int>(m_coordinateY));		//座標
	DrawFormatString(600, 100, GetColor(255, 255, 255), " y %d", m_coordinateY);		//座標
	//DrawFormatString(600, 125, GetColor(255, 255, 255), " x %d", x);		//座標

	if (field[m_coordinateY][m_coordinateX] == 1)
	{
		DrawFormatString(600, 50, GetColor(255, 255, 255), " %d", 1);
	}
	if (Placed() == true)
	{
		DrawFormatString(700, 300, GetColor(255, 255, 255), " a");		//座標
	}
	if (Placed() == false)
	{
		DrawFormatString(700, 300, GetColor(255, 255, 255), " b");		//座標
	}
}