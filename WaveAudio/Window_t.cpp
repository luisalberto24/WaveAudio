#include <vector>
#include<iostream> 
#include <sstream>  // for string streams 
#include <string>  // for string 
#include "Window_t.h"

Window_t::Window_t()
{
	this->instance = NULL;
	this->windowclass = {};
	memset(
		this->controls,
		0,
		sizeof(WControl_t*) * MAX_CONTROLS_TYPES_PER_WINDOW * MAX_CONTROLS_PER_WINDOW);
}

Window_t::Window_t(HINSTANCE instance, std::wstring className, std::wstring windowName, std::wstring windowTitle)
{
	this->instance = instance;
	this->className = className;
	this->windowName = windowName;
	this->title = windowTitle;
	this->windowclass = {};
	memset(
		this->controls,
		0, 
		sizeof(WControl_t*) * MAX_CONTROLS_TYPES_PER_WINDOW * MAX_CONTROLS_PER_WINDOW);
}

Window_t::~Window_t()
{
	for (int controlType = 0; controlType < MAX_CONTROLS_TYPES_PER_WINDOW; controlType++)
	{
		for (int controlIndex = 0; controlIndex < MAX_CONTROLS_PER_WINDOW; controlIndex++)
		{
			if (this->controls[controlType][controlIndex])
			{
				if (this->controls[controlType][controlIndex])
				{
					delete this->controls[controlType][controlIndex];
					this->controls[controlType][controlIndex] = NULL;
				}
			}
		}
	}
}

const HINSTANCE Window_t::GetInstance()
{
	return static_cast<const HINSTANCE>(this->instance);
}

const HWND	Window_t::GetHandler()
{
	return this->handler;
}

WORD Window_t::RegisterWindow()
{
	this->windowclass.cbSize		=	sizeof(WNDCLASSEXW);
	this->windowclass.style			=	0;
	this->windowclass.lpfnWndProc	=	(WNDPROC)StaticWindowProcedure;
	this->windowclass.cbClsExtra	=	0;
	this->windowclass.cbWndExtra	=	0;
	this->windowclass.hInstance		=	this->instance;
	this->windowclass.hIcon			=	NULL;
	this->windowclass.hCursor		=	LoadCursor(NULL, IDC_ARROW);
	this->windowclass.hbrBackground	=	(HBRUSH)(COLOR_WINDOW + 1);
	this->windowclass.lpszMenuName	=	NULL;
	this->windowclass.lpszClassName	=	_bstr_t(this->className.c_str());
	this->windowclass.hIconSm	=	NULL;

	return RegisterClassExW(&this->windowclass);
}

BOOL Window_t::Show(int showCommand)
{
	if (!this->RegisterWindow())
	{
		return FALSE;
	}

	this->handler = CreateWindowExW(
		NULL,
		this->className.c_str(),
		NULL,
		WS_OVERLAPPEDWINDOW | WS_BORDER,
		CW_USEDEFAULT,
		0, 
		650, 
		200, 
		nullptr, 
		nullptr, 
		this->instance,
		(LPVOID)this);

	if (!this->handler)
	{
		return FALSE;
	}

	::ShowWindow(this->handler, showCommand);
	::UpdateWindow(this->handler);
	::SetWindowTextW(this->handler, this->title.c_str());
	
	this->SetStyleOff(WS_MAXIMIZEBOX | WS_SIZEBOX);

	return TRUE;
}

MSG	Window_t::Loop()
{
	MSG message;

	while (GetMessage(&message, nullptr, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
		
		if (this->windowMessageLoopProcedure != nullptr)
		{
			this->windowMessageLoopProcedure(message);
		}
	}

	return message;
}

const WControlsArray_t* Window_t::GetAllControls()
{
	return &this->controls;
}

std::wstring Window_t::GetLastErrorMessage()
{
	DWORD error = GetLastError();
	if (error)
	{
		LPVOID messageBuffer = NULL;
		DWORD bufferLength = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			error,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&messageBuffer,
			0,
			NULL);

		if (bufferLength > 0 && bufferLength <= MAX_ERROR_BUFFER_SIZE)
		{
			wostringstream  message;
			message << "Error code: ";
			message << error;
			message << ", Message: ";
			message << (LPCWSTR)messageBuffer;

			LocalFree(messageBuffer);

			return message.str();
		}
	}

	return std::wstring(L"");
}

VOID Window_t::GetLastErrorMessageBox(HWND windowHandler, std::wstring title)
{
	std::wstring errorMessage = Window_t::GetLastErrorMessage();
	if (errorMessage.length() > 0)
	{
		if (title.c_str() == NULL || title.length() == 0)
		{
			title = L"Error!";
		}

		MessageBoxW(windowHandler, errorMessage.c_str(), title.c_str(), MB_ICONERROR | MB_OK);
	}
}

VOID Window_t::SetWindowProcedure(const WNDPROC wndProcedure)
{
	this->exWindowProcedure = wndProcedure;
}

VOID Window_t::SetWindowMessageProcedure(const WNDMESSAGELOOPPROC wndMessageProcedure)
{
	this->windowMessageLoopProcedure = wndMessageProcedure;
}

inline ControlTypes	Window_t::GetControlType(DWORD controlId)
{
	return Window_t::GetControlType(this->handler, controlId);
}

inline ControlTypes	Window_t::GetControlType(HWND controlHandler)
{
	int controlId = GetDlgCtrlID(controlHandler);
	return Window_t::GetControlType(this->handler, controlId);
}

inline VOID Window_t::SetStyleOn(DWORD style)
{
	::SetWindowLongW(
		this->handler,
		GWL_STYLE,
		GetWindowLong(this->handler, GWL_STYLE) | style);
}

inline VOID Window_t::SetStyleOff(DWORD style)
{
	::SetWindowLongW(
		this->handler,
		GWL_STYLE,
		GetWindowLong(this->handler, GWL_STYLE) & ~style);
}

ControlTypes Window_t::GetControlType(HWND windowHandler, DWORD controlId)
{
	HWND controlHwnd = GetDlgItem(windowHandler, controlId);
	std::wstring controlType(MAX_BUFFER_SIZE, 0);
	GetClassNameW(controlHwnd, (LPWSTR)controlType.c_str(), MAX_BUFFER_SIZE);
	if (!controlType.empty())
	{
		Utilities::ToLower(controlType);
		LPCWSTR data = controlType.c_str();
		
		if (!lstrcmpW(data, L"edit")) return ControlTypes::EDIT;
		if (!lstrcmpW(data, L"button")) return ControlTypes::BUTTON;
		if (!lstrcmpW(data, L"static")) return ControlTypes::LABEL;
		if (!lstrcmpW(data, UPDOWN_CLASSW)) return ControlTypes::SPINNER;
		if (!lstrcmpW(data, PROGRESS_CLASSW)) return ControlTypes::PROGRESSBAR;
	}

	return ControlTypes::UNKNOWN;
}

template<typename T, typename ...Ts>
WControl_t* Window_t::GetControlInTypes(HWND controlHandler, T firstType, Ts... types)
{
	if (controlHandler)
	{
		WControl_t* control = this->GetControlInTypes(controlHandler, firstType);
		return control ? control : this->GetControlInTypes(controlHandler, types...);
	}
	
	return nullptr;
}

template<>
WControl_t* Window_t::GetControlInTypes(HWND controlHandler, ControlTypes cType)
{
	if (controlHandler)
	{
		int controlId = GetDlgCtrlID(controlHandler);
		ControlTypes controlType = Window_t::GetControlType(this->handler, controlId);
		if (cType == controlType)
		{
			DWORD controlIndex = GET_CTRL_TYPE_INDEX(controlId, controlType);
			if (controlIndex >= 0)
			{
				return this->controls[controlType - 1][controlIndex];
			}
		}
	}

	return nullptr;
}

template<typename T, typename ...Ts>
WControl_t* Window_t::GetControlOutOfTypes(HWND controlHandler, T firstType, Ts... types)
{
	if (controlHandler)
	{
		int controlId = GetDlgCtrlID(controlHandler);
		ControlTypes controlType = Window_t::GetControlType(this->handler, controlId);

		if (!Utilities::Find(controlType, firstType, types...))
		{
			DWORD controlIndex = GET_CTRL_TYPE_INDEX(controlId, controlType);
			if (controlIndex >= 0)
			{
				return this->controls[controlType - 1][controlIndex];
			}
		}
	}

	return nullptr;
}

static LRESULT CALLBACK StaticWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Window_t* window = nullptr;
	if (message != WM_CREATE)
	{
		window = (Window_t*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
	}

	switch (message)
	{
		case WM_CREATE:
			if (!ControlsListDrawn)
			{
				ControlsListDrawn = TRUE;
				HMODULE moduleId = GetModuleHandleW(NULL);
				Window_t* window = (Window_t*)(((LPCREATESTRUCT)lParam)->lpCreateParams); // Window_t type;
				SetWindowLongPtrW(hWnd, GWLP_USERDATA, (INT_PTR)window);
				const WControlsArray_t* controls = window->GetAllControls();
				for (int controlType = 0; controlType < MAX_CONTROLS_TYPES_PER_WINDOW; controlType++)
				{
					for (int controlIndex = 0; controlIndex < MAX_CONTROLS_PER_WINDOW; controlIndex++)
					{
						if ((*controls)[controlType][controlIndex])
						{
							WControl_t* control = (*controls)[controlType][controlIndex];
							WControlAttributes_t attr = control->GetAttributes();
							if (!attr.Created)
							{	attr.ParentHandler = hWnd;
								attr.ModuleId = moduleId;
								attr.Window = window;

								HWND handler = CreateWindowExW(
									attr.ExStyle,
									_bstr_t(attr.ClassName),
									_bstr_t(attr.WindowName),
									attr.Style,
									attr.Coordinates.left,
									attr.Coordinates.top,
									attr.Coordinates.right,
									attr.Coordinates.bottom,
									attr.ParentHandler,
									(HMENU)attr.ControlId,
									attr.ModuleId,
									NULL);

								attr.Handler = handler;
								attr.Created = TRUE;
								control->SetAttributes(attr);

								control->OnCreate(wParam, lParam);
							}
						}
					}
				}
			}

			return DefWindowProc(hWnd, message, wParam, lParam);

		case WM_COMMAND:
			{
				if (window->GetHandler())
				{
					BEGIN_VALIDATE_WINDOW_CONTROL_TYPE(hWnd, controlId, LOWORD(wParam))
						DWORD controlIndex = GET_CTRL_TYPE_INDEX(controlId, controType);
					if (controlIndex >= 0)
					{
						DWORD eventId = HIWORD(wParam);
						// DWORD MessageId = LOWORD(wParam);

						const WControlsArray_t* controls = window->GetAllControls();
						WControl_t* control = (*controls)[controType - 1][controlIndex];
						
						if (((HWND)lParam) && (eventId == BN_CLICKED))
						{
							return control->OnClick(wParam, lParam);
						}
						else if (eventId == EN_KILLFOCUS)
						{
							return control->OnBlur(wParam, lParam);
						}
						else if (eventId == EN_SETFOCUS)
						{
							return control->OnFocus(wParam, lParam);
						}

						return control->OnCommand(wParam, lParam);
					}
					END_VALIDATE_WINDOW_CONTROL_TYPE
				}

				return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_CTLCOLOREDIT:
			{
				WControl_t* control = window->GetControlInTypes(
					(HWND)lParam, ControlTypes::EDIT);
				if (control)
				{
					return control->OnColorChange(wParam, lParam);
				}
			}
			break;
		case WM_CTLCOLORSTATIC:
			{
				WControl_t* control = window->GetControlInTypes(
					(HWND)lParam, ControlTypes::LABEL, ControlTypes::EDIT);
				if (control)
				{
					return control->OnColorChange(wParam, lParam);
				}
			}
			break;
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				// TODO: Add any drawing code that uses hdc here...
				
				if (wParam > 0)
				{
					WControl_t* control = window->GetControlOutOfTypes((HWND)wParam, ControlTypes::UNKNOWN);
					if (control)
					{
						return control->OnPaint(hdc, ps);
					}
				}

				EndPaint(hWnd, &ps);
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
