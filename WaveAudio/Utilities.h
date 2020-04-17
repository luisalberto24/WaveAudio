#include "stdafx.h"

#pragma once

using namespace std;

#if (!defined(_UTILITIES_H_))
#define	_UTILITIES_H_

class Utilities
{
	public:
		static VOID ToUpper(std::wstring& value);
		static VOID ToLower(std::wstring& value);
		static BOOL	FileExists(const std::wstring& fileName);
		static std::wstring	GetFileDirectory(const std::wstring& fileName);
		static BOOL	DirectoryExists(const std::wstring& directoryName);
		static DWORD GetDialogFileName(std::wstring& filePath);
		static BOOL	GetDirectoryName(std::wstring& folder, std::wstring caption = NULL, HWND ownerHandler = NULL);
		template<typename T, typename... Ts>
		static BOOL Find(T a, Ts... arguments)
		{
			if (sizeof...(Ts) != 0)
			{
				T elements[] = { a, arguments... };
				DWORD i = 1;
				for (; i < sizeof...(Ts) + 1; i++) {
					if (elements[0] == elements[i])
					{
						break;
					}
				}

				return (i != (sizeof...(Ts) + 1)) ? TRUE : FALSE;
			}

			return TRUE;
		}
};

#endif