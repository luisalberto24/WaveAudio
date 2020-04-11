#include "stdafx.h"
#include "Window_t.h"
#include "WaveAudioRIFF_t.h"

#pragma once

#if (!defined(_WAVE_AUDIO_T_H_))
#	define	_WAVE_AUDIO_T_H_

#pragma comment(lib, "Winmm.lib")

class WaveAudio_t
{
	public:
		WaveAudio_t(
			Window_t* window,
			WORD format = WAVE_FORMAT_PCM,
			WORD channels = 1,
			WORD samplesPerSec = AT_FCY_SAMPLES_PER_SECONDS_44100,
			WORD bitsPerSample = AT_BITS_PER_SAMPLE_16);
		~WaveAudio_t							();
	public:
		VOID				Close				();
		BOOL				IsFormatSupported	();
		DWORD				GetBufferSize		();
		const WAVEFORMATEX* GetAudioFormat		();
		int					Open				();
		int					Prepare				(DWORD recordSeconds);
		int					Start				();
		VOID				Stop				();
		BOOL				IsRunning			();
		VOID				Record				(DWORD seconds, VOID (CALLBACK*fncDoWhileRecording)(VOID*), VOID* whileRecordingObjPtr);
		BOOL				Save				(wstring fileName);
	protected:
		WAVEFORMATEX		waveFormat;
		WAVEHDR				waveHeader;
		HWAVEIN				hWaveHandle;
		WaveAudioRIFF_t		WavAudioRIFF;
		Window_t*			window;

};

#endif

