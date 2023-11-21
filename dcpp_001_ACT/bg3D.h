//=================================================
//
// 3D�w�i(Bg3D.cpp)
// Author: Kai Takada
//
//=================================================
#ifndef _BG3D_H_								//���̃}�N����`������ĂȂ�������
#define _BG3D_H_								//��d�C���N���[�h�h�~�̃}�N�����`����

//============================
// �C���N���[�h�t�@�C��
//============================
#include "manager.h"
#include "object3D.h"

//============================
// �}�N����`
//============================
#define DEF_BG3D_SIZE D3DXVECTOR3(16384.0f,0.0f,2048.0f)				//�f�t�H���g�T�C�Y
#define DEF_VERTEX3D D3DXVECTOR3(0.0f,0.0f,0.0f)				//�f�t�H���g����

//============================
// 3D�|���S���N���X
//============================
class CBg3D : public CObject3D
{
public:
	CBg3D(int nPriority = 1);
	~CBg3D();

	HRESULT Init(void);
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		//������(�I�o��)
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBg3D *Create(void);		//����
	static CBg3D *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot = DEF_VERTEX3D, const D3DXVECTOR3 size = DEF_BG3D_SIZE);		//����

private:

};
#endif
