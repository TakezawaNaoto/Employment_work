//=============================================================================
//
// ゲーム カメラ クラス [GameCamera.h]
// Author : NAOTO TAKEZAWA
//
//=============================================================================
#pragma once
#include "Camera.h"
#include "GameObj.h"

class CGameCamera : public CCamera
{
private:
	CGameObj* m_pPlayer;	// 自機
	float m_fRadius;		// 自機半径
	int m_nMode;			// カメラモード
	float m_fAngle;			// カメラアングル

public:
	CGameCamera();

	virtual void Init();
	virtual void Update();

	void SetPlayer(CGameObj* pPlayer);
};
