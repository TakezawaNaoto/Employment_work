//=============================================================================
//
// �v���C���[ �N���X��` [Enemy.h]
// Author : NAOTO TAKEZAWA
//
//=============================================================================
#pragma once
#include "Model.h"
#include "Land.h"

class CEnemy : public CModel
{
private:
	UINT m_uTick;
	XMFLOAT4X4 m_mInvWorld;
	float m_fSpeed;			// ����
	CLand* m_pLand;			// �n��

public:
	CEnemy(CScene* pScene);
	virtual ~CEnemy();

	virtual HRESULT Init();
	virtual void Fin();
	virtual void Update();

	XMFLOAT4X4& GetInvWorld() { return m_mInvWorld; }
};
