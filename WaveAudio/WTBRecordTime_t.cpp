#include "Window_t.h"
#include "WTBRecordTime_t.h"

WTBRecordTime_t::WTBRecordTime_t()
{
}

WTBRecordTime_t::WTBRecordTime_t(WControlAttributes_t& attributes) : WTextBox_t::WTextBox_t(attributes)
{
}

WTBRecordTime_t::~WTBRecordTime_t() 
{
	WTextBox_t::WTextBox_t();
}

LRESULT	WTBRecordTime_t::OnCreate(WPARAM wParam, LPARAM lParam)
{
	::SendMessageW(this->attributes.Handler, WM_SETTEXT, 0, (LPARAM)L"10");

	return 0;
}

LRESULT	WTBRecordTime_t::OnPaint(HDC dcHandler, PAINTSTRUCT ps)
{
	return WTextBox_t::OnPaint(dcHandler, ps);
}

LRESULT	WTBRecordTime_t::OnColorChange(WPARAM wParam, LPARAM lParam)
{
	return WTextBox_t::OnColorChange(wParam, lParam);
}

LRESULT	WTBRecordTime_t::OnClick(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT	WTBRecordTime_t::OnBlur(WPARAM wParam, LPARAM lParam)
{
	std::wstring text = this->GetText();
	WORD value = atoi(_bstr_t(text.c_str()));

	if (value < 1)
	{
		this->SetText(L"1");
	}
	else if (value > 60)
	{
		this->SetText(L"60");
	}

	return 0;
}

LRESULT	WTBRecordTime_t::OnCommand(WPARAM wParam, LPARAM lParam)
{
	return 0;
}
