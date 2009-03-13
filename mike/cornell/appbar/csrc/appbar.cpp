// *********************************************************
// AppBar -- Advanced Menu bar for Windows 95/NT
// All code Copyright (C) 1995, 1996 by Mike Perham
// mperham@cs.cornell.edu
// 
// This code MAY NOT be used for any other program without
// my permission and is forbidden in any shareware/commercial
// program.  This code is provided for educational use only
// and there are no guarantees or promises implied.  Blah blah
// *********************************************************
// Notes:
//
//  The AppBar interface in Win95 is a bit quirky.  If you
//  register an AppBar, the system reserves desktop space for
//  the window.  If the window is autohide though, the space
//  is still reserved and you get a hole where no windows can
//  go.  To work around this, you need to unregister the AppBar
//  or set its RECT to {0,0,0,0} (which is what I do).
//
//  The menus are stored in a doubly-linked list pointed to by
//  glob_menu.  The structure looks (to me) just like the UI i.e.
//
//  --->menu--->menu--->menu-->NULL
//      |        |
//     app      app     etc...
//      |        |
//     app      app
//
// Set tabstops to 4
//

#include "appbar.h"
#include "globals.h"

// AppBar global variables

HWND ab_hwnd,                   // appbar window handle
	 EditDlg;                   // edit dlg handle
ab_vars sys_vars;               // System variables
menu_struct *glob_menu;         // Menus/Applications linked list
user_options user_vars;         // User options
WNDCLASS ab_wc;                 // window class
HINSTANCE ab_inst;              // instance
HMENU ab_menu, popup;           // menu handles
app_list *applist;              // internal applist
BOOL iserror = FALSE,           // error exit?
	 IsShown = TRUE;            // AB not autohidden at the moment?
APPBARDATA abd;                 // structure for registering autohide bars with system
char origdir[PATH_SIZE];        // dir of AppBar

// Program entry point and main loop

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmdline, int cmdshow)
{
	MSG msg;

	ab_inst = hInst;
	if (!init_app())                        // Read in Registry settings and command line
		return FALSE;
	if (!setup_win())                       // Create and set up window
		return FALSE; 

	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

// Main Message loop for AppBar

LRESULT CALLBACK AppBarWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{   
	app_struct *find;
	static UINT timer = 0;
	ATOM adam;

	switch (msg) {
		case WM_TIMECHANGE:
			modify_time();
			return DefWindowProc(hWnd, msg, wParam, lParam);
		case WM_WINDOWPOSCHANGED:
			if (sys_vars.newshell) {
				abd.cbSize = sizeof(APPBARDATA);
				abd.hWnd = ab_hwnd;
				SHAppBarMessage(ABM_WINDOWPOSCHANGED, &abd);
			}
			return DefWindowProc(hWnd, msg, wParam, lParam);
		case WM_DISPLAYCHANGE:
			sys_vars.width = GetSystemMetrics(SM_CXSCREEN);
			sys_vars.height = GetSystemMetrics(SM_CYSCREEN);
			MoveWindow(ab_hwnd, 0, (user_vars.bottom ? sys_vars.height - AB_HEIGHT : 0),
						AB_WIDTH, AB_HEIGHT, TRUE);
			return DefWindowProc(hWnd, msg, wParam, lParam);
		case WM_POWERBROADCAST:
			if (sys_vars.power) {
				SYSTEM_POWER_STATUS sps;
				GetSystemPowerStatus(&sps);
				sys_vars.battery = (sps.ACLineStatus ? FALSE : TRUE);
				modify_time();
			}
			return DefWindowProc(hWnd, msg, wParam, lParam);
		case WM_HOTKEY:
			HideAppBar(FALSE);
			SetForegroundWindow(ab_hwnd);
			// this is the code for pressing the Alt key down
			// so we can make the menu highlight
			PostMessage(ab_hwnd, WM_SYSKEYDOWN, VK_MENU,
						(((0x00000001 | 38<<16) | 1<<24) | 1<<29));
			PostMessage(ab_hwnd, WM_SYSKEYUP, VK_MENU, 
						(((0x00000001 | 38<<16) | 1<<30) | 1<<31));
			return TRUE;
		case WM_NCRBUTTONDOWN:
			POINTS pts;
			pts = MAKEPOINTS(lParam);
			TrackPopupMenu(popup, 0, pts.x, pts.y, 0, ab_hwnd, NULL);
			return DefWindowProc(hWnd, msg, wParam, lParam);
		case WM_SHOWWINDOW:
			if (!RegisterHotKey(ab_hwnd, GlobalAddAtom("AppBar HotKey"), MOD_ALT | MOD_CONTROL, 0x5A /*z*/))
				if (!RegisterHotKey(ab_hwnd, GlobalAddAtom("AppBar HotKey"), MOD_ALT | MOD_CONTROL, 0x41 /*a*/))
					ab_message(ERROR_HOTKEY);
			IsShown = TRUE;
			SyncTime();
			return DefWindowProc(hWnd, msg, wParam, lParam);
		case WM_TIMER:
			if (wParam == TIME_UPDATE)
				modify_time();
			  else if (wParam == HIDE_TIMER) {
				if (user_vars.autohide)
					if (GetActiveWindow() != ab_hwnd) {
						POINT pt;
						GetCursorPos(&pt);
						if (WindowFromPoint(pt) != ab_hwnd) {
							KillTimer(ab_hwnd, HIDE_TIMER);
							timer = 0;
							HideAppBar(TRUE);
						}
					}
			  } else if (wParam == SYNC_TIMER) {
				  KillTimer(ab_hwnd, HIDE_TIMER);
				  KillTimer(ab_hwnd, SYNC_TIMER);
				  SetTimer(ab_hwnd, TIME_UPDATE, 10000, NULL);
				  modify_time();
			}
			return 0;
		case WM_ACTIVATE:
			if ((LOWORD(wParam) == WA_INACTIVE) && user_vars.autohide) {
				HideAppBar(TRUE);
				KillTimer(ab_hwnd, HIDE_TIMER);
			}
			if (sys_vars.newshell) {
				abd.cbSize = sizeof(APPBARDATA);
				abd.hWnd = ab_hwnd;
				SHAppBarMessage(ABM_ACTIVATE, &abd);
			}
			return DefWindowProc(hWnd, msg, wParam, lParam);
		case WM_NCMOUSEMOVE:
			if (user_vars.autohide)
				if (!IsShown) {
					POINT pt;
					GetCursorPos(&pt);
				// Don't show AppBar if the mouse moves in the right 10% of the screen
				// this is so using the max/min buttons doesn't accidently uncover
				// AppBar.
					if (pt.x < (sys_vars.width - (int)(sys_vars.width/10)))
						HideAppBar(FALSE);
					timer = SetTimer(ab_hwnd, HIDE_TIMER, 500, NULL);
				  } else {
					if (timer)
						KillTimer(ab_hwnd, HIDE_TIMER);
					timer = SetTimer(ab_hwnd, HIDE_TIMER, 500, NULL);
				}
			return 0;
		case WM_CLOSE:
		case WM_QUIT:
//        case WM_NCLBUTTONDBLCLK:
			adam = GlobalFindAtom("AppBar HotKey");
			UnregisterHotKey(ab_hwnd, adam);
			GlobalDeleteAtom(adam);
			exit_appbar(FALSE);
			PostQuitMessage(0);
			return 0;
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
/*              case ID_RUN:
					DialogBox(ab_inst, MAKEINTRESOURCE(IDD_RUN), ab_hwnd, (DLGPROC)RunProc);
					return 0; */
				case ID_EDIT:
					DialogBox(ab_inst, MAKEINTRESOURCE(IDD_EDIT), ab_hwnd, (DLGPROC)EditProc);
					return 0;
				case ID_ABOUT:
					DialogBox(ab_inst, MAKEINTRESOURCE(IDD_ABOUT), ab_hwnd, (DLGPROC)AboutProc);
					return 0;
				case ID_OPTIONS:
					DialogBox(ab_inst, MAKEINTRESOURCE(IDD_OPTIONS), ab_hwnd,(DLGPROC)OptionsProc);
					return 0;
				case ID_EXITAPPBAR:
					adam = GlobalFindAtom("AppBar HotKey");
					UnregisterHotKey(ab_hwnd, adam);
					GlobalDeleteAtom(adam);
					exit_appbar(FALSE);
					PostQuitMessage(0);
					return 0;
				default:
					find = find_appId((UINT)LOWORD(wParam));
					if (!find) return 0;
					execute_application(find);
					return 0;
			}
/*      case WM_APPBAR:
			if ((wParam == ABN_FULLSCREENAPP) && user_vars.stayontop)
				SetWindowPos(ab_hwnd, (!lParam ? HWND_TOPMOST : HWND_NOTOPMOST),
								0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
			return 0; */
		default:            
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

// Returns app structure associated with a given menu ID

app_struct * find_appId(WPARAM menuId)
{
	app_list * temp;

	temp = applist;
	while (temp->appId != (int)menuId) {
		temp = temp->next;
		if (temp == NULL)
			return NULL;
	}
	return temp->app;
}

// create and show the appbar window

BOOL show_appbar(void)
{
	int flags = (user_vars.stayontop ? WS_EX_TOPMOST : 0) | WS_EX_TOOLWINDOW;
	ab_hwnd = CreateWindowEx(flags,"ABClass", "AppBar", WS_POPUP | WS_DLGFRAME, 0, 
				(user_vars.bottom ? sys_vars.height - AB_HEIGHT : 0),
				AB_WIDTH, AB_HEIGHT, 0, 0, ab_inst, 0);

	if (!ab_hwnd)
		return FALSE;
	
	if (sys_vars.newshell) {
		BOOL ab;
		abd.cbSize = sizeof(APPBARDATA);
		abd.hWnd = ab_hwnd;
		abd.uCallbackMessage = NULL; //WM_APPBAR;
		abd.uEdge = (user_vars.bottom ? ABE_BOTTOM : ABE_TOP);
		ab = SHAppBarMessage(ABM_NEW, &abd);
		if (ab && user_vars.autohide) {
			abd.lParam = TRUE;
			if (!SHAppBarMessage(ABM_SETAUTOHIDEBAR, &abd)) {
				ab_message(ERROR_AUTOHIDING);
				user_vars.autohide = FALSE;
			}
		} else if (ab) {
			abd.rc.top = 0;
			abd.rc.left = 0;
			abd.rc.right = GetSystemMetrics(SM_CXSCREEN);
			abd.rc.bottom = GetSystemMetrics(SM_CYSCREEN);
			SHAppBarMessage(ABM_QUERYPOS, &abd);
			abd.rc.top = (user_vars.bottom ? abd.rc.bottom - AB_HEIGHT : abd.rc.top);
			MoveWindow(ab_hwnd, abd.rc.left, abd.rc.top, AB_WIDTH, AB_HEIGHT, TRUE);
			abd.rc.bottom = abd.rc.top + AB_HEIGHT;
			abd.rc.right = AB_WIDTH;
			SHAppBarMessage(ABM_SETPOS, &abd);
		}
	}
		// Insert applications into window menu
	update_menus();
	ShowWindow(ab_hwnd, SW_SHOW);
	if (sys_vars.newshell) 
		if (user_vars.autohide)
			HideAppBar(TRUE);
		  else
			modify_time();
	  else
		HideAppBar(TRUE);
	return TRUE;
}

void update_menus(void)
{
	int a=1, m=1;
	app_struct *app;
	menu_struct *menu, *firstapp;
	HMENU hmenu;
	app_list *curapplist, *prevapplist;

	kill_applist();
	DestroyMenu(ab_menu);
	
	ab_menu = CreateMenu();
	SetMenu(ab_hwnd, ab_menu);

	if (!glob_menu) {
		applist = NULL;
		DrawMenuBar(ab_hwnd);
		modify_time();
		return;
	}

	for (menu = glob_menu, firstapp = NULL; menu; menu = menu->nextmenu)
		if (menu->nextapp) {
			firstapp = menu;
			break;
		}

	for (menu = glob_menu; menu; menu = menu->nextmenu) {
		hmenu = CreateMenu();
		for (app = menu->nextapp; app; app = app->nextapp) {
			if (app->separator)                 // Put in separator
				AppendMenu(hmenu, MF_SEPARATOR, 0, 0);
			AppendMenu(hmenu, MF_STRING, (m*100 + a), app->appname);
			if (firstapp->nextapp == app) {
				applist = new app_list;
				curapplist = applist;
			  } else {
				curapplist = new app_list;
				prevapplist->next = curapplist;
			}
			curapplist->appId = m*100 + a;
			curapplist->app = app;                              
			curapplist->next = NULL;
			prevapplist = curapplist;
			a++;
		}
		InsertMenu(ab_menu, m, MF_BYPOSITION | MF_POPUP, (UINT)hmenu, menu->menuname);
		a = 1;
		m++;
	}
	DrawMenuBar(ab_hwnd);
	return;
}

// hides or shows AppBar, depending on "hide" variable

void HideAppBar(BOOL hide)
{
	int newy;
	BOOL drag = TRUE;

	if (!hide && IsShown)
		return;

	if (sys_vars.newshell)
		SystemParametersInfo(SPI_GETDRAGFULLWINDOWS, 0, &drag, 0);

	if (hide) {
		newy = (user_vars.bottom ? sys_vars.height - 2 : -(AB_HEIGHT - 2));
		if (drag)
			SlideWindow(newy);
		  else
			SetWindowPos(ab_hwnd, NULL, 0, newy, AB_WIDTH,
						AB_HEIGHT, SWP_NOACTIVATE | SWP_NOZORDER);
		IsShown = FALSE;
	} else {
		newy = (user_vars.bottom ? sys_vars.height - AB_HEIGHT : 0);
		if (drag)
			SlideWindow(newy);
		  else
			SetWindowPos(ab_hwnd, NULL, 0, newy, AB_WIDTH, AB_HEIGHT,
						SWP_NOACTIVATE | SWP_NOZORDER);
		IsShown = TRUE;
		modify_time();
	}
}

// draws arrow buttons in edit box

void draw_buttons(DRAWITEMSTRUCT *dw, UINT CtlID)
{
	// these icons will be loaded once only (because they are static)
	static HICON up1   = (HICON) LoadImage(ab_inst, MAKEINTRESOURCE(IDI_UP1), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	static HICON down1 = (HICON) LoadImage(ab_inst, MAKEINTRESOURCE(IDI_DOWN1), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	static HICON up2   = (HICON) LoadImage(ab_inst, MAKEINTRESOURCE(IDI_UP2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	static HICON down2 = (HICON) LoadImage(ab_inst, MAKEINTRESOURCE(IDI_DOWN2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);

	if ((CtlID == IDB_APPUP) || (CtlID == IDB_MENUUP)) {
		if (dw->itemState & ODS_SELECTED)
			DrawIconEx(dw->hDC, 0, 0, up2, 16, 16, NULL, NULL, DI_NORMAL);
		  else 
			DrawIconEx(dw->hDC, 0, 0, up1, 16, 16, NULL, NULL, DI_NORMAL);
		return;
	  } else if ((CtlID == IDB_APPDOWN) || (CtlID == IDB_MENUDOWN)) {
		if (dw->itemState & ODS_SELECTED)
			DrawIconEx(dw->hDC, 0, 0, down2, 16, 16, NULL, NULL, DI_NORMAL);
		  else 
			DrawIconEx(dw->hDC, 0, 0, down1, 16, 16, NULL, NULL, DI_NORMAL);
		return;
	}
}


// MAX(a,b) was causing a bug in AppBar because I was in-line decrementing so it would expand to:
// ((--a>b) ? (--a) : b) because it is a macro, not a function.
//
// I just wanted: ((--a>b) ? (a) : (b))

inline int mymax(int a, int b)
{
	return ((a>b) ? a : b);
}

inline int mymin(int a, int b)
{
	return ((a>b) ? b : a);
}


LRESULT CALLBACK EditProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	char menu_sel[30],
		 app_sel[30];
	menu_struct *menus, *newmenu;
	app_struct *apps, *newapp;
	int index;
	int i;
	BOOL sep, flag;
	hack Hack;
	
	switch (message) {              // this is the mother of all switch statements
		case WM_INITDIALOG:         // Fill menu list with current menus
			EditDlg = hDlg;
			for (menus = glob_menu; menus; menus = menus->nextmenu)
				SendDlgItemMessage(hDlg, IDC_MENULIST, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)((LPSTR)menus->menuname));
			menus = glob_menu;
			DragAcceptFiles(GetDlgItem(EditDlg, IDC_MENULIST), TRUE);
			EnableWindow(GetDlgItem(EditDlg, IDB_DELMENU), FALSE);
			EnableWindow(GetDlgItem(EditDlg, IDB_DELAPP), FALSE);
			EnableWindow(GetDlgItem(EditDlg, IDB_SEPARATOR), FALSE);
			return TRUE;
		case WM_DRAWITEM:
			draw_buttons((DRAWITEMSTRUCT*)lParam, (UINT)wParam);
			return TRUE;
		case WM_DROPFILES:
			HDROP hd;
			RECT r;
			POINT p;
			div_t dt;
			int m, width;
			char *last_slash, *last_period, *name;

			hd = (HDROP) wParam;
			m = DragQueryFile(hd, 0xFFFFFFFF, 0, 0);
			DragQueryPoint(hd, &p);
			SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETITEMRECT, 0, (LPARAM)&r);
			width = r.bottom - r.top;
			dt = div(p.y, width);
			dt.quot += SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETTOPINDEX, 0, 0);
			menus = glob_menu;
			if (!menus) {DragFinish(hd); return TRUE;}
			for (i=0;i<dt.quot;i++) {
				if (menus->nextmenu)
					menus = menus->nextmenu;
				  else {DragFinish(hd); return TRUE;}
			}
			while (m--) {
				apps = menus->nextapp;
				if (apps)
					while (apps->nextapp)
						apps = apps->nextapp;
				if (apps) {
					apps->nextapp = new app_struct;
					apps->nextapp->prevapp = apps;
					apps = apps->nextapp;
				  } else {
					menus->nextapp = new app_struct;
					menus->nextapp->prevapp = NULL;
					apps = menus->nextapp;
				}
				DragQueryFile(hd, m, apps->appexe, sizeof(apps->appexe));
				last_slash = strrchr(apps->appexe, 0x5C);  // backslash
				last_period = strrchr(apps->appexe, 0x2E); // period
				if (!last_slash) last_slash = (char *) apps->appexe;
				if (!last_period)
					strcpy(apps->appname, last_slash);
				  else { 
					last_slash++;
					name = (char *) apps->appname;
					while (last_slash != last_period) {
						*last_slash = tolower(*last_slash);
						*name++ = *last_slash++;
					}
				}
				apps->appname[0] = (char) toupper((int)apps->appname[0]);
				if (!strcmp(apps->appname, ""))
					strcpy(apps->appname, DEFAULT_NAME);
				menus->numapps++;

				char drive[40], path[80];
				_splitpath(apps->appexe, drive, path, NULL, NULL);
				sprintf(apps->workingdir, "%s%s", drive, path);
				int len = strlen(apps->workingdir);
				// we don't want to remove the \ in c:\
				if (len>3)
					// remove trailing backslash on directory
					*(apps->workingdir + len - 1) = '\0';
				SendDlgItemMessage(hDlg, IDC_MENULIST, LB_SETCURSEL, i, 0);
				SetFocus(GetDlgItem(hDlg, IDC_MENULIST));
			}
			DragFinish(hd);
			return TRUE;
		case WM_COMMAND:
			switch LOWORD(wParam) {
				case IDOK:
					save_menus();
					update_menus();
					modify_time();
					EndDialog(hDlg, TRUE);
					return TRUE;
				case IDC_MENULIST:      // User selected a menu, get menu and show related apps
					if (HIWORD(wParam)==LBN_SELCHANGE) {
						EnableWindow(GetDlgItem(EditDlg, IDB_DELMENU), TRUE);
						index = SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETCURSEL, 0, 0);
						SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETTEXT,(WPARAM) index,(LPARAM)((LPSTR) menu_sel));
						menus = find_menu(menu_sel);
						if (!menus) return FALSE;
						// Found correct menu, now fill other listbox with apps
						SendDlgItemMessage(hDlg, IDC_APPLIST, LB_RESETCONTENT, 0,0);
						for (apps = menus->nextapp; apps; apps = apps->nextapp) {
							if (apps->separator)
								SendDlgItemMessage(hDlg, IDC_APPLIST, LB_ADDSTRING, 0, (LPARAM)((LPSTR) SEPARATOR_STRING));
							SendDlgItemMessage(hDlg, IDC_APPLIST, LB_ADDSTRING, 0, (LPARAM)((LPSTR) apps->appname));
						}
					  } else if (HIWORD(wParam) == LBN_DBLCLK) {
							index = SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETCURSEL, 0, 0);
							if (index == LB_ERR) {ab_message(SELECT_MENU);return 0;}
							SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETTEXT,(WPARAM) index,(LPARAM)((LPSTR) menu_sel));
							menus = find_menu(menu_sel);
							if (!menus) return FALSE;
							Hack.isnew = FALSE;
							Hack.app = NULL;
							Hack.menu = menus;
							DialogBoxParam(ab_inst, MAKEINTRESOURCE(IDD_NEWMENU), hDlg, (DLGPROC) MenuProc, (LPARAM)&Hack);
							SendDlgItemMessage(hDlg, IDC_MENULIST, LB_SETCURSEL, index, 0);
					  }
					return FALSE;
				case IDC_APPLIST:
					if (HIWORD(wParam)==LBN_DBLCLK) {
						menus = glob_menu;
						index = SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETCURSEL, 0, 0);
						if (index == LB_ERR) {ab_message(SELECT_MENU);return TRUE;}
						SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETTEXT,(WPARAM) index,(LPARAM)((LPSTR) menu_sel));
						menus = find_menu(menu_sel);
						if (!menus) return FALSE;
						apps = menus->nextapp;
						index = SendDlgItemMessage(hDlg, IDC_APPLIST, LB_GETCURSEL, 0, 0);
						SendDlgItemMessage(hDlg, IDC_APPLIST, LB_GETTEXT,(WPARAM) index,(LPARAM)((LPSTR) app_sel));
						apps = find_app(apps, app_sel);
						if (!apps) return FALSE;
						Hack.app = apps;
						Hack.isnew = FALSE;
						Hack.menu = menus;
						DialogBoxParam(ab_inst, MAKEINTRESOURCE(IDD_NEWAPP), hDlg, (DLGPROC) AppProc, (LPARAM)&Hack);
						SendDlgItemMessage(hDlg, IDC_APPLIST, LB_SETCURSEL, index, 0);
						return FALSE;
					  } else if (HIWORD(wParam)==LBN_SELCHANGE) {
						EnableWindow(GetDlgItem(EditDlg, IDB_DELAPP), TRUE);
						EnableWindow(GetDlgItem(EditDlg, IDB_SEPARATOR), TRUE);
					}
					return FALSE;
				case IDB_NEWMENU:
					newmenu = glob_menu;
					if (newmenu)
						while (newmenu->nextmenu)
							newmenu = newmenu->nextmenu;
					Hack.isnew = TRUE;
					Hack.app = NULL;
					Hack.menu = newmenu;
					DialogBoxParam(ab_inst, MAKEINTRESOURCE(IDD_NEWMENU), hDlg, (DLGPROC)MenuProc, (LRESULT)&Hack);
					return FALSE;
				case IDB_NEWAPP:
					index = SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETCURSEL, 0, 0);
					if (index == LB_ERR) {ab_message(SELECT_MENU);return 0;}
					SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETTEXT, (WPARAM)index, (LPARAM)((LPSTR)menu_sel));
					menus = find_menu(menu_sel);
					if (!menus) return FALSE;
					newapp = menus->nextapp;
					if (newapp)
						while (newapp->nextapp)
							newapp = newapp->nextapp;
					Hack.isnew = TRUE;
					Hack.app = newapp;
					Hack.menu = menus;
					DialogBoxParam(ab_inst, MAKEINTRESOURCE(IDD_NEWAPP), hDlg, (DLGPROC)AppProc, (LPARAM)&Hack);
					return FALSE;
				case IDB_DELMENU:
					index = SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETCURSEL, 0, 0);
					if (index == LB_ERR) {ab_message(SELECT_MENU);return 0;}
					SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETTEXT, (WPARAM)index, (LPARAM)((LPSTR)menu_sel));
					menus = find_menu(menu_sel);
					if (!menus) return FALSE;
					i = MessageBox(hDlg, CONFIRM_DELETE, CONFIRM_DELETE_TITLE, MB_YESNO);
					if (i == IDYES) {
						killmenu(menus);
						SendDlgItemMessage(hDlg, IDC_MENULIST, LB_DELETESTRING, (WPARAM)index, 0);
						SendDlgItemMessage(hDlg, IDC_APPLIST, LB_RESETCONTENT, 0, 0);
					}
					SetFocus(GetDlgItem(EditDlg, IDC_MENULIST));
					SendDlgItemMessage(hDlg, IDC_MENULIST, LB_SETCURSEL, (WPARAM) index, 0);
					return FALSE;
				case IDB_DELAPP:
					index = SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETCURSEL, 0, 0);
					if (index == LB_ERR) {ab_message(SELECT_MENU);return 0;}
					SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETTEXT, (WPARAM)index, (LPARAM)((LPSTR)menu_sel));
					menus = find_menu(menu_sel);
					if (!menus) return FALSE;
					index = SendDlgItemMessage(hDlg, IDC_APPLIST, LB_GETCURSEL, 0, 0);
					if (index == LB_ERR) {ab_message(SELECT_ITEM);return 0;}
					sep = FALSE;  // whether we should delete the separator
					SendDlgItemMessage(hDlg, IDC_APPLIST, LB_GETTEXT, (WPARAM)index, (LPARAM)((LPSTR)app_sel));
					if (!strcmp(app_sel,SEPARATOR_STRING))  {   // User wants to delete a separator
						SendDlgItemMessage(hDlg, IDC_APPLIST, LB_GETTEXT, (WPARAM)++index, (LPARAM)((LPSTR)app_sel));
						index--;
						sep = TRUE;
					}
					apps = menus->nextapp;
					apps = find_app(apps, app_sel);
					if (!apps) return FALSE;
					if (sep)    // If we are deleting sep, just reset variable
						apps->separator = FALSE;
					  else {    // else kill app structure
						  // if the app has a separator, we need to delete it from the listbox too
						if (apps->separator) {
							SendDlgItemMessage(hDlg, IDC_APPLIST, LB_DELETESTRING, --index, 0);
							flag = TRUE;
						}
						if (menus->nextapp == apps)
							menus->nextapp = apps->nextapp;
						killapp(apps);
						menus->numapps--;
					}
					SendDlgItemMessage(hDlg, IDC_APPLIST, LB_DELETESTRING, (WPARAM)index, 0);
					SetFocus(GetDlgItem(EditDlg, IDC_APPLIST));
					if (flag) index--;
					SendDlgItemMessage(hDlg, IDC_APPLIST, LB_SETCURSEL, (WPARAM) index, 0);
					return FALSE;
				case IDB_SEPARATOR:
					index = SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETCURSEL, 0, 0);
					if (index == LB_ERR) {ab_message(SELECT_MENU);return 0;}
					SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETTEXT, (WPARAM)index, (LPARAM)((LPSTR)menu_sel));
					menus = find_menu(menu_sel);
					if (!menus) return FALSE;
					index = SendDlgItemMessage(hDlg, IDC_APPLIST, LB_GETCURSEL, 0, 0);
					if (index == LB_ERR) {ab_message(SELECT_ITEM);return 0;}
					SendDlgItemMessage(hDlg, IDC_APPLIST, LB_GETTEXT, (WPARAM)index, (LPARAM)((LPSTR)app_sel));
					apps = menus->nextapp;
					apps = find_app(apps, app_sel);
					if (!apps) return FALSE;
					if (apps->separator) return FALSE;  // Can't add a second separator!
					apps->separator = TRUE;
					SendDlgItemMessage(hDlg, IDC_APPLIST, LB_INSERTSTRING, (WPARAM)index, (LPARAM)((LPSTR)SEPARATOR_STRING));
					return FALSE;
				case IDB_MENUDOWN:
				case IDB_MENUUP:
					index = SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETCURSEL, 0, 0);
					if (index == LB_ERR) {ab_message(SELECT_MENU);return 0;}
					SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETTEXT, (WPARAM)index, (LPARAM)((LPSTR)menu_sel));
					menus = find_menu(menu_sel);
					if (!menus) return FALSE;
					if (LOWORD(wParam) == IDB_MENUDOWN)
						switch_places_m(menus, DOWN);
					  else
						switch_places_m(menus, UP);
					SendDlgItemMessage(hDlg, IDC_MENULIST, LB_RESETCONTENT, 0, 0);
					for (menus = glob_menu; menus; menus = menus->nextmenu)
						SendDlgItemMessage(hDlg, IDC_MENULIST, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)((LPSTR)menus->menuname));
					SetFocus(GetDlgItem(EditDlg, IDC_MENULIST));
					i = SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETCOUNT, 0, 0);
					SendDlgItemMessage(hDlg, IDC_MENULIST, LB_SETCURSEL, (WPARAM) (LOWORD(wParam)==IDB_MENUUP ? mymax(0, --index) : mymin(--i, ++index)), 0);
					return FALSE;
				case IDB_APPDOWN:
				case IDB_APPUP:
					menus = glob_menu;
					index = SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETCURSEL, 0, 0);
					if (index == LB_ERR) {ab_message(SELECT_MENU);return TRUE;}
					SendDlgItemMessage(hDlg, IDC_MENULIST, LB_GETTEXT,(WPARAM) index,(LPARAM)((LPSTR) menu_sel));
					menus = find_menu(menu_sel);
					if (!menus) return FALSE;
					apps = menus->nextapp;
					index = SendDlgItemMessage(hDlg, IDC_APPLIST, LB_GETCURSEL, 0, 0);
					if (index == LB_ERR) {ab_message(SELECT_ITEM);return TRUE;}
					SendDlgItemMessage(hDlg, IDC_APPLIST, LB_GETTEXT,(WPARAM) index,(LPARAM)((LPSTR) app_sel));
					apps = find_app(apps, app_sel);
					if (!apps) return FALSE;
					if ((LOWORD(wParam)) == IDB_APPUP) {	// move over separators...
						if (apps->prevapp)
							if (apps->prevapp->separator)
								index--;
					} else {
						if (apps->nextapp)
							if (apps->nextapp->separator)
								index++;
					}
					if (LOWORD(wParam) == IDB_APPDOWN) {
						if (menus->nextapp == apps)
							menus->nextapp = menus->nextapp->nextapp;
						switch_places_a(apps, DOWN);
					  } else {
						if (menus->nextapp->nextapp)
							if (menus->nextapp->nextapp == apps)
								menus->nextapp = menus->nextapp->nextapp;
						switch_places_a(apps, UP);
					}
					SendDlgItemMessage(hDlg, IDC_APPLIST, LB_RESETCONTENT, 0, 0);
					for (apps = menus->nextapp; apps; apps = apps->nextapp) {
						if (apps->separator) 
							SendDlgItemMessage(hDlg, IDC_APPLIST, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)((LPSTR)SEPARATOR_STRING));
						SendDlgItemMessage(hDlg, IDC_APPLIST, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)((LPSTR)apps->appname));
					}
					SetFocus(GetDlgItem(EditDlg, IDC_APPLIST));
					i = SendDlgItemMessage(hDlg, IDC_APPLIST, LB_GETCOUNT, 0, 0);
					SendDlgItemMessage(hDlg, IDC_APPLIST, LB_SETCURSEL, (WPARAM) (LOWORD(wParam)==IDB_APPUP ? mymax(0, --index) : mymin(--i, ++index)), 0);
					return FALSE;
				default:
					return FALSE;
			}
		default:
			return FALSE;
	}
}

LRESULT CALLBACK MenuProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{           
	static menu_struct *newmenu;
	static BOOL isnew = FALSE;
	static int index;
	static hack * phack;

	switch (message) {
		case WM_INITDIALOG:
			phack = (hack *) lParam;
			newmenu = phack->menu;
			isnew = phack->isnew;
			if (isnew)
				if (newmenu) {
					newmenu->nextmenu = new menu_struct;
					newmenu->nextmenu->prevmenu = newmenu;
					newmenu = newmenu->nextmenu;
				  } else {
					glob_menu = new menu_struct;
					newmenu = glob_menu;
				}
			SetFocus(GetDlgItem(hDlg, IDC_MENUNAME));
			SendMessage(GetDlgItem(hDlg, IDC_MENUNAME), WM_SETTEXT, 0, (LPARAM)newmenu->menuname);
			index = SendDlgItemMessage(EditDlg,IDC_MENULIST, LB_GETCURSEL, 0, 0);
			return FALSE;
		case WM_COMMAND:
			if (wParam == IDOK) {
				char buffer[30];

				SendMessage(GetDlgItem(hDlg, IDC_MENUNAME), WM_GETTEXT, sizeof(buffer), (LPARAM)buffer);
				if (!strcmp(buffer,"")) {
					ab_message(ERROR_MENUNAME);
					return TRUE;
				}
				strcpy(newmenu->menuname, buffer);
				if (!isnew) {
					SendDlgItemMessage(EditDlg, IDC_MENULIST, LB_DELETESTRING,  index, 0);
					SendDlgItemMessage(EditDlg, IDC_MENULIST, LB_INSERTSTRING, index, (LPARAM) (LPCSTR)newmenu->menuname);
				  } else
					SendDlgItemMessage(EditDlg, IDC_MENULIST, LB_INSERTSTRING, (WPARAM)-1, (LPARAM) (LPCSTR)newmenu->menuname);
				EndDialog(hDlg, TRUE);
				return TRUE;
			  } else if (wParam==IDCANCEL) {
				if (isnew) {
					delete newmenu;
					phack->menu->nextmenu = NULL;
				}
				EndDialog(hDlg, TRUE);
				return TRUE;
			}                           
		default:
			return FALSE;
	}
}

LRESULT CALLBACK AppProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static app_struct *pnewapp;
	static menu_struct *menu;
	static BOOL isnew = FALSE;
	static hack *phack;
	static int index;
	int check_button;
			
	switch (message) {    
		case WM_INITDIALOG:
			phack = (hack *) lParam;        // hack is a hack so that I can pass two 32-bit
			isnew = phack->isnew;           // pointers with one 32-bit pointer
			if (isnew) {
				menu = phack->menu;
				pnewapp = new app_struct;
			  } else 
				pnewapp = phack->app;
			switch (pnewapp->show) {
				case SW_MAXIMIZE:
					check_button = IDC_MAX;
					break;
				case SW_MINIMIZE:
					check_button = IDC_MIN;
					break;
				default:
					check_button = IDC_NORMAL;
					break;
			}
			CheckRadioButton(hDlg, IDC_NORMAL, IDC_MIN, check_button);
			index = SendDlgItemMessage(EditDlg,IDC_APPLIST, LB_GETCURSEL, 0, 0);
			SendMessage(GetDlgItem(hDlg, IDC_EXENAME), WM_SETTEXT, 0, (LPARAM)pnewapp->appexe);
			SendMessage(GetDlgItem(hDlg, IDC_APPNAME), WM_SETTEXT, 0, (LPARAM)pnewapp->appname);
			SendMessage(GetDlgItem(hDlg, IDC_WORKINGDIR), WM_SETTEXT, 0, (LPARAM)pnewapp->workingdir);
			SendMessage(GetDlgItem(hDlg, IDC_PARAMETERS), WM_SETTEXT, 0, (LPARAM)pnewapp->params);
			SetFocus(GetDlgItem(hDlg, IDC_APPNAME));
			return FALSE;
		case WM_COMMAND:
			if (wParam==IDOK) {
				char buf1[80], buf2[30];
				SendMessage(GetDlgItem(hDlg, IDC_EXENAME), WM_GETTEXT, sizeof(buf1), (LPARAM)buf1);
				SendMessage(GetDlgItem(hDlg, IDC_APPNAME), WM_GETTEXT, sizeof(buf2), (LPARAM)buf2);
				if ((!strcmp(buf1, "")) || (!strcmp(buf2, ""))) {
					ab_message(ERROR_NAME_FILENAME);
					return TRUE;
				}
				SendMessage(GetDlgItem(hDlg, IDC_EXENAME), WM_GETTEXT, sizeof(pnewapp->appexe), (LPARAM)pnewapp->appexe);
				SendMessage(GetDlgItem(hDlg, IDC_APPNAME), WM_GETTEXT, sizeof(pnewapp->appname), (LPARAM)pnewapp->appname);
				SendMessage(GetDlgItem(hDlg, IDC_PARAMETERS), WM_GETTEXT, sizeof(pnewapp->params), (LPARAM)pnewapp->params);
				SendMessage(GetDlgItem(hDlg, IDC_WORKINGDIR), WM_GETTEXT, sizeof(pnewapp->workingdir), (LPARAM)pnewapp->workingdir);
				if (!strcmp(pnewapp->workingdir, "")) {
					char drive[4], path[80];
					_splitpath(pnewapp->appexe, drive, path, NULL, NULL);
					sprintf(pnewapp->workingdir, "%s%s", drive, path);
					int len = strlen(pnewapp->workingdir);
					// we don't want to remove the \ in c:\
					if (len>3)
						// remove trailing backslash on directory
						*(pnewapp->workingdir + len - 1) = '\0';
				}
				if (IsDlgButtonChecked(hDlg, IDC_NORMAL))
					pnewapp->show = SW_RESTORE;
				  else if (IsDlgButtonChecked(hDlg, IDC_MAX))
					pnewapp->show = SW_MAXIMIZE;
				  else if (IsDlgButtonChecked(hDlg, IDC_MIN))
					pnewapp->show = SW_MINIMIZE;
				if (isnew) {
					if (phack->app) {
						phack->app->nextapp = pnewapp;
						pnewapp->prevapp = phack->app;
					  } else {          // first app in menu
						phack->menu->nextapp = pnewapp;
						pnewapp->prevapp = NULL;
					}
					menu->numapps++;
					SendDlgItemMessage(EditDlg, IDC_APPLIST, LB_INSERTSTRING, (WPARAM) -1, (LPARAM)pnewapp->appname);
				  } else {
					SendDlgItemMessage(EditDlg, IDC_APPLIST, LB_DELETESTRING, index, 0);
					SendDlgItemMessage(EditDlg, IDC_APPLIST, LB_INSERTSTRING, index, (LPARAM)pnewapp->appname);
				}
				EndDialog(hDlg, TRUE);
				return TRUE;
			} else if (wParam==IDCANCEL) {
				if (isnew)
					delete pnewapp;
				EndDialog(hDlg, TRUE);
				return TRUE;
			} else if (wParam == IDC_BROWSE) {
				DoBrowse(0, hDlg);
				return FALSE;
		}
		default:
			return FALSE;
	}   
}

LRESULT CALLBACK OptionsProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	char buffer[80];

	switch (message) {
		case WM_INITDIALOG:
			SendMessage(GetDlgItem(hDlg, IDC_WAVNAME), WM_SETTEXT, 0, (LPARAM)user_vars.wavfile);
			CheckDlgButton(hDlg, IDC_CHIME, user_vars.chime);
			CheckDlgButton(hDlg, IDC_DATE, user_vars.date);
			CheckDlgButton(hDlg, IDC_MEMORY, user_vars.memory);
			CheckDlgButton(hDlg, IDC_STAYONTOP, user_vars.stayontop);
			CheckDlgButton(hDlg, IDC_BOTTOM, user_vars.bottom);
			CheckDlgButton(hDlg, IDC_AUTOHIDE, user_vars.autohide);
			CheckDlgButton(hDlg, IDC_TIME, user_vars.time);
			CheckDlgButton(hDlg, IDC_USER, user_vars.user);
			return TRUE;
		case WM_COMMAND:
			if (wParam == IDOK) {
				SendMessage(GetDlgItem(hDlg, IDC_WAVNAME), WM_GETTEXT, sizeof(buffer), (LPARAM)buffer);
				if (!strcmp(buffer, "") && user_vars.chime) {
					ab_message(ERROR_ENTER_WAVNAME);
					return FALSE;
				}
				strcpy(user_vars.wavfile, buffer);
				EndDialog(hDlg, TRUE);
				return TRUE;
			} else if (HIWORD(wParam) == BN_CLICKED) {

				switch (LOWORD(wParam)) {
					case IDC_DATE:
						user_vars.date = !user_vars.date;
						CheckDlgButton(hDlg, IDC_DATE, user_vars.date);
						modify_time();
						return FALSE;
					case IDC_USER:
						user_vars.user = !user_vars.user;
						CheckDlgButton(hDlg, IDC_USER, user_vars.user);
						modify_time();
						return FALSE;
					case IDC_TIME:
						user_vars.time = !user_vars.time;
						CheckDlgButton(hDlg, IDC_TIME, user_vars.time);
						modify_time();
						return FALSE;
					case IDC_MEMORY:
						user_vars.memory = !user_vars.memory;
						CheckDlgButton(hDlg, IDC_MEMORY, user_vars.memory);
						modify_time();
						return FALSE;
					case IDC_CHIME:
						user_vars.chime = !user_vars.chime;
						CheckDlgButton(hDlg, IDC_CHIME, user_vars.chime);
						return FALSE;
					case IDC_AUTOHIDE:
						if (sys_vars.newshell) {
							user_vars.autohide = !user_vars.autohide;
							CheckDlgButton(hDlg, IDC_AUTOHIDE, user_vars.autohide);
							// set or unset the autohide bar for this edge
							abd.cbSize = sizeof(APPBARDATA);
							abd.hWnd = ab_hwnd;
							abd.uEdge = (user_vars.bottom ? ABE_BOTTOM : ABE_TOP);
							abd.lParam = (user_vars.autohide ? TRUE : FALSE);
							if (!SHAppBarMessage(ABM_SETAUTOHIDEBAR, &abd)) {
								user_vars.autohide = !user_vars.autohide;
								CheckDlgButton(hDlg, IDC_AUTOHIDE, user_vars.autohide);
								ab_message(ERROR_AUTOHIDING);
								return FALSE;
							}
							// update the position of the autohide bar
							if (user_vars.autohide) {
								abd.rc.top = abd.rc.left = abd.rc.right = abd.rc.bottom = 0;
								if (user_vars.bottom)
									abd.rc.top = abd.rc.bottom = sys_vars.height;
								SHAppBarMessage(ABM_SETPOS, &abd);
							  } else {
								abd.rc.top = abd.rc.left = 0;
								abd.rc.right = sys_vars.width;
								abd.rc.bottom = sys_vars.height;
								SHAppBarMessage(ABM_QUERYPOS, &abd);
								abd.rc.top = (user_vars.bottom ? abd.rc.bottom - AB_HEIGHT : abd.rc.top);
								MoveWindow(ab_hwnd, 0, abd.rc.top, AB_WIDTH, AB_HEIGHT, TRUE);
								abd.rc.bottom = abd.rc.top + AB_HEIGHT;
								abd.rc.right = AB_WIDTH;
								SHAppBarMessage(ABM_SETPOS, &abd);
							}
							HideAppBar(user_vars.autohide);
						  } else {
							ab_message(ERROR_AUTOHIDE_NT);
							user_vars.autohide = TRUE;
							CheckDlgButton(hDlg, IDC_AUTOHIDE, user_vars.autohide);
						}
						return FALSE;

					case IDC_BOTTOM:
						user_vars.bottom = !user_vars.bottom;
						CheckDlgButton(hDlg, IDC_BOTTOM, user_vars.bottom);
						MoveWindow(ab_hwnd, 0, (user_vars.bottom ? sys_vars.height - AB_HEIGHT : 0),
									AB_WIDTH, AB_HEIGHT, TRUE);
						modify_time();
						if (sys_vars.newshell) {
							// we are changing our onscreen position so
							// we need to reinitialize our appbar system info
							abd.cbSize = sizeof(APPBARDATA);
							abd.hWnd = ab_hwnd;
							abd.uEdge = (user_vars.bottom ? ABE_BOTTOM : ABE_TOP);
							if (user_vars.autohide) {
								abd.lParam = TRUE;
								abd.uCallbackMessage = NULL; //WM_APPBAR;
								if (!SHAppBarMessage(ABM_SETAUTOHIDEBAR, &abd)) {
									SHAppBarMessage(ABM_REMOVE, &abd);
									SHAppBarMessage(ABM_NEW, &abd);
									user_vars.bottom = !user_vars.bottom;
									SetWindowPos(ab_hwnd, NULL, 0, (user_vars.bottom ? sys_vars.height - AB_HEIGHT : 0),
															0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
									abd.uEdge = (user_vars.bottom ? ABE_BOTTOM : ABE_TOP);
									SHAppBarMessage(ABM_SETAUTOHIDEBAR, &abd);
									CheckDlgButton(hDlg, IDC_BOTTOM, user_vars.bottom);
									ab_message(ERROR_AUTOHIDING);
									return FALSE;
								}
								HideAppBar(user_vars.autohide);
							} else {
								abd.rc.top = abd.rc.left = abd.rc.right = abd.rc.bottom = 0;
								abd.rc.right = sys_vars.width;
								abd.rc.bottom = sys_vars.height;
								SHAppBarMessage(ABM_QUERYPOS, &abd);
								abd.rc.left = 0;
								abd.rc.top = (user_vars.bottom ? abd.rc.bottom - AB_HEIGHT : abd.rc.top);
								abd.rc.bottom = abd.rc.top + AB_HEIGHT;
								abd.rc.right = AB_WIDTH;
								SHAppBarMessage(ABM_SETPOS, &abd);
							}
						} else 
							HideAppBar(TRUE);
						return FALSE;
					case IDC_STAYONTOP:
						user_vars.stayontop = !user_vars.stayontop;
						SetWindowPos(ab_hwnd, (user_vars.stayontop ? HWND_TOPMOST : HWND_NOTOPMOST),
										0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
						return FALSE;
					case IDC_FINDWAV:
						DoBrowse(1, hDlg);
						return FALSE;
					case IDC_TESTWAV:
						SendMessage(GetDlgItem(hDlg, IDC_WAVNAME), WM_GETTEXT, sizeof(buffer), (LPARAM)buffer);
						if (!strcmp(buffer, "")) {
							ab_message(ERROR_ENTER_WAVNAME);
							return FALSE;
						}
						if (!PlaySound(buffer, NULL, SND_ASYNC | SND_FILENAME))
							ab_message(ERROR_PLAYING_WAV);
						return FALSE;
				}
			}
		default:
			return FALSE;
	}
}


///// Whew, these functions are NOT pretty... /////

BOOL switch_places_a(app_struct *app, int dir)
{
	if (!app)
		return FALSE;
	if (!(app->prevapp) && (dir == UP))
		return FALSE;
	if (!(app->nextapp) && (dir == DOWN))
		return FALSE;
	if (dir == UP) {
		if (app->nextapp)
			app->nextapp->prevapp = app->prevapp;
		if (app->prevapp->prevapp)
			app->prevapp->prevapp->nextapp = app;
		app->prevapp->nextapp = app->nextapp;
		app->nextapp = app->prevapp;
		app->prevapp = app->prevapp->prevapp;
		app->nextapp->prevapp = app;
		return TRUE;
	  } else {
		if (app->prevapp)
			app->prevapp->nextapp = app->nextapp;
		if (app->nextapp->nextapp)
			app->nextapp->nextapp->prevapp = app;
		app->nextapp->prevapp = app->prevapp;
		app->prevapp = app->nextapp;
		app->nextapp = app->nextapp->nextapp;
		app->prevapp->nextapp = app;
		return TRUE;
	}
}

BOOL switch_places_m(menu_struct *menu, int dir)
{
	if (!menu)
		return FALSE;
	if (!(menu->prevmenu) && (dir == UP))
		return FALSE;
	if (!(menu->nextmenu) && (dir == DOWN))
		return FALSE;
	if (dir == UP) {
		if (menu->nextmenu)
			menu->nextmenu->prevmenu = menu->prevmenu;
		if (menu->prevmenu->prevmenu)
			menu->prevmenu->prevmenu->nextmenu = menu;
		  else
			glob_menu = menu;
		menu->prevmenu->nextmenu = menu->nextmenu;
		menu->nextmenu = menu->prevmenu;
		menu->prevmenu = menu->prevmenu->prevmenu;
		menu->nextmenu->prevmenu = menu;
		return TRUE;
	  } else {
		if (menu->prevmenu)
			menu->prevmenu->nextmenu = menu->nextmenu;
		  else
			glob_menu = menu->nextmenu;
		if (menu->nextmenu->nextmenu)
			menu->nextmenu->nextmenu->prevmenu = menu;
		menu->nextmenu->prevmenu = menu->prevmenu;
		menu->prevmenu = menu->nextmenu;
		menu->nextmenu = menu->nextmenu->nextmenu;
		menu->prevmenu->nextmenu = menu;
		return TRUE;
	}
}
