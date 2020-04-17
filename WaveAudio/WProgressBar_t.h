#include "stdafx.h"
#include "WControl_t.h"

#pragma once

#if (!defined(_W_PROGRESS_BAR_T_H_))
#define	_W_PROGRESS_BAR_T_H_

class WProgressBar_t : public WControl_t
{
	public:
		WProgressBar_t();
		WProgressBar_t(WControlAttributes_t attributes);
		virtual	~WProgressBar_t();
	public:
		virtual LRESULT OnCreate(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnPaint(HDC dcHandler, PAINTSTRUCT ps);
		virtual LRESULT OnCommand(WPARAM wParam, LPARAM lParam);
	public:
		virtual LRESULT SetRange(DWORD minValue, DWORD maxValue);
		virtual UINT_PTR GetPosition();
		virtual LRESULT SetPosition(DWORD position);
		LRESULT SetStep(DWORD step);
		LRESULT StepIt(); 
		DWORD GetMininumValue();
		DWORD GetMaximunValue();
	protected:
		DWORD minValue;
		DWORD maxValue;
};

#endif

