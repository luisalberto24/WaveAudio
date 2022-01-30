#include "Window_t.h"
#include "WControl_t.h"

WControl_t::WControl_t()
{
}

WControl_t::WControl_t(WControlAttributes_t controlAttributes)
{
	this->SetAttributes(controlAttributes);
}

WControl_t::~WControl_t()
{
}

const LPVOID WControl_t::GetWindow()
{
	return (const LPVOID)this->attributes.Window;
}

HWND WControl_t::GetControlHandler()
{
	return this->attributes.Handler;
}

RECT WControl_t::GetRectangle()
{
	RECT rectangle;
	GetWindowRect(this->attributes.Handler, &rectangle);
	
	return rectangle;
}

VOID WControl_t::Invalidate(BOOL erase)
{
	RECT rectangle = this->GetRectangle();
	InvalidateRect(this->attributes.Handler, &rectangle, erase);
}

WORD WControl_t::GetControlId()
{
	return this->attributes.ControlId;
}

WORD WControl_t::GetControlType()
{
	return static_cast<WORD>(this->attributes.TypeId);
}

const WControlAttributes_t WControl_t::GetAttributes()
{
	return this->attributes;
}

void WControl_t::SetAttributes(WControlAttributes_t attributes)
{
	this->attributes = { 0 };
	this->attributes.ControlId = attributes.ControlId;
	this->attributes.Handler = attributes.Handler;
	this->attributes.TypeId = attributes.TypeId;
	this->attributes.ParentHandler = attributes.ParentHandler;
	this->attributes.ModuleId = attributes.ModuleId;
	this->attributes.ExStyle = attributes.ExStyle;
	this->attributes.Style = attributes.Style;
	this->attributes.Coordinates = attributes.Coordinates;
	this->attributes.Window = attributes.Window;
	this->attributes.Created = attributes.Created;

	memcpy(this->attributes.ClassName, attributes.ClassName,
		sizeof(attributes.ClassName) / sizeof(attributes.ClassName[0]));
	memcpy(this->attributes.WindowName, attributes.WindowName,
		sizeof(attributes.WindowName) / sizeof(attributes.WindowName[0]));
}

LRESULT	WControl_t::OnCreate(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT WControl_t::OnPaint(HDC dcHandler, PAINTSTRUCT ps)
{
	return 0;
}

LRESULT WControl_t::OnColorChange(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT WControl_t::OnClick(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT	WControl_t::OnFocus(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT	WControl_t::OnBlur(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT WControl_t::OnCommand(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT WControl_t::SendMsg(UINT messageId, WPARAM wParam, LPARAM lParam)
{
	return ::SendMessageW(this->attributes.Handler, messageId, wParam, lParam);
}

DWORD WControl_t::GetTextLength()
{
	return GetWindowTextLengthW(this->attributes.Handler);
}

std::wstring WControl_t::GetText()
{
	DWORD len = GetWindowTextLengthW(this->attributes.Handler);
	std::wstring text = new wchar_t[len + 1];
	text[len] = NULL;
	
	::GetWindowTextW(
		this->attributes.Handler, 
		(LPWSTR)text.c_str(), 
		this->GetTextLength()+1);

	return text;
}

VOID WControl_t::SetText(std::wstring text)
{
	SetWindowTextW(this->attributes.Handler, text.c_str());
}

VOID WControl_t::Enable()
{
	EnableWindow(this->attributes.Handler, TRUE);
}

VOID WControl_t::Disable()
{
	EnableWindow(this->attributes.Handler, FALSE);
}

VOID WControl_t::SetBuddy(HWND buddyHandler)
{
	if (buddyHandler)
	{
		::SendMessageW(this->attributes.Handler, UDM_SETBUDDY, (WPARAM)buddyHandler, NULL);
	}
}

LRESULT WControl_t::SetRange(DWORD minValue, DWORD maxValue)
{
	return ::SendMessageW(this->attributes.Handler, UDM_SETRANGE, 0, MAKELPARAM(maxValue, minValue));
}

LRESULT WControl_t::SetPosition(DWORD position)
{
	return ::SendMessageW(this->attributes.Handler, UDM_SETBASE, (LPARAM)position, 0);
}
