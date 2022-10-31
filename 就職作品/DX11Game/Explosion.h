// �����G�t�F�N�g �N���X [Explosion.h]
#pragma once
#include "GameObj.h"
#include "AssimpModel.h"

// �\���̒�`
//----- ���_���W
struct VERTEX {
	XMFLOAT3 position;
	XMFLOAT3 normal;
	XMFLOAT4 diffuse;
};

// �j�ЃN���X
class CDebris
{
private:
	XMFLOAT3 m_vertex[3];	// ���_���W
	XMFLOAT3 m_normal;		// �@���x�N�g��
	XMFLOAT4X4 m_world;		// ���[���h�ϊ�
	XMFLOAT3 m_velocity;	// ���x
	XMFLOAT3 m_accel;		// �����x
	XMFLOAT3 m_axis;		// ��]��
	float m_rotate;			// ��]���x
	float m_alpha;			// �s�����x

public:
	HRESULT Init(XMFLOAT3& v0, XMFLOAT3& v1, XMFLOAT3& v2,
		float fRadius, XMFLOAT4X4* pWorld, XMFLOAT3* pVelocity);	// ������
	void Update();								// �X�V
	void UpdateBuffer(VERTEX* pVertex);			// ���_�o�b�t�@�X�V
};

// �����G�t�F�N�g �N���X
class CExplosion : public CGameObj
{
private:
	CDebris* m_pDebris;							// �j��
	UINT m_uDebris;								// �j�Ђ̐�
	ID3D11Buffer* m_pVertexBuffer;				// ���_�o�b�t�@
	static ID3D11Buffer* m_pConstantBuffer[2];	// �萔�o�b�t�@
	static ID3D11VertexShader* m_pVertexShader;	// ���_�V�F�[�_
	static ID3D11InputLayout* m_pInputLayout;	// ���_�t�H�[�}�b�g
	static ID3D11PixelShader* m_pPixelShader;	// �s�N�Z���V�F�[�_
	TAssimpVertex* m_pVertex;					// ���_�z��
	UINT m_uVertex;								// ���_��
	UINT* m_pIndex;								// �C���f�b�N�X�z��
	UINT m_uIndex;								// �C���f�b�N�X��

public:
	CExplosion(CScene* pScene);
	~CExplosion();
	static HRESULT InitShader();
	static void FinShader();
	HRESULT Init();					// ������
	void Fin();						// �I������
	void Update();					// �X�V
	void Draw();					// �`��
	void DrawAlpha();				// �����������`��
	// ���f���ݒ�
	HRESULT SetModel(CAssimpModel* pModel);
	// �����J�n
	HRESULT Start(XMFLOAT4X4* pWorld, XMFLOAT3* pVelocity = nullptr);
};
