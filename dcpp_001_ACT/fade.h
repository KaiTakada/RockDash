//===============================================
//
// �Q�[��(game.h)
// Author: ���c ����
//
//===============================================
#ifndef _FADE_H_		//���̃}�N����`������ĂȂ�������
#define _FADE_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "manager.h"
#include "object2D.h"

//=========================
// �O���錾
//=========================
//class CRenderer;
//class CObject2D;

//=========================
// ���(�V�[��)�N���X
//=========================
class CFade : public CObject2D
{
public:

	//�t�F�[�h�̏��
	typedef enum
	{
		STATE_NONE = 0,		//�������ĂȂ����
		STATE_IN,			//�t�F�[�h�C�����
		STATE_OUT,			//�t�F�[�h�A�E�g���
		STATE_MAX
	}STATE;

	CFade(int nPriority = PRIORITY_FADE);
	~CFade();

	HRESULT Init(CScene::MODE modeNext);		//������
	virtual void Uninit();		//�I��
	virtual void Update();		//�X�V
	virtual void Draw();		//�`��
	static CFade *Create(CScene::MODE modeNext);		//����

	bool SetState(CScene::MODE modeNext);
	STATE GetState(void) { return m_state; }	//�t�F�[�h��Ԏ擾

protected:

private:
	STATE m_state;												//�t�F�[�h�̏��
	CScene::MODE m_modeNext;									//���̉��(���[�h)
	D3DXCOLOR m_colorFade;										//�|���S��(�t�F�[�h)�̐F
	bool m_bExc;												//���s���t���O
};

#endif
