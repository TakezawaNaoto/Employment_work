//=============================================================================
//
// �v���C���[ �N���X���� [Enemy.cpp]
// Author : NAOTO TAKEZAWA
//
//=============================================================================
#include "Enemy.h"
#include "Input.h"
#include "DebugProc.h"
#include "GameCamera.h"
#include "Scene.h"

// �O���[�o���ϐ�
namespace {
	const float g_fSpeed = 15.0f;
	const float g_fRotSpd = 5.0f;
	const float g_fAccel = 0.1f;
	const float g_fBrake = 0.2f;
	const float g_fMaxSpeed = 10.0f;
}

// �R���X�g���N�^
CEnemy::CEnemy(CScene* pScene) : CModel(pScene)
{
	m_id = GOT_ENEMY;
	m_uTick = 0;
	m_fSpeed = 0.0f;
	m_pLand = nullptr;
	XMStoreFloat4x4(&m_mInvWorld, XMMatrixIdentity());
}

// �f�X�g���N�^
CEnemy::~CEnemy()
{
}

// ������
HRESULT CEnemy::Init()
{
	HRESULT hr = CModel::Init();
	SetModel(MODEL_ENEMY);
	m_vPos.x = 100.0f;
	m_uTick = 0;
	m_pLand = (CLand*)m_pScene->Find(GOT_LAND);
	return hr;
}

// �I������
void CEnemy::Fin()
{
	CModel::Fin();
}

// �X�V
void CEnemy::Update()
{
	// �^�C�}�X�V
	++m_uTick;
	// ��]
	XMFLOAT3 angle = GetAngle();
	if (CInput::GetKeyPress(VK_LEFT) || CInput::GetKeyPress(VK_A)) {
		angle.y -= g_fRotSpd;
		if (angle.y < -180.0f)
			angle.y += 360.0f;
	}
	if (CInput::GetKeyPress(VK_RIGHT) || CInput::GetKeyPress(VK_D)) {
		angle.y += g_fRotSpd;
		if (angle.y >= 180.0f)
			angle.y -= 360.0f;
	}
	// ������
	if (CInput::GetKeyPress(VK_UP) || CInput::GetKeyPress(VK_W)) {
		m_fSpeed += g_fAccel;
		if (m_fSpeed > g_fMaxSpeed)
			m_fSpeed = g_fMaxSpeed;
	}
	if (CInput::GetKeyPress(VK_DOWN) || CInput::GetKeyPress(VK_S)) {
		m_fSpeed -= g_fBrake;
		if (m_fSpeed < 0.0f)
			m_fSpeed = 0.0f;
	}

	// ���݈ʒu�擾
	XMFLOAT3 vPos = GetPos();
	// ��]�}�g���b�N�X����
	XMFLOAT4X4 mW;
	XMStoreFloat4x4(&mW, XMMatrixRotationY(XMConvertToRadians(angle.y)));
	// ���f�����W���擾
	XMFLOAT3 vZ = XMFLOAT3(mW._31, mW._32, mW._33);

	// �ړ�
	vPos.x += vZ.x * m_fSpeed;
	vPos.y += vZ.y * m_fSpeed;
	vPos.z += vZ.z * m_fSpeed;

	// �n�ʂƂ̓����蔻��
	XMFLOAT3 vP0;
	vP0.x = vPos.x;
	vP0.y = vPos.y + GetRadius() * 2;
	vP0.z = vPos.z;
	XMFLOAT3 vX, vN;
	if (m_pLand && m_pLand->Collision(vP0,
		XMFLOAT3(0.0f, -1.0f, 0.0f), &vX, &vN)) {
		vPos.y = vX.y;
	}
	else {
		vPos.y = 0.0f;
	}

	mW._41 = vPos.x;
	mW._42 = vPos.y;
	mW._43 = vPos.z;
	SetPos(vPos);

	// ���[���h�ϊ��s��X�V
	SetWorld(mW);

	// �p�x�X�V
	SetAngle(angle);

	//CModel::Update();
}
