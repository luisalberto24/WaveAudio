#include "WTBFolder_t.h"

WTBFolder_t::WTBFolder_t() :WTextBox_t()
{
}

WTBFolder_t::WTBFolder_t(WControlAttributes_t attributes) : WTextBox_t(attributes)
{
}

WTBFolder_t::~WTBFolder_t()
{
	WTextBox_t::~WTextBox_t();
}

LRESULT	WTBFolder_t::OnCreate(WPARAM wParam, LPARAM lParam)
{
	this->Disable();
	return 0;
}

LRESULT	WTBFolder_t::OnPaint(HDC dcHandler, PAINTSTRUCT ps)
{
	return WTextBox_t::OnPaint(dcHandler, ps);
}

LRESULT	WTBFolder_t::OnColorChange(WPARAM wParam, LPARAM lParam)
{
	return WTextBox_t::OnColorChange(wParam, lParam);
}

LRESULT	WTBFolder_t::OnClick(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT	WTBFolder_t::OnCommand(WPARAM wParam, LPARAM lParam)
{
	return WControl_t::OnCommand(wParam, lParam);
}

