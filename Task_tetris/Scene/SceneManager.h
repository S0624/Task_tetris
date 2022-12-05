#pragma once
#include"SceneBase.h"

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	//初期化
	void Init();
	//終了処理
	void End();
	//更新処理
	void Update();
	//描画処理
	void Draw();

private:
	// シーンベースポインタ
	SceneBase* m_pScene;
};