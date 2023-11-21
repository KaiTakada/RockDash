//===============================================
//
// X���f���I�u�W�F�N�g�p�[�c(Parts.cpp)	//�e���f���������f��
// Author: ���c ����
//
//===============================================
#ifndef _PARTS_H_								//���̃}�N����`������ĂȂ�������
#define _PARTS_H_								//��d�C���N���[�h�h�~�̃}�N�����`����

//================================
// �C���N���[�h�t�@�C��
//================================
#include "manager.h"
#include "object.h"

//================================
// �}�N����`
//================================
#define DEF_VERTEX3D D3DXVECTOR3(0.0f,0.0f,0.0f)				//�f�t�H���g�T�C�Y
#define MAX_XMODEL (128)				//���f���̎󂯎M�e��

//================================
// ���f���N���X
//================================
class CParts : public CObject
{
public:
	//=============================
	// �p�[�c���\���̂̒�`
	//=============================
	typedef struct
	{
		char *pFilepass;		//�t�@�C���p�X
		int nIdxParent;			//�e�̃C���f�b�N�X
	}PassParent;

	CParts(int nPriority = 3);
	~CParts();

	HRESULT Init(void);							//������(�f�t�H)
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);			//������(�I�o��)
	void Uninit(void);							//�I��
	void Update(void);							//�X�V
	void Draw(void);							//�`��

	static CParts *Create(const char *pFilename, const D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//����
	void SetParent(CParts *pParts);
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }						//���݈ʒu�ݒ�
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }						//���݌����ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }				//���݈ʒu�擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }				//���݌����擾
	D3DXMATRIX GetMtxWorld(void);		//���[���h�}�g���b�N�X�擾

	void SetIdxModel(int nIdx) { m_nIdxModel = nIdx; }		//���f���ԍ��̊��蓖��
	int GetIdxModel() { return m_nIdxModel; }		//���f���ԍ��̎擾
	D3DXVECTOR3 GetOutcomePos(CParts *pParts);		//���v���W
	CParts *GetParent() { return m_pParent; }			//�e���f���|�C���^�擾
	void SetMat(D3DXMATERIAL mat) { m_mat = mat; }		//�F�ݒ�

protected:

private:
	D3DXVECTOR3 m_pos;			//���݈ʒu
	D3DXVECTOR3 m_rot;			//���݌���
	CParts *m_pParent;			//�e���f���ւ̃|�C���^
	int m_nIdxModel;			//���f���ԍ�
	D3DXMATERIAL m_mat;			//�w��F
};

#endif
