#pragma once
//#include "SceneBase.h"
#include"UI/Vec2.h"

class ObjectMino
{
public:
	typedef enum state {
		empty = 0,
		input = 1,
		frame = 9,
		move = 2
	};

public:
	ObjectMino();
	virtual ~ObjectMino() {}

	//初期化
	virtual void Init();
	//終了処理
	virtual void End() {}

	//ミノの初期化処理
	virtual void MinoInit();
	//ミノの移動処理
	virtual void MoveUpdate();
	//ミノが置かれたかどうか
	virtual bool Placed() { return m_placed; }
	void MinoAcquisition();
	//更新処理
	virtual void Update();
	//描画処理
	virtual void Draw();

	//fieldの情報
	int Field(int field[12][22]);

	//ミノのX座標
	int PosX();
	//ミノのY座標
	int PosY();
	//置かれたフラグを扱う
	bool Flag();
	//ゲームオーバーのフラグ
	bool EndFlag();

	virtual void MinoPos(int posX, int posY);


private:
	int m_frametimer;	//フレームタイマー
	int m_minotimer;	//ミノのタイマー
	Vec2 m_pos;			//ミノの位置
	Vec2 m_size;		//ミノのサイズ
	int m_gravity;		//ミノの重力落下
	float m_speed;		//押された時のミノのスピード	
	bool m_placed;		//ミノが置かれたかどうか
	int m_suspend;		//消されてからミノが落ちるまでのタイマー
	int m_generation;
	int m_field[12][22];

	int m_posX;
	int m_posY;
};

