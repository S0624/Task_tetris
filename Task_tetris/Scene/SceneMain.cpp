#include"DxLib.h"
#include "SceneMain.h"
#include"ObjectMino.h"
#include"UI/Pad.h"
#include"game.h"

namespace
{
	ObjectMino mino;
	//ObjectMino Mino[2];

	constexpr int kFieldHeight = 0;				//fieldの大きさ
	constexpr int kFieldWindth = 0;				//fieldの大きさ
	constexpr int kFieldFloor = 570;			//fieldの下
	constexpr int kFieldDisplace = 50;			//fieldをずらす


	constexpr int kFrameTimer = 50;				//ミノが落下するインターバル
	constexpr int kMinoTimer = 5;				//ミノが設置されるまでの時間

	constexpr int kBlocHeight = 22;				//fieldの高さ
	constexpr int kBlocWindht = 12;				//fieldの横幅
	int kField[kBlocWindht][kBlocHeight];		//fieldの設置

	int kCoordinateX = 0;						//現在地から座標を取得する
	int kCoordinateY = 0;						//現在地から座標を取得する

	bool kIsEnd = false;						//ゲームの終了フラグ
	int kSuspend = 30;							//ミノが消されて上のミノが落ちてくるまでの時間

	float kPosX = 0;
	float kPosY = 0;
}

SceneMain::SceneMain() :
	m_frametimer(),								//フレームタイマー
	m_pos(),									//ミノのポジション
	m_size(),									//ミノのサイズ
	m_gravity(),								//ミノの重力
	m_speed(),									//ミノの落下スピード
	m_placed(false),							//置かれたかどうか
	m_minotimer(),								//ミノが下まで行って置かれるまでのインターバル
	m_suspend()									//ミノが消されてから落下するまでのタイマー
{
	//mino.MinoInit();
	//for (auto& mino : Mino)
	{
		mino.Init();
		mino.MinoInit();
	}
	//for (auto& mino : Mino)
	//{
	//	mino.MinoInit();
	//}
}

void SceneMain::Init()
{

	//m_frametimer = kFrameTimer;					//タイマーを設定
	//m_minotimer = kMinoTimer;
	//
	for (int i = 0; i < kBlocHeight; i++)		//fieldの初期化
	{
		for (int j = 0; j < kBlocWindht; j++)
		{
			kField[j][i] = empty;
		}
	}

	for (int i = 0; i < kBlocHeight; i++)		//フレームの表示
	{
		kField[0][i] = frame;
		kField[11][i] = frame;
	}
	for (int j = 0; j < kBlocWindht; j++)
	{
		kField[j][21] = frame;
	}
}


void SceneMain::MinoInit()
{
	//	m_pos.x = 180;								//初期位置
	//	m_pos.y = 25;								//初期位置
	//	m_size.x = 26;								//初期サイズ
	//	m_size.y = 26;								//初期サイズ
	//	m_gravity = m_size.y / 2;								//重力
	//	m_speed = 2.5f;								//スピード
	//	m_placed = false;
}

void SceneMain::MoveUpdate()
{
	//for (auto& mino : Mino)
	//{
		//mino.MoveUpdate();
	//}
	//	kCoordinateY = (m_pos.y - 25) / m_size.y;						//ミノの現在地を座標にする
	//	kCoordinateX = (m_pos.x - kFieldDisplace) / m_size.x;			//ミノの現在地を座標にする
	//
	//	if (m_placed == true)								//	ミノの設置処理
	//	{
	//		if (m_minotimer > 0)
	//		{
	//			m_minotimer--;
	//			return;
	//		}
	//	}
	//
	//	if (Pad::isTrigger(PAD_INPUT_LEFT))				//左の移動処理、移動制限
	//	{
	//		if (field[kCoordinateX - 1][kCoordinateY] == empty)
	//		{
	//			m_pos.x -= m_size.x;						//キーが押されたら押された方向に動く
	//		}
	//	}
	//	if (Pad::isTrigger(PAD_INPUT_RIGHT))			//右の移動処理、移動制限
	//	{
	//		if (field[kCoordinateX + 1][kCoordinateY] == empty)
	//		{
	//			m_pos.x += m_size.x;
	//		}
	//	}
	//	
	//	if (field[kCoordinateX][kCoordinateY + 1] != empty)								//field下から出ないように設定
	//	{
	//		m_placed = true;
	//		return;
	//	}						
	//
	//	if (Pad::isTrigger(PAD_INPUT_UP))				//上の移動処理
	//	{
	//		for (int i = 0; i <= kBlocHeight; i++)
	//		{
	//			if (field[kCoordinateX][i] != empty)
	//			{
	//				m_pos.y = i + (i * 25);				//置ける場所のチェック
	//				break;
	//			}
	//		}
	//	}
	//	
	//	if (Pad::isPress(PAD_INPUT_DOWN))				//下の移動処理
	//	{
	//		if (field[kCoordinateX][kCoordinateY] == empty)
	//		{
	//			m_pos.y += m_speed;							//キーが押されたら押された方向に動く
	//		}
	//		return;										//押されている間はフレームタイマーの処理をスキップする
	//	}
	//	
	//	if (m_frametimer > 0)							//下キーが押されていないときはタイマーの数を減らす
	//	{
	//		m_frametimer--;
	//	}
	//	if (m_frametimer == 0)							//タイマーがゼロになったら落下させる
	//	{
	//		m_pos.y += m_gravity;
	//		m_frametimer = kFrameTimer;					//落下させたらタイマーの数値を元に戻す
	//	}
}

SceneBase* SceneMain::Update()
{
	//for (auto& mino : Mino) 
	{
		mino.Update();
	}

	if (mino.flag() == true)
	{
		kField[mino.PosX()][mino.PosY()] = input;		//置かれたらfieldに代入する
	}

	if (m_suspend > 0)
	{
		m_suspend--;
	}

	//if (m_minotimer <= 0)
	//{
	//	field[kCoordinateX][kCoordinateY] = input;		//置かれたらfieldに代入する
	//	m_placed = false;								//フラグをもとに戻す
	//	m_minotimer = kMinoTimer;
	//	for (auto& mino : Mino)
	//	{
	//		if (m_suspend <= 0)
	//		{
	//			mino.MinoInit();
	//		}
	//	}
	//}
	//
	//for (int j = 1; j < kBlocWindht - 1; j++)
	//{
	//	if (field[j][0] != empty)
	//	{
	//		kIsEnd = true;								//ゲームオーバー
	//	}
	//}
	//if (kIsEnd == false)
	//{
	//	for (auto& mino : Mino)
	//	{
	//		mino.MoveUpdate();									//ミノの移動処理
	//	}
	//}
	//
	bool disappear = false;
	int height = 0;
	for (int i = 1; i < kBlocHeight - 1; i++)
	{
		if (kField[1][i] == input && kField[2][i] == input && kField[3][i] == input
			&& kField[4][i] == input && kField[5][i] == input && kField[6][i] == input
			&& kField[7][i] == input && kField[8][i] == input && kField[9][i] == input && kField[10][i] == input)
		{
			disappear = true;
			height = i;
		}
	}
	for (int j = 1; j < kBlocWindht - 1; j++)
	{
		if (disappear == true)
		{
			kField[j][height] = empty;
			m_suspend = kSuspend;
		}
	}

	if (m_suspend <= 0)
	{
		MinoInit();
	}

	if (m_suspend == 1)
		//if (disappear == true)
	{
		for (int i = kBlocHeight - 2; i >= 1; i--)
		{
			for (int j = 1; j < kBlocWindht - 1; j++)
			{
				kField[j][i] = kField[j][i - 1];
			}
		}
	}

	mino.Field(kField);		//fieldの設置;

	return this;
}
void SceneMain::Draw()
{
	for (int i = 0; i < kBlocHeight; i++)
	{
		for (int j = 0; j < kBlocWindht; j++)
		{
			switch (kField[j][i])
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

	//for (auto& mino : Mino)
	{
		mino.Draw();
	}


	///////////////////////////////////////
	///        確認用の数値表示         ///
	///////////////////////////////////////

	if (kIsEnd == false)
	{
		DrawString(500, 0, "GamePlay", GetColor(255, 0, 0));
	}
	if (kIsEnd == true)
	{
		DrawString(500, 0, "GameOver", GetColor(255, 0, 0));
	}

	//DrawFormatString(600, 0, GetColor(255, 255, 255), "%d", kCount);
	//DrawFormatString(650, 0, GetColor(255, 255, 255), "%d", kTotal);
	DrawFormatString(650, 200, GetColor(255, 255, 255), "%d", mino.PosX());
	DrawFormatString(650, 250, GetColor(255, 255, 255), "%d", mino.PosY());
}