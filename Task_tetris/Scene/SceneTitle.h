#pragma once
#include "SceneBase.h"
class SceneTitle :
    public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle() {}

	virtual void init()override { m_isEnd = false; }
	void end()override {}

	void update()override;
	void draw() override;

	//virtual bool isEnd()override { return m_isEnd; }
private:
	int m_freamCount;
	bool m_isEnd;
};

