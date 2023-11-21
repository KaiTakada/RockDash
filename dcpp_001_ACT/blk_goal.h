//==================================================
//
// �S�[������(blk_goal.h)
// Author : Kai Takada
//
//==================================================
#ifndef _BLK_GOAL_H_								//���̃}�N����`������ĂȂ�������
#define _BLK_GOAL_H_								//��d�C���N���[�h�h�~�̃}�N�����`����

//============================================
// �C���N���[�h�t�@�C��
//============================================
#include "block.h"

//============================================
//�}�N����`
//============================================

//============================================
// �O���錾
//============================================

//============================================
// �u���b�N�N���X
//============================================
class CBlk_Goal : public CBlock
{
public:
	CBlk_Goal(int nPriority = 1);
	~CBlk_Goal();

	HRESULT Init(void);			//������
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, TYPE_Blk type = TYPE_GOAL);		//������(�I�o��)
	void Uninit(void);			//�I��
	void Update(void);			//�X�V
	void Draw(void);			//�`��

	virtual bool CollisionRect(void);		//�����蔻��(�p��)

	static CBlk_Goal *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//����

protected:

private:
};

#endif
