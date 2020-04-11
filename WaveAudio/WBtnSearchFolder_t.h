#include "stdafx.h"
#include "WControl_t.h"

#pragma once

#if (!defined(_W_BTN_SEARCH_FOLDER_T_H_))
#	define	_W_BTN_SEARCH_FOLDER_T_H_

class WBtnSearchFolder_t : public WControl_t
{
	public:
		WBtnSearchFolder_t	();
		WBtnSearchFolder_t	(WControlAttributes_t attributes);
		~WBtnSearchFolder_t	();
	public:
		virtual LRESULT	OnClick	(WPARAM wParam, LPARAM lParam);
};

#endif 

