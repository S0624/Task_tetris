#pragma once
#include "SceneBase.h"
class SceneMain :
    public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain() {}

	virtual void init()override { m_isEnd = false; }
	virtual void end()override {}

	virtual void update()override;
	virtual void draw() override;

	virtual bool isEnd()override { return m_isEnd; }
private:
	bool m_isEnd;
};

