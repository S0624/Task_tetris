#include"DxLib.h"
#include "SceneMain.h"
#include"UI/Pad.h"
#include"game.h"

namespace
{
	constexpr int kFieldHeight = 0;				//fieldの大きさ
	constexpr int kFieldWindth = 0;				//fieldの大きさ
	constexpr int kBlocHeight = 22;				//fieldの高さ
	constexpr int kBlocWindht = 12;				//fieldの横幅
	constexpr int kFieldFloor = 570;			//fieldの下
	constexpr int kFieldDisplace = 50;			//fieldをずらす


	constexpr int kFrameTimer = 50;				//ミノが落下するインターバル
	constexpr int kMinoTimer = 5;				//ミノが設置されるまでの時間

	int field[kBlocWindht][kBlocHeight];		//fieldの設置
	
	int m_coordinateX = 0;
	int m_coordinateY = 0;

	bool isEnd = false;
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
		field[j][21] = frame;
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
	m_coordinateY = (m_pos.y - 25) / m_size.y;
	m_coordinateX = (m_pos.x - kFieldDisplace) / m_size.x;

	if (m_placed == true)								//	ミノの設置処理
	{
		if (m_minotimer > 0)
		{
			m_minotimer--;
			return;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_LEFT))				//左の移動処理、移動制限
	{
		if (field[m_coordinateX - 1][m_coordinateY] == empty)
		{
			m_pos.x -= m_size.x;						//キーが押されたら押された方向に動く
		}
	}
	if (Pad::isTrigger(PAD_INPUT_RIGHT))			//右の移動処理、移動制限
	{
		if (field[m_coordinateX + 1][m_coordinateY] == empty)
		{
			m_pos.x += m_size.x;
		}
	}
	
	if (field[m_coordinateX][m_coordinateY + 1] != empty)								//field下から出ないように設定
	{
		m_placed = true;
		return;
	}						

	if (Pad::isTrigger(PAD_INPUT_UP))				//上の移動処理
	{
		for (int i = kBlocHeight; i > 0; i--)
		{
			if (field[m_coordinateX][i - 1] == empty)
			{
				m_pos.y = i + (i * 25);				//置ける場所のチェック
				break;
			}
		}
	}
	
	if (Pad::isPress(PAD_INPUT_DOWN))				//下の移動処理
	{
		if (field[m_coordinateX][m_coordinateY + 1] == empty)
		{
			m_pos.y += m_speed;							//キーが押されたら押された方向に動く
		}
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
	if (m_minotimer <= 0)
	{
		field[m_coordinateX][m_coordinateY] = input;
		m_placed = false;
		m_minotimer = kMinoTimer;
		MinoInit();
	}

	for (int j = 1; j < kBlocWindht - 1; j++)
	{
		if (field[j][0] != empty)
		{
			isEnd = true;
		}
	}
	if (isEnd == false)
	{
		MoveUpdate();									//ミノの移動処理
	}

	for (int j = 1; j < kBlocWindht - 1; j++)
	{
		if (field[1][20] == input && field[2][20] == input && field[3][20] == input
			&& field[4][20] == input && field[5][20] == input && field[6][20] == input
			&& field[7][20] == input && field[8][20] == input && field[9][20] == input && field[10][20] == input)
		{
			field[j][20] = empty;
		}
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
				DrawString(kFieldDisplace + j + (j * 25), 25 + i + (i * 25), "　", GetColor(255, 255, 255));
			default:
				break;
			case input:
				DrawString(kFieldDisplace + j + (j * 25), 25 + i + (i * 25), "■", GetColor(255, 255, 255));
				break;
			case frame:
				DrawString(kFieldDisplace + j + (j * 25), 25 + i + (i * 25), "□", GetColor(255, 255, 255));
				break;
			}
		}
	}

	DrawString(m_pos.x, m_pos.y, "■",GetColor(255, 0, 0));



	///////////////////////////////////////
	///        確認用の数値表示         ///
	///////////////////////////////////////

	if (isEnd == false)
	{
		DrawString(500, 0, "GamePlay", GetColor(255, 0, 0));
	}
	if (isEnd == true)
	{
		DrawString(500, 0, "GameOver", GetColor(255, 0, 0));
	}
}
