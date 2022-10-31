//=============================================================================
//
// �Q�[�� �N���X���� [Game.cpp]
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

// �R���X�g���N�^
CGame::CGame() : CScene()
{
	m_id = SCENE_GAME;

	m_pPlayer = nullptr;
	m_pEnemy = nullptr;

	m_nBoundary = 0;
}

// �f�X�g���N�^
CGame::~CGame()
{
}

// ������
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

	// �S�I�u�W�F�N�g������
	if (FAILED(CGameObj::InitAll(m_pObj))) {
		return false;
	}

	m_camera.SetPlayer(m_pPlayer);

	// BGM�Đ��J�n
	//CSound::Play(BGM_GAME);

	return true;
}

// �I������
void CGame::Fin()
{
	// BGM�Đ���~
	CSound::Stop(BGM_GAME);

	// �S�I�u�W�F�N�g�I������
	CGameObj::FinAll(m_pObj);
}

// �X�V
void CGame::Update()
{
	//if (CInput::GetKeyTrigger(VK_B)) {
	//	m_nBoundary = (m_nBoundary + 1) % 2;
	//	UpdateBoundary();
	//}

	// �S�L�����X�V
	CGameObj::UpdateAll(m_pObj);

	if (!m_bResult) {
		if (CInput::GetKeyRelease(VK_BACK) ||
			CInput::GetKeyRelease(VK_DELETE)) {
			m_bResult = true;
			CFade::Out(SCENE_TITLE);
		}
	}

	//static LPCSTR boundary[] = {"�ˮ���", "���"};
	//CDebugProc::Print("[B] : ����� %s\n", boundary[m_nBoundary]);
	//CDebugProc::Print("\n");
}

// �`��
void CGame::Draw()
{
	// �S�L�����`��
	CGameObj::DrawAll(m_pObj);
}

// ���E�\���X�V
void CGame::UpdateBoundary()
{
	for (CGameObj* pObj = GetObj(); pObj; pObj = pObj->GetNext()) {
		switch (pObj->GetID()) {
		case GOT_PLAYER:
			switch (m_nBoundary) {
			case 0:	// ���E�\������
				pObj->SetBSphereVisible(false);
				break;
			case 1:	// ���E��
				pObj->SetBSphereVisible();
				break;
			}
			break;

		case GOT_ENEMY:
			switch (m_nBoundary) {
			case 0:	// ���E�\������
				pObj->SetBSphereVisible(false);
				break;
			case 1:	// ���E��
				pObj->SetBSphereVisible();
				break;
			}
			break;
		}
	}
}
