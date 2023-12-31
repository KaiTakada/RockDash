//===============================================
//
// Q[(game.h)
// Author: ûüc ÀË
//
//===============================================
#ifndef _GAME_H_		//±Ì}Nè`ª³êÄÈ©Á½ç
#define _GAME_H_		//ñdCN[hh~Ì}Nðè`·é

//=========================
// CN[ht@C
//=========================
#include "main.h"
#include "manager.h"

//=========================
// Oûé¾
//=========================
//class CRenderer;
class CPause;
class CGrowSelecter;
class CTimer;
class CEnemy_Boss;
class CMap;

//=========================
// æÊ(V[)NX
//=========================
class CGame : public CScene
{
public:
	CGame();
	~CGame();

	virtual HRESULT Init();		//ú»
	virtual void Uninit();		//I¹
	virtual void Update();		//XV
	virtual void Draw();		//`æ
	static CGame *Create();		//¶¬

	static CPlayer *GetPlayer() { return m_pPlayer; }							//vC[Ìæ¾
	static CPause *GetPause() { return m_pPause; }								//|[YÌæ¾
	static CTimer *GetTimer() { return m_pTimer; }								//^C}[Ìæ¾
	static CMap *GetMap() { return m_pMap; }								//}bvÌæ¾

	static void NullPause() { m_pPause = nullptr; }								//|[Y|C^ðnullÉ
	static bool MapFlag() { return m_pMap != nullptr; }								//|[Y|C^ðnullÉ

protected:

private:
	static CPlayer *m_pPlayer;					//vC[
	static CPause *m_pPause;					//|[Y
	static CTimer *m_pTimer;					//^C}[
	static CMap *m_pMap;						//}bv
	CField *m_pField;							//nÊ
};

#endif