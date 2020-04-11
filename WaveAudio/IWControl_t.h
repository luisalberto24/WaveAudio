#include "stdafx.h"

#pragma once

#if !defined(_IWCONTROL_T_H_)
#	define	_IWCONTROL_T_H_

class IWControl_t
{
	public:
		virtual LRESULT			OnCreate		(WPARAM wParam, LPARAM lParam) = 0;
		virtual LRESULT			OnPaint			(HDC dcHandler, PAINTSTRUCT ps) = 0;
		virtual LRESULT			OnColorChange	(WPARAM wParam, LPARAM lParam)	= 0;
		virtual LRESULT			OnClick			(WPARAM wParam, LPARAM lParam)	= 0;
		virtual LRESULT			OnFocus			(WPARAM wParam, LPARAM lParam) = 0;
		virtual LRESULT			OnBlur			(WPARAM wParam, LPARAM lParam) = 0;
		virtual LRESULT			OnCommand		(WPARAM wParam, LPARAM lParam) = 0;
};

#endif