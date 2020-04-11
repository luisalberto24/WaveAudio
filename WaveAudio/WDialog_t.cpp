#include "Window_t.h"
#include "resource.h"
#include "WDialog_t.h"

WDialog_t::WDialog_t()
{
	WDialog_t::WDialog_t(NULL);
}

WDialog_t::WDialog_t(UINT dialogId)
{
	this->dialogId = dialogId;
	this->icon = icon;
	this->handler = NULL;
	this->title = L"";
	this->text  = L"";
	this->icon = NULL;
}

WDialog_t::~WDialog_t()
{
}

BOOL WDialog_t::Show(std::wstring title, std::wstring text, UINT icon, HWND parentHandler)
{
	return this->Show(this->dialogId, title, text, this->icon, parentHandler);
}

BOOL WDialog_t::Show(UINT dialogId, std::wstring title, std::wstring text, UINT icon, HWND parentHandler)
{
	assert(dialogId);
	this->isOpen = FALSE;
	this->title = title;
	this->text = text;
	this->icon = icon;

	HWND hHandler = (HWND)::DialogBoxParamW(
		NULL, 
		(LPCWSTR)MAKEINTRESOURCE(dialogId), 
		parentHandler, 
		(DLGPROC)WDialog_t::DialogProcedure, 
		(LONG_PTR)this);

	if (!this->isOpen)
	{
		Window_t::GetLastErrorMessageBox(NULL, NULL);
			
		return FALSE;
	}
	
	this->isOpen = FALSE;

	return TRUE;
}

const HWND WDialog_t::GetHandler()
{
	return static_cast<const HWND>(this->handler);
}

VOID WDialog_t::Destroy()
{
	if (this->handler)
	{
		::DestroyWindow(this->handler);
		this->handler = NULL;
	}
}

INT_PTR WDialog_t::OnCreate(UINT messageId, WPARAM wParam, LPARAM lParam)
{
	RECT windowRect;
	GetWindowRect(this->parentHandler, &windowRect);
	if (this->title.length() > 0) SetWindowTextW(this->handler, this->title.c_str());
	
	return 1;
}

INT_PTR WDialog_t::OnOk(UINT messageId, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

INT_PTR WDialog_t::OnCancel(UINT messageId, WPARAM wParam, LPARAM lParam)
{
	this->OnEndDialog(messageId, wParam, lParam);
	return 0;
}

VOID WDialog_t::OnEndDialog(UINT messageId, WPARAM wParam, LPARAM lParam)
{
	WORD commandId = LOWORD(wParam);
	EndDialog(this->handler, commandId);
	this->Destroy();
}


INT_PTR WDialog_t::OnDialogProcedure(HWND dialogHandler, UINT messageId, WPARAM wParam, LPARAM lParam)
{
	switch (messageId)
	{
		case WM_INITDIALOG:
			return this->OnCreate(messageId, wParam, lParam);
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDOK:
					return this->OnOk(messageId, wParam, lParam);
				case IDCANCEL:
					return this->OnCancel(messageId, wParam, lParam);
				default:
					return DefWindowProc(dialogHandler, messageId, wParam, lParam);
			}
		}
	}

	return 0;
}

INT_PTR WDialog_t::DialogProcedure(HWND dialogHandler, UINT messageId, WPARAM wParam, LPARAM lParam)
{
	WDialog_t* dialog = NULL;
	if (messageId == WM_INITDIALOG)
	{		
		dialog = (WDialog_t*)lParam;
		assert(dialog);
		SetWindowLongPtrW(dialogHandler, GWLP_USERDATA, lParam);
		if (dialog)
		{
			dialog->handler = dialogHandler;
			dialog->isOpen = TRUE;
			dialog->parentHandler = GetParent(dialogHandler);
		}
	}
	else
	{
		dialog = (WDialog_t*)GetWindowLongPtrW(dialogHandler, GWLP_USERDATA);
	}
	
	return (dialog) ? dialog->OnDialogProcedure(dialogHandler, messageId, wParam, lParam) : 0;
}