// �n�� [Land.h]
#pragma once
#include "Model.h"

class CLand : public CModel
{
private:
	UINT m_nVertex;				// ���_��
	TAssimpVertex* m_pVertex;	// ���_�z��
	UINT m_nIndex;				// �C���f�b�N�X��
	UINT* m_pIndex;				// �C���f�b�N�X�z��

public:
	CLand(CScene* pScene);		// �R���X�g���N�^
	virtual ~CLand();			// �f�X�g���N�^

	virtual HRESULT Init();		// ������
	virtual void Fin();			// �I������

	bool Collision(XMFLOAT3 vP0, XMFLOAT3 vW, XMFLOAT3* pX = nullptr, XMFLOAT3* pN = nullptr);
								// ���C�Ƃ̓����蔻��
};
