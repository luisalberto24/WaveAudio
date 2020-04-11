#include "WTextBox_t.h"

WTextBox_t::WTextBox_t() : WControl_t()
{
}

WTextBox_t::WTextBox_t(WControlAttributes_t controlAttributes) : WControl_t(controlAttributes)
{
}

WTextBox_t::~WTextBox_t() 
{
	WControl_t::~WControl_t();
}

LRESULT WTextBox_t::OnCreate(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT WTextBox_t::OnPaint(HDC dcHandler, PAINTSTRUCT ps)
{
	HFONT DeafultFont = CreateFontW(-11, 0, 0, 0, FW_NORMAL, false, false, false, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, L"Microsoft Sans Serif");
	SendMessage((HWND)this->attributes.ControlId, WM_SETFONT, (WPARAM)DeafultFont, MAKELPARAM(true, 0));
	return 0;
}

LRESULT WTextBox_t::OnColorChange(WPARAM wParam, LPARAM lParam)
{
	HDC hdc = (HDC)wParam; 
	HBRUSH solidBrush = CreateSolidBrush(RGB(213, 234, 236));
	COLORREF color = (LONG)GetDCBrushColor(hdc);
	SetBkMode(hdc, TRANSPARENT); 
	HBRUSH hbrushborder = CreateSolidBrush(RGB(125, 236, 200));
	FrameRect(hdc, &this->attributes.Coordinates, hbrushborder);
	OffsetRect(
		&this->attributes.Coordinates, 
		-this->attributes.Coordinates.top, 
		-this->attributes.Coordinates.left);

	return (LRESULT)solidBrush; 
}

LRESULT WTextBox_t::OnClick(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT WTextBox_t::OnCommand(WPARAM wParam, LPARAM lParam)
{

	return 0;
}
