#include "stdafx.h"
#include "WControl_t.h"

#pragma once

#if (!defined(_W_BTN_PROCESS_T_H_))
#define	_W_BTN_PROCESS_T_H_

class WBtnProcess_t : public WControl_t
{
	public:
		WBtnProcess_t(WControlAttributes_t& attributes);
		~WBtnProcess_t();
	public:
		virtual LRESULT	OnClick(WPARAM wParam, LPARAM lParam);
};

#endif 