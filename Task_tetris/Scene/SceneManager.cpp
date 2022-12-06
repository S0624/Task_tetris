#include<assert.h>
#include "SceneManager.h"
#include"SceneTitle.h"
#include"SceneMain.h"
#include"UI/Pad.h"

SceneManager::SceneManager() :
	m_pScene(nullptr)
{
	//m_pScene = new SceneTitle;
	m_pScene = new SceneMain;
}

SceneManager::~SceneManager()
{
	delete m_pScene;
}

void SceneManager::Init()
{
	m_pScene->Init();
}

void SceneManager::End()
{
	// 確認処理
	assert(m_pScene);
	if (!m_pScene)	return;

	m_pScene->End();
}

void SceneManager::Update()
{
	Pad::update();
	// 確認処理
	assert(m_pScene);
	if (!m_pScene)	return;
	// SceneBaseのupdate処理呼び出し
	SceneBase* pScene = m_pScene->Update();
	if (pScene != m_pScene)
	{
		m_pScene->End();
		delete m_pScene;
		// 初期化
		m_pScene = pScene;
		m_pScene->Init();
	}
}

void SceneManager::Draw()
{
	assert(m_pScene);
	if (!m_pScene)	return;
	m_pScene->Draw();
}
