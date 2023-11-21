//===============================================
//
// X���f���I�u�W�F�N�g(Xmodel.cpp)
// Author: ���c ����
//
//===============================================
#ifndef _XMODEL_H_								//���̃}�N����`������ĂȂ�������
#define _XMODEL_H_								//��d�C���N���[�h�h�~�̃}�N�����`����

//================================
// �C���N���[�h�t�@�C��
//================================
#include "object.h"

//================================
// �}�N����`
//================================
#define DEF_VERTEX3D D3DXVECTOR3(0.0f,0.0f,0.0f)				//�f�t�H���g�T�C�Y
#define MAX_XMODEL (128)				//���f���̎󂯎M�e��
#define XMODEL_SIZE_META (0.1f)				//���f���̏o�͔{��

//================================
// ���f���N���X
//================================
class CXModel
{
public:
	typedef struct
	{
		D3DXMATRIX mtxWorld;				//���[���h�}�g���b�N�X
		LPD3DXMESH pMesh;					//���b�V��(���_���)�ւ̃|�C���^
		LPD3DXBUFFER pBuffMat;				//�}�e���A���ւ̃|�C���^
		LPDIRECT3DTEXTURE9 *pTexture;		//�e�N�X�`���ւ̃|�C���^
		DWORD dwNumMat;						//�}�e���A���̐�
		D3DXVECTOR3 vtxMin;					//��`�̍ŏ����W
		D3DXVECTOR3 vtxMax;					//��`�̍ő���W
	}Model;

	CXModel();
	~CXModel();

	HRESULT Load(void);		//�e�N�X�`���ǂݍ���
	void Unload(void);		//�e�N�X�`���j��
	int Regist(const char *pFilename, D3DXVECTOR3 *vtxMin = nullptr, D3DXVECTOR3 *vtxMax = nullptr);		//���f���ǉ��Ǎ�
	Model *GetAddress(int nIdx); /*{ return m_apModel[nIdx]; }*/		//���f�����擾
	D3DXVECTOR3 GetVtxMin(int nIdx) { return m_aModel[nIdx].vtxMin; }		//���f�����擾
	D3DXVECTOR3 GetVtxMax(int nIdx) { return m_aModel[nIdx].vtxMax; }		//���f�����擾

protected:

private:
	Model m_aModel[MAX_XMODEL];		//���f�����i�[
	char *m_apFilename[MAX_XMODEL];		//�t�@�C��������
	static int m_nNumAll;		//�����f����
};

#endif
