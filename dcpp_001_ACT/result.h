//===============================================
//
// ���U���g(result.h)
// Author: ���c ����
//
//===============================================
#ifndef _RESULT_H_		//���̃}�N����`������ĂȂ�������
#define _RESULT_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "main.h"
#include "manager.h"
#include "object.h"

//=========================
// �O���錾
//=========================
//class CRenderer;
class CTimer;

//=========================
// ���(�V�[��)�N���X
//=========================
class CResult : public CScene
{
public:
	CResult();
	~CResult();

	virtual HRESULT Init();		//������
	virtual void Uninit();		//�I��
	virtual void Update();		//�X�V
	virtual void Draw();		//�`��
	static CResult *Create();		//����

protected:

private:
	CTimer *m_pTimer;		//�X�R�A
};

#endif