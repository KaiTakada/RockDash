//==================================================
//
// �u���b�N����(block.h)
// Author : Kai Takada
//
//==================================================
#ifndef _BLOCK_H_								//���̃}�N����`������ĂȂ�������
#define _BLOCK_H_								//��d�C���N���[�h�h�~�̃}�N�����`����

//============================================
// �C���N���[�h�t�@�C��
//============================================
#include "objectX.h"

//============================================
//�}�N����`
//============================================
#define MAX_BLOCK (256)						//�u���b�N�̍ő吔

//============================================
// �O���錾
//============================================

//============================================
// �u���b�N�N���X
//============================================
class CBlock : public CObjectX
{
public:
	//===================================
	// �u���b�N�񋓌^�̒�`
	//===================================
	enum TYPE_Blk
	{
		TYPE_NORMAL = 0,		//�ʏ�̃u���b�N
		TYPE_BREAK,		//�󂹂�u���b�N
		TYPE_GOAL,		//�S�[���u���b�N
		TYPE_MAX,
	};

	CBlock(int nPriority = 1);
	~CBlock();

	virtual HRESULT Init(void);			//������
	virtual HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, TYPE_Blk type = TYPE_NORMAL);		//������(�I�o��)
	virtual void Uninit(void);			//�I��
	virtual void Update(void);			//�X�V
	virtual void Draw(void);			//�`��

	static CBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f), TYPE_Blk type = TYPE_NORMAL);		//����
	virtual bool CollisionRect(void);		//�����蔻��
	static int GetNumAll(void) { return m_nNumAll; }		//�����擾
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }		//�O��ʒu�擾
	void SetType_Blk(CBlock::TYPE_Blk type) { m_type = type; }		//���
	CBlock::TYPE_Blk GetType_Blk() { return m_type; }		//���
	virtual int GetLocalType() { return (int)GetType_Blk(); }	//��ގ擾(��ꁦobject����p��)

protected:

private:
	static int m_nNumAll;											//���ݎg���Ă���u���b�N��

	D3DXVECTOR3 m_posOld;			//�O��̈ʒu
	CBlock::TYPE_Blk m_type;			//���
};

#endif
