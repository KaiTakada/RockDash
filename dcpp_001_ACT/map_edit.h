//===============================================
//
// �}�b�v(map.h)
// Author: ���c ����
//
//===============================================
#ifndef _MAP_H_
#define _MAP_H_

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "manager.h"

//=========================
// �}�N����`
//=========================

//=========================
// �O���錾
//=========================
class CBlock;

//=========================
// �v���C���[�N���X
//=========================
class CMap
{
public:

	enum MAP_FILE
	{
		MAP_LOAD = 0,
		MAP_SAVE,
		MAP_MAX,
	};

	CMap();		//�R���X�g���N�^
	~CMap();		//�f�X�g���N�^

	HRESULT Init(void);							//������(�f�t�H)
	HRESULT Init(const D3DXVECTOR3 pos);		//������(�I�o��)
	void Uninit(void);							//�I��
	void Update(void);							//�X�V
	void Draw(void);							//�`��
	static CMap *Create(const D3DXVECTOR3 pos);		//����
	void Load(const char* pFilepass);							//���[�h
	void Save(const char* pFilepass);							//�Z�[�u

protected:

private:
	CBlock *m_pBlock;			//�u���b�N(�J�[�\��)
};

#endif