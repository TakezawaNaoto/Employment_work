//=============================================================================
//
// ゲーム クラス定義 [Game.h]
// Author : NAOTO TAKEZAWA
//
//=============================================================================
#pragma once
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "Explosion.h"

// クラス定義
class CGame : public CScene
{
private:
	bool m_bResult;

	CGameCamera m_camera;
	CPlayer* m_pPlayer;
	CEnemy* m_pEnemy;
	int m_nBoundary;

public:
	CGame();
	virtual ~CGame();

	virtual bool Init();
	virtual void Fin();
	virtual void Update();
	virtual void Draw();

	int GetBoundary() { return m_nBoundary; }

	CPlayer* GetPlayer() { return m_pPlayer; }
	CEnemy* GetEnemy() { return m_pEnemy; }

private:
	void UpdateBoundary();
};
