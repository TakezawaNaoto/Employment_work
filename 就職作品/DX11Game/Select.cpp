//=============================================================================
//
// シーン クラス実装 [Scene.cpp]
// Author : NAOTO TAKEZAWA
//
//=============================================================================
#include "Select.h"
#include "Texture.h"
#include "Sound.h"
#include "Input.h"
#include "Polygon.h"
#include "Fade.h"
#include "Game.h"
#include "GameObj.h"

// 定数定義
namespace {
	const LPCWSTR g_pszPathTexStart = L"select_start";
	const float g_fTexStartWidth = 480.0f;
	const float g_fTexStartHeight = 120.0f;
	const float g_fTexStartY = SCREEN_HEIGHT / -2.5f;

	const LPCWSTR g_pszPathTexBG = L"select_bg";
}

// コンストラクタ
CSelect::CSelect() : CScene()
{
	m_id = SCENE_SELECT;

	m_bStart = false;
	m_pTexStart = nullptr;
	m_pTexBG = nullptr;
	m_nTimer = 0;
	Chara[MAX_CHARA] = NULL;
	selectChara = nullptr;
}
CSelect::~CSelect()
{
}

bool CSelect::Init()
{
	CCamera::Set();	// カメラセット

	if (!CScene::Init()) {
		return false;
	}

	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	m_bStart = false;
	// テクスチャの読み込み
	hr = CreateTextureFromFile(pDevice, g_pszPathTexStart, &m_pTexStart);
	if (FAILED(hr)) {
		Fin();
		return false;
	}
	hr = CreateTextureFromFile(pDevice, g_pszPathTexBG, &m_pTexBG);
	if (FAILED(hr)) {
		Fin();
		return false;
	}

	// BGM再生開始
	CSound::Play(BGM_SELECT);

	return true;
}
void CSelect::Fin()
{
	// BGM再生停止
	CSound::Stop(BGM_SELECT);

	// テクスチャ解放
	SAFE_RELEASE(m_pTexBG);
	SAFE_RELEASE(m_pTexStart);

	CSound::Fin();
}
void CSelect::Update()
{

	// キャラ選択
	if (CInput::GetKeyRelease(VK_RIGHT)) {
		selectNom++;
		if (selectNom > MAX_CHARA)
			selectNom = 0;
	}
	if (CInput::GetKeyRelease(VK_LEFT)) {
		selectNom--;
		if (selectNom < 0)
			selectNom = MAX_CHARA;
	}

	// セレクトしたらフェードアウトしてゲーム開始
	if (!m_bStart) {
		if (CInput::GetKeyRelease(VK_SPACE) ||
			CInput::GetKeyRelease(VK_RETURN)) {
			selectChara = &Chara[selectNom];	// 選択したキャラ情報を入れる
			m_bStart = true;
			CFade::Out(SCENE_GAME);
		}
	}

	// スタート点滅用
	++m_nTimer;
	if (m_nTimer > 120) {

	}
}
void CSelect::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	// BG
	CPolygon::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	CPolygon::SetTexture(m_pTexBG);
	CPolygon::SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::SetFrameSize(1.0f, 1.0f);
	CPolygon::SetPos(0.0f, 0.0f);
	CPolygon::Draw(pDC);

	// Start
	CPolygon::SetAlpha((m_nTimer <= 60) ? m_nTimer / 60.0f : (120 - m_nTimer) / 60.0f);
	CPolygon::SetTexture(m_pTexStart);
	CPolygon::SetSize(g_fTexStartWidth, g_fTexStartHeight);
	CPolygon::SetPos(0.0f, g_fTexStartY);
	CPolygon::Draw(pDC);


}