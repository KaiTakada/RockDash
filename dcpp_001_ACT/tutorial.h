//===============================================
//
// �`���[�g���A��(tutorial.h)
// Author: ���c ����
//
//===============================================
#ifndef _TUTORIAL_H_		//���̃}�N����`������ĂȂ�������
#define _TUTORIAL_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "main.h"
#include "manager.h"

//=========================
// �O���錾
//=========================
//class CRenderer;

//=========================
// ���(�V�[��)�N���X
//=========================
class CTutorial : public CScene
{
public:
	CTutorial();
	~CTutorial();

	virtual HRESULT Init();		//������
	virtual void Uninit();		//�I��
	virtual void Update();		//�X�V
	virtual void Draw();		//�`��
	static CTutorial *Create();		//����

protected:

private:

};

#endif