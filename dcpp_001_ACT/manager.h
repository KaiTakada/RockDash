//===============================================
//
// �}�l�[�W��(manager.h)
// Author ���c ����
//
//===============================================
#ifndef _MANAGER_H_		//���̃}�N����`������ĂȂ�������
#define _MANAGER_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "main.h"
#include "renderer.h"

//=========================
// �O���錾
//=========================
class CRenderer;
class CTexture;
class CXModel;
class CCamera;
class CLight;
class CSound;
class CSpawn;
class CFade;

class CInputKeyboard;
class CInputGamepad;
class CInputMouse;

class CBg;
class CMultiBg;
class CNumber;
class CScore;

class CObject3D;
class CField;

class CObjectBillboard;
class CItem;
class CBullet;
class CExplosion;
class CEffect;
class CParticle;

class CObjectX;
class CBlock;
class CEnemy;
class CPlayer;

class CDebugProc;

//=========================
// ���(�V�[��)�N���X
//=========================
class CScene
{
public:
	enum MODE
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,
		MODE_MAX
	};

	CScene();
	~CScene();

	virtual HRESULT Init();		//������
	virtual void Uninit();		//�I��
	virtual void Update();		//�X�V
	virtual void Draw();		//�`��
	static CScene *Create(MODE mode);		//����
	CScene::MODE GetMode() { return m_mode; }		//���݂̃��[�h�擾
	static CFade *GetFade(void) { return m_pFade; }									//�t�F�[�h�̓�

	static CBg *GetBg(void) { return m_pBg; }											//�w�i�̎擾
	static CMultiBg *GetMultiBg(void) { return m_pMultiBg; }							//���d�w�i�̎擾
	static CEffect *GetEffect(void) { return m_pEffect; }								//�G�t�F�N�g�̎擾
	static CParticle *GetParticle(void) { return m_pParticle; }							//�p�[�e�B�N���̎擾
	static CNumber *GetNumber(void) { return m_pNumber; }								//�����̎擾
	static CScore *GetScore(void) { return m_pScore; }									//�X�R�A�̎擾

	static CObject3D *GetObject3D(void) { return m_pObject3D; }							//3D�|���S���̎擾
	static CField *GetField(void) { return m_pField; }									//�n�ʂ̎擾

	static CObjectBillboard *GetBillBoard(void) { return m_pBillBoard; }				//�r���{�[�h�̎擾
	static CItem *GetItem(void) { return m_pItem; }										//�A�C�e���̎擾
	static CBullet *GetBullet(void) { return m_pBullet; }								//�e�̎擾
	static CExplosion *GetExplosion(void) { return m_pExplosion; }						//�����̎擾

	static CObjectX *GetObjectX(void) { return m_pObjectX; }							//���f���̎擾
	static CEnemy *GetEnemy(void) { return m_pEnemy; }									//�G�̎擾
	static CBlock *GetBlock(void) { return m_pBlock; }									//�u���b�N�̎擾

	static int GetNowTime(void) { return m_nTime; }									//����v���C���ʂ̎擾
	static void SetNowTime(int nScore) { m_nTime = nScore; }							//����v���C���ʂ̎擾

protected:

private:
	MODE m_mode;		//���݂̃��[�h

	static CBg *m_pBg;									//�w�i
	static CMultiBg *m_pMultiBg;						//���d�w�i
	static CNumber *m_pNumber;							//����
	static CScore *m_pScore;							//�X�R�A
	static CFade *m_pFade;								//�t�F�[�h

	static CObject3D *m_pObject3D;						//3D�|���S��
	static CField *m_pField;							//�n��

	static CObjectBillboard *m_pBillBoard;				//�r���{�[�h
	static CItem *m_pItem;								//�A�C�e��
	static CEffect *m_pEffect;							//�G�t�F�N�g
	static CParticle *m_pParticle;						//�p�[�e�B�N��
	static CBullet *m_pBullet;							//�e
	static CExplosion *m_pExplosion;					//����

	static CObjectX *m_pObjectX;						//���f��
	static CEnemy *m_pEnemy;							//�G
	static CBlock *m_pBlock;							//�u���b�N
	static int m_nTime;								//����v���C����
};

//=========================
// �}�l�[�W���N���X
//=========================
class CManager
{
public:

	//========================
	// ���U���g��
	//========================
	enum RESULT_TYPE
	{
		RT_NONE = 0,
		RT_WIN,
		RT_LOSE,
		RT_MAX,
	};

	CManager();			//�R���X�g���N�^
	~CManager();		//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);		//������
	void Uninit(void);												//�I��
	void Update(void);												//�X�V
	void Draw(void);												//�`��
	void SetMode(CScene::MODE mode);							//�V�[���ݒ�
	
	static CManager *GetInstance();						//�C���X�^���X�擾
	static void Release();						//�����[�X

	CRenderer *GetRenderer(void) { return m_pRenderer; }							//�����_���[�̎擾
	CTexture *GetTexture(void) { return m_pTeture; }								//�e�N�X�`���̎擾
	CXModel *GetXModel(void) { return m_pXModel; }								//X�t�@�C�����f���̎擾
	CCamera *GetCamera(void) { return m_pCamera; }								//�J�����̎擾
	CLight *GetLight(void) { return m_pLight; }									//���C�g�̎擾
	CSound *GetSound(void) { return m_pSound; }									//�T�E���h�̎擾
	CSpawn *GetSpawn(void) { return m_pSpawn; }									//�G�X�|�[���̎擾

	CInputKeyboard *GetInputKeyboard(void) { return m_pCInputKeyboard; }			//���͏��̎擾(�L�[�{�[�h)
	CInputGamepad *GetInputGamepad(void) { return m_pCInputGamepad; }			//���͏��̎擾(Pad [X])
	CInputMouse *GetInputMouse(void) { return m_pCInputMouse; }					//���͏��̎擾(�}�E�X)

	//CBg *GetBg(void) { return m_pBg; }											//�w�i�̎擾
	//CMultiBg *GetMultiBg(void) { return m_pMultiBg; }							//���d�w�i�̎擾
	//CEffect *GetEffect(void) { return m_pEffect; }								//�G�t�F�N�g�̎擾
	//CParticle *GetParticle(void) { return m_pParticle; }							//�p�[�e�B�N���̎擾
	//CNumber *GetNumber(void) { return m_pNumber; }								//�����̎擾
	//CScore *GetScore(void) { return m_pScore; }									//�X�R�A�̎擾

	//CObject3D *GetObject3D(void) { return m_pObject3D; }							//3D�|���S���̎擾
	//CField *GetField(void) { return m_pField; }									//�n�ʂ̎擾

	//CObjectBillboard *GetBillBoard(void) { return m_pBillBoard; }				//�r���{�[�h�̎擾
	//CItem *GetItem(void) { return m_pItem; }										//�A�C�e���̎擾
	//CBullet *GetBullet(void) { return m_pBullet; }								//�e�̎擾
	//CExplosion *GetExplosion(void) { return m_pExplosion; }						//�����̎擾

	//CObjectX *GetObjectX(void) { return m_pObjectX; }								//���f���̎擾
	//CPlayer *GetPlayer(void) { return m_pPlayer; }								//�v���C���[�̎擾
	//CEnemy *GetEnemy(void) { return m_pEnemy; }									//�G�̎擾
	//CBlock *GetBlock(void) { return m_pBlock; }									//�u���b�N�̎擾

	CDebugProc *GetDebugProc(void) { return m_pDebugProc; }				//�f�o�b�O�̎擾
	CScene *GetScene(void) { return m_pScene; }							//�V�[���̎擾

	void SetPause(bool bPause) { m_bPause = bPause; }					//�|�[�Y��Ԑݒ�
	bool GetPause(void) { return m_bPause; }								//�|�[�Y��Ԏ擾
	void InvPause(void) { m_bPause = m_bPause ? false : true; }			//�|�[�Y�؂�ւ�

	void SetGrow(bool bGrow) { m_bGrow = bGrow; }						//�i���V�[����Ԑݒ�
	bool GetGrow(void) { return m_bGrow; }								//�i���V�[����Ԏ擾
	void InvGrow(void) { m_bGrow = m_bGrow ? false : true; }				//�i���V�[���؂�ւ�

	void SetEdit(bool bEdit) { m_bEdit = bEdit; }						//�i���V�[����Ԑݒ�
	bool GetEdit(void) { return m_bEdit; }								//�i���V�[����Ԏ擾
	void InvEdit(void) { m_bEdit = m_bEdit ? false : true; }				//�i���V�[���؂�ւ�

	void SetResult(RESULT_TYPE result) { m_result = result; }			//���s��Ԑݒ�
	RESULT_TYPE GetResult(void) { return m_result; }						//���s��Ԏ擾

protected:

private:
	CRenderer *m_pRenderer;						//�����_���[
	CTexture *m_pTeture;						//�e�N�X�`��
	CXModel *m_pXModel;							//X�t�@�C�����f��
	CCamera *m_pCamera;							//�J����
	CLight *m_pLight;							//���C�g
	CSound *m_pSound;							//�T�E���h
	CSpawn *m_pSpawn;							//�G�X�|�[��

	CInputKeyboard *m_pCInputKeyboard;			//����(�L�[�{�[�h)
	CInputGamepad *m_pCInputGamepad;			//����(Pad[X])
	CInputMouse *m_pCInputMouse;				//����(�}�E�X)

	CDebugProc *m_pDebugProc;					//�f�o�b�O
	CScene *m_pScene;							//�V�[��

	bool m_bPause;				//�|�[�Y�t���O(���Q�[���V�[���Ŏg�p��Renderer����)
	bool m_bGrow;				//�i���V�[���t���O(���Q�[���V�[���Ŏg�p��Renderer����)
	bool m_bEdit;				//�G�f�B�b�g�t���O(���Q�[���V�[���Ŏg�p��Renderer����)
	RESULT_TYPE m_result;		//���s�t���O(���Q�[�������U���g�V�[���Ŏg�p)
	
	static CManager *m_pManager;		//�C���X�^���X�ێ�
};

#endif
