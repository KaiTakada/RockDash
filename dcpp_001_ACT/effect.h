//===============================================
//
// �G�t�F�N�g(effect.cpp)
// Author ���c ����
//
//===============================================
#ifndef _EFFECT_H_		//���̃}�N����`������ĂȂ�������
#define _EFFECT_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "manager.h"
#include "objectBillboard.h"

//=========================
// �}�N����`
//=========================

//=========================
// �I�u�W�F�N�g2D�w�i�N���X
//=========================
class CEffect : public CObjectBillboard
{
public:
	enum TEX
	{
		TEX_000 = 0,
		TEX_SMOKE,
		TEX_MAX,
	};

	CEffect(int nPriority = 4);		//�R���X�g���N�^
	~CEffect();		//�f�X�g���N�^

	HRESULT Init(void);							//������(�f�t�H)
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//������(�I�o��)
	void Uninit(void);							//�I��
	void Update(void);							//�X�V
	void Draw(void);							//�`��

	void SetLife(int nLife) { m_nLife = nLife; }				//�c�����
	int GetLife() { return m_nLife; }							//�c�����

	void SetLifeMax(int nLife) { m_nLifeMax = nLife; }				//����
	int GetLifeMax() { return m_nLifeMax; }							//����

	void SetType(TEX type) { m_type = type; }				//����
	TEX GetType() { return m_type; }						//����

	static CEffect *Create(void);		//����
	static CEffect *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f), const D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		const D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f), int nLife = 10, const TEX TexType = TEX_000);		//����

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TEX_MAX];				//�e�N�X�`���o�b�t�@
	int m_nLife;		//�c�����
	int m_nLifeMax;		//����
	TEX m_type;			//���
};

#endif