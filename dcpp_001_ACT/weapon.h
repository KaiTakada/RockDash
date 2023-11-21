//==================================================
//
// ���폈��(weapon.h)
// Author : Kai Takada
//
//==================================================
#ifndef _WEAPON_H_								//���̃}�N����`������ĂȂ�������
#define _WEAPON_H_								//��d�C���N���[�h�h�~�̃}�N�����`����

#include "Parts.h"

//�}�N����`
#define MAX_WEAPON (256)						//�u���b�N�̍ő吔
#define BLOCK_WIDTH (80.0f)						//�u���b�N�̕�
#define BLOCK_HEIGHT (80.0f)					//�u���b�N�̍���

//============================================
// �O���錾
//============================================

//============================================
// �u���b�N�N���X
//============================================
class CWeapon : public CParts
{
public:
	//===================================
	// �u���b�N�񋓌^�̒�`
	//===================================
	typedef enum
	{
		WPNTYPE_NIFE = 0,		//�i�C�t
		WPNTYPE_REVOLVER,		//���{���o�[
		WPNTYPE_AK,				//���C�t��
		WPNTYPE_BOOST,			//�u�[�X�g
		WPNTYPE_MAX,
	}WPNTYPE;

	CWeapon(int nPriority = 3);
	~CWeapon();

	HRESULT Init(void);			//������
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const WPNTYPE type);		//������(�I�o��)
	void Uninit(void);			//�I��
	void Update(void);			//�X�V
	void Draw(void);			//�`��
	virtual void Attack(const D3DXVECTOR3 rot, const int nDamage = 1);			//�U��

	static CWeapon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f), WPNTYPE type = WPNTYPE_NIFE);		//����

	void SetWpnType(CWeapon::WPNTYPE type);
	CWeapon::WPNTYPE GetWpnType() { return m_type; }
	void GetCooltime(int nCooltime) { m_nCooltime = nCooltime; }
	int SetCooltime() { return m_nCooltime; }
	void SetCooltimeMin(int nCooltime) { m_nCooltimeMin = nCooltime; }
	int GetCooltimeMin() { return m_nCooltimeMin; }

protected:

private:
	void ReadMuzzleFile(WPNTYPE type = WPNTYPE_NIFE);
	void ReadCooltime(WPNTYPE type = WPNTYPE_NIFE);

	CWeapon::WPNTYPE m_type;				//���
	D3DXVECTOR3 m_muzzlePos;				//�e���ʒu
	int m_nCooltime;						//�N�[���^�C��
	int m_nCooltimeMin;						//�N�[���^�C���}�C�i�X��
};

#endif
