#include "WLabel_t.h"

WLabel_t::WLabel_t(WControlAttributes_t controlAttributes) : WControl_t(controlAttributes)
{
}

WLabel_t::~WLabel_t()
{
	WControl_t::~WControl_t();
}

LRESULT	WLabel_t::OnPaint(HDC dcHandler, PAINTSTRUCT ps)
{
	SendMessage(this->attributes.Handler, WM_ENABLE, 0, 0);
	SendMessage(this->attributes.Handler, EM_SETREADONLY, 0, 0);
	
	return 0;
}

LRESULT	WLabel_t::OnColorChange(WPARAM wParam, LPARAM lParam)
{
	// transparent background
	return (LRESULT)GetStockObject(NULL_BRUSH);
}

LRESULT	WLabel_t::OnClick(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT	WLabel_t::OnCommand(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

