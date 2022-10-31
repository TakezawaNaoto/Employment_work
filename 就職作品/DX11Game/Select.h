//=============================================================================
//
// カメラ クラス [Camera.h]
// Author : NAOTO TAKEZAWA
//
//=============================================================================
#pragma once
#include "Scene.h"

// 変数定義
#define MAX_CHARA (3)

class CSelect : CScene
{
private:
	bool m_bStart;	// ゲーム開始フラグ
	ID3D11ShaderResourceView* m_pTexStart;
	ID3D11ShaderResourceView* m_pTexBG;
	int m_nTimer;	// スタートボタンの点滅用タイマー
	char Chara[MAX_CHARA];	// キャラ候補
	int selectNom;			// 選択しているキャラの添え字
	static char* selectChara;		// 決定したキャラ

public:
	CSelect();
	virtual ~CSelect();

	virtual bool Init();
	virtual void Fin();
	virtual void Update() = 0;
	virtual void Draw() = 0;

	static void * GetPlayer() { return selectChara; }
};