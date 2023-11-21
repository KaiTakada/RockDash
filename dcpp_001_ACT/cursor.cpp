//===============================================
//
// �w�i(bg.cpp)
// Author ���c ����
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "cursor.h"
#include "texture.h"
#include "input.h"

//============================
// �}�N����`
//============================
#define CSR_DIST (SCREEN_HEIGHT * 0.35f)		//�J�[�\���̈ʒu�i���a�j

//============================
// �ÓI�����o�ϐ��錾
//============================
LPDIRECT3DTEXTURE9 CCursor::m_pTexture[CCursor::TEX_MAX] = {};

//============================
// �t�@�C������`
//============================
static const char *c_apTexpass[CCursor::TEX_MAX] =
{
	"data\\TEXTURE\\CURSOR\\Aim.png",
	"data\\TEXTURE\\CURSOR\\Aim.png",
	"data\\TEXTURE\\CURSOR\\Aim.png",
};

//============================
// �R���X�g���N�^
//============================
CCursor::CCursor()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Defpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bMouse = true;
}

//============================
// �f�X�g���N�^
//============================
CCursor::~CCursor()
{

}

//====================================
// 2D�|���S���̏���������(�f�t�H)
//====================================
HRESULT CCursor::Init(void)
{
	CObject2D::Init();

	SetType(TYPE_BG);

	return S_OK;
}

//====================================
// 2D�|���S���̏�����(�ʒu�I�o��)
//====================================
HRESULT CCursor::Init(const D3DXVECTOR3 pos)
{
	CObject2D::Init();

	CObject2D::SetPos(pos);

	SetType(TYPE_BG);

	return S_OK;
}

//============================
// 2D�|���S���̏I������
//============================
void CCursor::Uninit(void)
{
	//���g�̔j��
	CObject2D::Uninit();

	//Release();
}

//============================
// 2D�|���S���̍X�V����
//============================
void CCursor::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();

	if (m_bMouse)
	{//�}�E�X����
		pos += pInputMouse->GetChangePos();
	
		if (pos.x >= SCREEN_WIDTH - GetSize().x)
		{//�E��
			pos.x = SCREEN_WIDTH - GetSize().x;
		}
		else if (pos.x <= 0.0f + GetSize().x)
		{//����
			pos.x = 0.0f + GetSize().x;
		}

		if (pos.y >= SCREEN_HEIGHT - GetSize().y)
		{//����
			pos.y = SCREEN_HEIGHT - GetSize().y;
		}
		else if (pos.y <= 0.0f + GetSize().y)
		{//���
			pos.y = 0.0f + GetSize().x;
		}
	}
	else
	{//�}�E�X�ȊO
		if (pInputKeyboard->GetPress(DIK_DOWN) ||
			pInputGamepad->GetGameStickRYPress(0) < 0)
		{
			move.y += 1.0f;
		}
		if (pInputKeyboard->GetPress(DIK_UP) ||
			pInputGamepad->GetGameStickRYPress(0) > 0)
		{
			move.y -= 1.0f;
		}
		if (pInputKeyboard->GetPress(DIK_LEFT) ||
			pInputGamepad->GetGameStickRXPress(0) < 0)
		{
			move.x -= 1.0f;
		}
		if (pInputKeyboard->GetPress(DIK_RIGHT) ||
			pInputGamepad->GetGameStickRXPress(0) > 0)
		{
			move.x += 1.0f;
		}

		if (move == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			move = m_move;
		}
		else
		{
			m_move = move;
		}

		pos = m_Defpos;
	
		float fAngle = -atan2f(move.y, move.x) + D3DX_PI * 0.5f;
		pos.x += sinf(fAngle) * CSR_DIST;
		pos.y += cosf(fAngle) * CSR_DIST;
	}

	if (pInputMouse->GetPress(CInputMouse::BUTTON_RIGHT))
	{
		m_bMouse = !m_bMouse;
	}


	SetPos(pos);

	m_vec = pos - m_Defpos;
}

//============================
// 2D�|���S���̕`�揈��
//============================
void CCursor::Draw(void)
{
	CObject2D::Draw();
}

//============================
// 2D�|���S���̐�������
//============================
CCursor * CCursor::Create(void)
{
	CCursor *pBg;

	//�I�u�W�F�N�g����
	pBg = new CCursor;

	//������
	pBg->Init();

	return pBg;
}

//============================
// 2D�|���S���̐�������
//============================
CCursor * CCursor::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const TEX TexType)
{
	CCursor *pCursor = nullptr;

	//�I�u�W�F�N�g����&������
	if (pCursor == nullptr)
	{
		pCursor = new CCursor;

		if (pCursor != nullptr)
		{
			pCursor->Init(pos);

			//���S�_���E�B���h�E�̒��S�ɂ���
			pCursor->m_Defpos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
			pCursor->SetSize(size);

			CTexture *pTexture = CManager::GetInstance()->GetTexture();
			pCursor->SetIdxTexture(pTexture->Regist(c_apTexpass[TexType]));
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}

	return pCursor;
}

//============================
// �x�N�g����Rot�Ƃ��ēn��
//============================
D3DXVECTOR3 CCursor::GetRot()
{
	D3DXVECTOR3 pos = GetPos();

	D3DXVECTOR3 vecDiff = D3DXVECTOR3(pos.x - m_Defpos.x,
		pos.y - m_Defpos.y,
		0.0f);

	//D3DXVec3Normalize(&vecDiff, &vecDiff);		//�x�N�g���𐳋K������(1.0f�ɂ���)

	float fAngle = atan2f(vecDiff.y, vecDiff.x) + D3DX_PI * -0.5f;

	return D3DXVECTOR3(0.0f, fAngle, 0.0f);
}
