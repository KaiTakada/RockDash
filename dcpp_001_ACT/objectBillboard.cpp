//=================================================
//
// �r���{�[�h(billboard.cpp)
// Author: Kai Takada
//
//=================================================
#include "manager.h"
#include "objectBillboard.h"
#include "debugproc.h"
#include "input.h"
#include "texture.h"
#include "Anim.h"

//==============================
// �}�N����`
//==============================
#define BILLBOARD_SIZE (100.0f)
#define TEX_PASS "data\\TEXTURE\\chara.png"

//==============================
// �ÓI�����o�ϐ��錾
//==============================

//==============================
// �R���X�g���N�^
//==============================
CObjectBillboard::CObjectBillboard(int nPriority) : CObject(nPriority)
{
	m_mtxWorld = {};								//���[���h�}�g���b�N�X
	m_pTexture = nullptr;							//�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = nullptr;							//���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�傫��
	m_nIdxTexture = -1;
	m_bZtest = false;
	m_bAtest = false;
	m_bAbrend = false;
	m_bLight = false;
}

//==============================
// �f�X�g���N�^
//==============================
CObjectBillboard::~CObjectBillboard()
{

}

//==============================
// �r���{�[�h�̏���������
//==============================
HRESULT CObjectBillboard::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu
	m_size = D3DXVECTOR3(BILLBOARD_SIZE, BILLBOARD_SIZE, BILLBOARD_SIZE);			//�傫��
	m_bZtest = false;
	m_bAtest = true;
	m_bAbrend = false;
	m_bLight = false;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;		//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, 0.0f);		//(x,y,z)
	pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_size.x, -m_size.y, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);	//(x,y,z)
	pVtx[1].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				//(x,y)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	SetType(TYPE_BILLBOARD);

	return S_OK;
}

//==============================
// �r���{�[�h�̏���������
//==============================
HRESULT CObjectBillboard::Init(const D3DXVECTOR3 pos)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	m_pos = pos;			//�ʒu
	m_size = D3DXVECTOR3(BILLBOARD_SIZE, BILLBOARD_SIZE, BILLBOARD_SIZE);			//�傫��
	m_bZtest = false;
	m_bAtest = true;
	m_bAbrend = false;
	m_bLight = false;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}


	VERTEX_3D *pVtx;		//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, 0.0f);		//(x,y,z)
	pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_size.x, -m_size.y, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//(x,y,z)
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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

	SetType(TYPE_BILLBOARD);

	return S_OK;
}

//==============================
// �r���{�[�h�̏I������
//==============================
void CObjectBillboard::Uninit(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;					//�e�N�X�`���j��
	}

	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;					//�o�b�t�@�̔j��
	}

	//���S�t���O�����Ă��Ⴄ
	SetDeath(true);
	Release();
}

//==============================
// �r���{�[�h�̍X�V����
//==============================
void CObjectBillboard::Update(void)
{

}

//==============================
// �r���{�[�h�̕`�揈��
//==============================
void CObjectBillboard::Draw(void)
{
	//�e�N�X�`���擾
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetInstance()->GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;						//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;									//�r���[�}�g���b�N�X�擾�p

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);

	//m_mtxWorld._21 = 0.0f;		//Y����]�̑ł�����
	//m_mtxWorld._22 = 1.0f;		//rot��xyz?
	//m_mtxWorld._23 = 0.0f;

	m_mtxWorld._41 = 0.0f;		//�S�������t��
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//Z�e�X�g�𖳌��ɂ���
	if (m_bZtest == true)
	{
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	}

	//�A���t�@�e�X�g��L���ɂ���
	if (m_bAtest == true)
	{
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	}

	//a�u�����f�B���O�����Z�����ɐݒ�
	if (m_bAbrend == true)
	{
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	//���C�e�B���O��TRUE�ɐݒ�
	if (m_bLight == true)
	{
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	}

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));
	//pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
		0,												//�`�悷��ŏ��̃C���f�b�N�X
		2);												//�`�悷��v���~�e�B�u��

	//���C�e�B���O��TRUE�ɐݒ�
	if (m_bLight == true)
	{
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}

	//Z�e�X�g��L���ɂ���
	if (m_bZtest == true)
	{
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}

	//�A���t�@�e�X�g�𖳌��ɂ���
	if (m_bAtest == true)
	{
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 255);
	}

	//a�u�����f�B���O�����ɖ߂�
	if (m_bAbrend == true)
	{
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//============================
// 2D�|���S���̐�������
//============================
CObjectBillboard * CObjectBillboard::Create(void)
{
	CObjectBillboard *pObject3D;

	//�I�u�W�F�N�g����
	pObject3D = new CObjectBillboard;

	//������
	pObject3D->Init();

	return pObject3D;
}

//============================
// 3D�|���S���̐�������
//============================
CObjectBillboard * CObjectBillboard::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, bool bZtest)
{
	CObjectBillboard *pBillBoard = nullptr;

	//�I�u�W�F�N�g����&������
	pBillBoard = new CObjectBillboard;

	if (pBillBoard != nullptr)
	{
		pBillBoard->Init(pos);

		pBillBoard->m_bZtest = bZtest;

		pBillBoard->SetSize(size);

		pBillBoard->SetIdxTexture(0);
	}
	else
	{
		return nullptr;
	}

	return pBillBoard;
}

//============================
// �ʒu�ݒ�
//============================
void CObjectBillboard::SetPos(const D3DXVECTOR3 pos)
{ 
	m_pos = pos; 
}

//============================
// �傫���ݒ�
//============================
void CObjectBillboard::SetSize(const D3DXVECTOR3 size)
{
	m_size = size; 

	VERTEX_3D *pVtx;		//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, 0.0f);		//(x,y,z)
	pVtx[1].pos = D3DXVECTOR3(size.x, size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(size.x, -size.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================
// �e�N�X�`�����W�ݒ�
//============================
void CObjectBillboard::SetTexPos(const D3DXVECTOR2 rightDown, const D3DXVECTOR2 leftUp)
{
	VERTEX_3D *pVtx;

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

//============================
// �F�ݒ�
//============================
void CObjectBillboard::SetColor(const D3DXCOLOR col)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_��񂩂�F�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================
// �F�擾
//============================
D3DXCOLOR CObjectBillboard::GetColor()
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_��񂩂�F�̎擾
	D3DXCOLOR col = pVtx[0].col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return col;
}

//==========================================
//============= �A�j���[�V���� =============
//============================
// �R���X�g���N�^
//============================
CObjectBillboardAnim::CObjectBillboardAnim(int nPriority) : CObjectBillboard(nPriority)
{
	m_anim = nullptr;
}

//============================
// �f�X�g���N�^
//============================
CObjectBillboardAnim::~CObjectBillboardAnim()
{

}

//====================================
// ����������(�f�t�H)
//====================================
HRESULT CObjectBillboardAnim::Init(void)
{
	//������
	CObjectBillboard::Init();

	m_anim = new CAnim;

	if (m_anim != nullptr)
	{
		m_anim->Init();
	}

	CObjectBillboard::SetTexPos(D3DXVECTOR2(1.0f / m_anim->GetNumPtnX(), 1.0f / m_anim->GetNumPtnY()), D3DXVECTOR2(0.0f, 0.0f));

	return S_OK;
}

//====================================
// ������(�ʒu�I�o��)
//====================================
HRESULT CObjectBillboardAnim::Init(const D3DXVECTOR3 pos)
{
	if(FAILED(CObjectBillboard::Init(pos)))
	{
		return E_FAIL;
	}

	m_anim = new CAnim;

	if (m_anim != nullptr)
	{
		m_anim->Init();
	}

	CObjectBillboard::SetTexPos(D3DXVECTOR2(1.0f / m_anim->GetNumPtnX(), 1.0f / m_anim->GetNumPtnY()), D3DXVECTOR2(0.0f, 0.0f));

	return S_OK;
}

//============================
// �I������
//============================
void CObjectBillboardAnim::Uninit(void)
{
	if (m_anim != nullptr)
	{
		m_anim->Uninit();
		delete m_anim;
		m_anim = nullptr;
	}

	//�I��
	CObjectBillboard::Uninit();
}

//============================
// �X�V����
//============================
void CObjectBillboardAnim::Update(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = CObjectBillboard::GetVtxBuff();
	VERTEX_3D *pVtx;

	CObjectBillboard::Update();

	//�A�j���[�V�����X�V
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
// �`�揈��
//============================
void CObjectBillboardAnim::Draw(void)
{
	//�`��
	CObjectBillboard::Draw();
}

//============================
// �A�j��BB�̐�������
//============================
CObjectBillboardAnim * CObjectBillboardAnim::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CObjectBillboardAnim *pBillBoardAnim = nullptr;

	//�I�u�W�F�N�g����&������
	pBillBoardAnim = new CObjectBillboardAnim;

	if (pBillBoardAnim != nullptr)
	{
		pBillBoardAnim->Init(pos);

		pBillBoardAnim->SetSize(size);

		pBillBoardAnim->SetIdxTexture(0);
	}
	else
	{
		return nullptr;
	}

	return pBillBoardAnim;
}
