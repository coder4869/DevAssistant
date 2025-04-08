// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "CETrayIcon.h"

#include <iostream>

#if WIN
#	include <windows.h>
#endif

NS_CE_BEGIN

void TrayIcon::SetIcon(int winid, const std::string& icon_name, const std::string& tips, unsigned long mode)
{
#if WIN
	NOTIFYICONDATA tray_icon;
	HWND hwnd = HWND(winid);
	CreateSemaphore(NULL, 1, 1, tips.c_str());
	if (mode == 0 && GetLastError() == ERROR_ALREADY_EXISTS) {
		//ShowWindow(hwnd, SW_HIDE);
		return;
	}

	memset(&tray_icon, 0, sizeof(NOTIFYICONDATA));
	tray_icon.cbSize = sizeof(NOTIFYICONDATA);
	//tray_icon.uID = icon_name.c_str();
	HINSTANCE hinst = (HINSTANCE)::GetModuleHandle(NULL);
	tray_icon.hIcon = ::LoadIcon(hinst, icon_name.c_str());
	tray_icon.hWnd = hwnd;
	lstrcpy(tray_icon.szTip, tips.c_str());
	tray_icon.uCallbackMessage = WM_TO_TRAY;
	tray_icon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		
	/// mode : 0-NIM_ADD, 1-NIM_MODIFY, 2-NIM_DELETE, 3-NIM_SETFOCUS, 4-NIM_SETVERSION
	if (mode == 0) {
		Shell_NotifyIcon(NIM_ADD, &tray_icon);
		//ShowWindow(hwnd, SW_HIDE);
	}
	else if (mode == 1) {
		Shell_NotifyIcon(NIM_MODIFY, &tray_icon);
		//ShowWindow(hwnd, SW_HIDE);
	}
	else if (mode == 2) {
		Shell_NotifyIcon(NIM_DELETE, &tray_icon);
		//ShowWindow(hwnd, SW_HIDE);
	}
	else if (mode == 3) {
		Shell_NotifyIcon(NIM_SETFOCUS, &tray_icon);
		//ShowWindow(hwnd, SW_SHOWNORMAL);
	}
	else if (mode == 4) {
		Shell_NotifyIcon(NIM_SETVERSION, &tray_icon);
		//ShowWindow(hwnd, SW_HIDE);
	}

#else

#endif // WIN
}

void TrayIcon::ShowWindow(int winid, bool show)
{
#if WIN
	ShowWindow(HWND(winid), show ? SW_SHOWNORMAL : SW_HIDE);
#else

#endif // WIN
}

void TrayIcon::DelIcon(int winid)
{
#if WIN
	NOTIFYICONDATA tray_icon;
	HWND hwnd = HWND(winid);
	memset(&tray_icon, 0, sizeof(NOTIFYICONDATA));
	tray_icon.hWnd = hwnd;
	Shell_NotifyIcon(NIM_DELETE, &tray_icon);
	ShowWindow(hwnd, SW_SHOWNORMAL);
#else

#endif // WIN
}

NS_CE_END
