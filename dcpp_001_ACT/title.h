//===============================================
//
// �^�C�g��(title.h)
// Author: ���c ����
//
//===============================================
#ifndef _TITLE_H_		//���̃}�N����`������ĂȂ�������
#define _TITLE_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "main.h"
#include "manager.h"

//=========================
// �O���錾
//=========================
class CObject2D;
class CPress_Enter;

//=========================
// ���(�V�[��)�N���X
//=========================
class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();

	virtual HRESULT Init();		//������
	virtual void Uninit();		//�I��
	virtual void Update();		//�X�V
	virtual void Draw();		//�`��
	static CTitle *Create();		//����

protected:

private:
	CField *m_pField;							//�n��

	CPress_Enter *m_pEnter;	//press enter
	int m_nAlphaCnter;						//PRESS ENTER�̓_�ŊԊu�̔���
	int m_nTimeInterval;						//PRESS ENTER�̓_�ŊԊu
	float m_fAlphaColor;					//���_�J���[
	int m_nCntRanking;						//�����L���O�J��
};

#endif