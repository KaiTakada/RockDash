//===============================================
//
// enter����(press_enter.cpp)
// Author ���c ����
//
//===============================================
#ifndef _PRESS_ENTER_H_		//���̃}�N����`������ĂȂ�������
#define _PRESS_ENTER_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "manager.h"
#include "object2D.h"

//=========================
// �}�N����`
//=========================
#define DEF_SIZE_ENTER D3DXVECTOR3(90.0f * 1.5f, 90.0f, 0.0f)				//�f�t�H���g�T�C�Y

//=========================
// �O���錾
//=========================

//=========================
// �I�u�W�F�N�g2D�N���X
//=========================
class CPress_Enter : public CObject2D
{
public:

	//=========================
	// �^�C�v�񋓌^
	//=========================
	enum UPDATE_TYPE
	{
		UPDATE_TYPE_NONE = 0,
		UPDATE_TYPE_ANIM,
		UPDATE_TYPE_MAX
	};

	CPress_Enter(int nPriority = CObject2D::PRIORITY_UI);		//�R���X�g���N�^
	~CPress_Enter();		//�f�X�g���N�^

	HRESULT Init(void);							//������(�f�t�H)
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		//������(�I�o��)
	void Uninit(void);							//�I��
	void Update(void);							//�X�V
	void Draw(void);							//�`��

	static CPress_Enter *Create(void);		//����
	static CPress_Enter *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size = DEF_SIZE_ENTER, const D3DXVECTOR3 rot = DEF_VEC3);		//����

	void SetInterval(int nCtr) { m_nTimeInterval = nCtr; }
	int SetInterval() { return m_nTimeInterval; }

protected:

private:
	int m_nAlphaCnter;						//PRESS ENTER�̓_�ŊԊu�̔���
	int m_nTimeInterval;					//PRESS ENTER�̓_�ŊԊu
	float m_fAlphaColor;					//���_�J���[a
};

#endif