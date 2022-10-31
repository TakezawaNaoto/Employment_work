//=============================================================================
//
// ゲーム カメラ クラス [GameCamera.cpp]
// Author : NAOTO TAKEZAWA
//
//=============================================================================
#include "GameCamera.h"
#include "Model.h"
#include "Input.h"
#include "DebugProc.h"

// グローバル変数
namespace {
	const float CAM_POS_P_X = 0.0f;		// 定点カメラの視点位置(X座標)
	const float CAM_POS_P_Y = 400.0f;	// 定点カメラの視点位置(Y座標)
	const float CAM_POS_P_Z = -1000.0f;	// 定点カメラの視点位置(Z座標)
	const float CAM_POS_R_X = 0.0f;		// 定点カメラの注視点位置(X座標)
	const float CAM_POS_R_Y = 0.0f;		// 定点カメラの注視点位置(Y座標)
	const float CAM_POS_R_Z = 0.0f;		// 定点カメラの注視点位置(Z座標)

	const float FP_POS_P_X = 0.0f;		// 一人称カメラの視点位置(X座標)
	const float FP_POS_P_Y = 38.6f;		// 一人称カメラの視点位置(Y座標)
	const float FP_POS_P_Z = 159.96f;	// 一人称カメラの視点位置(Z座標)
	const float FP_POS_R_X = 0.0f;		// 一人称カメラの注視点位置(X座標)
	const float FP_POS_R_Y = 22.6f;		// 一人称カメラの注視点位置(Y座標)
	const float FP_POS_R_Z = 259.96f;	// 一人称カメラの注視点位置(Z座標)

	const float TP_POS_P_X = 0.0f;		// 三人称カメラの視点位置(X座標)
	const float TP_POS_P_Y = 100.0f;	// 三人称カメラの視点位置(Y座標)
	const float TP_POS_P_Z = -300.0f;	// 三人称カメラの視点位置(Z座標)
	const float TP_POS_R_X = 0.0f;		// 三人称カメラの注視点位置(X座標)
	const float TP_POS_R_Y = 80.0f;		// 三人称カメラの注視点位置(Y座標)
	const float TP_POS_R_Z = 0.0f;		// 三人称カメラの注視点位置(Z座標)
};

// カメラモード
enum ECamMode {
	CM_FIXED = 0,	// 固定
	CM_FP,			// 一人称
	CM_BT,			// バレットタイム風
	CM_TP,			// 三人称

	MAX_CM
};

// コンストラクタ
CGameCamera::CGameCamera()
{
	m_pPlayer = nullptr;
	m_fAngle = 0.0f;
	m_fRadius = 1.0f;
	m_nMode = CM_FIXED;
}

// 初期化
void CGameCamera::Init()
{
	CCamera::Init();
	SetSky(CModel::GetAssimp(MODEL_SKY));
}

// 更新
void CGameCamera::Update()
{
	// 視点切替
	if (CInput::GetKeyRelease(VK_0) || CInput::GetKeyRelease(VK_NUMPAD0))
		m_nMode = 0;
	if (CInput::GetKeyRelease(VK_1) || CInput::GetKeyRelease(VK_NUMPAD1))
		m_nMode = 1;
	if (CInput::GetKeyRelease(VK_2) || CInput::GetKeyRelease(VK_NUMPAD2))
		m_nMode = 2;
	if (CInput::GetKeyRelease(VK_3) || CInput::GetKeyRelease(VK_NUMPAD3))
		m_nMode = 3;

	if (m_pPlayer) {
		XMMATRIX mW;
		switch (m_nMode) {
		case CM_FIXED:	// 定点カメラ
			m_vTarget = m_pPlayer->GetPos();
			m_vPos = XMFLOAT3(CAM_POS_P_X, CAM_POS_P_Y, CAM_POS_P_Z);
			m_vUp = XMFLOAT3(0.0f, 1.0f, 0.0f);
			break;
		case CM_FP:		// 一人称カメラ
			mW = XMLoadFloat4x4(&m_pPlayer->GetWorld());
			XMStoreFloat3(&m_vUp,
				XMVector3TransformNormal(XMVectorSet(0, 1, 0, 0), mW));
			XMStoreFloat3(&m_vTarget,
				XMVector3TransformCoord(
					XMVectorSet(FP_POS_R_X, FP_POS_R_Y, FP_POS_R_Z, 1.0f), mW));
			XMStoreFloat3(&m_vPos,
				XMVector3TransformCoord(
					XMVectorSet(FP_POS_P_X, FP_POS_P_Y, FP_POS_P_Z, 1.0f), mW));
			break;
		case CM_BT:		// バレットタイム風カメラ
			m_fAngle += 1.0f;
			if (m_fAngle >= 180.0f)
				m_fAngle -= 360.0f;
			m_vTarget = m_pPlayer->GetPos();
			m_vUp = XMFLOAT3(0.0f, 1.0f, 0.0f);
			m_vPos.x = m_vTarget.x +
				sinf(XMConvertToRadians(m_fAngle)) * (m_fRadius * 2.5f);
			m_vPos.y = m_vTarget.y + 30.0f;
			m_vPos.z = m_vTarget.z +
				cosf(XMConvertToRadians(m_fAngle)) * (m_fRadius * 2.5f);
			break;
		case CM_TP:	// 三人称カメラ
			XMFLOAT3 vNewUp, vNewTarget, vNewPos;
			mW = XMLoadFloat4x4(&m_pPlayer->GetWorld());
			XMStoreFloat3(&vNewUp,
				XMVector3TransformNormal(XMVectorSet(0, 1, 0, 0), mW));
			XMStoreFloat3(&vNewTarget,
				XMVector3TransformCoord(
					XMVectorSet(TP_POS_R_X, TP_POS_R_Y, TP_POS_R_Z, 1.0f), mW));
			XMStoreFloat3(&vNewPos,
				XMVector3TransformCoord(
					XMVectorSet(TP_POS_P_X, TP_POS_P_Y, TP_POS_P_Z, 1.0f), mW));
			m_vUp.x = m_vUp.x * 0.9f + vNewUp.x * 0.1f;
			m_vUp.y = m_vUp.y * 0.9f + vNewUp.y * 0.1f;
			m_vUp.z = m_vUp.z * 0.9f + vNewUp.z * 0.1f;
			m_vTarget.x = m_vTarget.x * 0.9f + vNewTarget.x * 0.1f;
			m_vTarget.y = m_vTarget.y * 0.9f + vNewTarget.y * 0.1f;
			m_vTarget.z = m_vTarget.z * 0.9f + vNewTarget.z * 0.1f;
			m_vPos.x = m_vPos.x * 0.9f + vNewPos.x * 0.1f;
			m_vPos.y = m_vPos.y * 0.9f + vNewPos.y * 0.1f;
			m_vPos.z = m_vPos.z * 0.9f + vNewPos.z * 0.1f;
			break;
		}
	} else {
		m_vPos = XMFLOAT3(CAM_POS_P_X, CAM_POS_P_Y, CAM_POS_P_Z);
		m_vTarget = XMFLOAT3(CAM_POS_R_X, CAM_POS_R_Y, CAM_POS_R_Z);
		m_vUp = XMFLOAT3(0.0f, 1.0f, 0.0f);
	}

	CCamera::Update();

	// デバッグ表示
	CDebugProc::Print("*** ｶﾒﾗ ｿｳｻ ***\n");
	CDebugProc::Print("[1] : FP View\n");
	CDebugProc::Print("[2] : Bullet-time style\n");
	CDebugProc::Print("[3] : TP View\n");
	CDebugProc::Print("[0] : Fixed point\n");
	CDebugProc::Print("[ｶﾒﾗ ｲﾁ : (%f, %f, %f)]\n", m_vPos.x, m_vPos.y, m_vPos.z);
	CDebugProc::Print("[ﾁｭｳｼﾃﾝ : (%f, %f, %f)]\n",
		m_vTarget.x, m_vTarget.y, m_vTarget.z);
	CDebugProc::Print("\n");
}

// 自機設定
void CGameCamera::SetPlayer(CGameObj* pPlayer)
{
	m_pPlayer = pPlayer;
	if (m_pPlayer) {
		m_fRadius = m_pPlayer->GetRadius();
	} else {
		m_fRadius = 1.0f;
	}
}
