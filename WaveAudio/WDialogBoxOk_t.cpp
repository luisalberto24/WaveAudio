#include "WDialog_t.h"
#include "WDialogBoxOk_t.h"

WDialogBoxOk_t::WDialogBoxOk_t()
{

}

WDialogBoxOk_t::WDialogBoxOk_t(UINT dialogId)
{
	WDialog_t::WDialog_t();
	this->dialogId = dialogId;
	this->icon = NULL;
}

WDialogBoxOk_t::~WDialogBoxOk_t()
{
}

BOOL WDialogBoxOk_t::Show(std::wstring title, std::wstring text, UINT icon, HWND parentHandler)
{
	return WDialog_t::Show(title, text, icon, parentHandler);
}

BOOL WDialogBoxOk_t::Show(UINT dialogId, std::wstring title, std::wstring text, UINT icon, HWND parentHandler)
{
	return WDialog_t::Show(dialogId, title, text, icon, parentHandler);
}

INT_PTR WDialogBoxOk_t::OnOk(UINT messageId, WPARAM wParam, LPARAM lParam)
{
	this->OnEndDialog(messageId, wParam, lParam);

	return 0;
}

