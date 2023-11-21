//==============================================
//
//�J�����̏���(camera.h)
// Author: Kai Takada
//
//==============================================
#ifndef _CAMERA_H_								//���̃}�N����`������ĂȂ�������
#define _CAMERA_H_								//��d�C���N���[�h�h�~�̃}�N�����`����

//===============================
// �C���N���[�h�t�@�C��
//================================

//===============================
// �J�����N���X
//================================
class CCamera
{
public:
	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	void CameraStalk(void);		//��荞��
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void PlayerStalk(void);
	void EditStalk(void);

protected:

private:

	D3DXMATRIX m_mtxProjection;		//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;			//�r���[�}�g���b�N�X
	D3DXVECTOR3 m_posV;				//���_
	D3DXVECTOR3 m_posR;				//�����_
	D3DXVECTOR3 m_posVDest;			//�\�莋�_
	D3DXVECTOR3 m_posRDest;			//�\�蒍���_
	float m_posRAdjt;				//�����_���炵
	D3DXVECTOR3 m_move;				//�ړ���
	D3DXVECTOR3 m_vecU;				//������x�N�g��
	D3DXVECTOR3 m_rot;				//����
	D3DXVECTOR3 m_rotDest;			//�\�����
	float m_fAngle;					//�p�x
	float m_fDis;					//����
};

#endif
