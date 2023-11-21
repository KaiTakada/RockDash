//==================================================
//
// �A�C�e��(item.h)
// Author : Kai Takada
//
//==================================================
#ifndef _ITEM_H_								//���̃}�N����`������ĂȂ�������
#define _ITEM_H_								//��d�C���N���[�h�h�~�̃}�N�����`����

#include "manager.h"
#include "objectBillboard.h"

//�}�N����`
#define ITEM_SIZE D3DXVECTOR3(50.0f,50.0f,50.0f)					//�f�t�H���g�T�C�Y

//============================================
// �O���錾
//============================================

//============================================
// �u���b�N�N���X
//============================================
class CItem : public CObjectBillboard
{
public:
	//===================================
	// �^�C�v�񋓌^��`
	//===================================
	typedef enum
	{
		TYPE_EXP = 0,						//�o���l�N���X�^��
		TYPE_MAX,
	}TYPE;

	CItem(int nPriority = 1);
	~CItem();

	HRESULT Init(void);			//������
	HRESULT Init(const D3DXVECTOR3 pos);		//������(�I�o��)
	void Uninit(void);			//�I��
	void Update(void);			//�X�V
	void Draw(void);			//�`��

	CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size = ITEM_SIZE, TYPE type = TYPE_EXP);		//����
	bool CItem::CollisionBall(void);		//�����蔻��
	int GetNumAll(void) { return m_nNumAll; }		//�����擾

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];			//�e�N�X�`���ւ̃|�C���^
	static int m_nNumAll;									//���ݎg���Ă���u���b�N��

	CItem::TYPE m_type;					//���
};

#endif
