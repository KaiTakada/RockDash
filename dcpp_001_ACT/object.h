//===============================================
//
// �|���S��(object.cpp)
// Author ���c ����
//
//===============================================
#ifndef _OBJECT_H_								//���̃}�N����`������ĂȂ�������
#define _OBJECT_H_								//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "manager.h"

//=========================
// �}�N����`
//=========================
#define MAX_OBJECT (1024)		//�ő吔
#define DEF_VEC3 (D3DXVECTOR3(0.0f, 0.0f, 0.0f))		//3���̏����l

//=========================
// �I�u�W�F�N�g�N���X
//=========================
class CObject
{
public:

	//========================
	// �I�u�W�F�N�g�^�C�v
	//========================
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_BULLET,
		TYPE_EXPLOSION,
		TYPE_BG,
		TYPE_MULTIBG,
		TYPE_EFFECT,
		TYPE_PARTICLE,
		TYPE_NUMBER,
		TYPE_SCORE,
		TYPE_BLOCK,
		TYPE_ITEM,
		TYPE_3DPOLYGON,
		TYPE_BILLBOARD,
		TYPE_MODEL,
		TYPE_FIELD,
		TYPE_WEAPON,
		TYPE_GAUGE,
		TYPE_PARTS,
		TYPE_EXP,
		TYPE_FADE,
		TYPE_TIMER,
		TYPE_EVO,
		TYPE_ITEM2D,
		TYPE_SPAWN,
		TYPE_BOSS,
		TYPE_ENTER,
		TYPE_MAX
	}TYPE;

	//========================
	// �D�揇��
	//========================
	typedef enum
	{
		PRIORITY_BG = 0,
		PRIORITY_MAP,
		PRIORITY_OBJ,
		PRIORITY_MOB,
		PRIORITY_MAIN,
		PRIORITY_UI,
		PRIORITY_PAUSE,
		PRIORITY_FADE,
		PRIORITY_MAX,
	}PRIORITY;

	//CObject();				//�R���X�g���N�^(�f�t�H)
	CObject(int nPriority = 3);				//�R���X�g���N�^(�`�揇�I�o��)
	virtual ~CObject();		//�f�X�g���N�^

	virtual HRESULT Init(void) = 0;							//������(�f�t�H)
	virtual HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot) { pos; rot; return E_FAIL; }		//������(�I�o��)
	virtual void Uninit(void) = 0;							//�I��
	virtual void Update(void) = 0;							//�X�V
	virtual void Draw(void) = 0;							//�`��
	
	virtual void SetPos(const D3DXVECTOR3 pos) { pos; }			//�ʒu�ݒ�
	virtual void SetRot(const D3DXVECTOR3 rot) { rot; }			//�����ݒ�
	virtual void SetJump(const bool bJump) { bJump; }		//�W�����v����ݒ�
	virtual void SetBoost(const bool bBoost) { bBoost; }		//�u�[�X�g����ݒ�
	virtual void SetMove(const D3DXVECTOR3 move) { move; }		//�ړ��ʐݒ�
	virtual D3DXVECTOR3 GetPos(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }			//���݈ʒu�擾
	virtual D3DXVECTOR3 GetRot(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }			//�����擾
	virtual D3DXVECTOR3 GetPosOld(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		//�O��ʒu�擾
	virtual D3DXVECTOR3 GetSize(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }			//2D�T�C�Y�擾
	virtual bool GetJump(void) { return FALSE; }		//�W�����v����擾
	virtual bool GetBoost(void) { return FALSE; }		//�u�[�X�g����擾
	virtual D3DXVECTOR3 GetMove(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }			//�ړ��ʎ擾
	virtual void GetPolyPos(D3DXVECTOR3 Vtx0, D3DXVECTOR3 Vtx1, D3DXVECTOR3 Vtx2, D3DXVECTOR3 Vtx3) { Vtx0, Vtx1, Vtx2, Vtx3; }		//�ړ��ʎ擾
	virtual D3DXVECTOR3 GetMinVtx(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }			//�ŏ����W�擾
	virtual D3DXVECTOR3 GetMaxVtx(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }			//�ő���W�擾

	static void ReleaseAll(void);		//�S�Ă̔j��
	static void UpdateAll(void);		//�S�Ă̍X�V
	static void DrawAll(void);			//�S�Ă̕`��
	static int GetNumAll(void) { return m_nNumAll; }		//�����擾

	void SetType(CObject::TYPE type) { m_type = type; }		//�^�C�v�擾
	CObject::TYPE GetType() { return m_type; }		//�^�C�v�擾
	virtual int GetLocalType() { assert(false); return 0; }			//���ꂼ��̃N���X�ō�����^�C�v���擾(�g�p���͌p���錾�����Ă�������)

	void SetDeath(bool bDeath) { m_bDeath = bDeath; }		//���S�t���O�擾
	bool GetDeath(void) { return m_bDeath; }				//���S�t���O�擾

	static CObject *GetTop(int nPrty) { return m_apTop[nPrty]; }		//�I�u�W�F�N�g
	static CObject *GetEnd(int nPrty) { return m_apEnd[nPrty]; }		//�D�揇�ł̃I�u�W�F�N�g
	void SetNext(CObject *pNext) { m_pNext = pNext; }		//�O�A�h���X�ݒ�
	CObject *GetNext(void) { return m_pNext; }				//�O�A�h���X�擾
	void SetPrev(CObject *pPrev) { m_pPrev = pPrev; }		//��A�h���X�ݒ�
	CObject *GetPrev(void) { return m_pPrev; }				//��A�h���X�擾

protected:
	void Release(void);		//���g�̔j��

private:
	static int m_nNumAll;		//�I�u�W�F�N�g����
	static CObject *m_apTop[PRIORITY_MAX];		//�擪�I�u�W�F�N�g
	static CObject *m_apEnd[PRIORITY_MAX];		//�Ō���I�u�W�F�N�g
	CObject *m_pNext;				//���I�u�W�F�N�g
	CObject *m_pPrev;				//�O�I�u�W�F�N�g
	CObject::TYPE m_type;		//�^�C�v
	int m_nPriority;	//�`�揇
	bool m_bDeath;		//���S�t���O
};

#endif