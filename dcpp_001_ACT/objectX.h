//===============================================
//
// X���f���I�u�W�F�N�g(objectX.cpp)
// Author: ���c ����
//
//===============================================
#ifndef _OBJECTX_H_								//���̃}�N����`������ĂȂ�������
#define _OBJECTX_H_								//��d�C���N���[�h�h�~�̃}�N�����`����

//================================
// �C���N���[�h�t�@�C��
//================================
#include "object.h"
#include "Xmodel.h"

//================================
// �}�N����`
//================================
#define DEF_VERTEX3D D3DXVECTOR3(0.0f,0.0f,0.0f)				//�f�t�H���g�T�C�Y

//================================
// �O���錾
//================================

//================================
// ���f���N���X
//================================
class CObjectX : public CObject
{
public:

	CObjectX(int nPriority = 1);
	~CObjectX();

	HRESULT Init(void);
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		//������(�I�o��)
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Draw(const D3DMATERIAL9 mat);

	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }			//�ʒu�ݒ�
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }			//�����ݒ�
	void SetSize(const D3DXVECTOR3 size);						//�T�C�Y�ݒ�
	void SetVtx(const D3DXVECTOR3 vtxMin, const D3DXVECTOR3 vtxMax) { m_vtxMin = vtxMin; m_vtxMax = vtxMax; }			//�����ݒ�
	void SetCol(const D3DXCOLOR col) { m_col = col; }		//�F�ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }		//���݈ʒu�擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }		//�����擾
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }		//�O��ʒu�擾
	D3DXVECTOR3 GetSize(void) { return m_size; }		//2D�T�C�Y�擾
	D3DXVECTOR3 GetMinVtx(void) { return m_vtxMin; }			//�ŏ����W�擾
	D3DXVECTOR3 GetMaxVtx(void) { return m_vtxMax; }			//�ő���W�擾
	D3DXCOLOR GetCol(void) { return m_col; }			//�F�擾
	int GetIdxModel(void) { return m_nIdxModel; }				//���f���ԍ��擾
	static CObjectX *Create(void);		//����
	static CObjectX *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot = DEF_VERTEX3D, float fSize = 1.0f);		//����
	void SetIdxModel(int nIdx) { m_nIdxModel = nIdx; }		//���f���ԍ��̊��蓖��

protected:

private:
	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_posOld;				//�ʒu
	D3DXVECTOR3 m_rot;					//�ړ���
	D3DXVECTOR3 m_size;					//�T�C�Y
	D3DXVECTOR3 m_vtxMin;				//��`�̍ŏ����W
	D3DXVECTOR3 m_vtxMax;				//��`�̍ő���W
	D3DXCOLOR m_col;					//�F
	int m_nIdxModel;					//���f���ԍ�
};

#endif
