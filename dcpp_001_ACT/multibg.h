//===============================================
//
// �}���`�w�i(multibg.h)
// Author ���c ����
//
//===============================================
#ifndef _MULTIBG_H_		//���̃}�N����`������ĂȂ�������
#define _MULTIBG_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "manager.h"
#include "object.h"

//=========================
// �}�N����`
//=========================
#define MAX_MULTIBG (16)		//����
//#define MAX_MULTIBG (128)		//����

//=========================
// �O���錾
//=========================
class CObject2D;

//=========================
// �I�u�W�F�N�g2D�N���X
//=========================
class CMultiBg : public CObject
{
public:

	CMultiBg();		//�R���X�g���N�^
	~CMultiBg();		//�f�X�g���N�^

	HRESULT Init(void);							//������(�f�t�H)
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, D3DXVECTOR2 move, const D3DXVECTOR3 size, int nNum);
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		//������(�I�o��)
	void Uninit(void);							//�I��
	void Update(void);							//�X�V
	void Draw(void);							//�`��
	static CMultiBg *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, D3DXVECTOR2 move, const D3DXVECTOR3 size,int nNum);		//����
	static void Release(int nID);							//�j��

	void SetPos(const D3DXVECTOR3 pos);			//�ʒu�ݒ�
	void SetRot(const D3DXVECTOR3 rot);			//�����ݒ�
	D3DXVECTOR3 GetPos(void);		//�ʒu�擾
	D3DXVECTOR3 GetSize(void);		//2D�T�C�Y�擾
	bool GetJump(void) { return false; }		//�W�����v����
	D3DXVECTOR3 GetPosOld(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		//�O��ʒu�擾

protected:

private:
	CObject2D *m_apObject[MAX_MULTIBG];			//�A�h���X�����擾�p
};

#endif