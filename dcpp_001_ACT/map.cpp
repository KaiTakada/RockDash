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
#include "blk_goal.h"
#include "debugproc.h"

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
	m_pBlock->SetDeath(true);

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
	m_pBlock->SetDeath(true);
	//m_pBlock->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

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
	
	if (m_pBlock == nullptr)
	{
		return;
	}
	
	D3DXVECTOR3 pos = m_pBlock->GetPos();
	D3DXVECTOR3 size = m_pBlock->GetSize();

	if (pInputKeyboard->GetTrigger(DIK_B))
	{
		//�󂵂�
		int nType = m_pBlock->GetType_Blk();
		m_pBlock->SetDeath(true);

		//1���炵
		nType++;
		nType %= CBlock::TYPE_MAX;

		//��蒼��
		m_pBlock = CBlock::Create(pos,DEF_VEC3,(CBlock::TYPE_Blk)nType);
		m_pBlock->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		m_pBlock->SetDeath(true);
	}

	//�u���b�N�T�C�Y�ύX
	if (pInputKeyboard->GetTrigger(DIK_UP))
	{
		size.y += 1.0f;
		m_pBlock->SetSize(size);
	}
	if (pInputKeyboard->GetTrigger(DIK_DOWN))
	{
		size.y -= 1.0f;
		m_pBlock->SetSize(size);
	}
	if (pInputKeyboard->GetTrigger(DIK_RIGHT))
	{
		size.x += 1.0f;
		m_pBlock->SetSize(size);
	}
	if (pInputKeyboard->GetTrigger(DIK_LEFT))
	{
		size.x -= 1.0f;
		m_pBlock->SetSize(size);
	}


	//�J�[�\���̈ړ�
	if (pInputKeyboard->GetPress(DIK_SPACE))
	{
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
	}
	else
	{
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
	}

	m_pBlock->SetPos(pos);


	if (pInputKeyboard->GetTrigger(DIK_RETURN))
	{//�u���b�N�ݒu
		CBlock *pBlock = CBlock::Create(pos, DEF_VEC3, m_pBlock->GetType_Blk());
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
	D3DXVECTOR3 pos = m_pBlock->GetPos();
	D3DXVECTOR3 size = m_pBlock->GetSize();

	//�f�o�b�O
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();
	pDebug->Print("--- �G�f�B�b�g��� ---\n");
	pDebug->Print("���݂̍��W:%f %f %f\n", pos.x, pos.y, pos.z);
	pDebug->Print("���݂̃T�C�Y:%f %f %f\n", size.x, size.y, size.z);
	pDebug->Print("�Z�[�u�FF9 �E ���[�h�FF8\n");
	pDebug->Print("�ݒu�FEnter �E �^�C�v�ύX�FB\n");
	pDebug->Print("----------------------\n");
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
	int nType = CBlock::TYPE_NORMAL;
	CBlock *pBlock = nullptr;		//�������e

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
				else if (strcmp(pComp, "TYPE") == 0)
				{
					fscanf(pFile, "%s", pComp);
					fscanf(pFile, "%d", &nType);
					continue;
				}
			}

			//�ǂݍ��񂾃p�����[�^�����ɐ���
			pBlock = CBlock::Create(pos, rot,(CBlock::TYPE_Blk)nType);
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
	int nType = CBlock::TYPE_NORMAL;

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
				bool bDeath = pObject->GetDeath();

				if (type == CObject::TYPE_BLOCK && !bDeath)
				{//����łȂ��u���b�N��������
					pos = pObject->GetPos();
					rot = pObject->GetRot();
					size = pObject->GetSize();

					nType = pObject->GetLocalType();

					fprintf(pFile, "SET_PARAM\n");
					fprintf(pFile, "POS = %.2f %.2f %.2f\n", pos.x, pos.y, pos.z);
					fprintf(pFile, "ROT = %.2f %.2f %.2f\n", rot.x, rot.y, rot.z);
					fprintf(pFile, "SIZE = %.2f %.2f %.2f\n", size.x, size.y, size.z);
					fprintf(pFile, "TYPE = %d\n", nType);
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

//============================
// �J�[�\�����
//============================
CBlock *CMap::GetCursor()
{
	return m_pBlock;
}
