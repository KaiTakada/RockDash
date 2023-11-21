//============================
//
// 3D�|���S������(object3D.cpp)
// Author: Kai Takada
//
//============================
#include "object3D.h"
#include "texture.h"
#include "Anim.h"
#include "manager.h"
#include "debugproc.h"

//==================================
// �}�N����`
//==================================

//==================================
// �ÓI�����o�ϐ��錾
//==================================

//==================================
// �R���X�g���N�^
//==================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = nullptr;
	m_mtxWorld = {};
	m_pos = DEF_VERTEX3D;
	m_rot = DEF_VERTEX3D;
	m_size = DEF_SIZE;
}

//==================================
// �f���X�g���N�^
//==================================
CObject3D::~CObject3D()
{

}

//==================================
// 3D�|���S���̏���������
//==================================
HRESULT CObject3D::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	m_pos = DEF_VERTEX3D;	//����������
	m_rot = DEF_VERTEX3D;	//����������

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;		//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-DEF_SIZE.x, 0.0f, DEF_SIZE.z);		//(x,y,z)
	pVtx[1].pos = D3DXVECTOR3(DEF_SIZE.x, 0.0f, DEF_SIZE.z);
	pVtx[2].pos = D3DXVECTOR3(-DEF_SIZE.x, 0.0f, -DEF_SIZE.z);
	pVtx[3].pos = D3DXVECTOR3(DEF_SIZE.x, 0.0f, -DEF_SIZE.z);

	//�@���x�N�g���̐ݒ�
	D3DXVECTOR3 nor0 = vec(pVtx[0].pos, pVtx[1].pos, pVtx[2].pos);
	D3DXVECTOR3 nor3 = vec(pVtx[3].pos, pVtx[2].pos, pVtx[1].pos);

	pVtx[0].nor = D3DXVECTOR3(nor0);	//(x,y,z)
	pVtx[1].nor = D3DXVECTOR3((nor0 + nor3) * 0.5f);
	pVtx[2].nor = D3DXVECTOR3((nor0 + nor3) * 0.5f);
	pVtx[3].nor = D3DXVECTOR3(nor3);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				//(x,y)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	SetType(TYPE_3DPOLYGON);

	return S_OK;
}

//====================================
// 2D�|���S���̏�����(�ʒu�I�o��)
//====================================
HRESULT CObject3D::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	//�ʒu�ݒ�
	m_pos = pos;

	//�����ݒ�
	m_rot = rot;

	//�T�C�Y�ݒ�
	m_size = D3DXVECTOR3(DEF_SIZE.x, 0.0f, DEF_SIZE.z);

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{//���s�����ꍇ
		return E_FAIL;
	}

	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, 0.0f, m_size.z);		//(x,y,z)
	pVtx[1].pos = D3DXVECTOR3(m_size.x, 0.0f, m_size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, 0.0f, -m_size.z);
	pVtx[3].pos = D3DXVECTOR3(m_size.x, 0.0f, -m_size.z);

	//�@���x�N�g���̐ݒ�
	D3DXVECTOR3 nor0 = vec(pVtx[0].pos, pVtx[1].pos, pVtx[2].pos);
	D3DXVECTOR3 nor3 = vec(pVtx[3].pos, pVtx[2].pos, pVtx[1].pos);

	pVtx[0].nor = D3DXVECTOR3(nor0);	//(x,y,z)
	pVtx[1].nor = D3DXVECTOR3((nor0 + nor3) * 0.5f);
	pVtx[2].nor = D3DXVECTOR3((nor0 + nor3) * 0.5f);
	pVtx[3].nor = D3DXVECTOR3(nor3);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	SetType(TYPE_3DPOLYGON);

	return S_OK;
}

//==================================
//3D�|���S���̏I������
//==================================
void CObject3D::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;					//�o�b�t�@�̔j��
	}

	//���S�t���O�����Ă��Ⴄ
	SetDeath(true);
	Release();
}

//==================================
//3D�|���S���̍X�V����
//==================================
void CObject3D::Update(void)
{

}

//==================================
//3D�|���S���̕`�揈��
//==================================
void CObject3D::Draw(void)
{
	//�e�N�X�`���擾
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;						//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
		0,												//�`�悷��ŏ��̃C���f�b�N�X
		2);												//�`�悷��v���~�e�B�u��
}

//============================
// 2D�|���S���̐�������
//============================
CObject3D * CObject3D::Create(void)
{
	CObject3D *pObject3D;

	//�I�u�W�F�N�g����
	pObject3D = new CObject3D;

	//������
	pObject3D->Init();

	return pObject3D;
}

//============================
// 3D�|���S���̐�������
//============================
CObject3D * CObject3D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
{
	CObject3D *pObject3D = nullptr;

	//�I�u�W�F�N�g����&������
	pObject3D = new CObject3D;

	if (pObject3D != nullptr)
	{
		pObject3D->Init(pos, rot);

		pObject3D->SetSize(size);

		pObject3D->SetIdxTexture(0);
	}
	else
	{
		return nullptr;
	}

	return pObject3D;
}

//====================================
// �ʒu�̐ݒ�
//====================================
void CObject3D::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//====================================
// �ʒu�̐ݒ�
//====================================
void CObject3D::SetRot(const D3DXVECTOR3 rot)
{
	m_rot = rot;

	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�@���x�N�g���̐ݒ�
	D3DXVECTOR3 nor0 = vec(pVtx[0].pos, pVtx[1].pos, pVtx[2].pos);
	D3DXVECTOR3 nor3 = vec(pVtx[3].pos, pVtx[2].pos, pVtx[1].pos);

	pVtx[0].nor = D3DXVECTOR3(nor0);	//(x,y,z)
	pVtx[1].nor = D3DXVECTOR3((nor0 + nor3) * 0.5f);
	pVtx[2].nor = D3DXVECTOR3((nor0 + nor3) * 0.5f);
	pVtx[3].nor = D3DXVECTOR3(nor3);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//====================================
// �ʒu�̐ݒ�
//====================================
void CObject3D::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;

	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-size.x, 0.0f, size.z);		//(x,y,z)
	pVtx[1].pos = D3DXVECTOR3(size.x, 0.0f, size.z);
	pVtx[2].pos = D3DXVECTOR3(-size.x, 0.0f, -size.z);
	pVtx[3].pos = D3DXVECTOR3(size.x, 0.0f, -size.z);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//====================================
// �e�N�X�`���̕�����
//====================================
void CObject3D::SetDivTex(int nDivU, int nDivV)
{
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(float(nDivU), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, float(nDivV));
	pVtx[3].tex = D3DXVECTOR2(float(nDivU), float(nDivV));

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================
// �e�N�X�`�����W�ݒ�
//============================
void CObject3D::SetTexPos(const D3DXVECTOR2 rightDown, const D3DXVECTOR2 leftUp)
{
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(leftUp.x, leftUp.y);
	pVtx[1].tex = D3DXVECTOR2(rightDown.x, leftUp.y);
	pVtx[2].tex = D3DXVECTOR2(leftUp.x, rightDown.y);
	pVtx[3].tex = D3DXVECTOR2(rightDown.x, rightDown.y);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//====================================
// ����Ă���I�u�W�F�N�g�̈ʒuy�擾
//====================================
float CObject3D::GetHeight(D3DXVECTOR3 posObj)
{
	D3DXVECTOR3 vecToPos0, vecToPos1, vecToPos2, vecToPos3;			//pos0��pos1�̍����i�ʒu�֌W�j
	D3DXVECTOR3 vecLine0, vecLine1, vecLine2, vecLine3;		//�ǂ̒���
	D3DXVECTOR3 vecLineMid, vecToPosMid;	//�^�񒆂̒����E����


	D3DXVECTOR3 Vtxpos0, Vtxpos1, Vtxpos2, Vtxpos3;

	GetPolyPos(&Vtxpos0, &Vtxpos1, &Vtxpos2, &Vtxpos3);

	vecLine0 = Vtxpos1 - Vtxpos0;
	vecToPos0 = posObj - Vtxpos0;

	vecLine1 = Vtxpos0 - Vtxpos2;
	vecToPos1 = posObj - Vtxpos2;

	vecLine2 = Vtxpos2 - Vtxpos3;
	vecToPos2 = posObj - Vtxpos3;

	vecLine3 = Vtxpos3 - Vtxpos1;
	vecToPos3 = posObj - Vtxpos1;

	//�^��
	vecLineMid = Vtxpos1 - Vtxpos2;
	vecToPosMid = posObj - Vtxpos2;

	//�v���C���[���|���S���̓����ɂ���
	if ((vecLine0.z * vecToPos0.x) - (vecLine0.x * vecToPos0.z) >= 0.0f &&
		(vecLine1.z * vecToPos1.x) - (vecLine1.x * vecToPos1.z) >= 0.0f &&
		(vecLine2.z * vecToPos2.x) - (vecLine2.x * vecToPos2.z) >= 0.0f &&
		(vecLine3.z * vecToPos3.x) - (vecLine3.x * vecToPos3.z) >= 0.0f)
	{
		D3DXVECTOR3 nor;
		float fHeight;		//���߂鍂��

		//�ΏۃI�u�W�F�N�g�ւ̃x�N�g��
		D3DXVECTOR3 vec0;
		D3DXVECTOR3 vec1;
		D3DXVECTOR3 VtxposOrg;
		D3DXVECTOR3 vecP;

		if ((vecLineMid.z * vecToPosMid.x) - (vecLineMid.x * vecToPosMid.z) <= 0.0f)
		{
			VtxposOrg = Vtxpos0;
			vecP = posObj - Vtxpos0;
			vec0 = Vtxpos1 - Vtxpos0;
			vec1 = Vtxpos2 - Vtxpos0;
		}
		else
		{
			VtxposOrg = Vtxpos3;
			vecP = posObj - Vtxpos3;
			vec0 = Vtxpos2 - Vtxpos3;
			vec1 = Vtxpos1 - Vtxpos3;
		}

		//2�̃x�N�g������@�������߂�
		D3DXVec3Cross(&nor, &vec0, &vec1);

		//�@���𐳋K��
		D3DXVec3Normalize(&nor, &nor);

		if (nor.y != 0.0f)
		{//�N�����Ȃ������ꍇ

			fHeight = (-((vecP.x * nor.x) + (vecP.z * nor.z)) + (VtxposOrg.y * nor.y)) / nor.y;

			return fHeight;
		}
	}

	return posObj.y;
}

//============================
// ���_�ʒu�擾
//============================
void CObject3D::GetPolyPos(D3DXVECTOR3 *Vtx0, D3DXVECTOR3 *Vtx1, D3DXVECTOR3 *Vtx2, D3DXVECTOR3 *Vtx3)
{
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	*Vtx0 = pVtx[0].pos;		//(x,y,z)
	*Vtx1 = pVtx[1].pos;
	*Vtx2 = pVtx[2].pos;
	*Vtx3 = pVtx[3].pos;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================
// �@���x�N�g���擾
//============================
D3DXVECTOR3 CObject3D::vec(D3DXVECTOR3 vtxpos0, D3DXVECTOR3 vtxpos1, D3DXVECTOR3 vtxpos2)
{
	D3DXVECTOR3 vec1;		//�e�̃x�N�g��
	D3DXVECTOR3 vec2;		//�e�̃x�N�g��
	D3DXVECTOR3 nor;		//�e�̃x�N�g��

	vec1 = vtxpos0 - vtxpos1;
	vec2 = vtxpos0 - vtxpos2;

	nor.x = (vec1.y * vec2.z - vec1.z * vec2.y);
	nor.y = (vec1.z * vec2.x - vec1.x * vec2.z);
	nor.z = (vec1.x * vec2.y - vec1.y * vec2.x);

	//�x�N�g���𐳋K������(1.0f�ɂ���)
	D3DXVec3Normalize(&nor, &nor);

	//�O��
	D3DXVec3Cross(&nor, &vec1, &vec2);
	
	//����
	D3DXVec3Dot(&vec1, &vec2);

	return nor;
}

//==========================================
//============= �A�j���[�V���� =============
//============================
// �R���X�g���N�^
//============================
CObject3DAnim::CObject3DAnim(int nPriority) : CObject3D(nPriority)
{
	m_anim = nullptr;
}

//============================
// �f�X�g���N�^
//============================
CObject3DAnim::~CObject3DAnim()
{

}

//====================================
// 2D�|���S���̏���������(�f�t�H)
//====================================
HRESULT CObject3DAnim::Init(void)
{
	//������
	CObject3D::Init();

	m_anim = new CAnim;

	if (m_anim != nullptr)
	{
		m_anim->Init();

		m_anim->SetNumLoop(0);
		m_anim->SetNumPtnX(1);
		m_anim->SetNumPtnY(1);
	}

	CObject3D::SetTexPos(D3DXVECTOR2(0.2f, 0.5f), D3DXVECTOR2(0.0f, 0.0f));

	return S_OK;
}

//====================================
// 2D�|���S���̏�����(�ʒu�I�o��)
//====================================
HRESULT CObject3DAnim::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CObject3D::Init();

	CObject3D::SetPos(pos);
	CObject3D::SetRot(rot);
	CObject3D::SetSize(D3DXVECTOR3(DEF_SIZE_ANIM.x, DEF_SIZE_ANIM.y, 0.0f));

	m_anim = new CAnim;

	if (m_anim != nullptr)
	{
		m_anim->Init();

		m_anim->SetNumLoop(0);
		m_anim->SetNumPtnX(1);
		m_anim->SetNumPtnY(1);
	}

	CObject3D::SetTexPos(D3DXVECTOR2(1.0f / m_anim->GetNumPtnX(), 1.0f / m_anim->GetNumPtnY()), D3DXVECTOR2(0.0f, 0.0f));

	return S_OK;
}

//============================
// 2D�|���S���̏I������
//============================
void CObject3DAnim::Uninit(void)
{
	if (m_anim != nullptr)
	{
		m_anim->Uninit();
		delete m_anim;
	}

	//�I��
	CObject3D::Uninit();
}

//============================
// 2D�|���S���̍X�V����
//============================
void CObject3DAnim::Update(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = CObject3D::GetVtxBuff();
	VERTEX_2D*pVtx;

	m_anim->Update();
	D3DXVECTOR2 *pTexpos = m_anim->GetTexpos();

	//�e�N�X�`���̍X�V
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	for (int nCntTex = 0; nCntTex < MAX_VTX; nCntTex++)
	{
		pVtx[nCntTex].tex = pTexpos[nCntTex];		//(x,y)
	}

	//���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//============================
// 2D�|���S���̕`�揈��
//============================
void CObject3DAnim::Draw(void)
{
	//�`��
	CObject3D::Draw();
}
