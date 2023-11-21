//===============================================
//
// �w�i(bg.cpp)
// Author ���c ����
//
//===============================================
#ifndef _BG_H_		//���̃}�N����`������ĂȂ�������
#define _BG_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "manager.h"
#include "object2D.h"

//=========================
// �}�N����`
//=========================

//=========================
// �I�u�W�F�N�g2D�w�i�N���X
//=========================
class CBg : public CObject2D
{
public:
	enum TEX
	{
		TEX_000 = 0,
		TEX_001,
		TEX_002,
		TEX_MAX,
	};

	CBg();		//�R���X�g���N�^
	~CBg();		//�f�X�g���N�^

	HRESULT Init(void);							//������(�f�t�H)
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		//������(�I�o��)
	void Uninit(void);							//�I��
	void Update(void);							//�X�V
	void Draw(void);							//�`��

	static CBg *Create(void);		//����
	static CBg *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR2 move, const D3DXVECTOR3 size, const TEX TexType);		//����
	void SetMove(const D3DXVECTOR2 move) { m_texMove = move; }		//�ړ��ʐݒ�
	D3DXVECTOR3 GetMove(void) { return D3DXVECTOR3(m_texMove.x, m_texMove.y, 0.0f); }		//�ړ��ʎ擾

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TEX_MAX];				//�e�N�X�`���o�b�t�@
	static int m_nIdx[TEX_MAX];				//�e�N�X�`���o�b�t�@
	D3DXVECTOR2 m_texMove;				//�ړ���
};

#endif