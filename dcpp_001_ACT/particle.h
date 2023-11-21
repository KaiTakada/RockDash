//===============================================
//
// �p�[�e�B�N��(particle.h)
// Author ���c ����
//
//===============================================
#ifndef _PARTICLE_H_		//���̃}�N����`������ĂȂ�������
#define _PARTICLE_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "manager.h"
#include "object.h"

//=========================
// �}�N����`
//=========================
#define MAX_PARTICLE (256)		//����

//=========================
// �O���錾
//=========================
class CEffect;

//=========================
// �I�u�W�F�N�g2D�N���X
//=========================
class CParticle : public CObject
{
public:
	enum TYPE
	{
		TYPE_NONE = 0,	//����
		TYPE_EXPLODE,	//����
		TYPE_BOOST,	//�u�[�X�g
		TYPE_MAX,
	};

	CParticle(int nPriority = 5);		//�R���X�g���N�^
	~CParticle();		//�f�X�g���N�^

	HRESULT Init(void);							//������(�f�t�H)
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, D3DXVECTOR3 move, const D3DXVECTOR3 size, TYPE type);
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		//������(�I�o��)
	void Uninit(void);							//�I��
	void Update(void);							//�X�V
	void Draw(void);							//�`��
	static CParticle *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move, const D3DXVECTOR3 size, TYPE type);		//����
	static void Release(int nID);							//�j��

	void SetPos(const D3DXVECTOR3 pos);			//�ʒu�ݒ�
	void SetRot(const D3DXVECTOR3 rot);			//�����ݒ�
	D3DXVECTOR3 GetPos(void);		//�ʒu�擾
	D3DXVECTOR3 GetSize(void);		//2D�T�C�Y�擾
	bool GetJump(void) { return false; }		//�W�����v����
	D3DXVECTOR3 GetPosOld(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		//�O��ʒu�擾

protected:

private:
	CEffect *m_apEffect[MAX_PARTICLE];			//�A�h���X�����擾�p
	int m_nLife;	//����

};

#endif