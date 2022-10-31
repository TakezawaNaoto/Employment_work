//=============================================================================
//
// ゲーム クラス実装 [Game.cpp]
// Author : NAOTO TAKEZAWA
//
//=============================================================================
#include "Game.h"
#include "Input.h"
#include "GameObj.h"
#include "Sound.h"
#include "Fade.h"
#include "DebugProc.h"
#include "Land.h"

// コンストラクタ
CGame::CGame() : CScene()
{
	m_id = SCENE_GAME;

	m_pPlayer = nullptr;
	m_pEnemy = nullptr;

	m_nBoundary = 0;
}

// デストラクタ
CGame::~CGame()
{
}

// 初期化
bool CGame::Init()
{
	m_bResult = false;

	m_camera.Init();
	CCamera::Set(&m_camera);

	CLight* pLight = CLight::Get();
	if (pLight) {
		pLight->Init();
	}

	new CLand(this);
	m_pPlayer = new CPlayer(this);
	m_pEnemy = new CEnemy(this);

	UpdateBoundary();

	// 全オブジェクト初期化
	if (FAILED(CGameObj::InitAll(m_pObj))) {
		return false;
	}

	m_camera.SetPlayer(m_pPlayer);

	// BGM再生開始
	//CSound::Play(BGM_GAME);

	return true;
}

// 終了処理
void CGame::Fin()
{
	// BGM再生停止
	CSound::Stop(BGM_GAME);

	// 全オブジェクト終了処理
	CGameObj::FinAll(m_pObj);
}

// 更新
void CGame::Update()
{
	//if (CInput::GetKeyTrigger(VK_B)) {
	//	m_nBoundary = (m_nBoundary + 1) % 2;
	//	UpdateBoundary();
	//}

	// 全キャラ更新
	CGameObj::UpdateAll(m_pObj);

	if (!m_bResult) {
		if (CInput::GetKeyRelease(VK_BACK) ||
			CInput::GetKeyRelease(VK_DELETE)) {
			m_bResult = true;
			CFade::Out(SCENE_TITLE);
		}
	}

	//static LPCSTR boundary[] = {"ﾋﾋｮｳｼﾞ", "ｷｭｳ"};
	//CDebugProc::Print("[B] : ｷｮｳｶｲ %s\n", boundary[m_nBoundary]);
	//CDebugProc::Print("\n");
}

// 描画
void CGame::Draw()
{
	// 全キャラ描画
	CGameObj::DrawAll(m_pObj);
}

// 境界表示更新
void CGame::UpdateBoundary()
{
	for (CGameObj* pObj = GetObj(); pObj; pObj = pObj->GetNext()) {
		switch (pObj->GetID()) {
		case GOT_PLAYER:
			switch (m_nBoundary) {
			case 0:	// 境界表示無し
				pObj->SetBSphereVisible(false);
				break;
			case 1:	// 境界球
				pObj->SetBSphereVisible();
				break;
			}
			break;

		case GOT_ENEMY:
			switch (m_nBoundary) {
			case 0:	// 境界表示無し
				pObj->SetBSphereVisible(false);
				break;
			case 1:	// 境界球
				pObj->SetBSphereVisible();
				break;
			}
			break;
		}
	}
}
