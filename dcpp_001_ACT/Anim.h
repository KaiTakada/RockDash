//===============================================
//
// 2D�|���S��(object2D.cpp)
// Author ���c ����
//
//===============================================
#ifndef _ANIM_H_		//���̃}�N����`������ĂȂ�������
#define _ANIM_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "manager.h"

//=========================
// �}�N����`
//=========================
#define MAX_VTX (4)		//���_��
#define DEF_SIZE_ANIM D3DXVECTOR2(125.0f,200.0f)				//�f�t�H���g�T�C�Y

//=========================
// �I�u�W�F�N�g2D�N���X
//=========================
class CAnim
{
public:
	CAnim();		//�R���X�g���N�^
	~CAnim();		//�f�X�g���N�^

	HRESULT Init(void);							//������(�f�t�H)
	void Uninit(void);							//�I��
	void Update(void);							//�X�V

	void SetNumPtnX(const int nNumPtn) { m_nNumPtnAnimX = nNumPtn; }			//�p�^�[�����ݒ�x
	void SetNumPtnY(const int nNumPtn) { m_nNumPtnAnimY = nNumPtn; }			//�p�^�[�����ݒ�y
	void SetNumLoop(const int nNumLoop) { m_nLoop = nNumLoop; }			//�p�^�[�����ݒ�
	void SetNumFrame(const int nFrame) { m_nFrame = nFrame; }			//�t���[�����ݒ�
	void SetTexpos(const D3DXVECTOR2 *pTexpos);					//�e�N�X�`�����W�ݒ�
	int GetNumPtnX(void) { return m_nNumPtnAnimX; }			//�p�^�[�����擾x
	int GetNumPtnY(void) { return m_nNumPtnAnimY; }			//�p�^�[�����擾y
	int GetNumLoop(void) { return m_nLoop; }			//�p�^�[�����擾
	int GetNumFrame(void) { return m_nFrame; }			//�t���[�����擾
	D3DXVECTOR2 *GetTexpos(void) { return &m_aTexpos[0]; }		//�e�N�X�`�����W�擾

protected:

private:
	int m_nCtrAnim;							//�A�j���[�V�����J�E���^�[
	int m_nPtnAnimX;						//�A�j���[�V�����p�^�[��x No.
	int m_nPtnAnimY;						//�A�j���[�V�����p�^�[��y No.
	int m_nNumPtnAnimX;						//�A�j���[�V�����p�^�[����x
	int m_nNumPtnAnimY;						//�A�j���[�V�����p�^�[����y
	int m_nFrame;		//�X�V�p�x�t���[��
	int m_nLoop;		//���[�v��(-1�Ŗ���)

	D3DXVECTOR2 m_aTexpos[MAX_VTX];
};

#endif