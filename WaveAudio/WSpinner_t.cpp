#include "Window_t.h"
#include "WSpinner_t.h"

WSpinner_t::WSpinner_t() : WControl_t::WControl_t() 
{}

WSpinner_t::WSpinner_t(WControlAttributes_t& attributes) : WControl_t::WControl_t(attributes)
{}

WSpinner_t::~WSpinner_t()
{
}

LRESULT	WSpinner_t::OnCreate(WPARAM wParam, LPARAM lParam)
{
	Window_t* window = (Window_t*)this->GetWindow();
	WControl_t* editRecortTimeCtrl = (WControl_t*)window->GetControl(ID_EDIT_RECORD_TIME, ControlTypes::EDIT);
	if (editRecortTimeCtrl)
	{
		HWND handler = editRecortTimeCtrl->GetControlHandler();
		this->SetBuddy(handler);
		this->SetRange(1, 60);
		this->SetPosition(1);
	}

	return 0;
}
LRESULT	WSpinner_t::OnPaint(HDC dcHandler, PAINTSTRUCT ps)
{
	return WControl_t::OnPaint(dcHandler, ps);
}

LRESULT	WSpinner_t::OnColorChange(WPARAM wParam, LPARAM lParam)
{
	return WControl_t::OnColorChange(wParam, lParam);
}

LRESULT	WSpinner_t::OnClick(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT	WSpinner_t::OnCommand(WPARAM wParam, LPARAM lParam)
{
	return 0;
}
