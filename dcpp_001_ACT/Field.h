//=================================================
//
// 3D�n��(Field.cpp)
// Author: Kai Takada
//
//=================================================
#ifndef _FIELD_H_								//���̃}�N����`������ĂȂ�������
#define _FIELD_H_								//��d�C���N���[�h�h�~�̃}�N�����`����

//============================
// �C���N���[�h�t�@�C��
//============================
#include "manager.h"
#include "object3D.h"

//============================
// �}�N����`
//============================
#define DEF_FIELD_SIZE D3DXVECTOR3(16384.0f,0.0f,512.0f)				//�f�t�H���g�T�C�Y
#define DEF_VERTEX3D D3DXVECTOR3(0.0f,0.0f,0.0f)				//�f�t�H���g����

//============================
// 3D�|���S���N���X
//============================
class CField : public CObject3D
{
public:
	CField(int nPriority = 1);
	~CField();

	HRESULT Init(void);
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		//������(�I�o��)
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CField *Create(void);		//����
	static CField *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot = DEF_VERTEX3D, const D3DXVECTOR3 size = DEF_FIELD_SIZE);		//����

private:

};
#endif
