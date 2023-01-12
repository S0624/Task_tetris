#pragma once
#include "SceneBase.h"
#include"UI/Vec2.h"
class SceneMain : public SceneBase		//継承してクラスを作成
{
public:
	typedef enum state {
		empty = 0,
		input = 1,
		frame = 9,
		move = 2
	};

public:
	SceneMain();
	virtual ~SceneMain() {}

	//初期化
	virtual void Init()override;
	//終了処理
	virtual void End()override {}

	//ミノの初期化処理
	virtual void MinoInit();
	//ミノの移動処理
	virtual void MoveUpdate();
	//ミノが置かれたかどうか
	virtual bool Placed() { return m_placed; }
	//更新処理
	virtual SceneBase* Update()override;
	//描画処理
	virtual void Draw() override;
	//生成intervalの管理フラグ
	virtual bool intervalFlag();

	int MinoBlock(int mino[4][4]);

private:
	int m_frametimer;	//フレームタイマー
	int m_minotimer;	//ミノのタイマー
	Vec2 m_pos;			//ミノの位置
	Vec2 m_size;		//ミノのサイズ
	int m_gravity;		//ミノの重力落下
	float m_speed;		//押された時のミノのスピード	
	bool m_placed;		//ミノが置かれたかどうか
	int m_suspend;		//消されてからミノが落ちるまでのタイマー
};