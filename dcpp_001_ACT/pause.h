//===============================================
//
// �|�[�Y(pause.h)
// Author: ���c ����
//
//===============================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "object.h"

//=========================
// �}�N����`
//=========================

//=========================
// �O���錾
//=========================
class CObject2D;

//=========================
// �v���C���[�N���X
//=========================
class CPause : public CObject
{
public:

	//�|�[�Y���j���[�̗񋓌^
	enum PAUSE_MENU
	{
		PAUSE_MENU_CONTINUE = 0,	//�Q�[���ɖ߂�
		PAUSE_MENU_RETRY,			//�Q�[������蒼��
		PAUSE_MENU_QUIT,			//�^�C�g����ʂɖ߂�
		PAUSE_MENU_MAX
	};

	CPause(int nPriority = PRIORITY_PAUSE);		//�R���X�g���N�^
	~CPause();		//�f�X�g���N�^

	HRESULT Init(void);							//������(�f�t�H)
	HRESULT Init(const D3DXVECTOR3 pos);		//������(�I�o��)
	void Uninit(void);							//�I��
	void Update(void);							//�X�V
	void Draw(void);							//�`��
	static CPause *Create(const D3DXVECTOR3 pos);		//����

protected:

private:
	CObject2D *m_pItem[PAUSE_MENU_MAX];			//�I������()
	CObject2D *m_pBg;			//�w�i()
	PAUSE_MENU m_pauseMenu;		//�|�[�Y���j���[
	int m_nPauseSelect;			//���݂̑I����
	bool m_bEnter;				//����t���O
};

#endif