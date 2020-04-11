#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include "Window_t.h"
#include "WLabel_t.h"
#include "WBtnProcess_t.h"
#include "WBtnSearchFolder_t.h"
#include "WTBFolder_t.h"
#include "WTBFileName_t.h"
#include "WTBRecordTime_t.h"
#include "WSpinner_t.h"
#include "WProgressBar_t.h"
#include "WaveAudio_t.h"
#include "WaveAudioRIFF_t.h"

using namespace std;

// function prototypes
VOID RegisterWindowControls(Window_t*);

// Program entry point
int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance, 
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine, 
	_In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	Window_t window(hInstance, L"CWaveWindow", L"WaveWindow", L"RIFF - WAV Audio Saver from Windows Microphone");
	RegisterWindowControls((Window_t*)&window);
	if (!window.Show(nCmdShow))
	{
		Window_t::GetLastErrorMessageBox(window.GetHandler(), L"Error showing window!");
		return -1;
	}

	return window.Loop().message;
}

VOID RegisterWindowControls(Window_t* window)
{	
	window->RegisterControl<WLabel_t>
		({ ID_LABEL_FOLDERNAME, ControlTypes::LABEL,	0, 0, 0, "STATIC", "Folder:", WS_CHILD | WS_VISIBLE | WS_EX_TRANSPARENT | SS_RIGHT, 
		{10, 10, 70, 20} });
	window->RegisterControl<WLabel_t>
		({ ID_LABEL_FILENAME, ControlTypes::LABEL,	0, 0, 0, "STATIC", "File Name:", WS_CHILD | WS_VISIBLE | WS_EX_TRANSPARENT | SS_RIGHT,
		{10, 32, 70, 20} });
	window->RegisterControl<WLabel_t>
		({ ID_LABEL_SPINNER, ControlTypes::LABEL,	0, 0, 0, "STATIC", "Seconds:", WS_CHILD | WS_VISIBLE | WS_EX_TRANSPARENT | SS_RIGHT,
		{10, 54, 70, 20} });
	window->RegisterControl<WLabel_t>
		({ ID_LABEL_PROGRESSBAR, ControlTypes::LABEL,	0, 0, 0, "STATIC", "Progress:", WS_CHILD | WS_VISIBLE | WS_EX_TRANSPARENT | SS_RIGHT,
		{10, 76, 70, 20} });
	window->RegisterControl<WTBFolder_t>
		({ ID_EDIT_FOLDERNAME, ControlTypes::EDIT,	0, 0, 0, "EDIT",   "", WS_CHILD | WS_VISIBLE,
		{85, 10, 500, 20} });
	window->RegisterControl<WTBFileName_t>
		({ ID_EDIT_FILENAME, ControlTypes::EDIT,	0, 0, 0, "EDIT",   "", WS_CHILD | WS_VISIBLE,
		{85, 32, 300, 20} });
	window->RegisterControl<WTBRecordTime_t>
		({ ID_EDIT_RECORD_TIME, ControlTypes::EDIT,	0, 0, 0, "EDIT",   "", WS_CHILDWINDOW | ES_NUMBER  | WS_VISIBLE | ES_AUTOHSCROLL,
		{85, 54, 45, 20} });
	window->RegisterControl<WSpinner_t>
		({ ID_SPINNER_RECORD_TIME, ControlTypes::SPINNER,	0, 0, 0, UPDOWN_CLASSA, "", WS_CHILD | WS_VISIBLE | UDS_ALIGNRIGHT | UDS_SETBUDDYINT| UDS_ARROWKEYS,
		{0, 0, 0, 0} });
	window->RegisterControl<WBtnSearchFolder_t>
		({ ID_BTN_SEARCH_FOLDER, ControlTypes::BUTTON,	0, 0, 0, "BUTTON", "...", WS_CHILD | WS_VISIBLE | BS_USERBUTTON,
		{590, 10, 30, 20} });
	window->RegisterControl<WBtnProcess_t>	
		({	ID_BTN_PROCESS, ControlTypes::BUTTON,	0, 0, 0, "BUTTON", "Save Audio", WS_CHILD | WS_VISIBLE | BS_USERBUTTON,
		{85, 100, 150, 30} });
	window->RegisterControl<WProgressBar_t>
		({ ID_PB_PROGRESS, ControlTypes::PROGRESSBAR,	0, 0, 0, PROGRESS_CLASSA, "...", WS_CHILD | WS_VISIBLE,
		{85, 77, 300, 20} });
}