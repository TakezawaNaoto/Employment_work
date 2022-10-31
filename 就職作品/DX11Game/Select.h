//=============================================================================
//
// �J���� �N���X [Camera.h]
// Author : NAOTO TAKEZAWA
//
//=============================================================================
#pragma once
#include "Scene.h"

// �ϐ���`
#define MAX_CHARA (3)

class CSelect : CScene
{
private:
	bool m_bStart;	// �Q�[���J�n�t���O
	ID3D11ShaderResourceView* m_pTexStart;
	ID3D11ShaderResourceView* m_pTexBG;
	int m_nTimer;	// �X�^�[�g�{�^���̓_�ŗp�^�C�}�[
	char Chara[MAX_CHARA];	// �L�������
	int selectNom;			// �I�����Ă���L�����̓Y����
	static char* selectChara;		// ���肵���L����

public:
	CSelect();
	virtual ~CSelect();

	virtual bool Init();
	virtual void Fin();
	virtual void Update() = 0;
	virtual void Draw() = 0;

	static void * GetPlayer() { return selectChara; }
};