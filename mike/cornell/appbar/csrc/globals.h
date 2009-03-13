// Global variables
#ifndef GLOBALS_H
#define GLOBALS_H

extern HWND ab_hwnd,					// appbar window handle
			EditDlg;					// Edit Menus HWND
extern ab_vars sys_vars;				// System variables
extern menu_struct *glob_menu;			// Applications linked list
extern user_options user_vars;			// User setup
extern WNDCLASS ab_wc;					// AppBar window class
extern HINSTANCE ab_inst;				// AppBar instance
extern HMENU ab_menu, popup;			// User menus and popup menu handles
extern menu_list *menulist;				// internal menulist
extern app_list *applist;				// internal applist
extern BOOL iserror;					// exiting because of fatal error?
extern HHOOK hook;						// stayontop hook
extern APPBARDATA abd;
extern BOOL IsShown;
extern char origdir[128];
#endif // globals_h
