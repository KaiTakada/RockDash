//==================================================
//
// �u�[�X�^�[(wp_boost.h)
// Author : Kai Takada
//
//==================================================
#ifndef _WP_BOOST_H_								//���̃}�N����`������ĂȂ�������
#define _WP_BOOST_H_								//��d�C���N���[�h�h�~�̃}�N�����`����

#include "weapon.h"

//============================================
// �}�N����`
//============================================

//============================================
// �O���錾
//============================================

//============================================
// �u���b�N�N���X
//============================================
class CBoost : public CWeapon
{
public:
	CBoost(int nPriority = 3);
	~CBoost();

	HRESULT Init(void);			//������
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		//������(�I�o��)
	void Uninit(void);			//�I��
	void Update(void);			//�X�V
	void Draw(void);			//�`��
	virtual void Attack(const D3DXVECTOR3 rot, const int nDamage = 1);			//�U��

	static CBoost *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//����

protected:

private:

};

#endif
