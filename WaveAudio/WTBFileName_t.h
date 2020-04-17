#include "stdafx.h"
#include "WTextBox_t.h"

#pragma once

#if (!defined(_W_TBFILENAME_T_H_))
#define	_W_TBFILENAME_T_H_

class WTBFileName_t : public WTextBox_t
{
	public:
		WTBFileName_t();
		WTBFileName_t(WControlAttributes_t attributes);
		~WTBFileName_t();
	public:
		virtual LRESULT	OnCreate(WPARAM wParam, LPARAM lParam);
		virtual LRESULT	OnPaint(HDC dcHandler, PAINTSTRUCT ps);
		virtual LRESULT	OnColorChange(WPARAM wParam, LPARAM lParam);
		virtual LRESULT	OnClick(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnCommand(WPARAM wParam, LPARAM lParam);
};

#endif