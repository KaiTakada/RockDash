//===============================================
//
// �|���S��(object.cpp)
// Author ���c ����
//
//===============================================
#include "object.h"
#include "manager.h"
#include "debugproc.h"
#include "main.h"
#include "block.h"
#include "item.h"
#include "enemy.h"
#include "camera.h"

//============================
// �ÓI�����o�ϐ��錾
//============================
CObject *CObject::m_apTop[PRIORITY_MAX] = {};
CObject *CObject::m_apEnd[PRIORITY_MAX] = {};
int CObject::m_nNumAll;		//�I�u�W�F�N�g����

//============================
// �R���X�g���N�^(�`�揇�I�o��)
//============================
CObject::CObject(int nPriority)
{
	if (m_apTop[nPriority] == nullptr)
	{//�擪�����Ȃ��Ȃ�this�𐘂���
		m_apTop[nPriority] = this;
	}

	m_pNext = nullptr;

	//����̍Ō��
	m_pPrev = m_apEnd[nPriority];
	m_nPriority = nPriority;
	m_bDeath = false;

	if (m_apEnd[nPriority] != nullptr)
	{
		m_apEnd[nPriority]->m_pNext = this;
	}

	m_apEnd[nPriority] = this;
	m_nNumAll++;
}
//============================
// �f�X�g���N�^
//============================
CObject::~CObject()
{

}

////============================
//// �I�u�W�F�N�g�̔j��
////============================
//void CObject::Release(void)
//{
//	int nPrity = m_nPriority;
//	CObject *pNext = m_pNext;		//����
//	CObject *pPrev = m_pPrev;		//�O��
//
//	if (m_apTop != nullptr)
//	{
//		if (m_apTop == this)
//		{//�擪��this���ꏏ�ł����
//			m_apTop = pNext;
//		}
//	}
//
//	if (m_apEnd != nullptr)
//	{
//		if (m_apEnd == this)
//		{//�Ō����this���ꏏ�ł����
//			m_apEnd = m_pPrev;
//		}
//	}
//
//	if (pPrev != nullptr)
//	{
//		if (pNext == nullptr)
//		{
//			pPrev->m_pNext = nullptr;
//		}
//		else
//		{
//			pPrev->m_pNext = pNext;
//		}
//	}
//
//	if (pNext != nullptr)
//	{
//		pNext->m_pPrev = m_pPrev;
//	}
//
//	delete this;
//	//this = nullptr;
//
//	//�����_�E��
//	m_nNumAll--;
//}

//============================
// �I�u�W�F�N�g�̔j��
//============================
void CObject::Release(void)
{
	int nPrity = m_nPriority;
	CObject *pNext = m_pNext;		//����
	CObject *pPrev = m_pPrev;		//�O��

	if (m_apTop[nPrity] != nullptr)
	{
		if (m_apTop[nPrity] == this)
		{//�擪��this���ꏏ�ł����

			m_apTop[nPrity] = pNext;
		}
	}

	if (m_apEnd[nPrity] != nullptr)
	{
		if (m_apEnd[nPrity] == this)
		{//�Ō����this���ꏏ�ł����

			m_apEnd[nPrity] = m_pPrev;
		}
	}

	if (pPrev != nullptr)
	{
		if (pNext == nullptr)
		{
			pPrev->m_pNext = nullptr;
		}
		else
		{//���g�̌����Ɉ����p������
			pPrev->m_pNext = pNext;
		}
	}

	if (pNext != nullptr)
	{//���g�̑O���㑱�Ɉ����p������
		pNext->m_pPrev = m_pPrev;
	}

	delete this;

	//�����_�E��
	m_nNumAll--;
}

//============================
// �S�Ă̔j��
//============================
void CObject::ReleaseAll(void)
{
	CObject *pObject = m_apTop[0];

	//�S�ĂɎ��S�t���O�𗧂ĂĂ���
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		while (pObject != nullptr)
		{
			CObject *pObjectNext = pObject->m_pNext;

			pObject->m_bDeath = true;

			pObject = pObjectNext;
		}

		pObject = m_apTop[nCnt];
	}

	//���S�t���OON�Ȃ����
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		while (pObject != nullptr)
		{
			CObject *pObjectNext = pObject->m_pNext;

			if (pObject->m_bDeath == true)
			{
				pObject->Uninit();

				pObject = pObjectNext;
			}
		}

		pObject = m_apTop[nCnt];
	}
}

//============================
// �S�Ă̍X�V
//============================
void CObject::UpdateAll(void)
{
	CObject *pObject = m_apTop[0];

	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		while ((pObject != nullptr))
		{
			if (pObject != nullptr)
			{
				if (pObject->m_type == TYPE_FADE)
				{
					pObject->Update();
				}

				CObject *pObjectNext = pObject->m_pNext;

				pObject->Update();

				pObject = pObjectNext;
			}
			else
			{// (pObject == NULL) == End�܂ōs�������Ă��Ƃł��̗D��x�͏I��
				break;
			}
		}

		pObject = m_apTop[nCnt];
	}

	//���S�t���O�ɉ����ď���
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		while (pObject != nullptr)
		{
			CObject *pObjectNext = pObject->m_pNext;

			if (pObject->m_bDeath == true)
			{
				pObject->Uninit();
			}

			pObject = pObjectNext;
		}

		pObject = m_apTop[nCnt];
	}
}

//============================
// �S�Ă̕`��
//============================
void CObject::DrawAll(void)
{
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	if (pCamera != nullptr)
	{
		pCamera->SetCamera();
	}

	CObject *pObject = nullptr;

	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		pObject = m_apTop[nCnt];

		while ((pObject != nullptr))
		{
			if (pObject != nullptr)
			{
				pObject->Draw();

				pObject = pObject->m_pNext;
			}
			else
			{// (pObject == NULL) == End�܂ōs�������Ă��Ƃł��̗D��x�͏I��
				break;
			}
		}
	}

	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();
	pDebug->Print("FPS:%d", GetFPS());
	pDebug->Draw();
}
