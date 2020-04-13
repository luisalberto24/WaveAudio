#include "Window_t.h"
#include "WBtnProcess_t.h"
#include "WProgressBar_t.h"
#include "WaveAudio_t.h"

static VOID CALLBACK DoWhileRecording(VOID* pBar)
{
	WProgressBar_t* progressBar = static_cast<WProgressBar_t*>(pBar);
	if (progressBar->GetPosition() < progressBar->GetMaximunValue())
	{
		progressBar->StepIt();
	}
}

WBtnProcess_t::WBtnProcess_t(WControlAttributes_t& controlAttributes) : WControl_t(controlAttributes)
{
}

WBtnProcess_t::~WBtnProcess_t()
{
	WControl_t::~WControl_t();
}

LRESULT WBtnProcess_t::OnClick(WPARAM wParam, LPARAM lParam)
{
	Window_t* window = (Window_t*)this->GetWindow();
	WControl_t* directoryCtrl	= (WControl_t*)window->GetControl<ControlTypes::EDIT>(ID_EDIT_FOLDERNAME);
	WControl_t* fileNameCtrl	= (WControl_t*)window->GetControl<ControlTypes::EDIT>(ID_EDIT_FILENAME);
	if (directoryCtrl && fileNameCtrl)
	{
		HWND windowHandler = window->GetHandler();
		
		DWORD directoryNameLength = directoryCtrl->GetTextLength();
		DWORD fileNameLength = fileNameCtrl->GetTextLength();
		if (directoryNameLength > 0 && fileNameLength > 0)
		{
			wstring fileName = directoryCtrl->GetText().substr(0, directoryNameLength);
			fileName.append(L"\\");
			fileName.append(fileNameCtrl->GetText().substr(0, fileNameLength));

			WControl_t* editRecordTimeCtrl = (WControl_t*)window->GetControl<ControlTypes::EDIT>(ID_EDIT_RECORD_TIME);
			if (editRecordTimeCtrl)
			{
				this->Disable();
				try
				{
					DWORD recordTime = atoi(_bstr_t(editRecordTimeCtrl->GetText().c_str()));
					WProgressBar_t* progressBar = (WProgressBar_t*)window->GetControl<ControlTypes::PROGRESSBAR>(ID_PB_PROGRESS);
					progressBar->SetRange(1, recordTime);
					progressBar->SetStep(1);
					WaveAudio_t waveAudio(window);
					waveAudio.Record(recordTime, DoWhileRecording, (VOID*)progressBar);
					waveAudio.Save(fileName);

					MessageBoxW(windowHandler, fileName.c_str(), L"File saved!", MB_ICONINFORMATION | MB_OK);

					progressBar->SetRange(0, 0);
				}
				catch (...) {}

				this->Enable();
			}
		}
	}

	return 0;
}
