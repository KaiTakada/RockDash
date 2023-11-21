//===============================================
//
// 2D�|���S��(object2D.cpp)
// Author ���c ����
//
//===============================================
#ifndef _OBJECT2D_H_		//���̃}�N����`������ĂȂ�������
#define _OBJECT2D_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "manager.h"
#include "object.h"

//=========================
// �}�N����`
//=========================
#define DEF_SIZE_STATIC D3DXVECTOR2(160.0f,90.0f)				//�f�t�H���g�T�C�Y

//=========================
// �O���錾
//=========================
class CAnim;

//=========================
// �I�u�W�F�N�g2D�N���X
//=========================
class CObject2D : public CObject
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

	CObject2D(int nPriority = CObject::PRIORITY_UI);		//�R���X�g���N�^
	~CObject2D();		//�f�X�g���N�^

	HRESULT Init(void);							//������(�f�t�H)
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		//������(�I�o��)
	void Uninit(void);							//�I��
	void Update(void);							//�X�V
	void Draw(void);							//�`��

	D3DXVECTOR3 GetPos(void) { return m_pos; }		//�ʒu�擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }		//�����擾
	D3DXVECTOR3 GetSize(void) { return m_size; }		//�T�C�Y�擾
	float GetLength(void) { return m_fLength; }		//�Ίp���̒����擾
	float GetAngle(void) { return m_fAngle; }		//�Ίp���̊p�x�擾
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }		//�o�b�t�@�擾
	D3DXVECTOR2 GetTexPosleftUp(void);			//�e�N�X�`�����W�擾(����)
	D3DXVECTOR2 GetTexPosrightDown(void);			//�e�N�X�`�����W�擾(�E��)
	D3DXVECTOR2 GetTexPosDif(void);			//�e�N�X�`�����W�擾(�E�� - ����)
	D3DXCOLOR CObject2D::GetTexCol(void);		//���_�J���[�擾

	void SetPos(const D3DXVECTOR3 pos);			//�ʒu�ݒ�
	void SetRot(const D3DXVECTOR3 rot);			//�����ݒ�
	void SetSize(const D3DXVECTOR3 size);			//�T�C�Y�ݒ�
	void SetTexPos(const D3DXVECTOR2 rightDown, const D3DXVECTOR2 leftUp);			//�e�N�X�`�����W�ݒ�()
	void SetTexCol(D3DXCOLOR col);			//���_�J���[�ݒ�
	void SetAbrend(const bool bAbrend) { m_bAbrend = bAbrend; }			//���u�����h�ݒ�
	static CObject2D *Create(void);		//����
	static CObject2D *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size, const UPDATE_TYPE UpdType);		//����
	void SetIdxTexture(int nIdx) { m_nIdxTexture = nIdx; }		//�e�N�X�`���ԍ��̊��蓖��

	//�t��������...
	bool GetAbrend(void) { return m_bAbrend; }		//���u�����h�擾
	bool GetJump(void) { return false; }		//�W�����v����
	D3DXVECTOR3 GetPosOld(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		//�O��ʒu�擾

protected:

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@

	D3DXVECTOR3 m_pos;		//���W
	D3DXVECTOR3 m_rot;		//����
	D3DXVECTOR3 m_size;		//�T�C�Y
	float m_fLength;		//�Ίp���̒���
	float m_fAngle;		//�Ίp���̊p�x
	int m_nIdxTexture;		//�e�N�X�`���̃C���f�b�N�X
	bool m_bAbrend;			//���u�����h�̐���
};

//=========================
// �I�u�W�F�N�g2D�A�j���[�V�����N���X
//=========================
class CObject2DAnim : public CObject2D
{
public:
	CObject2DAnim(int nPriority = 3);		//�R���X�g���N�^
	~CObject2DAnim();		//�f�X�g���N�^

	HRESULT Init(void);							//������(�f�t�H)
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		//������(�I�o��)
	void Uninit(void);							//�I��
	void Update(void);							//�X�V
	void Draw(void);							//�`��
	CAnim *GetAnim(void) { return m_anim; }		//�A�j�����擾

protected:

private:
	CAnim *m_anim;		//�A�j���[�V�����v�f
};

#endif