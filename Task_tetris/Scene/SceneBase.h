#pragma once

//シーンのベースになるクラス
class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}
	//初期化
	virtual void Init() {}				//初期化
	//終了処理
	virtual void End() {}
	//更新処理
	virtual SceneBase* Update() { return this; }			//更新処理
	//フェード処理
	virtual void Fade(){};
	//描画
	virtual void Draw() {}									//描画処理

protected:

};

