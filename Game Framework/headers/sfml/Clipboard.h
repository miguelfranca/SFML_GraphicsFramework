#pragma once
#include <windows.h>
#include <iostream>

namespace GF {
	struct Clipboard {
		// https://stackoverflow.com/questions/1264137/how-to-copy-string-to-clipboard-in-c
		static void setText(const char* str) {
			const size_t len = strlen(str) + 1;
			HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
			memcpy(GlobalLock(hMem), str, len);
			GlobalUnlock(hMem);
			OpenClipboard(0);
			EmptyClipboard();
			SetClipboardData(CF_TEXT, hMem);
			CloseClipboard();
		}

		// https://stackoverflow.com/questions/14762456/getclipboarddatacf-text
		static std::string getText()
		{
			// Try opening the clipboard
			if (!OpenClipboard(nullptr)) {
				std::cout << "couldnt open the clipboard" << std::endl;
				exit(0);
			}

			// Get handle of clipboard object for ANSI text
			HANDLE hData = GetClipboardData(CF_TEXT);
			if (hData == nullptr)
				std::cout << "error getting handle of clipboard object" << std::endl;

			// Lock the handle to get the actual text pointer
			char* pszText = static_cast<char*>(GlobalLock(hData));
			if (pszText == nullptr)
				std::cout << "error locking the handle" << std::endl;

			// Save text in a string class instance
			std::string text(pszText);

			// Release the lock
			GlobalUnlock(hData);

			// Release the clipboard
			CloseClipboard();

			return text;
		}
	};
}