#include"DxLib.h"
#include "SceneMain.h"
#include"UI/Pad.h"
#include"game.h"

namespace
{
	constexpr int kFieldHeight = 0;				//fieldの大きさ
	constexpr int kFieldWindth = 0;				//fieldの大きさ
	constexpr int kBlocHeight = 21;				//fieldの高さ
	constexpr int kBlocWindht = 12;				//fieldの横幅
	constexpr int kFieldFloor = 570;			//fieldの下
	constexpr int kFieldDisplace = 50;			//fieldをずらす


	constexpr int kFrameTimer = 50;
	constexpr int kMinoTimer = 10;

	int field[kBlocWindht][kBlocHeight];
	
	int m_coordinateX = 0;
	int m_coordinateY = 0;
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
	
	for (int i = 0; i < kBlocHeight; i++)		//fieldの初期化
	{
		for (int j = 0; j < kBlocWindht; j++)
		{
			field[j][i] = empty;
		}
	}
	
	for (int i = 0; i < kBlocHeight; i++)		//フレームの表示
	{
		field[0][i] = frame;
		field[11][i] = frame;
	}
	for (int j = 0; j < kBlocWindht; j++)
	{
		field[j][20] = frame;
	}
}


void SceneMain::MinoInit()
{
	m_pos.x = 180;								//初期位置
	m_pos.y = 25;								//初期位置
	m_size.x = 26;								//初期サイズ
	m_size.y = 26;								//初期サイズ
	m_gravity = m_size.y / 2;								//重力
	m_speed = 2.5f;								//スピード
	m_placed = false;
}

void SceneMain::MoveUpdate()
{
	m_coordinateY = m_pos.y  / m_size.y;
	m_coordinateX = (m_pos.x - kFieldDisplace) / m_size.x;

	if (m_pos.y == kFieldFloor)								//
	{
		//MinoInit();
		if (m_minotimer > 0)
		{
			m_minotimer--;
			return;
		}
		if (m_minotimer <= 0)
		{
			field[m_coordinateY][m_coordinateX] = 1;
			m_placed = true;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_LEFT))				//左の移動処理、移動制限
	{
		m_pos.x -= m_size.x;						//キーが押されたら押された方向に動く
		if (m_pos.x < kFieldDisplace + m_size.x)
		{
			m_pos.x = kFieldDisplace + m_size.x;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_RIGHT))			//右の移動処理、移動制限
	{
		m_pos.x += m_size.x;						//キーが押されたら押された方向に動く
		if (m_pos.x > 336 - m_size.x)
		{
			m_pos.x = 336 - m_size.x;
		}
	}
	
	if (m_pos.y >= 546 - m_size.y)								//field下から出ないように設定
	{
		m_pos.y = 546 - m_size.y;

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
	if (m_pos.y >= 546 - m_size.y)								//field下から出ないように設定
	{
		m_pos.y = 546 - m_size.y;
	}

}

SceneBase* SceneMain::Update()
{
	//if (m_placed == false)
	{
		MoveUpdate();									//ミノの移動処理
	}

	return this;
}
void SceneMain::Draw()
{

	for (int i = 0; i < kBlocHeight; i++)
	{
		for (int j = 0; j < kBlocWindht; j++)
		{
			switch (field[j][i])
			{
			case empty:
				DrawFormatString(kFieldDisplace + j + (j * 25), 25 + i + (i * 25), GetColor(255, 255, 255), "■", j);
				//DrawString(kFieldDisplace + j + (j * 25), 25 + i + (i * 25), "■", GetColor(255, 255, 255));
			default:
				break;
			case input:
				//DrawString(i + (i * 30), j + (i * 30), " ■", GetColor(255, 255, 255));
				DrawString(kFieldDisplace + j + (j * 25), 25 + i + (i * 25), "■", GetColor(255, 255, 255));
				break;
			case frame:
				DrawString(kFieldDisplace + j + (j * 25), 25 + i + (i * 25), "□", GetColor(255, 255, 255));
				break;
			}
		}
	}

	DrawString(m_pos.x, m_pos.y, "■",GetColor(255, 0, 0));
	//if (Placed())
	//{
	//	DrawBox(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),						//ミノの表示
	//		static_cast<int>(m_pos.x + m_size.x), static_cast<int>(m_pos.y + m_size.y),
	//		GetColor(255, 0, 0), false);
	//}

	//if (!Placed())
	//{
	//	DrawBox(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),						//ミノの表示
	//	static_cast<int>(m_pos.x + m_size.x), static_cast<int>(m_pos.y + m_size.y),
	//	GetColor(0, 255, 255), false);
	//}


	///////////////////////////////////////
	///        確認用の数値表示         ///
	///////////////////////////////////////

	//for (int i = 0; i < kBlocHeight; i++)
	//{
	//	//DrawFormatString(kFieldWindth, kFieldHeight + (i * 30), GetColor(255, 255, 255), " %d", i);
	//	DrawFormatString(kFieldWindth, kFieldHeight + (i * 30), GetColor(255, 255, 255), " %d", i);
	//	for (int j = 0; j < kBlocWindht; j++)
	//	{
	//		DrawFormatString(kFieldWindth + (j * 30), kFieldHeight, GetColor(255, 255, 255), " %d", j);
	//	}
	//}

	//DrawFormatString(500, 0, GetColor(255, 255, 255), " %d", m_frametimer);
	DrawFormatString(600, 0, GetColor(255, 255, 255), " {x %d,y %d}", static_cast<int>(m_pos.x / 30), static_cast<int>(m_pos.y / 30));		//座標
	DrawFormatString(600, 75, GetColor(255, 255, 255), " {x %d,y %d}", static_cast<int>(m_coordinateX), static_cast<int>(m_coordinateY));		//座標
	DrawFormatString(600, 100, GetColor(255, 255, 255), " y %d", m_coordinateY);		//座標
	DrawFormatString(600, 125, GetColor(255, 255, 255), " m:x %f", m_pos.x);		//座標

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
