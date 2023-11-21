//===============================================
//
// 2D�|���S��(object2D.cpp)
// Author ���c ����
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "object2D.h"
#include "texture.h"
#include "Anim.h"

//============================
// �}�N����`
//============================

//============================
// �O���錾
//============================
//class CPlayer;

//============================
// �ÓI�����o�ϐ��錾
//============================

//============================
// �R���X�g���N�^(�f�t�H)
//============================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = nullptr;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_nIdxTexture = 0;
	m_bAbrend = false;
}

//============================
// �f�X�g���N�^
//============================
CObject2D::~CObject2D()
{

}

//====================================
// 2D�|���S���̏���������(�f�t�H)
//====================================
HRESULT CObject2D::Init(void)
{
	//�T�C�Y�ݒ�
	m_size = D3DXVECTOR3(DEF_SIZE_STATIC.x, DEF_SIZE_STATIC.y, 0.0f);

	//�Ίp���̒������Z�o����
	m_fLength = sqrtf((m_size.x * m_size.x * 4) + (m_size.y * m_size.y * 4)) * 0.5f;

	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(m_size.x * 2, m_size.y * 2);

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{//���s�����ꍇ
		return E_FAIL;
	}

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;	//(x)
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;	//(y)
	pVtx[0].pos.z = 0.0f;	//(z)

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//====================================
// 2D�|���S���̏�����(�ʒu�I�o��)
//====================================
HRESULT CObject2D::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	//�ʒu�ݒ�
	m_pos = pos;

	//�����ݒ�
	m_rot = rot;

	//�T�C�Y�ݒ�
	m_size = D3DXVECTOR3(DEF_SIZE_STATIC.x, DEF_SIZE_STATIC.y, 0.0f);

	//�Ίp���̒������Z�o����
	m_fLength = sqrtf((m_size.x * m_size.x * 4) + (m_size.y * m_size.y * 4)) * 0.5f;

	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(m_size.x * 2, m_size.y * 2);

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{//���s�����ꍇ
		return E_FAIL;
	}

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;	//(x)
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;	//(y)
	pVtx[0].pos.z = 0.0f;	//(z)

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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

	return S_OK;
}

//============================
// 2D�|���S���̏I������
//============================
void CObject2D::Uninit(void)
{
	//���_�o�b�t�@�j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//���S�t���O�����Ă��Ⴄ
	SetDeath(true);
	//���g�̔j��
	Release();
}

//============================
// 2D�|���S���̍X�V����
//============================
void CObject2D::Update(void)
{

}

//============================
// 2D�|���S���̕`�揈��
//============================
void CObject2D::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�e�N�X�`���擾
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//a�u�����f�B���O�����Z�����ɐݒ�
	if (m_bAbrend == true)
	{
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//2D�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//�v���~�e�B�u�̎��
		0,															//�擪�v���~�e�B�u�ԍ�
		2);															//�`�悷��v���~�e�B�u��

	//a�u�����f�B���O�����ɖ߂�
	if (m_bAbrend == true)
	{
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//============================
// 2D�|���S���̈ʒu�ݒ菈��
//============================
void CObject2D::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;	//(x)
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;	//(y)
	pVtx[0].pos.z = 0.0f;	//(z)

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================
// 2D�|���S���̌����ݒ菈��
//============================
void CObject2D::SetRot(const D3DXVECTOR3 rot)
{
	m_rot = rot;

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;	//(x)
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;	//(y)
	pVtx[0].pos.z = 0.0f;	//(z)
					
	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;
					
	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;
					
	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================
// 2D�|���S���̃T�C�Y�ݒ菈��
//============================
void CObject2D::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;

	//�Ίp���̒������Z�o����
	m_fLength = sqrtf((size.x * size.x * 4) + (size.y * size.y * 4)) * 0.5f;

	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(size.x * 2, size.y * 2);

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;	//(x)
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;	//(y)
	pVtx[0].pos.z = 0.0f;	//(z)

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================
// �e�N�X�`�����W�ݒ�
//============================
void CObject2D::SetTexPos(const D3DXVECTOR2 rightDown, const D3DXVECTOR2 leftUp)
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

//============================
// 2D�|���S���̐�������
//============================
CObject2D * CObject2D::Create(void)
{
	CObject2D *pObject2D;

	//�I�u�W�F�N�g����
	pObject2D = new CObject2D;

	//������
	pObject2D->Init();

	return pObject2D;
}

//============================
// 2D�|���S���̐�������
//============================
CObject2D * CObject2D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size, const UPDATE_TYPE UpdType)
{
	CObject2D *pObject2D = nullptr;

	//�I�u�W�F�N�g����&������
	switch (UpdType)
	{
	case UPDATE_TYPE_ANIM:
	
		pObject2D = new CObject2DAnim;

		break;

	default:
		
		pObject2D = new CObject2D;

		break;
	}

	if (pObject2D != nullptr)
	{
		pObject2D->Init(pos, rot);
		
		pObject2D->SetSize(size);

		pObject2D->SetIdxTexture(0);
	}
	else
	{
		return nullptr;
	}

	return pObject2D;
}

//==========================================
//============= �A�j���[�V���� =============
//============================
// �R���X�g���N�^
//============================
CObject2DAnim::CObject2DAnim(int nPriority) : CObject2D(nPriority)
{
	m_anim = nullptr;
}

//============================
// �f�X�g���N�^
//============================
CObject2DAnim::~CObject2DAnim()
{

}

//====================================
// 2D�|���S���̏���������(�f�t�H)
//====================================
HRESULT CObject2DAnim::Init(void)
{
	//������
	CObject2D::Init();
	
	m_anim = new CAnim;

	if (m_anim != nullptr)
	{
		m_anim->Init();
	
		m_anim->SetNumLoop(0);
		m_anim->SetNumPtnX(1);
		m_anim->SetNumPtnY(1);
	}

	CObject2D::SetTexPos(D3DXVECTOR2(0.2f, 0.5f), D3DXVECTOR2(0.0f, 0.0f));

	return S_OK;
}

//====================================
// 2D�|���S���̏�����(�ʒu�I�o��)
//====================================
HRESULT CObject2DAnim::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CObject2D::Init();

	CObject2D::SetPos(pos);
	CObject2D::SetRot(rot);
	CObject2D::SetSize(D3DXVECTOR3(DEF_SIZE_ANIM.x, DEF_SIZE_ANIM.y, 0.0f));

	m_anim = new CAnim;

	if (m_anim != nullptr)
	{
		m_anim->Init();

		m_anim->SetNumLoop(0);
		m_anim->SetNumPtnX(1);
		m_anim->SetNumPtnY(1);
	}
	
	CObject2D::SetTexPos(D3DXVECTOR2(1.0f / m_anim->GetNumPtnX(), 1.0f / m_anim->GetNumPtnY()), D3DXVECTOR2(0.0f, 0.0f));

	return S_OK;
}

//============================
// 2D�|���S���̏I������
//============================
void CObject2DAnim::Uninit(void)
{
	if (m_anim != nullptr)
	{
		m_anim->Uninit();
		delete m_anim;
	}

	//�I��
	CObject2D::Uninit();
}

//============================
// 2D�|���S���̍X�V����
//============================
void CObject2DAnim::Update(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = CObject2D::GetVtxBuff();
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
void CObject2DAnim::Draw(void)
{
	//�`��
	CObject2D::Draw();
}

//============================
// �e�N�X�`�����W�ݒ�(����)
//============================
D3DXVECTOR2 CObject2D::GetTexPosleftUp(void)
{
	D3DXVECTOR2 texPosleftUp;

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	texPosleftUp = pVtx[0].tex;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return texPosleftUp;
}

//============================
// �e�N�X�`�����W�ݒ�(�E��)
//============================
D3DXVECTOR2 CObject2D::GetTexPosrightDown(void)
{
	D3DXVECTOR2 texPosrightDown;

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	texPosrightDown = pVtx[3].tex;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return texPosrightDown;
}

//============================
// �e�N�X�`�����W�ݒ�(�E�� - ����)
//============================
D3DXVECTOR2 CObject2D::GetTexPosDif(void)
{
	D3DXVECTOR2 texPosDif;

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	texPosDif = pVtx[0].tex - pVtx[3].tex;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return texPosDif;
}

//============================
// ���_�J���[�擾
//============================
D3DXCOLOR CObject2D::GetTexCol(void)
{
	D3DXCOLOR col;

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	col = pVtx[0].col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return col;
}

//============================
// ���_�J���[�ݒ�
//============================
void CObject2D::SetTexCol(D3DXCOLOR col)
{
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
