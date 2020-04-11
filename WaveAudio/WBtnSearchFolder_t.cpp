#include "Window_t.h"
#include "WBtnSearchFolder_t.h"

WBtnSearchFolder_t::WBtnSearchFolder_t()
{
}

WBtnSearchFolder_t::WBtnSearchFolder_t(WControlAttributes_t attributes) : WControl_t(attributes)
{
}
WBtnSearchFolder_t::~WBtnSearchFolder_t()
{
	WControl_t::~WControl_t();
}

LRESULT	WBtnSearchFolder_t::OnClick(WPARAM wParam, LPARAM lParam)
{
	Window_t* window = (Window_t*)this->GetWindow();
	WControl_t* control = (WControl_t*)window->GetControl(ID_EDIT_FOLDERNAME, ControlTypes::EDIT);
	if (control)
	{
		HWND windowHandler = window->GetHandler();
		std::wstring folderName;
		Utilities::GetDirectoryName(folderName, L"Get Folder Name", windowHandler);
		if (folderName.length() > 0)
		{
			control->SetText(folderName);
		}
	}

	return 0;
}

