#include "stdafx.h"
#include "WControl_t.h"

#pragma once

#if (!defined(_W_SPINNER_T_H_))
#	define	_W_SPINNER_T_H_

class WSpinner_t : public WControl_t
{
	public:
		WSpinner_t	();
		WSpinner_t	(WControlAttributes_t& attributes);
		~WSpinner_t	();
	public:
		virtual LRESULT	OnCreate		(WPARAM wParam, LPARAM lParam);
		virtual LRESULT	OnPaint			(HDC dcHandler, PAINTSTRUCT ps);
		virtual LRESULT	OnColorChange	(WPARAM wParam, LPARAM lParam);
		virtual LRESULT	OnClick			(WPARAM wParam, LPARAM lParam);
		virtual LRESULT	OnCommand		(WPARAM wParam, LPARAM lParam);
};

#endif

