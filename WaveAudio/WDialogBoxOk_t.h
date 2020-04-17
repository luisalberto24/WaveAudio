#include "stdafx.h"

#pragma once

#if (!defined(_W_DIALOG_BOX_OK_T_))
#define	_W_DIALOG_BOX_OK_T_

class WDialogBoxOk_t : WDialog_t
{
	public:
		WDialogBoxOk_t();
		WDialogBoxOk_t(UINT dialogId);
		virtual	~WDialogBoxOk_t();
	public:
		virtual BOOL Show(std::wstring title, std::wstring text, UINT icon, HWND parentHandler);
		virtual BOOL Show(UINT dialogId, std::wstring title, std::wstring text, UINT icon, HWND parentHandler);
		virtual INT_PTR OnOk(UINT messageId, WPARAM wParam, LPARAM lParam);
};

#endif
