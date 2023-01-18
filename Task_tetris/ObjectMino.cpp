#include"DxLib.h"
#include "ObjectMino.h"
#include"Scene/SceneMain.h"
#include"UI/Pad.h"
#include"game.h"

#include<cassert>

namespace
{
	SceneMain main;
	constexpr int kFieldHeight = 0;				//fieldの大きさ
	constexpr int kFieldWindth = 0;				//fieldの大きさ
	constexpr int kBlocHeight = 22;				//fieldの高さ
	constexpr int kBlocWindht = 12;				//fieldの横幅
	constexpr int kFieldFloor = 570;			//fieldの下
	constexpr int kFieldDisplace = 50;			//fieldをずらす

	constexpr int kFrameTimer = 50;				//ミノが落下するインターバル
	constexpr int kMinoTimer = 5;				//ミノが設置されるまでの時間

	int kField[kBlocWindht][kBlocHeight];		//fieldの設置

	int kCoordinateX = 0;						//現在地から座標を取得する
	int kCoordinateY = 0;						//現在地から座標を取得する

	bool kIsEnd = false;						//ゲームの終了フラグ
	constexpr int kSuspend = 10;				//ミノが消されて上のミノが落ちてくるまでの時間
	constexpr int kGeneration = 10;				//次のミノの生成インタ-バル

	float kPosX;
	float kPosY;
	bool kFlag = false;
	constexpr int kMinoblock = 4;

	//
	int minoBlock[kMinoblock][kMinoblock] = {
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}
	};
	
	//I
	int Imino1[kMinoblock][kMinoblock] = {
	{0,0,2,0},
	{0,0,2,0},
	{0,0,2,0},
	{0,0,2,0}
	};
	int Imino2[kMinoblock][kMinoblock] = {
	{2,2,2,2},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}
	};
	
	//O
	int Omino[kMinoblock][kMinoblock] = {
	{0,2,2,0},
	{0,2,2,0},
	{0,0,0,0},
	{0,0,0,0}
	};
	
	//T
	int Tmino1[kMinoblock][kMinoblock] = {
	{0,2,0,0},
	{2,2,2,0},
	{0,0,0,0},
	{0,0,0,0}
	};
	int Tmino2[kMinoblock][kMinoblock] = {
	{0,2,0,0},
	{2,2,0,0},
	{0,2,0,0},
	{0,0,0,0}
	};
	int Tmino3[kMinoblock][kMinoblock] = {
	{0,0,0,0},
	{0,0,0,0},
	{2,2,2,0},
	{0,2,0,0}
	};
	int Tmino4[kMinoblock][kMinoblock] = {
	{0,2,0,0},
	{0,2,2,0},
	{0,2,0,0},
	{0,0,0,0}
	};

	//S
	int Smino1[kMinoblock][kMinoblock] = {
	{0,2,2,0},
	{2,2,0,0},
	{0,0,0,0},
	{0,0,0,0}
	};
	
	//Z
	int Zmino1[kMinoblock][kMinoblock] = {
	{2,2,0,0},
	{0,2,2,0},
	{0,0,0,0},
	{0,0,0,0}
	};

	//J

	//L

	//
	int kPadflag = false;
	int kMinoRight = 0;
	int kMinoLeft = 0;
	int kMinoUp = 0;
	int kMinoDown = 0;
	int kRotation = 0;
}

ObjectMino::ObjectMino() :
	m_frametimer(),								//フレームタイマー
	m_pos(),									//ミノのポジション
	m_size(),									//ミノのサイズ
	m_gravity(),								//ミノの重力
	m_speed(),									//ミノの落下スピード
	m_placed(false),							//置かれたかどうか
	m_minotimer(),								//ミノが下まで行って置かれるまでのインターバル
	m_suspend(),								//ミノが消されてから落下するまでのタイマー
	m_generation()								//次のミノの生成インターバル
{
	MinoInit();
}

void ObjectMino::Init()
{
	m_frametimer = kFrameTimer;					//タイマーを設定
	m_minotimer = kMinoTimer;					//タイマーを設定
	m_generation = kGeneration;
	
}


void ObjectMino::MinoInit()
{
	m_pos.x = 154;								//初期位置
	m_pos.y = 25;								//初期位置
	m_size.x = 26;								//初期サイズ
	m_size.y = 26;								//初期サイズ
	m_gravity = m_size.y / 2;								//重力
	m_speed = 2.5f;								//スピード
	m_placed = false;


	for (int i = 0; i < kMinoblock; i++)		//fieldの初期化
	{
		for (int j = 0; j < kMinoblock; j++)
		{
			minoBlock[j][i] = Omino[i][j];;
			//minoBlock[j][i] = Imino1[i][j];
			//minoBlock[j][i] = Zmino1[i][j];
		}
	}
}

void ObjectMino::MoveUpdate()
{
	//if (Pad::isTrigger(PAD_INPUT_1))				//回転
	//{
	//	kRotation += 1;
	//	kPadflag = true;
	//	for (int i = 0; i < 4; i++)		//fieldの初期化
	//	{
	//		for (int j = 0; j < 4; j++)
	//		{
	//			if (kRotation == 0)
	//			{
	//				minoBlock[j][i] = Imino1[i][j];;
	//				//minoBlock[j][i] = Imino1[i][j];;
	//				//kRotation = 0;
	//			}
	//			if (kRotation == 1)
	//			{
	//				minoBlock[j][i] = Imino2[i][j];;
	//			}
	//			if (kRotation == 2)
	//			{
	//				//minoBlock[j][i] = Imino1[i][j];;
	//				kRotation = 0;
	//			}
	//		}
	//	}
	//}

	kCoordinateY = (m_pos.y - 26) / m_size.y;						//ミノの現在地を座標にする
	kCoordinateX = (m_pos.x - kFieldDisplace) / m_size.x;			//ミノの現在地を座標にする

	if (m_placed == true)								//	ミノの設置処理
	{
		if (m_minotimer > 0)
		{
			m_minotimer--;
			return;
		}
	}
	if (m_placed == false)
	{
		if (Pad::isTrigger(PAD_INPUT_LEFT))				//左の移動処理、移動制限
		{
			if (kField[kCoordinateX + kMinoLeft - 1][kCoordinateY] == empty)
			//if (kField[kCoordinateX + kMinoLeft - 1][kCoordinateY] == empty)
			{
				m_pos.x -= m_size.x;						//キーが押されたら押された方向に動く
			}
		}
		if (Pad::isTrigger(PAD_INPUT_RIGHT))			//右の移動処理、移動制限
		{
			if (kField[kCoordinateX + kMinoRight + 1][kCoordinateY] == empty)
			{
				m_pos.x += m_size.x;
			}
		}
	}
	
	if (kField[kCoordinateX + kMinoRight][kCoordinateY + kMinoDown + 1] != empty ||
		kField[kCoordinateX + kMinoLeft][kCoordinateY + kMinoDown + 1] != empty)								//field下から出ないように設定
	{
		m_placed = true;
		return;
	}
	if (Pad::isTrigger(PAD_INPUT_UP))				//上の移動処理
	{
		int checkdown = 0;
		for (int i = kCoordinateY; i < kBlocHeight; i++)
		{
			if (kField[kCoordinateX + kMinoLeft][i] != empty)
			{
				checkdown = i;
				break;
			}
		
		}
		for (int i = kCoordinateY; i < kBlocHeight; i++)
		{
			if (kField[kCoordinateX + kMinoRight][i] != empty)
			{
				if (checkdown > i)
				{
					checkdown = i;
				}
				break;
			}

		}
		m_pos.y = ((checkdown - kMinoDown) * 26);				//置ける場所のチェック
	}
	if (Pad::isPress(PAD_INPUT_DOWN))				//下の移動処理
	{
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

void ObjectMino::MinoAcquisition()
{
	int left = kMinoblock;					//左をとるための変数
	int right = 0;							//右をとるための変数
	int up = kMinoblock;					//上をとるための変数
	int down = 0;							//下をとるための変数

	//左をとるための処理
	for (int i = 0; i < kMinoblock; i++)
	{
		for (int j = 0; j < kMinoblock; j++)
		{
			if (minoBlock[j][i] == 2)
			{
				if (left >= j)				//今入っている数字より小さいものが見つかったら代入する
				{
					left = j;
				}
			}
		}
	}
	//右をとるための処理
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 3; j >= 0; j--)
		{
			if (minoBlock[j][i] == 2)
			{
				if (right <= j)
				{
					right = j;				//今入っている数字より大きいものが見つかったら代入する
				}
			}
		}
	}
	//上をとるための処理
	for (int i = 0; i < kMinoblock; i++)
	{
		for (int j = 0; j < kMinoblock; j++)
		{
			if (minoBlock[j][i] == 2)
			{
				if (up >= i)				//今入っている数字より小さいものが見つかったら代入する
				{
					up = i;
				}
			}
		}
	}
	//下をとるための処理
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 3; j >= 0; j--)
		{
			if (minoBlock[j][i] == 2)
			{
				if (down <= i)
				{
					down = i;				//今入っている数字より大きいものが見つかったら代入する
				}
			}
		}
	}


	kMinoLeft = left;
	kMinoRight = right;
	kMinoUp = up;
	kMinoDown = down;

}

void ObjectMino::Update()
{
	MinoAcquisition();
	if (m_minotimer <= 0)
	{
		kFlag = true;
		main.MinoBlock(minoBlock);
		if (m_generation > 0)
		{
			m_generation--;
		}

		if (m_generation <= 0)
		{
			if (m_suspend > 0)
			{
				m_suspend--;
			}
			if (m_suspend <= 0)
			{
				kFlag = false;
				m_placed = false;								//フラグをもとに戻す
				//if (main.intervalFlag() == false)
				{
					//m_pos.x = 180 + m_posX;								//初期位置
					//m_pos.y = 25 + m_posY;								//初期位置
					MinoInit();
					kRotation = 0;
				}
				m_minotimer = kMinoTimer;
				m_generation = kGeneration;
			}
		}

		for (int j = 1; j < kBlocWindht - 2; j++)
		{
			if (kField[j][0] == input)
			{
				kIsEnd = true;
			}
		}
	}

	//for (int j = 1; j < kBlocWindht - 1; j++)
	//{
	//	if (field[j][0] != empty)
	//	{
	//		kIsEnd = true;								//ゲームオーバー
	//	}
	//}

	if (kIsEnd == false)
	{
		MoveUpdate();									//ミノの移動処理
	}

	//bool disappear = false;
	//int height = 0;
	//for (int i = 1; i < kBlocHeight - 1; i++)
	//{
	//	if (kField[1][i] == input && kField[2][i] == input && kField[3][i] == input
	//		&& kField[4][i] == input && kField[5][i] == input && kField[6][i] == input
	//		&& kField[7][i] == input && kField[8][i] == input && kField[9][i] == input && kField[10][i] == input)
	//	{
	//		disappear = true;
	//		height = i;
	//	}
	//}
	//for (int j = 1; j < kBlocWindht - 1; j++)
	//{
	//	if (disappear == true)
	//	{
	//		kField[j][height] = empty;
	//		m_suspend = kSuspend;
	//	}
	//}
//
	//if (m_suspend == 1)
	//{
	//	for (int i = kBlocHeight - 2; i >= 1; i--)
	//	{
	//		for (int j = 1; j < kBlocWindht - 1; j++)
	//		{
	//			kField[j][i] = kField[j][i - 1];
	//		}
	//	}
	//}

	//return this;
}
void ObjectMino::Draw()
{
	//for (int i = 0; i < kBlocHeight; i++)
	//{
	//	for (int j = 0; j < kBlocWindht; j++)
	//	{
	//		switch (kField[j][i])
	//		{
	//		case empty:
	//			DrawString(kFieldDisplace + j + (j * 25), 25 + i + (i * 25), "　", GetColor(255, 255, 255));
	//		default:
	//			break;
	//		case input:
	//			//DrawString(kFieldDisplace + j + (j * 25), 25 + i + (i * 25), "a", GetColor(255, 0, 0));
	//			break;
	//		case frame:
	//			DrawString(kFieldDisplace + j + (j * 25), 25 + i + (i * 25), "□", GetColor(255, 255, 255));
	//			break;
	//		}
	//	}
	//}

	for (int i = 0; i < kMinoblock; i++)
	{
		for (int j = 0; j < kMinoblock; j++)
		{
			if (minoBlock[j][i] == 2)
			{
				DrawString(m_pos.x + j + (j * 25), m_pos.y + i + (i * 25), "■", GetColor(255, 0, 0));
			}
		}
	}
	///////////////////////////////////////
	///        確認用の数値表示         ///
	///////////////////////////////////////

	if (kIsEnd == true)
	{
		DrawString(500, 0, "GameOver", GetColor(255, 0, 0));
	}
	else if (kIsEnd == false)
	{
		DrawString(500, 0, "GamePlay", GetColor(255, 0, 0));
	}
	
	if (kPadflag == false)
	{
		DrawString(500, 150, "押されていない", GetColor(255, 0, 0));
	}
	else if (kPadflag == true)
	{
		DrawString(500, 150, "押された", GetColor(255, 0, 0));
	}

	DrawFormatString(650, 280, GetColor(255, 0, 0), "回転%d", kRotation);
	//DrawFormatString(650, 350, GetColor(255, 0, 0), "R%d", kMinoRight);
	//DrawFormatString(650, 380, GetColor(255, 0, 0), "L%d", kMinoLeft);
	//DrawFormatString(650, 410, GetColor(255, 0, 0), "U%d", kMinoUp);
	//DrawFormatString(650, 440, GetColor(255, 0, 0), "D%d", kMinoDown);
	//DrawFormatString(650, 500, GetColor(255, 0, 0), "Y%d", kCoordinateY + kMinoDown);
	//DrawFormatString(650, 530, GetColor(255, 0, 0), "XL%d", kCoordinateX + kMinoLeft);
	//DrawFormatString(650, 560, GetColor(255, 0, 0), "XR%d", kCoordinateX + kMinoRight);
	
	//if (m_placed == false)
	//{
	//	DrawString(500, 100, "f", GetColor(255, 0, 0));
	//}
	//if (m_placed == true)
	//{
	//	DrawString(500, 150, "t", GetColor(255, 0, 0));
	//}
	//DrawFormatString(700, 0, GetColor(0, 255, 255), "%d", a);
	//DrawFormatString(600, 0, GetColor(255, 255, 255), "%d", kCount);
	//DrawFormatString(650, 0, GetColor(255, 255, 255), "%d", kTotal);
	//DrawFormatString(650, 0, GetColor(255, 255, 255), "%d", m_suspend);
	//DrawFormatString(650, 50, GetColor(255, 255, 255), "X:%f", kPosX);
	//DrawFormatString(650, 100, GetColor(255, 255, 255), "Y:%f", kPosY);
	//DrawFormatString(650, 150, GetColor(0, 20, 255), "0:%d", kField[1][20]);
}

int ObjectMino::Field(int field[12][22])
{
	//assert(false);

	for (int i = 0; i < kBlocHeight; i++)		//fieldの初期化
	{
		for (int j = 0; j < kBlocWindht; j++)
		{
			kField[j][i] = field[j][i];;
		}
	}
	return 0;
}


int ObjectMino::PosX()
{
	int posx = 0;
	posx = kCoordinateX;
	return posx;
}

int ObjectMino::PosY()
{
	int posy = 0;
	posy = kCoordinateY;
	return posy;
}

bool ObjectMino::Flag()
{
	bool flag;
	flag = kFlag;

	return flag;
}

bool ObjectMino::EndFlag()
{
	bool gameflag;
	gameflag = kIsEnd;

	return gameflag;
}

void ObjectMino::MinoPos(int posX,int posY)
{
	m_posX = posX;
	m_posY = posY;
}

//void ObjectMino::MinoPos(float posX, float posY)
//{
//	kPosX = posX;
//	kPosY = posY;
//}
