//===============================================
//
// ���[�V����(motion.h)
// Author ���c ����
//
//===============================================
#ifndef _MOTION_H_		//���̃}�N����`������ĂȂ�������
#define _MOTION_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
//#include "objectX.h"

//=========================
// �}�N����`
//=========================
#define MAX_PLAYER_PARTS (32)		//�ő�p�[�c��
#define NUM_MOTION (8)				//���[�V������
#define NUM_KEY (8)					//�L�[��

//=========================
// �O���錾
//=========================
class CParts;

//=========================
// �v���C���[�N���X
//=========================
class CMotion
{
public:
	//====================
	// �L�[�̍\����
	//====================
	typedef struct
	{
		float fPosX;		//�ʒuX
		float fPosY;		//�ʒuY
		float fPosZ;		//�ʒuZ
		float fRotX;		//�ʒuX
		float fRotY;		//�ʒuY
		float fRotZ;		//�ʒuZ
	}KEY;

	//====================
	// �L�[���̍\����
	//====================
	typedef struct
	{
		int nFrame;			//�Đ��t���[��
		KEY aKey[MAX_PLAYER_PARTS];		//�e���f���̃L�[�v�f
	}KEY_INFO;

	//====================
	// ���[�V�������̍\����
	//====================
	typedef struct
	{
		bool bLoop;				//���[�v���邩�ǂ���
		int nNumKey;			//�L�[�̑���
		KEY_INFO aKeyInfo[NUM_KEY];	//�L�[���
	}INFO;

	CMotion();		//�R���X�g���N�^
	~CMotion();		//�f�X�g���N�^

	HRESULT Init(void);						//������(�f�t�H)
	void Uninit(void);						//�I��
	void Set(int nType);					//���[�V�����̋N��
	void Update(void);						//�I��

	int GetType(void);						//���݂̃��[�V�����̎�ގ擾
	bool IsFinish(void);					//�I������擾
	void SetInfo(INFO *info, int nNum);				//���[�V�������ݒ�

	void SetModel(CParts **ppParts, int nNumModel);		//���f�����ݒ�
	//void SetOrg(CParts **ppParts, int nNumModel);		//�I�t�Z�b�g���ݒ�

	char **ReadParts(const char *pReadFile, int *pnNumFile);
	void ReadSetUp(const char *pReadFile, CParts **ppParts);
	void ReadMotions(const char *pReadFile, CMotion::INFO *pInfo);

	int GetKey(void) { return m_nKey; }		//���݂̃L�[�擾
	INFO *GetInfo(void) { return m_aInfo; }		//���݂̃L�[�擾

	int GetTotalCtr() { return m_nTotalCtr; }		//�g�[�^���J�E���g�擾

protected:

private:
	void ReadFile(char *pFilePass);	//�t�@�C���Ǎ�

	KEY m_aKeyOrg[MAX_PLAYER_PARTS];		//�e���f���̃v���Z�b�g���
	INFO m_aInfo[NUM_MOTION];	//���[�V�������
	int m_nNumAll;		//���[�V�����̑���
	int m_nType;		//���[�V�����̎��
	int m_nCounter;		//���[�V�����J�E���^�[
	int m_nNumKey;		//�L�[�̑���
	int m_nKey;			//���݂̃L�[No.
	bool m_bLoop;		//���[�v���邩�ǂ���
	bool m_bFinish;		//�I���������ǂ���
	int m_nTotalCtr;	//1�̃g�[�^���J�E���^�[

	CParts **m_ppParts;	//���f���ւ̃|�C���^
	int m_nNumModel;	//���f���̑���
};

#endif
