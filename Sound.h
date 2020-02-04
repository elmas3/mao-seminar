/*====================================================

	[Sound.h]
	Author : �o���đ�

=====================================================*/

#pragma once
#include "main.h"
#include "xaudio2.h"  // Xaudio���g�p

enum SoundLabel
{
	S_BGM_GAME,		// �Q�[��BGM
	S_BGM_GAMEEND,	// �Q�[���G���h
	S_BGM_TITLE,	// �^�C�g��
	S_SE_BALL,		// �{�[��SE
	S_SE_WHISTIL,	// �z�C�b�X��SE
	S_SE_BUTTON,	// �J�[�\���ړ�
	S_SE_ANSWER,	// ����

	SOUND_MAX
};

class Sound
{
private:
	static IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	static IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_MAX];	// �\�[�X�{�C�X
	static BYTE *m_apDataAudio[SOUND_MAX];					// �I�[�f�B�I�f�[�^
	static DWORD m_aSizeAudio[SOUND_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
	
	static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	static HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
public:
	static bool Init(HWND hWnd);
	static void Uninit();
	static void Play(SoundLabel label);
	static void Stop(SoundLabel label);
	static void Stop();
};

