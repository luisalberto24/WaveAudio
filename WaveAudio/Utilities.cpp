#include "Utilities.h"
#include <Vector>

VOID Utilities::ToUpper(std::wstring& value)
{
	for (size_t x = 0; x < value.length(); x++)
	{
		value[x] = ::toupper(value[x]);
	}
}

VOID Utilities::ToLower(std::wstring& value)
{
	for (size_t x = 0; x < value.length(); x++)
	{
		value[x] = ::tolower(value[x]);
	}
}

BOOL Utilities::FileExists(const std::wstring& fileName)
{
	FILE *file;

	if (!fopen_s(&file, _bstr_t(fileName.c_str()), "r") && file)
	{
		fclose(file);
		return TRUE;
	}

	return FALSE;
}

std::wstring Utilities::GetFileDirectory(const std::wstring& fileName)
{
	size_t pos = fileName.find_last_of(L"\\");
	if (pos != std::wstring::npos)
	{
		return fileName.substr(0, pos);
	}

	return L"";
}

BOOL Utilities::DirectoryExists(const std::wstring& directoryName)
{
	DWORD ftyp = GetFileAttributesW(directoryName.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return FALSE;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return TRUE;   // this is a directory!

	return FALSE;    // this is not a directory!
}

DWORD Utilities::GetDialogFileName(std::wstring& filePath)
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileOpenDialog *fileOpenPtr;
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&fileOpenPtr));

		if (SUCCEEDED(hr))
		{
			// Show the Open dialog box.
			hr = fileOpenPtr->Show(NULL);

			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem *ItemPtr;
				hr = fileOpenPtr->GetResult(&ItemPtr);
				if (SUCCEEDED(hr))
				{
					PWSTR path;
					hr = ItemPtr->GetDisplayName(SIGDN_FILESYSPATH, &path);
					if (SUCCEEDED(hr))
					{
						filePath = _bstr_t(path);
						CoTaskMemFree(path);
					}

					ItemPtr->Release();
				}
			}

			fileOpenPtr->Release();
		}

		CoUninitialize();
	}

	return 0;
}

BOOL Utilities::GetDirectoryName(std::wstring& folder, std::wstring caption, HWND ownerHandler)
{
	BOOL result = FALSE;

	BROWSEINFO browseInfo;
	memset(&browseInfo, 0, sizeof(browseInfo));

	browseInfo.ulFlags = BIF_USENEWUI;
	browseInfo.hwndOwner = ownerHandler;
	
	if (!caption.length())
	{
		caption = L"Get Folder Name";
	}

	browseInfo.lpszTitle = _bstr_t(caption.c_str());

	::OleInitialize(NULL);

	LPITEMIDLIST itemIdListPtr = ::SHBrowseForFolder(&browseInfo);
	if (itemIdListPtr != NULL)
	{
		wstring buffer = new wchar_t[_MAX_PATH + 1];
		buffer[_MAX_PATH] = '\x0';
		if (::SHGetPathFromIDListEx(itemIdListPtr, (LPWSTR)buffer.c_str(), _MAX_PATH, GPFIDL_DEFAULT) != 0)
		{
			folder = buffer;
			result = TRUE;
		}

		CoTaskMemFree(itemIdListPtr);
	}

	::OleUninitialize();

	return result;
}
