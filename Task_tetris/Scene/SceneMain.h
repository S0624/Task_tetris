#pragma once
#include "SceneBase.h"
#include"UI/Vec2.h"
class SceneMain : public SceneBase		//継承してクラスを作成
{
//public:
//	typedef enum state {
//		empty = 0,
//		input = 1
//	};

public:
	SceneMain();
	virtual ~SceneMain() {}

	//初期化
	virtual void Init()override;
	//終了処理
	virtual void End()override {}

	//ミノの移動処理
	virtual void MoveUpdate();
	//更新処理
	virtual SceneBase* Update()override;
	//描画処理
	virtual void Draw() override;

private:
	int m_frametimer;	//フレームタイマー
	Vec2 m_pos;			//ミノの位置
	Vec2 m_size;		//ミノのサイズ
	int m_gravity;		//ミノの重力落下
	float m_speed;		//押された時のミノのスピード	
};

