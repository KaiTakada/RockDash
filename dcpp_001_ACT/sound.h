//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : KAI TAKADA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//===================================
// �����N���X
//===================================
class CSound
{
public:
	//*****************************************
	// �T�E���h�ꗗ
	//*****************************************
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,
		SOUND_LABEL_BGM_TUTORIAL,
		SOUND_LABEL_BGM_GAME,
		SOUND_LABEL_BGM_RESULT,
		SOUND_LABEL_BGM_RANKING,
		SOUND_LABEL_SE_BUTTON,
		SOUND_LABEL_SE_ONFIRE,
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	CSound();
	~CSound();

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void Stop(void);
	void Stop(SOUND_LABEL label);

protected:

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	static IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	static IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y};
};

#endif
