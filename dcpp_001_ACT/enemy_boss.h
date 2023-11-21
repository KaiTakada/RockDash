//===============================================
//
// �{�X�G(enemy_boss.h)
// Author ���c ����
//
//===============================================
#ifndef _ENEMY_BOSS_H_		//���̃}�N����`������ĂȂ�������
#define _ENEMY_BOSS_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "enemy.h"

//=========================
// �}�N����`
//=========================

//=========================
// �O���錾
//=========================

//=========================
// �v���C���[�N���X
//=========================
class CEnemy_Boss : public CEnemy
{
public:

	//=========================
	// �G�̎��
	//=========================
	enum ATACKSTATE
	{
		AS_NONE = 0,
		AS_STALK,
		AS_BURST,
		AS_TACKLE,
		AS_MAX
	};

	CEnemy_Boss(int nPriority = 2);		//�R���X�g���N�^
	~CEnemy_Boss();		//�f�X�g���N�^

	HRESULT Init(void);							//������(�f�t�H)
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		//������(�I�o��)
	void Uninit(void);							//�I��
	void Update(void);							//�X�V
	void Draw(void);							//�`��
	static CEnemy_Boss *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		//����
	void SetAttack(CEnemy_Boss::ATACKSTATE state);		//�s���ݒ�
	void Attack();		//�U�����e�ē�
	bool Burst();		//�U�����e
	bool Tackle();		//�U�����e

protected:

private:
	CEnemy_Boss::ATACKSTATE m_AttackState;		//�s����
	int m_nCoolTime;		//�s���p�^�[������CT�ݒ�
	bool m_bClear;			//�s�������t���O
	int m_nMoveCnt;			//�s���J�E���^�[
};

#endif
