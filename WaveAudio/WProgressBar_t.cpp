#include "Window_t.h"
#include "WProgressBar_t.h"

WProgressBar_t::WProgressBar_t() 
{}

WProgressBar_t::WProgressBar_t(WControlAttributes_t attributes) : WControl_t(attributes)
{}

WProgressBar_t::~WProgressBar_t()
{
}

LRESULT	WProgressBar_t::OnCreate(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT	WProgressBar_t::OnPaint(HDC dcHandler, PAINTSTRUCT ps)
{
	return 0;
}

LRESULT	WProgressBar_t::OnCommand(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT WProgressBar_t::SetRange(DWORD minimumValue, DWORD maximumValue)
{
	this->minValue = minimumValue;
	this->maxValue = maximumValue;
	return ::SendMessageW(this->attributes.Handler, PBM_SETRANGE, 0, MAKELPARAM(this->minValue, this->maxValue));
}

UINT_PTR WProgressBar_t::GetPosition()
{
	return ::SendMessageW(this->attributes.Handler, PBM_GETPOS, 0, 0);
}

LRESULT WProgressBar_t::SetPosition(DWORD position)
{
	return ::SendMessageW(this->attributes.Handler, PBM_SETPOS, (WPARAM)position, 0);
}

LRESULT	WProgressBar_t::SetStep(DWORD step)
{
	return ::SendMessageW(this->attributes.Handler, PBM_SETSTEP, (WPARAM)step, 0);
}

LRESULT	WProgressBar_t::StepIt()
{
	return ::SendMessageW(this->attributes.Handler, PBM_STEPIT, 0, 0);
}

DWORD WProgressBar_t::GetMininumValue()
{
	return this->minValue;
}
DWORD WProgressBar_t::GetMaximunValue()
{
	return this->maxValue;
}