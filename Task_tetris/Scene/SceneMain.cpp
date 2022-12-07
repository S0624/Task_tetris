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

	int field[kBlocHeight][kBlocWindht];
	
	int x = 0;
	int y = 0;

	const char* kNameTitle = "Main画面";
	const char* kNameGuide = "未実装";
}

SceneMain::SceneMain():
	m_frametimer(),								//フレームタイマー
	m_pos(),									//ミノのポジション
	m_size(),									//ミノのサイズ
	m_gravity(),								//ミノの重力
	m_speed()									//ミノの落下スピード
{
	m_pos.x = 150;								//初期位置
	m_pos.y = 0;								//初期位置
	//m_pos.x = 250;
	//m_pos.y = 75;
	m_size.x = 30;								//初期サイズ
	m_size.y = 30;								//初期サイズ
	m_gravity = 15;								//重力
	m_speed = 2.5f;								//スピード
}

void SceneMain::Init()
{
	m_frametimer = kFrameTimer;					//タイマーを設定
	for (int i = 0; i < kBlocHeight; i++)
	{
		for (int j = 0; j < kBlocWindht; j++)
		{
			field[j][i] = 0;
			//field[j][i] = empty;
		}
	}
	

	//for (int i = 0; i < kBlocHeight; i++)
	//{
	//	printfDx("\n");
	//	for (int j = 0; j < kBlocWindht; j++)
	//	{
	//		switch (field[j][i])
	//		{
	//		case 0:
	//			printfDx("%d",j);
	//			break;
	//		case 1:
	//			printfDx("8");
	//		default:
	//			break;
	//		}
	//	}
	//}
}


void SceneMain::MoveUpdate()
{
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
		//m_pos.x += m_size.x;						//キーが押されたら押された方向に動く
		if (m_pos.x > 270)
		{
			m_pos.x = 270;
		}
	}

	if (m_pos.y > 600)								//fieldから出ないように設定
	{
		m_pos.y = 600;
	}
	if (Pad::isTrigger(PAD_INPUT_UP))				//上の移動処理
	{
		m_pos.y = kFieldFloor;								//キーが押されたら一瞬で下まで
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
	if (m_pos.y > kFieldFloor)								//fieldから出ないように設定
	{
		m_pos.y = kFieldFloor;
	}


	//////////
	//y = static_cast<int>(m_pos.y / m_size.y);
	//x = static_cast<int>(m_pos.x / m_size.x);
	
	
	y = m_pos.y / m_size.y;
	x = m_pos.x / m_size.x;
	
	if (m_pos.y == kFieldFloor)								//
	{
		field[19][1] = 1;
	}
}

SceneBase* SceneMain::Update()
{
	MoveUpdate();									//ミノの移動処理

	return this;
}
void SceneMain::Draw()
{
	//DrawBox(kFieldWindth, kFieldHeight + 30, 430, 705, GetColor(255, 255, 255), false);					//fieldの枠
	//DrawBox(kFieldWindth, kFieldHeight, 430, 705, GetColor(255, 255, 255), false);					//fieldの枠
	DrawBox(kFieldWindth, kFieldHeight, 300, 600, GetColor(255, 255, 255), false);					//fieldの枠

	DrawBox(static_cast<int>(m_pos.x + 2), static_cast<int>(m_pos.y + 2),						//ミノの表示
		static_cast<int>(m_pos.x + m_size.x - 2), static_cast<int>(m_pos.y + m_size.y - 2),
		GetColor(0, 255, 255), false);

	for (int i = 0; i < kBlocHeight; i++)
	{
		//DrawFormatString(kFieldWindth, kFieldHeight + (i * 30), GetColor(255, 255, 255), " %d", i);
		DrawFormatString(kFieldWindth, kFieldHeight + (i * 30), GetColor(255, 255, 255), " %d", i);
		for (int j = 0; j < kBlocWindht; j++)
		{
			DrawFormatString(kFieldWindth + (j * 30), kFieldHeight, GetColor(255, 255, 255), " %d", j);
		}
	}
	DrawFormatString(500, 0, GetColor(255, 255, 255), " %d", m_frametimer);
	DrawFormatString(600, 0, GetColor(255, 255, 255), " {x %d,y %d}", static_cast<int>(m_pos.x / 30), static_cast<int>(m_pos.y / 30));		//座標
	DrawFormatString(600, 75, GetColor(255, 255, 255), " {x %d,y %d}", static_cast<int>(x), static_cast<int>(y));		//座標
	DrawFormatString(600, 100, GetColor(255, 255, 255), " y %d", y);		//座標
	//DrawFormatString(600, 125, GetColor(255, 255, 255), " x %d", x);		//座標
	
	///////////////////////////////////////
	if (field[y][x] == 1)
	{
		DrawFormatString(600, 50, GetColor(255, 255, 255), " %d", 1);
	}
}