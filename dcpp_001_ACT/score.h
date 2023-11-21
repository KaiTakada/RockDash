//===============================================
//
// �X�R�A(score.cpp)
// Author ���c ����
//
//===============================================
#ifndef _SCORE_H_		//���̃}�N����`������ĂȂ�������
#define _SCORE_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "manager.h"
#include "object.h"

//=========================
// �}�N����`
//=========================
#define MAX_SCORE (6)	//�X�R�A����
#define DEF_NUMBER_SIZE D3DXVECTOR3(35.0f, 45.0f, 0.0f)	//�X�R�A����
#define DEF_NUMBER_ROT D3DXVECTOR3(0.0f, 0.0f, 0.0f)	//�X�R�A����

//=========================
// �O���錾
//=========================
class CNumber;

//=========================
// �I�u�W�F�N�g2D�w�i�N���X
//=========================
class CScore : public CObject
{
public:
	CScore();		//�R���X�g���N�^
	~CScore();		//�f�X�g���N�^

	HRESULT Init(void);							//������(�f�t�H)
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		//������(�I�o��)
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size, int nNum);		//������(�I�o��)
	void Uninit(void);							//�I��
	void Update(void);							//�X�V
	void Draw(void);							//�`��

	static CScore *Create(void);		//����
	static CScore *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot = DEF_NUMBER_ROT, const D3DXVECTOR3 size = DEF_NUMBER_SIZE, int nNum = MAX_SCORE);		//����

	void SetValue(int nValue);		//�X�R�A�l�ݒ�
	void CntValue(int nValue);		//�X�R�A�l���Z
	int GetValue() { return m_nValue; }		//�X�R�A�l�擾

	//���������֐��Ŏd���Ȃ��ɍ�����B��ŏ�������
	void SetPos(const D3DXVECTOR3 pos);			//�ʒu�ݒ�
	void SetRot(const D3DXVECTOR3 rot);			//�����ݒ�
	void SetNum(const int nNum) { m_nNum = nNum; }			//�i���o�[���ݒ�
	D3DXVECTOR3 GetPos(void);		//�ʒu�擾
	D3DXVECTOR3 GetSize(void);		//2D�T�C�Y�擾
	int GetNum(void) { return m_nNum; }		//�i���o�[���擾
	bool GetJump(void) { return false; }		//�W�����v����
	D3DXVECTOR3 GetPosOld(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		//�O��ʒu�擾

protected:

private:
	CNumber *m_apNumber[MAX_SCORE];		//�X�R�A���
	int m_nValue;		//�X�R�A�̒l
	int m_nNum;		//�i���o�[�̐�
};

#endif