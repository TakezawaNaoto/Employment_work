// 地面 [Land.cpp]
#include "Land.h"

// コンストラクタ
CLand::CLand(CScene* pScene) : CModel(pScene)
{
	m_id = GOT_LAND;

	m_pVertex = nullptr;
	m_nVertex = 0;
	m_pIndex = nullptr;
	m_nIndex = 0;
}

// デストラクタ
CLand::~CLand()
{
}

// 初期化
HRESULT CLand::Init()
{
	SetModel(MODEL_LAND);

	// 頂点配列、インデックス配列を取得しておく
	CAssimpModel* pModel = GetAssimp(MODEL_LAND);
	pModel->GetVertexCount(&m_nVertex, &m_nIndex);
	m_pVertex = new TAssimpVertex[m_nVertex];
	m_pIndex = new UINT[m_nIndex];
	pModel->GetVertex(m_pVertex, m_pIndex);

	return CModel::Init();
}

// 終了処理
void CLand::Fin()
{
	CModel::Fin();

	// 頂点配列、インデックス配列の解放
	SAFE_DELETE_ARRAY(m_pIndex);
	SAFE_DELETE_ARRAY(m_pVertex);
}

// レイとの当たり判定
bool CLand::Collision(XMFLOAT3 vP0, XMFLOAT3 vW, XMFLOAT3* pX, XMFLOAT3* pN)
{
	// 全ての三角形について繰り返し
	for (int i = 0; i < m_nIndex; ) {
		// 三角形の3頂点
		XMFLOAT3& vV0 = m_pVertex[m_pIndex[i++]].vPos;
		XMFLOAT3& vV1 = m_pVertex[m_pIndex[i++]].vPos;
		XMFLOAT3& vV2 = m_pVertex[m_pIndex[i++]].vPos;
		// 2辺より法線ベクトルを求める
		XMVECTOR v0v1 = XMVectorSet(vV1.x - vV0.x, vV1.y - vV0.y, vV1.z - vV0.z, 0.0f);
		XMVECTOR v1v2 = XMVectorSet(vV2.x - vV1.x, vV2.y - vV1.y, vV2.z - vV1.z, 0.0f);
		XMVECTOR n = XMVector3Normalize(XMVector3Cross(v0v1, v1v2));
		// 法線ベクトルとレイの方向ベクトルとの内積(式の分母)を求める
		float base;
		XMStoreFloat(&base, XMVector3Dot(n, XMLoadFloat3(&vW)));
		// 分母が0なら面と平行のため次の三角形へ
		if (base == 0.0f) {
			continue;
		}
		// 媒介変数tを求める
		float t;
		XMStoreFloat(&t, XMVector3Dot(n,
			XMVectorSet(vV0.x - vP0.x, vV0.y - vP0.y, vV0.z - vP0.z, 0.0f)));
		t /= base;
		// tが負なら交点はレイの後ろなので次の三角形へ
		if (t < 0.0f) {
			continue;
		}
		// 交点Xを求める
		XMFLOAT3 vX;
		vX.x = vP0.x + t * vW.x;
		vX.y = vP0.y + t * vW.y;
		vX.z = vP0.z + t * vW.z;
		// 交点が三角形の内側か調べる
		float dot;
		XMStoreFloat(&dot, XMVector3Dot(n,
			XMVector3Cross(v0v1,
				XMVectorSet(vX.x - vV0.x, vX.y - vV0.y, vX.z - vV0.z, 0.0f))));
		if (dot < 0.0f) {
			continue;
		}
		XMStoreFloat(&dot, XMVector3Dot(n,
			XMVector3Cross(v1v2,
				XMVectorSet(vX.x - vV1.x, vX.y - vV1.y, vX.z - vV1.z, 0.0f))));
		if (dot < 0.0f) {
			continue;
		}
		XMVECTOR v2v0 = XMVectorSet(vV0.x - vV2.x, vV0.y - vV2.y, vV0.z - vV2.z, 0.0f);
		XMStoreFloat(&dot, XMVector3Dot(n,
			XMVector3Cross(v2v0,
				XMVectorSet(vX.x - vV2.x, vX.y - vV2.y, vX.z - vV2.z, 0.0f))));
		if (dot < 0.0f) {
			continue;
		}
		// 点が内側だったので当たっている
		if (pX) {
			*pX = vX;
		}
		if (pN) {
			XMStoreFloat3(pN, n);
		}
		return true;
	}
	return false;	// 当たっていない
}
