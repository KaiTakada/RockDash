//=================================================
//
// �r���{�[�h(ObjectBillboard.cpp)
// Author: Kai Takada
//
//=================================================
#ifndef _OBJECTBILLBOARD_H_								//���̃}�N����`������ĂȂ�������
#define _OBJECTBILLBOARD_H_								//��d�C���N���[�h�h�~�̃}�N�����`����

//===============================
// �C���N���[�h�t�@�C��
//===============================
#include "object.h"

//============================
// �}�N����`
//============================
#define DEF_BBSIZE D3DXVECTOR3(20.0f,0.0f,20.0f)				//�f�t�H���g�T�C�Y
#define DEF_VERTEX3D D3DXVECTOR3(0.0f,0.0f,0.0f)				//�f�t�H���g�T�C�Y

//===============================
// �O���錾
//===============================
class CAnim;

//===============================
// �r���{�[�h�N���X
//===============================
class CObjectBillboard : public CObject
{
public:
	CObjectBillboard(int nPriority = 3);
	~CObjectBillboard();
	
	HRESULT Init(void);							//������(�f�t�H)
	HRESULT Init(const D3DXVECTOR3 pos);		//������(�I�o��)
	void Uninit(void);							//�I��
	void Update(void);							//�X�V
	void Draw(void);							//�`��
	static CObjectBillboard *Create(void);		//����
	static CObjectBillboard *Create(const D3DXVECTOR3 pos = DEF_VERTEX3D, const D3DXVECTOR3 size = DEF_BBSIZE, bool bZtest = false);		//����
	void SetIdxTexture(int nIdx) { m_nIdxTexture = nIdx; }		//�e�N�X�`���ԍ��̊��蓖��

	void SetPos(const D3DXVECTOR3 pos);			//�ʒu�ݒ�
	void SetSize(const D3DXVECTOR3 size);			//�����ݒ�
	void SetMove(const D3DXVECTOR3 move) { m_move = move; }			//�ړ��ʐݒ�
	void SetTexPos(const D3DXVECTOR2 rightDown, const D3DXVECTOR2 leftUp);			//�e�N�X�`�����W�ݒ�()
	void SetColor(const D3DXCOLOR col);			//�e�N�X�`���F�ݒ�()
	void SetZtest(const bool bZtest) { m_bZtest = bZtest; }			//Z�e�X�g�ݒ�
	void SetAtest(const bool bAtest) { m_bAtest = bAtest; }			//���e�X�g�ݒ�
	void SetAbrend(const bool bAbrend) { m_bAbrend = bAbrend; }			//���u�����h�ݒ�
	void SetLight(const bool bLight) { m_bLight = bLight; }			//���C�e�B���O�ݒ�

	D3DXVECTOR3 GetPos(void) { return m_pos; }		//���݈ʒu�擾
	D3DXVECTOR3 GetSize(void) { return m_size; }		//2D�T�C�Y�擾
	D3DXVECTOR3 GetMove(void) { return m_move; }		//2D�T�C�Y�擾
	D3DXCOLOR GetColor();			//�e�N�X�`���F�ݒ�()
	bool GetZtest(void) { return m_bZtest; }		//Z�e�X�g�擾
	bool GetAtest(void) { return m_bAtest; }		//���e�X�g�擾
	bool GetAbrend(void) { return m_bAbrend; }		//���u�����h�擾
	bool GetLight(void) { return m_bLight; }		//���C�e�B���O�擾
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }		//�o�b�t�@�擾

protected:

private:
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_move;							//�ړ���
	D3DXVECTOR3 m_pos;							//�ʒu
	D3DXVECTOR3 m_size;							//�傫��
	int m_nIdxTexture;		//�e�N�X�`���̃C���f�b�N�X
	bool m_bZtest;			//Z�e�X�g�̐���
	bool m_bAtest;			//���e�X�g�̐���
	bool m_bAbrend;			//���u�����h�̐���
	bool m_bLight;			//���C�e�B���O�̐���
};

//=========================
// �I�u�W�F�N�g2D�A�j���[�V�����N���X
//=========================
class CObjectBillboardAnim : public CObjectBillboard
{
public:
	CObjectBillboardAnim(int nPriority = 3);		//�R���X�g���N�^
	~CObjectBillboardAnim();		//�f�X�g���N�^

	HRESULT Init(void);							//������(�f�t�H)
	HRESULT Init(const D3DXVECTOR3 pos);		//������(�I�o��)
	void Uninit(void);							//�I��
	void Update(void);							//�X�V
	void Draw(void);							//�`��
	static CObjectBillboardAnim *Create(const D3DXVECTOR3 pos = DEF_VERTEX3D, const D3DXVECTOR3 size = DEF_BBSIZE);		//����
	CAnim *GetAnim(void) { return m_anim; }		//�A�j�����擾

protected:

private:
	CAnim *m_anim;		//�A�j���[�V�����v�f
};

#endif