//===============================================
//
// �����L���O(ranking.h)
// Author: ���c ����
//
//===============================================
#ifndef _RANKING_H_		//���̃}�N����`������ĂȂ�������
#define _RANKING_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "main.h"
#include "manager.h"

//=========================
// �}�N����`
//=========================
#define RK_NUM_SCORE (5)	//�\������X�R�A��
#define RANK_READ_FILE "data\\SET\\RANKING\\rank.txt"

//=========================
// �O���錾
//=========================
class CTimer;

//=========================
// ���(�V�[��)�N���X
//=========================
class CRanking : public CScene
{
public:
	CRanking();
	~CRanking();

	virtual HRESULT Init();		//������
	virtual void Uninit();		//�I��
	virtual void Update();		//�X�V
	virtual void Draw();		//�`��
	static CRanking *Create();		//����
	void SetScore(int nScore) { m_nScore = nScore; }		//����
	int GetScore() { return m_nScore; }		//����

protected:

private:
	void Sort();			//�����L���O�\�[�g
	void Read(char *pReadFile = RANK_READ_FILE);			//�t�@�C���Ǎ�
	void Write(char *pReadFile = RANK_READ_FILE);			//�t�@�C������

	CTimer *m_apTimer[RK_NUM_SCORE];
	int m_nScore;		//����̃X�R�A
	int m_nCntTitle;	//�^�C�g���J��
};

#endif