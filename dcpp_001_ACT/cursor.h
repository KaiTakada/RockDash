//===============================================
//
// �w�i(bg.cpp)
// Author ���c ����
//
//===============================================
#ifndef _CURSOR_H_		//���̃}�N����`������ĂȂ�������
#define _CURSOR_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "manager.h"
#include "object2D.h"

//=========================
// �}�N����`
//=========================
#define DEF_SIZE_CURSOR D3DXVECTOR3(40.0f, 40.0f, 0.0f)		//�f�t�H���g�T�C�Y

//=========================
// �I�u�W�F�N�g2D�w�i�N���X
//=========================
class CCursor : public CObject2D
{
public:
	enum TEX
	{
		TEX_AIM = 0,
		TEX_001,
		TEX_002,
		TEX_MAX,
	};

	CCursor();		//�R���X�g���N�^
	~CCursor();		//�f�X�g���N�^

	HRESULT Init(void);							//������(�f�t�H)
	HRESULT Init(const D3DXVECTOR3 pos);		//������(�I�o��)
	void Uninit(void);							//�I��
	void Update(void);							//�X�V
	void Draw(void);							//�`��

	static CCursor *Create(void);		//����
	static CCursor *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size = DEF_SIZE_CURSOR, const TEX TexType = TEX_AIM);		//����
	void SetMove(const D3DXVECTOR3 move) { m_move = move; }		//�ړ��ʐݒ�
	D3DXVECTOR3 GetMove() { return m_move; }		//�ړ��ʎ擾
	D3DXVECTOR3 GetVec() { return m_vec; }		//�ړ��ʎ擾
	D3DXVECTOR3 GetRot();		//�����擾

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TEX_MAX];				//�e�N�X�`���o�b�t�@
	static int m_nIdx[TEX_MAX];				//�e�N�X�`���o�b�t�@
	D3DXVECTOR3 m_move;				//�ړ���
	D3DXVECTOR3 m_Defpos;				//�����ʒu
	D3DXVECTOR3 m_vec;				//�����ʒu - ���݈ʒu�̃x�N�g��
	bool m_bMouse;		//�J�[�\���̃}�E�X����t���O
};

#endif