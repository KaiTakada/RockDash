//===============================================
//
// �X�|�[��(spawn.h)
// Author ���c ����
//
//===============================================
#ifndef _SPAWN_H_		//���̃}�N����`������ĂȂ�������
#define _SPAWN_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "manager.h"
#include "object.h"
#include "enemy.h"

//=========================
// �}�N����`
//=========================

//=========================
// �O���錾
//=========================

//=========================
// �X�|�[���N���X
//=========================
class CSpawn : public CObject
{
public:
	struct Generate		//�����v�f
	{
		int nFrequency;		//�����p�x
		int nNumMin;			//�������ŏ�
		int nNumMax;			//�������ő�
	};

	CSpawn();		//�R���X�g���N�^
	~CSpawn();		//�f�X�g���N�^

	HRESULT Init(void);							//������(�f�t�H)
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	void Uninit(void);							//�I��
	void Update(void);							//�X�V
	void Draw(void);							//�`��
	static CSpawn *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);		//����

	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }				//�ʒu�ݒ�
	void SetSize(const D3DXVECTOR3 size) { m_size = size; }			//�T�C�Y�ݒ�
	void SetRad(const float fRad) { m_fRad = fRad; }				//���a�ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }			//�ʒu�擾
	D3DXVECTOR3 GetSize(void) { return m_size; }		//�T�C�Y�擾
	float GetRad(void) { return m_fRad; }				//���a�擾
	void GenerateEnemy();									//�����֐�
	void FileRead();									//�t�@�C���Ǎ�

protected:

private:
	D3DXVECTOR3 m_pos;		//���ݍ��W
	D3DXVECTOR3 m_size;		//�X�|�[���͈�
	float m_fRad;			//�X�|�[�����a
	float m_fLegScr;		//��ʏ�̑Ίp���̒���
	int m_nCtr;				//�J�E���^�[
	int m_nEneGrowCtr;		//�G�����J�E���^�[

	bool m_bDebSpawn;		//�������
	Generate m_aGenerate[CEnemy::ET_MAX];				//�������
};

#endif