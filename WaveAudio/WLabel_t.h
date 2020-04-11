#include "stdafx.h"
#include "WControl_t.h"

#pragma once

#if (!defined(_W_LABEL_T_H_))
#	define	_W_LABEL_T_H_

class WLabel_t : public WControl_t
{
	public:
		WLabel_t	(WControlAttributes_t attributes);
		~WLabel_t	();
	public:
		virtual LRESULT	OnPaint			(HDC dcHandler, PAINTSTRUCT ps);
		virtual LRESULT	OnColorChange	(WPARAM wParam, LPARAM lParam);
		virtual LRESULT	OnClick			(WPARAM wParam, LPARAM lParam);
		virtual LRESULT	OnCommand		(WPARAM wParam, LPARAM lParam);

};

#endif
