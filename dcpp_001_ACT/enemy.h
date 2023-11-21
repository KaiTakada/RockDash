//===============================================
//
// �G(enemy.h)
// Author ���c ����
//
//===============================================
#ifndef _ENEMY_H_		//���̃}�N����`������ĂȂ�������
#define _ENEMY_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "objectX.h"

//=========================
// �}�N����`
//=========================

//=========================
// �O���錾
//=========================
class CState_Life;

//=========================
// �v���C���[�N���X
//=========================
class CEnemy : public CObjectX
{
public:

	//=========================
	// �G�̎��
	//=========================
	enum TYPE
	{
		ET_NONE = 0,
		ET_SPEED,
		ET_HP,
		ET_BOSS,
		ET_MAX
	};

	//====================
	// �L�����̃p�����[�^
	//====================
	struct Param
	{
		float fLife;		//�̗�
		float fLifeMax;		//�ő�̗�
		float fSpeed;		//�ړ����x
		float fAttack;		//�U����
	};

	CEnemy(int nPriority = 2);		//�R���X�g���N�^
	~CEnemy();		//�f�X�g���N�^

	HRESULT Init(void);							//������(�f�t�H)
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		//������(�I�o��)
	void Uninit(void);							//�I��
	void Update(void);							//�X�V
	void Draw(void);							//�`��
	static CEnemy *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, TYPE type = ET_NONE);		//����
	bool CollisionRect(void);
	void Damage(int nDamege = 1);
	void StalkPlayer();
	void SetMove(const D3DXVECTOR3 move) { m_move = move; }		//�ړ��ʐݒ�
	bool CollisionCircle(D3DXVECTOR3 pos);
	void InitialState(CEnemy::TYPE type);
	void InitialMove();
	void MoveSpeed();
	void MoveBoss();

	void SetTypeE(CEnemy::TYPE type) { m_type = type; }
	CEnemy::TYPE GetTypeE() { return m_type; }

	void SetParam(Param param) { m_param = param; }
	Param GetParam() { return m_param; }

	void SetMoveFrag(bool bMove) { m_bMove = bMove; }
	bool GetMoveFrag() { return m_bMove; }
	void MoveCtrl() { m_bMove = !m_bMove; }

protected:

private:
	D3DXVECTOR3 m_move;		//�ړ���
	CEnemy::TYPE m_type;	//�G��
	Param m_param;			//�p�����[�^
	bool m_bMove;			//���������܂��Ă���z��true�A�����ǂ�������z��false
	CState_Life *m_pStateLife;		//���
};

#endif
