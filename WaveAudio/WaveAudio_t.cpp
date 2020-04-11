#include "Window_t.h"
#include "WaveAudio_t.h"

WaveAudio_t::WaveAudio_t(
	Window_t* window, 
	WORD format, 
	WORD channels, 
	WORD samplesPerSecond,
	WORD bitsPerSample)
{
	this->waveFormat = { 0 };
	this->waveFormat.wFormatTag = format;
	this->waveFormat.nChannels = channels;
	this->waveFormat.nSamplesPerSec = samplesPerSecond;
	this->waveFormat.wBitsPerSample = bitsPerSample;
	this->waveFormat.nAvgBytesPerSec = samplesPerSecond * channels;
	this->waveFormat.nBlockAlign = (WORD)((channels * bitsPerSample) / 8);
	this->waveFormat.cbSize = 0;
	this->hWaveHandle = {0};
	this->window = window;
}

WaveAudio_t::~WaveAudio_t()
{
	this->Close();
}

VOID WaveAudio_t::Close()
{
	if (this->hWaveHandle != 0)
	{
		waveInClose(this->hWaveHandle);
		this->hWaveHandle = 0;
	}
}

BOOL WaveAudio_t::IsFormatSupported()
{
	return (WAVERR_BADFORMAT != waveInOpen(&this->hWaveHandle, WAVE_MAPPER, &this->waveFormat, 0, 0, WAVE_FORMAT_QUERY));
}

DWORD WaveAudio_t::GetBufferSize()
{
	return this->WavAudioRIFF.GetDataSize();
}

const WAVEFORMATEX* WaveAudio_t::GetAudioFormat()
{
	return (const WAVEFORMATEX*)&this->waveFormat;
}

int WaveAudio_t::Open()
{
	int res = 0;
	if (FAILED(res = waveInOpen((LPHWAVEIN)(&this->hWaveHandle), WAVE_MAPPER, &this->waveFormat, 0L, 0L, WAVE_FORMAT_DIRECT)))
	{
		HWND handler = this->window->GetHandler();
		waveInClose(this->hWaveHandle);
		MessageBoxW((const HWND)this->window->GetHandler(), L"Opening audio device.", L"Error!", MB_ICONERROR | MB_OK);
		return res;
	}

	return res;
}

int WaveAudio_t::Prepare(DWORD recordSeconds)
{
	this->waveHeader = { 0 };
	const WvAudioRIFF_t* audioRiff = this->WavAudioRIFF.Prepare(this->waveFormat, recordSeconds);
	this->waveHeader.dwBufferLength = audioRiff->DataChunkSize;
	this->waveHeader.lpData = audioRiff->Data;
	int res = 0;
	if (FAILED(res = waveInPrepareHeader(this->hWaveHandle, &this->waveHeader, sizeof(WAVEHDR))))
	{
		waveInUnprepareHeader(this->hWaveHandle, &this->waveHeader, 0);
		waveInClose(this->hWaveHandle);
		MessageBoxW(this->window->GetHandler(), L"Preparing audio device.", L"Error!", MB_ICONERROR | MB_OK);
		return res;
	}

	if (FAILED(res = waveInAddBuffer(this->hWaveHandle, &this->waveHeader, sizeof(WAVEHDR))))
	{
		waveInUnprepareHeader(this->hWaveHandle, &this->waveHeader, sizeof(WAVEHDR));
		waveInClose(this->hWaveHandle);
		MessageBoxW(this->window->GetHandler(), L"Buffer cannot be added.", L"Error!", MB_ICONERROR | MB_OK);
		return res;
	}

	return 0;
}

int WaveAudio_t::Start()
{
	int res = 0;
	if (FAILED(res = waveInStart(this->hWaveHandle)))
	{
		waveInUnprepareHeader(this->hWaveHandle, &this->waveHeader, sizeof(WAVEHDR));
		waveInClose(this->hWaveHandle);

		return res;
	}

	return 0;
}

VOID WaveAudio_t::Stop()
{
	waveInStop(this->hWaveHandle);
	waveInReset(this->hWaveHandle);
}

BOOL WaveAudio_t::IsRunning()
{
	return (this->waveHeader.dwFlags & WHDR_DONE) != WHDR_DONE;
}

VOID WaveAudio_t::Record(DWORD seconds, VOID(CALLBACK*fncDoWhileRecording)(VOID*), VOID* whileRecordingObjPtr)
{
	if (!this->IsFormatSupported())
	{
		MessageBoxW(this->window->GetHandler(), L"Audio format is not supported.", L"Error!", MB_ICONERROR | MB_OK);
		return;
	}
	
	if (seconds < 1) seconds = 1;

	this->Open();
	this->Prepare(seconds);
	this->Start();
	
	if (fncDoWhileRecording!=NULL && whileRecordingObjPtr!=NULL)
	{
		while (this->IsRunning()) 
		{
			Sleep(1000);
			fncDoWhileRecording(whileRecordingObjPtr);
		}
	}
	else
	{
		while (this->IsRunning()) {}
	}
}

BOOL WaveAudio_t::Save(wstring fileName)
{
	if (!this->IsRunning())
	{
		return this->WavAudioRIFF.Save(fileName);
	}

	return FALSE;
}
