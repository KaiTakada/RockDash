//===============================================
//
// �|���S���`��(main.h)
// Author ���c ����
//
//===============================================
#ifndef _MAIN_H_								//���̃}�N����`������ĂȂ�������
#define _MAIN_H_								//��d�C���N���[�h�h�~�̃}�N�����`����

#include "d3dx9.h"								//�`�揈���ɕK�v
#include "xaudio2.h"							//�T�E���h�����ɕK�v

//=========================
// ���C�u�����̃����N
//=========================
#pragma comment(lib,"d3d9.lib")					//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")				//�`�揈���̊g�����C�u����
#pragma comment(lib,"dxguid.lib")				//DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")				//�V�X�e�������擾�ɕK�v

//=========================
// �}�N����`
//=========================
#define SCREEN_WIDTH (1280)						//�E�B���h�E�̕�
#define SCREEN_HEIGHT (720)						//�E�B���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define WINDOW_NAME "RockDash"					//�E�B���h�E�̖��O(�L���v�V�����ɕ\��)
#define TIMER_FPS (60)							//����FPS

//=================================
// �}�N����`
//=================================
#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )		//�|�C���^�̉���Y�ꌟ�m
#else
#define DBG_NEW new
#endif

//====================================
// ���_���[2D]�̍\���̂��`
//====================================
typedef struct
{
	D3DXVECTOR3 pos;							//���W
	float rhw;									//���W�ϊ��p�W��
	D3DCOLOR col;								//�F
	D3DXVECTOR2 tex;							//�e�N�X�`�����W
}VERTEX_2D;

//====================================
// ���_���[3D]�̍\���̂��`
//====================================
typedef struct
{
	D3DXVECTOR3 pos;							//���W
	D3DXVECTOR3 nor;							//�@���x�N�g��
	D3DCOLOR col;								//�F
	D3DXVECTOR2 tex;							//�e�N�X�`�����W
}VERTEX_3D;

//=========================
// �O���錾
//=========================

//=========================
// �v���g�^�C�v�錾
//=========================
int GetFPS(void);		//FPS�擾

#endif