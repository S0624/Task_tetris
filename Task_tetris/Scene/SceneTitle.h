#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase		//継承してクラスを作成
{
public:
	SceneTitle();
	virtual ~SceneTitle() {}

	//初期化
	virtual void Init()override;
	//終了処理
	virtual void End()override;

	//更新処理
	virtual SceneBase* Update()override;
	//フェード処理
	virtual void Fead();
	//描画処理
	virtual void Draw() override;

private:
	int m_background;
	int m_fadeSpeed;				//フェード速度
	int m_fadeColor;				//フェードカラー
};

