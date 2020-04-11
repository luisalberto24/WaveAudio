#include "WTBFileName_t.h"

WTBFileName_t::WTBFileName_t() 
{
}

WTBFileName_t::WTBFileName_t(WControlAttributes_t attributes) : WTextBox_t(attributes)
{
}

WTBFileName_t::~WTBFileName_t()
{
	WTextBox_t::~WTextBox_t();
}

LRESULT	WTBFileName_t::WTBFileName_t::OnCreate(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT	WTBFileName_t::OnPaint(HDC dcHandler, PAINTSTRUCT ps)
{
	return WTextBox_t::OnPaint(dcHandler, ps);
}

LRESULT	WTBFileName_t::OnColorChange(WPARAM wParam, LPARAM lParam)
{
	return WTextBox_t::OnColorChange(wParam, lParam);
}

LRESULT	WTBFileName_t::OnClick(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT	WTBFileName_t::OnCommand(WPARAM wParam, LPARAM lParam)
{
	return 0;
}
