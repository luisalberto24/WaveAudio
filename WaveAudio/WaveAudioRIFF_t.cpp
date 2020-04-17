#include "Window_t.h"
#include "WaveAudioRIFF_t.h"
#include <mmsystem.h>
#include <amstream.h>

WaveAudioRIFF_t::WaveAudioRIFF_t()
{ 
	this->riffData = {}; 
}

WaveAudioRIFF_t::WaveAudioRIFF_t(const WvAudioRIFF_t data)
{
	this->riffData = {};
	this->riffData = data;
	if (this->riffData.DataChunkSize > 0)
	{
		this->riffData.Data = new char[this->riffData.DataChunkSize + 1];
		memset(this->riffData.Data, 0, this->riffData.DataChunkSize + 1);
	}
}

WaveAudioRIFF_t::~WaveAudioRIFF_t()
{
	if (this->riffData.DataChunkSize > 0 && this->riffData.Data)
	{
		delete this->riffData.Data;
		this->riffData.Data = NULL;
		this->riffData.DataChunkSize = 0;
	}
}

const WvAudioRIFF_t* WaveAudioRIFF_t::Prepare(const WAVEFORMATEX formatData, DWORD recordTime)
{
	this->riffData.FormatTag = formatData.wFormatTag;
	this->riffData.Channels = formatData.nChannels;
	this->riffData.SamplesPerSecond = formatData.nSamplesPerSec;
	this->riffData.AvgBytesPerSecond = formatData.nSamplesPerSec * formatData.nChannels;
	this->riffData.BlockAlign = formatData.nBlockAlign;
	this->riffData.BitsPerSample = formatData.wBitsPerSample;
	this->riffData.WaveChunkSize = 16;
	this->riffData.DataChunkSize = recordTime * (formatData.wBitsPerSample / 8)  * formatData.nAvgBytesPerSec;
	this->riffData.FileSize = this->riffData.DataChunkSize + 36;
	this->riffData.Data = new char[this->riffData.DataChunkSize + 1];
	memset(this->riffData.Data, 0, this->riffData.DataChunkSize + 1);

	return *this;
}

BOOL WaveAudioRIFF_t::Save(std::wstring fileName)
{
	if (fileName.length() > 0)
	{
		std::wstring directoryName = Utilities::GetFileDirectory(fileName);
		if (Utilities::DirectoryExists(directoryName))
		{
			BOOL createFile = TRUE;
			if (Utilities::FileExists(fileName))
			{
				int resultCode = MessageBoxW(NULL, L"File already exists!. Do you want to replace it?", L"Warning!",	MB_ICONEXCLAMATION | MB_APPLMODAL | MB_OKCANCEL);
				if (resultCode != IDOK)
				{
					return FALSE;
				}
			}

			ofstream wavFile(fileName, ofstream::out | ofstream::binary | ofstream::trunc);
			wavFile << this->riffData.FileType;
			wavFile.write((LPCSTR)&this->riffData.FileSize, sizeof(DWORD));
			wavFile << this->riffData.WaveId;
			wavFile << this->riffData.WaveChunkId;
			wavFile.write((LPCSTR)&this->riffData.WaveChunkSize, sizeof(DWORD));
			wavFile.write((LPCSTR)&this->riffData.FormatTag, sizeof(WORD));
			wavFile.write((LPCSTR)&this->riffData.Channels, sizeof(WORD));
			wavFile.write((LPCSTR)&this->riffData.SamplesPerSecond, sizeof(DWORD));
			wavFile.write((LPCSTR)&this->riffData.AvgBytesPerSecond, sizeof(DWORD));
			wavFile.write((LPCSTR)&this->riffData.BlockAlign, sizeof(WORD));
			wavFile.write((LPCSTR)&this->riffData.BitsPerSample, sizeof(WORD));
			wavFile << this->riffData.DataChunkId;
			wavFile.write((LPCSTR)&this->riffData.DataChunkSize, sizeof(DWORD));
			wavFile.write(this->riffData.Data, this->riffData.DataChunkSize);
			wavFile.flush();
			wavFile.close();
		}
	}

	return FALSE;
}

LPCSTR WaveAudioRIFF_t::GetDataPointer()
{
	return (LPCSTR)this->riffData.Data;
}

DWORD WaveAudioRIFF_t::GetDataSize()
{
	return (DWORD)this->riffData.DataChunkSize;
}

WaveAudioRIFF_t::operator const WvAudioRIFF_t*()
{
	return static_cast<const WvAudioRIFF_t*>(&this->riffData);
}