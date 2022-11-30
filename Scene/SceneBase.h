#pragma once
class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}

	virtual void init() {}
	virtual void end() {}

	virtual void update() {};
	virtual void draw() {}

	virtual bool isEnd() { return false; }
protected:

};

