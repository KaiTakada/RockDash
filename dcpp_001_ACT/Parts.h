//===============================================
//
// Xモデルオブジェクトパーツ(Parts.cpp)	//親モデルを持つモデル
// Author: ��田 佳依
//
//===============================================
#ifndef _PARTS_H_								//このマクロ定義がされてなかったら
#define _PARTS_H_								//二重インクルード防止のマクロを定義する

//================================
// インクルードファイル
//================================
#include "manager.h"
#include "object.h"

//================================
// マクロ定義
//================================
#define DEF_VERTEX3D D3DXVECTOR3(0.0f,0.0f,0.0f)				//デフォルトサイズ
#define MAX_XMODEL (128)				//モデルの受け皿容量

//================================
// モデルクラス
//================================
class CParts : public CObject
{
public:
	//=============================
	// パーツ情報構造体の定義
	//=============================
	typedef struct
	{
		char *pFilepass;		//ファイルパス
		int nIdxParent;			//親のインデックス
	}PassParent;

	CParts(int nPriority = 3);
	~CParts();

	HRESULT Init(void);							//初期化(デフォ)
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);			//初期化(オバロ)
	void Uninit(void);							//終了
	void Update(void);							//更新
	void Draw(void);							//描画

	static CParts *Create(const char *pFilename, const D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//生成
	void SetParent(CParts *pParts);
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }						//現在位置設定
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }						//現在向き設定
	D3DXVECTOR3 GetPos(void) { return m_pos; }				//現在位置取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }				//現在向き取得
	D3DXMATRIX GetMtxWorld(void);		//ワールドマトリックス取得

	void SetIdxModel(int nIdx) { m_nIdxModel = nIdx; }		//モデル番号の割り当て
	int GetIdxModel() { return m_nIdxModel; }		//モデル番号の取得
	D3DXVECTOR3 GetOutcomePos(CParts *pParts);		//合計座標
	CParts *GetParent() { return m_pParent; }			//親モデルポインタ取得
	void SetMat(D3DXMATERIAL mat) { m_mat = mat; }		//色設定

protected:

private:
	D3DXVECTOR3 m_pos;			//現在位置
	D3DXVECTOR3 m_rot;			//現在向き
	CParts *m_pParent;			//親モデルへのポインタ
	int m_nIdxModel;			//モデル番号
	D3DXMATERIAL m_mat;			//指定色
};

#endif
