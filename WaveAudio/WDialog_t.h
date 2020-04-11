#include "stdafx.h"

#pragma once

#if !defined(_WDIALOG_T_H_)
#	define	_WDIALOG_T_H_

class WDialog_t
{
	public:
				WDialog_t	();
				WDialog_t	(UINT dialogId);
		virtual	~WDialog_t	();
	public:
		const	HWND			GetHandler			();
		virtual BOOL			Show				(std::wstring title, std::wstring text, UINT icon, HWND parentHandler);
		virtual BOOL			Show				(UINT dialogId, std::wstring title, std::wstring text, UINT icon, HWND parentHandler);
		virtual INT_PTR			OnCreate			(UINT messageId, WPARAM wParam, LPARAM lParam);
		virtual INT_PTR			OnOk				(UINT messageId, WPARAM wParam, LPARAM lParam);
		virtual INT_PTR			OnCancel			(UINT messageId, WPARAM wParam, LPARAM lParam);
		virtual VOID			OnEndDialog			(UINT messageId, WPARAM wParam, LPARAM lParam);
		virtual INT_PTR			OnDialogProcedure	(HWND dialogHandler, UINT messageId, WPARAM wParam, LPARAM lParam);
		VOID					Destroy				();
	public:
		static	INT_PTR			DialogProcedure		(HWND dialogHandler, UINT messageId, WPARAM wParam, LPARAM lParam);
	protected:
		HWND			handler;
		HWND			parentHandler;
		BOOL			isOpen;
		UINT			dialogId;
		std::wstring	title;
		std::wstring	text;
		UINT			icon;
};

#endif 
