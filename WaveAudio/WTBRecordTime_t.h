#include "stdafx.h"
#include "WTextBox_t.h"

#pragma once

#if (!defined(_W_TB_RECORD_TIME_T_H_))
#	define	_W_TB_RECORD_TIME_T_H_

class WTBRecordTime_t : public WTextBox_t
{
	public:
		WTBRecordTime_t		();
		WTBRecordTime_t		(WControlAttributes_t& attributes);
		~WTBRecordTime_t	();
	public:
		virtual LRESULT	OnCreate			(WPARAM wParam, LPARAM lParam);
		virtual LRESULT	OnPaint				(HDC dcHandler, PAINTSTRUCT ps);
		virtual LRESULT	OnColorChange		(WPARAM wParam, LPARAM lParam);
		virtual LRESULT	OnClick				(WPARAM wParam, LPARAM lParam);
		virtual LRESULT	OnBlur				(WPARAM wParam, LPARAM lParam);
		virtual LRESULT	OnCommand			(WPARAM wParam, LPARAM lParam);
};

#endif

