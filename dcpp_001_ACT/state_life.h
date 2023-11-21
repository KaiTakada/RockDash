//===============================================
//
// ������ԊǗ�(state_life.cpp)
// Author: ���c ����
//
//===============================================
#ifndef _STATE_LIFE_H_								//���̃}�N����`������ĂȂ�������
#define _STATE_LIFE_H_								//��d�C���N���[�h�h�~�̃}�N�����`����

//================================
// �C���N���[�h�t�@�C��
//================================

//================================
// �}�N����`
//================================

//================================
// ���f���N���X
//================================
class CState_Life
{
public:
	enum STATE
	{
		STATE_NORMAL = 0,
		STATE_DAMAGE,
		STATE_GOD,
		STATE_DEATH,
		STATE_MAX,
	};

	CState_Life();
	~CState_Life();

	HRESULT Init();
	void Uninit();
	void Update();
	static CState_Life *Create();

	void Set(const STATE state, const int nCT) { m_state = state; m_nCtrState = nCT; }		//�ݒ�
	STATE Get(void) { return m_state; }		//���݈ʒu�擾
	int GetCnt(void) { return m_nCtrState; }		//�c��J�E���g�擾
	D3DXMATERIAL GetMat(void) { return m_MatDmg; }		//�c��J�E���g�擾

protected:

private:
	STATE m_state;						//���
	int m_nCtrState;					//��ԃJ�E���^�[
	D3DXMATERIAL m_MatDmg;					//�_���[�W�F
	CState_Life *m_pAdress;				//�󂯎M
};

#endif
