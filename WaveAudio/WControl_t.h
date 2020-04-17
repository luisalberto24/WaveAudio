#include "stdafx.h"
#include "IWControl_t.h"

#pragma once

#if (!defined(_W_CONTROL_T_H_))
#define	_W_CONTROL_T_H_

typedef struct tagWControlAttributes_t
{
	WORD ControlId;
	ControlTypes TypeId;
	HWND ParentHandler;
	HINSTANCE ModuleId;
	DWORD ExStyle;	
	char ClassName[MAX_CLASS_NAME_BUFFER_SIZE];
	char WindowName[MAX_WINDOW_NAME_BUFFER_SIZE];
	DWORD Style;
	RECT Coordinates;
	LPVOID Window;
	HWND Handler;
	BOOL Created;
} WControlAttributes_t, *WControlAttributesPtr_t;

class WControl_t : public IWControl_t
{			
	public:
		WControl_t();
		WControl_t(WControlAttributes_t attributes);
		virtual	~WControl_t();
	public:
		const LPVOID GetWindow();
		HWND GetControlHandler();
		RECT GetRectangle();
		VOID Invalidate(BOOL erase = TRUE);
		WORD GetControlId();
		WORD GetControlType();
		const WControlAttributes_t GetAttributes();
		VOID SetAttributes(WControlAttributes_t attributes);
		virtual LRESULT OnCreate(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnPaint(HDC dcHandler,	PAINTSTRUCT ps);
		virtual LRESULT OnColorChange(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnClick(WPARAM wParam,	LPARAM lParam);
		virtual LRESULT OnFocus(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnBlur(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnCommand(WPARAM wParam,	LPARAM lParam);
		virtual LRESULT SetRange(DWORD minValue, DWORD maxValue);
		virtual LRESULT SetPosition(DWORD position);
	public:
		LRESULT SendMsg(UINT messageId, WPARAM wParam, LPARAM lParam);
		DWORD GetTextLength();
		std::wstring GetText();
		VOID SetText(std::wstring text);
		VOID Enable();
		VOID Disable();
		VOID SetBuddy(HWND buddyHandler);
	protected:
		WControlAttributes_t attributes;
		LPVOID parentWindow;
};

#endif 

