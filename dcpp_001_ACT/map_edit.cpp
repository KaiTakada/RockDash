//===============================================
//
// �}�b�v(map.cpp)
// Author:Kai Takada
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "map.h"
#include "manager.h"	//�匳
#include "game.h"
#include "input.h"
#include "block.h"

//=======================
//�}�N����`
//=======================

//=======================
// �t�@�C���p�X
//=======================
const char *c_apFilenameMap[CMap::MAP_MAX] =
{
	"data\\SET\\MAP\\load.txt",
	"data\\SET\\MAP\\save.txt",
};

//=======================
// �ÓI�����o�ϐ�
//=======================

//============================
// �R���X�g���N�^
//============================
CMap::CMap()
{
	m_pBlock = nullptr;
}

//============================
// �f�X�g���N�^
//============================
CMap::~CMap()
{

}

//====================================
// ������(�ʒu�I�o��)
//====================================
HRESULT CMap::Init()
{
	if (m_pBlock != nullptr)
	{
		m_pBlock->Uninit();
		m_pBlock = nullptr;
	}

	m_pBlock->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//====================================
// ������(�ʒu�I�o��)
//====================================
HRESULT CMap::Init(const D3DXVECTOR3 pos)
{
	if (m_pBlock != nullptr)
	{
		m_pBlock->Uninit();
		m_pBlock = nullptr;
	}

	m_pBlock = CBlock::Create(pos);
	m_pBlock->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	return S_OK;
}

//============================
// �I��
//============================
void CMap::Uninit(void)
{
	if (m_pBlock != nullptr)
	{
		m_pBlock->Uninit();
		m_pBlock = nullptr;
	}
}

//============================
// �X�V
//============================
void CMap::Update(void)
{
	//�L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	D3DXVECTOR3 pos;
	
	if (m_pBlock == nullptr)
	{
		return;
	}
	
	pos = m_pBlock->GetPos();

	//�J�[�\���̈ړ�
	if (pInputKeyboard->GetPress(DIK_W))
	{//��
		pos.y += 10.0f;
	}
	if (pInputKeyboard->GetPress(DIK_S))
	{//��
		pos.y -= 10.0f;
	}
	if (pInputKeyboard->GetPress(DIK_A))
	{//��
		pos.x -= 10.0f;
	}
	if (pInputKeyboard->GetPress(DIK_D))
	{//��
		pos.x += 10.0f;
	}

	m_pBlock->SetPos(pos);


	if (pInputKeyboard->GetTrigger(DIK_RETURN))
	{//�u���b�N�ݒu
		CBlock *pBlock = CBlock::Create(pos);
		pBlock->SetSize(m_pBlock->GetSize());
	}

	if (pInputKeyboard->GetTrigger(DIK_F8))
	{//�u���b�N�ݒu
		Load(c_apFilenameMap[MAP_LOAD]);
	}
	if (pInputKeyboard->GetTrigger(DIK_F9))
	{//�u���b�N�ݒu
		Save(c_apFilenameMap[MAP_SAVE]);
	}
}

//============================
// �`��
//============================
void CMap::Draw(void)
{

}

//============================
// �|�[�Y�̐���
//============================
CMap * CMap::Create(D3DXVECTOR3 pos)
{
	CMap *pMap = nullptr;

	//�I�u�W�F�N�g����&������
	pMap = new CMap;

	if (pMap == nullptr)
	{
		return nullptr;
	}
	
	if (FAILED(pMap->Init(pos)))
	{//���s������
		return nullptr;
	}

	return pMap;
}

//============================
// ���[�h
//============================
void CMap::Load(const char * pFilepass)
{
	if (pFilepass == nullptr)
	{
		return;
	}

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	char *pComp = new char[256];
	FILE *pFile = nullptr;

	pFile = fopen(pFilepass, "r");

	if (pFile == nullptr)
	{
		assert(false);
	}

	while (fscanf(pFile, "%s", pComp) != EOF)
	{//EOF(���X�g��)��ǂݍ��񂾂�I��

		if (strncmp(pComp, "#", 1) == 0)
		{// ����̂��ƃR�����g
			fgets(pComp, 256, pFile);
			continue;
		}
		else if (strcmp(pComp, "SET_PARAM") == 0)
		{//�p�����[�^�ݒ�
			while (true)
			{
				fscanf(pFile, "%s", pComp);

				if (strncmp(pComp, "#", 1) == 0)
				{// ����̂��ƃR�����g
					fgets(pComp, 256, pFile);
					continue;
				}

				if (strcmp(pComp, "END_PARAM") == 0)
				{
					break;
				}
				else if (strcmp(pComp, "POS") == 0)
				{
					fscanf(pFile, "%s", pComp);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
					continue;
				}
				else if (strcmp(pComp, "ROT") == 0)
				{
					fscanf(pFile, "%s", pComp);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					continue;
				}
				else if (strcmp(pComp, "SIZE") == 0)
				{
					fscanf(pFile, "%s", pComp);
					fscanf(pFile, "%f %f %f", &size.x, &size.y, &size.z);
					continue;
				}
			}

			//�ǂݍ��񂾃p�����[�^�����ɐ���
			CBlock *pBlock;
			pBlock = CBlock::Create(pos, rot);
			pBlock->SetSize(size);
		}
	}

	fclose(pFile);

	delete[] pComp;
}

//============================
// �Z�[�u
//============================
void CMap::Save(const char * pFilepass)
{
	if (pFilepass == nullptr)
	{//�t�@�C��������
		return;
	}

	//���̒Z�k���p
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	FILE *pFile = nullptr;

	pFile = fopen(pFilepass, "w");

	if (pFile == nullptr)
	{//�t�@�C��������
		assert(false);
	}

	fprintf(pFile, "#===============================================================\n");
	fprintf(pFile, "#\n");
	fprintf(pFile, "# Map(Block���)\n");
	fprintf(pFile, "# Author : Kai Takada\n");
	fprintf(pFile, "#\n");
	fprintf(pFile, "#===============================================================\n");

	for (int nCntPrt = 0; nCntPrt < CObject::PRIORITY_MAX; nCntPrt++)
	{
		CObject *pObject = CObject::GetTop(nCntPrt);

		while ((pObject != nullptr))
		{
			if (pObject != nullptr)
			{
				CObject::TYPE type = pObject->GetType();	//����̃I�u�W�F�N�g�̃^�C�v

				if (type == CObject::TYPE_BLOCK)
				{//�v���C���\��������
					pos = pObject->GetPos();
					rot = pObject->GetRot();
					size = pObject->GetSize();

					fprintf(pFile, "SET_PARAM\n");
					fprintf(pFile, "POS = %.2f %.2f %.2f\n", pos.x, pos.y, pos.z);
					fprintf(pFile, "ROT = %.2f %.2f %.2f\n", rot.x, rot.y, rot.z);
					fprintf(pFile, "SIZE = %.2f %.2f %.2f\n", size.x, size.y, size.z);
					fprintf(pFile, "END_PARAM\n\n");
				}

				pObject = pObject->GetNext();
			}
			else
			{// (pObject == NULL) == End�܂ōs�������Ă��Ƃł��̗D��x�͏I��
				break;
			}
		}
	}

	fclose(pFile);
}
