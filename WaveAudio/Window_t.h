#include "stdafx.h"
#include "Utilities.h"
#include "WControl_t.h"
#include "WDialog_t.h"
#include "WDialogBoxOk_t.h"

using namespace std;
#pragma once

#if !defined(_WINDOW_T_H_)
#	define	_WINDOW_T_H_

static unique_ptr<WDialogBoxOk_t>	WMessageBox = make_unique<WDialogBoxOk_t>	(IDD_DLG_MSGBOX_OK);
static BOOL							ControlsListDrawn;
static LRESULT CALLBACK				StaticWindowProcedure						(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

typedef VOID						(CALLBACK* WNDMESSAGELOOPPROC)				(MSG message);
typedef WControl_t*					WControlsArray_t							[MAX_CONTROLS_TYPES_PER_WINDOW][MAX_CONTROLS_PER_WINDOW];

class Window_t
{
	public:
		Window_t	();
		Window_t	(HINSTANCE instance, std::wstring className, std::wstring windowName, std::wstring windowTitle);
		~Window_t	();
	public:
		const HINSTANCE											GetInstance	();
		const HWND												GetHandler	();
	
	public:
		BOOL						Show						(int showCommand);
		MSG							Loop						();
		const	WControlsArray_t*	GetAllControls				();
		VOID						SetWindowProcedure			(const WNDPROC wndProcedure);	
		VOID						SetWindowMessageProcedure	(const WNDMESSAGELOOPPROC wndMessageProcedure);
		inline ControlTypes			GetControlType				(DWORD controlId);
		inline ControlTypes			GetControlType				(HWND controlHandler);
		inline VOID 				SetStyleOn					(DWORD style);
		inline VOID 				SetStyleOff					(DWORD style);
	public: // templates			
		template<typename T>
		VOID						RegisterControl				(WControlAttributes_t controlAttributes)
		{
			assert(VALIDATE_CTRL_TYPE(controlAttributes.ControlId, controlAttributes.TypeId));
			DWORD controlIndex = GET_CTRL_TYPE_INDEX(controlAttributes.ControlId, controlAttributes.TypeId);
			controlAttributes.Window = (VOID*)this;
			this->controls[controlAttributes.TypeId - 1][controlIndex] = new T(controlAttributes);
		}
		
		template<ControlTypes typeId>
		const	WControl_t*			GetControl					(WORD controlId)
		{
			DWORD controlIndex = GET_CTRL_TYPE_INDEX(controlId, typeId);
			return controlIndex >= 0 ? this->controls[(typeId - 1)][controlIndex] : nullptr;
		}

		template<typename T, typename ...Ts>
		WControl_t*					GetControlInTypes			(HWND controlHandler, T firstType, Ts... types);

		template<typename T, typename ...Ts>
		WControl_t*					GetControlOutOfTypes		(HWND controlHandler, T firstType, Ts... types);
	public:
		static	ControlTypes		GetControlType				(HWND windowHandler, DWORD controlId);
		static	std::wstring		GetLastErrorMessage			();
		static	VOID				GetLastErrorMessageBox		(HWND windowHandler, std::wstring title);
	private:
		WORD						RegisterWindow				();
	private:
		WControlsArray_t	controls;
	protected:
		HINSTANCE			instance;
		HWND				handler;
		std::wstring		className;
		std::wstring		windowName;
		std::wstring		title;
		WNDPROC				exWindowProcedure;
		WNDMESSAGELOOPPROC	windowMessageLoopProcedure;
		WNDCLASSEXW			windowclass;
		
};
#endif
