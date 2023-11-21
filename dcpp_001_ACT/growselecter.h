//===============================================
//
// �����V�[��(growselecter.h)
// Author: ���c ����
//
//===============================================
#ifndef _GROWSELECTER_H_
#define _GROWSELECTER_H_

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "object.h"

//=========================
// �}�N����`
//=========================
#define MAX_ITEM (3)		//�A�C�e����

//=========================
// �O���錾
//=========================
class CItem2D;
class CObject2D;

//=========================
// �v���C���[�N���X
//=========================
class CGrowSelecter : public CObject
{
public:
	CGrowSelecter(int nPriority = PRIORITY_UI);		//�R���X�g���N�^
	~CGrowSelecter();		//�f�X�g���N�^

	HRESULT Init(void);							//������(�f�t�H)
	HRESULT Init(const D3DXVECTOR3 pos);		//������(�I�o��)
	void Uninit(void);							//�I��
	void Update(void);							//�X�V
	void Draw(void);							//�`��
	static CGrowSelecter *Create();		//����

protected:

private:
	CItem2D *m_pItem[MAX_ITEM];			//�I������()
	CObject2D *m_pBg;			//�w�i()
	int m_nPauseSelect;			//���݂̑I����
	bool m_bEnter;				//����t���O
};

#endif