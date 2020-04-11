#include "stdafx.h"

#pragma once

#if (!defined(_WAVE_AUDIO_RIFF_T_H_))
#	define	_WAVE_AUDIO_RIFF_T_H_

typedef struct tagWvAudioRIFF_t
{
	const char*	FileType			=	"RIFF";
	DWORD		FileSize;
	const char*	WaveId				=	"WAVE";
	const char*	WaveChunkId			=	"fmt ";
	DWORD		WaveChunkSize;
	WORD		FormatTag;
	WORD		Channels;
	DWORD		SamplesPerSecond;
	DWORD		AvgBytesPerSecond;
	WORD		BlockAlign;
	WORD		BitsPerSample;
	const char*	DataChunkId			=	"data";
	DWORD		DataChunkSize;
	char*		Data;
} WvAudioRIFF_t, *WvAudioRIFFPtr_t;

class WaveAudioRIFF_t
{
	public:
		WaveAudioRIFF_t		();
		WaveAudioRIFF_t		(const WvAudioRIFF_t data);
		~WaveAudioRIFF_t	();
	public:
		const	WvAudioRIFF_t*	Prepare			(const WAVEFORMATEX formatData, DWORD recordTime);
		BOOL					Save			(std::wstring fileName);
		LPCSTR					GetDataPointer	();
		DWORD					GetDataSize		();
		operator const	WvAudioRIFF_t*			();
	private:
		WvAudioRIFF_t riffData;
};

#endif 

