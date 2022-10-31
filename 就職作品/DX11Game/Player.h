//=============================================================================
//
// �v���C���[ �N���X��` [Player.h]
// Author : NAOTO TAKEZAWA
//
//=============================================================================
#pragma once
#include "Model.h"
#include "Land.h"

class CPlayer : public CModel
{
private:
	UINT m_uTick;
	XMFLOAT4X4 m_mInvWorld;
	float m_fSpeed;			// ����
	CLand* m_pLand;			// �n��

public:
	CPlayer(CScene* pScene);
	virtual ~CPlayer();

	virtual HRESULT Init();
	virtual void Fin();
	virtual void Update();

	XMFLOAT4X4& GetInvWorld() { return m_mInvWorld; }
};
