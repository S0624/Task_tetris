#pragma once

enum class InputType {
	next,		//次へ行くボタン
	back,		//前に戻るボタン
	pause		//ポーズボタン
};

class InputState
{
private:
	int keypadState;		//キーパッド状態
	int lastKeypadState;	//直前のキーパッド状態
	char keystate[256];		//キーボード状態
	char lastKeystate[256];	//直前のキーボード状態

public:
	bool IsTrigger(InputType type)const;		//押した瞬間にtrueを返す
	bool IsPressed(InputType type)const;		//押され続けたらtrueを返す
	void Update();			//更新処理
};

