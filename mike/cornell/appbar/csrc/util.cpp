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

#include "appbar.h"
#include "globals.h"

	// Syncs AppBar's timer with the system time
void SyncTime(void)
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	// install timer that goes off at next 10 sec interval (10, 20, 30, etc.)
	SetTimer(ab_hwnd, SYNC_TIMER, ((9-(st.wSecond%10))*1000)+(1000-st.wMilliseconds), NULL);
}

// Based on function in MSJ Mar 1996 by Jeffrey Richter.

void SlideWindow(int newy)
{
	int y, t_start, t_end, t_curr, hide_time;
	RECT start;

	hide_time = (IsShown ? 300 : 200);
	GetWindowRect(ab_hwnd, &start);
	t_start = GetTickCount();
	t_end = t_start + hide_time;
//  This will be smoother if we bump up the priority, but it's not polite
//  SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
	while ((t_curr = GetTickCount()) < t_end) {
		y = start.top - (start.top - newy) * (int) (t_curr - t_start) / hide_time;
		SetWindowPos(ab_hwnd, NULL, 0, y, 0, 0, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE);
		UpdateWindow(ab_hwnd);
	}
	SetWindowPos(ab_hwnd, NULL, 0, newy, 0, 0, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE);
	UpdateWindow(ab_hwnd);
//  SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);
}

// it's hideous, but it does the job...

void parse_cmd_args(void)
{
	char msg[80];
	int j;
	user_options args;
	BOOL done = FALSE;
	char filename[MAX_PATH];

	strcpy(sys_vars.user, "");
	strcpy(sys_vars.appfile, "");
	memset((void*)&args, 0, sizeof(user_vars));
	// now process the array of parameters
	for (j=1;j<__argc;j++) {
		if (!strncmp(__argv[j], "-", 1)) {
			if (!strncmp((char*)__argv[j]+1, "s", 1))
				args.stayontop = -1;
			  else if (!strncmp((char*)__argv[j]+1, "c", 1))
				args.chime = -1;
			  else if (!strncmp((char*)__argv[j]+1, "b", 1))
				args.bottom = -1;
			  else if (!strncmp((char*)__argv[j]+1, "a", 1))
				args.autohide = -1;
			  else if (!strncmp((char*)__argv[j]+1, "d", 1))
				args.date = -1;
			  else if (!strncmp((char*)__argv[j]+1, "m", 1))
				args.memory = -1;
			  else if (!strncmp((char*)__argv[j]+1, "t", 1))
				args.time = -1;
			  else if (!strncmp((char*)__argv[j]+1, "u", 1))
				args.user = -1;
			  else if (!strncmp((char*)__argv[j]+1, "f", 1)) {
				if ((j+1 <= __argc)) {
					char w = *(__argv[j+1]);
					// if filename does not start with '-' or '+'
					// assume it is a valid filename
					if (!((w == '+') || (w == '-')))
						strcpy((char *)filename, __argv[++j]);
					  else {
						j++;
						ab_message(INVALID_FILENAME);
					}
				} else
					ab_message(INVALID_FILENAME);
			  } else {
				sprintf(msg, UNKNOWN_OPTION, __argv[j]);
				ab_message(msg);
			}
		} else if (!strncmp(__argv[j], "+", 1)) {
			if (!strncmp((char*)__argv[j]+1, "s", 1))
				args.stayontop = 1;
			  else if (!strncmp((char*)__argv[j]+1, "c", 1))
				args.chime = 1;
			  else if (!strncmp((char*)__argv[j]+1, "a", 1))
				args.autohide = 1;
			  else if (!strncmp((char*)__argv[j]+1, "b", 1))
				args.bottom = 1;
			  else if (!strncmp((char*)__argv[j]+1, "d", 1))
				args.date = 1;
			  else if (!strncmp((char*)__argv[j]+1, "m", 1))
				args.memory = 1;
			  else if (!strncmp((char*)__argv[j]+1, "t", 1))
				args.time = 1;
			  else if (!strncmp((char*)__argv[j]+1, "u", 1))
				args.user = 1;
			  else if (!strncmp((char*)__argv[j]+1, "f", 1)) {
				if ((j+1 <= __argc)) {
					char w = *(__argv[j+1]);
					if (!((w == '+') || (w == '-')))
						strcpy((char *)filename, __argv[++j]);
					  else {
						j++;
						ab_message(INVALID_FILENAME);
					}
				} else
					ab_message(INVALID_FILENAME);
			  } else {
				sprintf(msg, UNKNOWN_OPTION, __argv[j]);
				ab_message(msg);
			}
		} else      // User gave a user configuration
			strcpy((char*)sys_vars.user, __argv[j]);
	} // end while

	if (strcmp((char*)sys_vars.user, ""))
		sprintf(sys_vars.appfile, "appbar.%s", sys_vars.user);

	if (strcmp(filename, ""))
		strcpy(sys_vars.appfile, filename);

	get_reg_keys(&args);
}

// Update time on menubar every minute

BOOL modify_time(void)
{
	char string[105] = "";
	char time[20] = "";
	char date[25] = "";
	char mem[10] = "";
	char user[40] = "";
	char batt[20] = "";
	static BOOL played_wav;
	SYSTEM_POWER_STATUS sps;

	if (IsShown) {
		if (user_vars.user)
			sprintf(user, "%s  ", sys_vars.user);
		
		if (user_vars.time) {
			GetTimeFormat(LOCALE_SYSTEM_DEFAULT, TIME_NOSECONDS, NULL, 
						NULL, time, sizeof(time));
			strcat(time, "  ");
		}

		if (user_vars.date) {
			GetDateFormat(LOCALE_SYSTEM_DEFAULT, NULL, NULL, NULL, 
						date, sizeof(date));
			strcat(date, "  ");
		}
		
		if (user_vars.memory) {
			MEMORYSTATUS ms;
			GlobalMemoryStatus(&ms);
			sprintf(mem, "%dk ", (int)ms.dwAvailPhys/1024);
		}

		if (sys_vars.power) {
			if (sys_vars.battery) {
					GetSystemPowerStatus(&sps);
					sprintf(batt, "%d%%", sps.BatteryLifePercent);
					if (sps.BatteryLifePercent == 255)              // unknown percentage
						sprintf(batt, "--%%");
				}
		}
		// final string to print on AppBar
		sprintf(string, "%s%s%s%s%s", user, time, date, mem, batt);

		SIZE s;
		int x,y;
		TEXTMETRIC tm;
		COLORREF c;
		HDC hdc;
		HFONT hOldFont, hfnt;
		NONCLIENTMETRICS ncm;

		hdc = GetWindowDC(ab_hwnd);
		if (sys_vars.newshell) {
			ncm.cbSize = sizeof(NONCLIENTMETRICS);
			SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &ncm, 0);
			hfnt = CreateFontIndirect(&(ncm.lfMenuFont));
			hOldFont = (HFONT) SelectObject(hdc, hfnt);
		}
		c = SetTextColor(hdc, GetSysColor(COLOR_MENUTEXT));
		SetBkMode(hdc, TRANSPARENT);
		GetTextExtentPoint32(hdc, string, strlen(string), &s);
		x = AB_WIDTH - s.cx - 7;
		GetTextMetrics(hdc, &tm);
		y = (int) ((AB_HEIGHT - tm.tmHeight) / 2);
			// Clear menubar and then draw time in menu corner
		DrawMenuBar(ab_hwnd);
		TextOut(hdc, x, y, string, strlen(string));
		if (sys_vars.power) {
			if (sys_vars.battery) {
				if (sps.BatteryLifePercent > 25)
					SetTextColor(hdc, GREEN);
				  else if (sps.BatteryLifePercent > 10)
					  SetTextColor(hdc, YELLOW);
				  else
					  SetTextColor(hdc, RED);
				GetTextExtentPoint32(hdc, batt, strlen(batt), &s);
				x = AB_WIDTH - s.cx - 7;
				TextOut(hdc, x, y, batt, strlen(batt));
			}
		}
		if (sys_vars.newshell) {
			SelectObject(hdc, hOldFont); 
			DeleteObject(hfnt);
		}
		SetTextColor(hdc, c);
		ReleaseDC(ab_hwnd, hdc);
	}   // end if (IsShown)

	if (user_vars.chime) {
		SYSTEMTIME st;
		GetSystemTime(&st);

		// if it's the top of the hour and we haven't already played this minute...
		if ((st.wMinute == 0) && (!played_wav)) {
			played_wav = TRUE;
			if (!PlaySound(user_vars.wavfile, NULL, SND_ASYNC | SND_FILENAME))
				ab_message(ERROR_PLAYING_WAV);
		  } else if (st.wMinute == 1)
			played_wav = FALSE;
	}
	return TRUE;
}

///////// Registry interface /////////////

#define SET(a); if (args->a == 1) \
					user_vars.a = TRUE; \
				 else if (args->a == -1) \
					user_vars.a = FALSE;

void get_reg_keys(user_options *args)
{
	HKEY root;
	DWORD isnew, type, size = sizeof(user_options);
	LONG rc;
	char *p, keyname[80], mike[80];

	strcpy(keyname, "Software\\AppBar\\Default");
	// each user gets his own key in the registry
	if (strlen(sys_vars.user)) {
		strcpy(mike, sys_vars.user);
		// this loop will not work with Unicode
		for (p=mike; p<mike+strlen(mike); p++)
			_tolower(*p);
		sprintf(keyname, "Software\\AppBar\\%s", mike);
	}

	if (!strcmp(sys_vars.appfile, ""))
		strcpy(sys_vars.appfile, "appbar.default");
	// create or open key
	rc = RegCreateKeyEx(HKEY_CURRENT_USER, keyname, 0, NULL,
					REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
					NULL, &root, &isnew);
	
	if (rc != ERROR_SUCCESS) {
		ab_message(ERROR_OPENING_REG);
		user_vars.stayontop = TRUE;
		user_vars.chime = FALSE;
		user_vars.date = FALSE;
		user_vars.bottom = FALSE;
		user_vars.memory = TRUE;
		user_vars.autohide = TRUE;
		user_vars.time = TRUE;
		user_vars.user = FALSE;
		strcpy(user_vars.wavfile, "");
		if (strlen(sys_vars.user)) {
			sprintf(keyname, "appbar.%s", sys_vars.user);
			strcpy(sys_vars.appfile, keyname);
		} else
			strcpy(sys_vars.appfile, "appbar.default");
		return;
	}
	
	if (isnew != REG_OPENED_EXISTING_KEY)
		make_new_reg_key(root);
	  else {
		rc = RegQueryValueEx(root, "User_Variables", NULL, &type, (PBYTE)&user_vars, &size);
		if (size != sizeof(user_options)) {
			ab_message(OBSOLETE_REG_DATA);
			RegDeleteKey(root, "User_Variables");
			make_new_reg_key(root);
		}
	}
	RegCloseKey(root);

		// modify user vars according to cmd args
	SET(date);
	SET(memory);
	SET(stayontop);
	SET(bottom);
	SET(autohide);
	SET(chime);
	SET(time);
	SET(user);

	if (!sys_vars.newshell)
		user_vars.autohide = TRUE;
}

void make_new_reg_key(HKEY root)
{
	char msg[100];
	char comma[3] = "";
	LONG rc;

	if (strcmp(sys_vars.user, ""))
		strcpy(comma, ", ");
	sprintf(msg, WELCOME_MSG, comma, sys_vars.user);
	ab_message(msg);
	user_vars.stayontop = TRUE;
	user_vars.chime = FALSE;
	user_vars.date = FALSE;
	user_vars.bottom = FALSE;
	user_vars.time = TRUE;
	user_vars.user = FALSE;
	user_vars.memory = TRUE;
	user_vars.autohide = TRUE;
	strcpy(user_vars.wavfile, "");
	rc = RegSetValueEx(root, "User_Variables", NULL, REG_BINARY, 
				(PBYTE) &user_vars, sizeof(user_options));
	if (rc != ERROR_SUCCESS)
		ab_message(ERROR_SAVING_REG);
}

void save_reg_keys(void)
{
	HKEY root;
	char keyname[80];
	DWORD isnew;
	LONG rc;

	if (strcmp((char*)sys_vars.user, ""))
		sprintf(keyname, "Software\\AppBar\\%s",sys_vars.user);
	  else
		strcpy((char*)keyname, "Software\\AppBar\\Default");

	rc = RegCreateKeyEx(HKEY_CURRENT_USER, keyname, 0, NULL,
				REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &root, &isnew);
	rc = RegSetValueEx(root, "User_Variables", NULL, REG_BINARY, 
				(PBYTE)&user_vars, sizeof(user_options));
	if (rc != ERROR_SUCCESS)
		ab_message(ERROR_SAVING_REG);
	RegCloseKey(root);
}

// Initialize system-dependent variables

BOOL init_app(void)
{
	HWND hOldWnd = FindWindow("ABClass", "AppBar");
	if (hOldWnd) {
		BringWindowToTop(hOldWnd);
		return FALSE;
	}

	DWORD dwVersion = GetVersion();
	DWORD dwMajor =  (DWORD)(LOBYTE(LOWORD(dwVersion)));
	DWORD dwMinor =  (DWORD)(HIBYTE(LOWORD(dwVersion)));

	if (dwVersion < 0x80000000) {               // Windows NT
		if (dwMajor == 3) {
			sys_vars.newshell = FALSE;
			sys_vars.power = FALSE;
		  } else if (dwMajor == 4) {
			sys_vars.newshell = TRUE;
			sys_vars.power = FALSE;
		  } else {  // NT5!
			sys_vars.newshell = TRUE;
			sys_vars.power = TRUE;
		}
	} else if (dwMajor < 4)        // Win32s - this should never happen
		return FALSE;
	  else {        // Windows 95 -- No build numbers provided
		sys_vars.newshell = TRUE;
		sys_vars.power = TRUE;
	}

	if (sys_vars.power) {
		SYSTEM_POWER_STATUS sps;
		GetSystemPowerStatus(&sps);
		if (sps.ACLineStatus)
			sys_vars.battery = FALSE;
		  else
			sys_vars.battery = TRUE;
	}

	sys_vars.width = GetSystemMetrics(SM_CXSCREEN);
	sys_vars.height = GetSystemMetrics(SM_CYSCREEN);

	// copy AppBar's directory to origdir
	
	GetModuleFileName(GetModuleHandle(NULL), origdir, PATH_SIZE);
	char *end = strrchr(origdir, '\\');
	char *front = (char *) origdir;

	while (front != end)
		front++;
	*front = '\0';

	parse_cmd_args();
	popup = GetSubMenu(LoadMenu(ab_inst, MAKEINTRESOURCE(IDR_MENU)),0);
	return TRUE;
}   
	
// Creates and displays window based on user options    
	
BOOL setup_win(void)
{
	if (!create_appbar())
		return FALSE;
	if (!read_in_apps())
		return FALSE;
	if (!show_appbar())
		return FALSE;                              
	return TRUE;
}

// Print error message and exit program

void error(char *err_msg)
{
	MessageBox(NULL, err_msg, FATAL_ERROR, MB_OK | MB_ICONSTOP);
	_fcloseall();
	exit_appbar(TRUE);
	PostQuitMessage(-1);
}                            
						 
// Initialize and register window class

BOOL create_appbar(void)
{
	ab_wc.style = NULL;                   
	ab_wc.lpfnWndProc = AppBarWinProc;  
										
	ab_wc.cbClsExtra = 0;                 
	ab_wc.cbWndExtra = 0;                
	ab_wc.hInstance = ab_inst;           
	ab_wc.hIcon = LoadIcon(ab_inst, MAKEINTRESOURCE(IDI_APPBAR));
	ab_wc.hCursor = NULL;
	if (!sys_vars.newshell)
		ab_wc.hbrBackground = NULL;
	  else
		ab_wc.hbrBackground = (HBRUSH) ((DWORD) COLOR_MENU + 1);
	ab_wc.lpszMenuName =  (char *)IDR_MENU;
	ab_wc.lpszClassName = "ABClass"; 

	return (RegisterClass(&ab_wc));
}           

// Reads in the user spec'd applications

BOOL read_in_apps(void)
{               
	FILE *appfile;
	int i, j=0, ver;
	BOOL exist = TRUE;
	char msg[80];
	menu_struct *cur_menu, *nextmenu, *prevmenu;
	app_struct *cur_app, *nextapp, *prevapp;

	// Create binary data file if none exists                            
	
	_chdir(origdir);
	if ((appfile = fopen(sys_vars.appfile, "r")) == NULL)
		exist = FALSE;
											 
	// Read application data until the end of the file
	// this tests for zero-length data files (exist, but are empty)
	if (exist)
		if (_filelength(_fileno(appfile)) == 0)
			exist = FALSE;

	if (exist) {
		fread(&ver, sizeof(int), 1, appfile);
		if (ver != APPBAR_FILE_VERSION)
			error(OLD_DATAFILE_FORMAT);
		cur_menu = new menu_struct;
		glob_menu = cur_menu;
		nextmenu = cur_menu;
		prevmenu = NULL;
		while (fread(nextmenu, sizeof(menu_struct), 1, appfile)) {
			j++;
			cur_menu = nextmenu;
			cur_menu->nextapp = NULL;
			prevapp = NULL;
			cur_menu->prevmenu = prevmenu;
			if (nextmenu->numapps) {
				cur_app = new app_struct;
				cur_menu->nextapp = cur_app;
				for (i=cur_menu->numapps;i>0; i--) {
					if (!fread(cur_app, sizeof(app_struct), 1, appfile)) {
						sprintf(msg, ERROR_READING_MENUS, j,
										cur_menu->numapps - i + 1, sys_vars.appfile);
						error(msg);
					}
					cur_app->prevapp = prevapp;
					prevapp = cur_app;
					if (i-1) {
						cur_app->nextapp = new app_struct;
						cur_app = cur_app->nextapp;
					  } else cur_app->nextapp = NULL;
				}
			}
			prevmenu = cur_menu;
			nextmenu = new menu_struct;
			nextmenu->prevmenu = cur_menu;
			cur_menu->nextmenu = nextmenu;
		}
		// Reached EOF.  Now we need to delete that last menu, since it was
		// created before we knew it was EOF.
		delete nextmenu;
		cur_menu->nextmenu = NULL;
		fclose(appfile);
	} else {
		// Create default menu structure 
		char path[80];
		menu_struct *tempmenu;

		tempmenu = new menu_struct;
		strcpy(tempmenu->menuname,"&Apps");
		tempmenu->numapps = 2;

		tempmenu->nextapp = new app_struct;
		strcpy(tempmenu->nextapp->appexe, "c:\\vc40\\bin\\msdev.exe");
		strcpy(tempmenu->nextapp->appname, "Visual &C++ v4.0");
		cur_app = tempmenu->nextapp;

		nextapp = new app_struct;
		cur_app->nextapp = nextapp;
		nextapp->prevapp = cur_app;
		strcpy(nextapp->appexe, "c:\\winword\\winword.exe");
		strcpy(nextapp->appname, "&Word v7.0");
		glob_menu = tempmenu;

		tempmenu = new menu_struct;
		glob_menu->nextmenu = tempmenu;
		tempmenu->prevmenu = glob_menu;
		strcpy(tempmenu->menuname,"&Games");
		tempmenu->numapps = 2;
		
		tempmenu->nextapp = new app_struct;
		GetWindowsDirectory(path, sizeof(path));
		strcat(path,"\\winmine.exe");
		strcpy(tempmenu->nextapp->appexe, path);
		strcpy(tempmenu->nextapp->appname, "&Minesweeper");
		cur_app = tempmenu->nextapp;

		nextapp = new app_struct;
		cur_app->nextapp = nextapp;
		nextapp->prevapp = cur_app;
		GetWindowsDirectory(path, sizeof(path));
		strcat(path,"\\sol.exe");
		strcpy(nextapp->appexe, path);
		strcpy(nextapp->appname, "&Solitaire");
	}
	return TRUE;
}                                 

// Exit function for appbar

void exit_appbar(BOOL error_exit)
{
	if (!error_exit) {  // if error, just bomb out...
		save_menus();
		save_reg_keys();
		release_app_memory();
	}
	destroy_window();
}   

// Release application linked list memory

void release_app_memory(void)
{             
	menu_struct *menu, *front;
	
	menu = glob_menu;
	if (!menu)
		return;
	front = menu->nextmenu;
	while (front!=NULL) {            
		killmenu(menu);
		menu = front;
		front = front->nextmenu;
	}
	killmenu(menu);
}

// Deletes menu list and frees resources

void kill_applist(void)
{
	app_list *curapplist;

	if (applist) {                  // Kill off old app list
		curapplist = applist;
		while (curapplist!=NULL) {
			curapplist = applist->next;
			delete applist;
			applist = curapplist;
		}
	}
}

void killmenu(menu_struct *menu)
{
	app_struct *app, *front;

	if (!menu)                  // Null menu
		return;
	app = menu->nextapp;
	if  (!app) {                // Menu w/o applications (?)
		delete menu;
		return;
	}
	front = app->nextapp;
	while (front!=NULL) {
		delete app;
		app = front;
		front = front->nextapp;
	}
	delete app;
	delete menu;
}

// Updates app linked list and deletes app node
// DOES NOT update menu->nextapp (calling code should)

void killapp(app_struct * app)
{
	if (!app)
		return;
	delete app;
}

// Unregister and destroy window class    
	
void destroy_window(void)
{
	if (sys_vars.newshell) {
		abd.cbSize = sizeof(APPBARDATA);
		abd.hWnd = ab_hwnd;
		abd.uEdge = (user_vars.bottom ? ABE_BOTTOM : ABE_TOP);
		abd.lParam = FALSE;
		SHAppBarMessage(ABM_SETAUTOHIDEBAR, &abd);
		SHAppBarMessage(ABM_REMOVE, &abd);
	}
	DestroyIcon(ab_wc.hIcon);
	DestroyMenu(ab_menu);
	DestroyMenu(popup);
	KillTimer(ab_hwnd, TIME_UPDATE);
	KillTimer(ab_hwnd, HIDE_TIMER);
	KillTimer(ab_hwnd, SYNC_TIMER);
	DestroyWindow(ab_hwnd);
	UnregisterClass("ABClass", ab_inst);
}

inline void ab_message(char * msg)
{
	MessageBox(ab_hwnd, msg, "AppBar", MB_OK | MB_ICONEXCLAMATION);
}

// Execute application pointed to by app

BOOL execute_application(app_struct * app)
{
	char msg[200];
	DWORD error;

	if (sys_vars.newshell) {
		char file[80];
		char dir[80];
		char params[80];
		int show;
		SHELLEXECUTEINFO sei;

		sei.cbSize = sizeof(SHELLEXECUTEINFO);
		sei.fMask = SEE_MASK_DOENVSUBST | SEE_MASK_NOCLOSEPROCESS;
		sei.hwnd = ab_hwnd;
		sei.lpVerb = "open";

		if (IsLink(app->appexe)) {
			if (!SUCCEEDED(GetLinkInfo(ab_hwnd, app->appexe, (LPSTR)file, (LPSTR)dir, (LPSTR)params, &show))) {
				ab_message(ERROR_LINK);
				return FALSE;
			}
			sei.lpFile = file;
			sei.lpDirectory = dir;
			sei.lpParameters = params;
			sei.nShow = show;
		  } else {
			sei.lpFile = app->appexe;
			sei.lpParameters = app->params;
			sei.lpDirectory = app->workingdir;
			sei.nShow = app->show;
		}
		ShellExecuteEx(&sei);

	} else {
		error = (DWORD) ShellExecute(ab_hwnd, "open", app->appexe, app->params, app->workingdir, app->show);
		if (error < 32) {
			switch (error) {
				case ERROR_FILE_NOT_FOUND:
					sprintf(msg, FILE_NOT_FOUND, app->appexe);
					break;
				case ERROR_PATH_NOT_FOUND:
					sprintf(msg, PATH_NOT_FOUND, app->appexe);
					break;
				default:
					sprintf(msg, RETURNED_ERROR, error);
					break;
			}
			ab_message(msg);
			return 0;
		}
	}
	return 1;
}

// the file is a link if it ends in ".LNK"

BOOL IsLink(char *filename)
{
	int len = strlen(filename);
	char *extension = filename + len - 4;

	if (_strnicmp(extension, ".lnk", 4))
		return FALSE;
	return TRUE;
}

// This hideous function courtesy of MS's Knowledge Base (search VC4 help for IShellLink)

HRESULT GetLinkInfo(HWND hWnd, LPSTR lpszLinkName, LPSTR lpszFile, LPSTR lpszDir, LPSTR lpszArgs, int *show)
{ 
	HRESULT hres;
	IShellLink *psl;
	WIN32_FIND_DATA wfd;

	CoInitialize(0);
	hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
						   IID_IShellLink,(LPVOID *)&psl );
   
	if (SUCCEEDED(hres)) {
		IPersistFile *ppf;
		hres = psl->QueryInterface(IID_IPersistFile,(LPVOID *)&ppf);
		if (SUCCEEDED(hres)) {
			WORD linkName[MAX_PATH];
			MultiByteToWideChar(CP_ACP, 0, lpszLinkName, -1, linkName, MAX_PATH);
			hres = ppf->Load(linkName, STGM_READ);
			if (SUCCEEDED(hres)) {
				// Resolve the link by calling the Resolve() interface function.
				hres = psl->Resolve(hWnd, SLR_ANY_MATCH | SLR_NO_UI);
				if (SUCCEEDED(hres)) {
					hres = psl->GetPath(lpszFile, MAX_PATH, &wfd, SLGP_SHORTPATH);
					hres = psl->GetWorkingDirectory(lpszDir, MAX_PATH );
					hres = psl->GetArguments(lpszArgs, MAX_PATH);
					hres = psl->GetShowCmd(show);
					if (!SUCCEEDED(hres))
						goto cleanup;
				}
			}
			ppf->Release();
		}
		psl->Release();
	}
	goto cleanup;

cleanup:
	CoUninitialize();
	return hres;
}


LRESULT CALLBACK AboutProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
		case WM_INITDIALOG:
			return TRUE;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK) {
				EndDialog(hDlg, TRUE);
				return TRUE;
			}
			break;
		default:
			return FALSE;
	}
	return FALSE;
}
/*
LRESULT CALLBACK RunProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
		case WM_INITDIALOG:
			SetFocus(GetDlgItem(hDlg, IDC_RUNTEXT));
			return FALSE;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK) {
				char command[120];

				SHELLEXECUTEINFO sei;
				SendMessage(GetDlgItem(hDlg, IDC_RUNTEXT), WM_GETTEXT, sizeof(command), (LPARAM)command);
				if (strcmp(command, "")) {
					char *token = command;
					char *exe = command;
					char params[80];

					// we have to tokenize the command line into EXE and parameters...
					// POINTER STEW (obfuscated C joke)
					while (*token != ' ' && *token != NULL) {
						if (*token == '"') {
							exe++;
							while ((*(token+1)) != '"')
								token++;
							token += 2;
							*(token-1) = '\0';
							break;
						} else
							token++;
					}

					strcpy(params, "");
					if (token != NULL)
						strcpy(params, token+1);
					*token = '\0';

					sei.fMask = SEE_MASK_DOENVSUBST | SEE_MASK_NOCLOSEPROCESS;
					sei.cbSize = sizeof(SHELLEXECUTEINFO);
					sei.hwnd = ab_hwnd;
					sei.lpVerb = NULL;
					sei.lpFile = exe;
					sei.lpParameters = params;
					sei.lpDirectory = NULL;
					sei.nShow = SW_NORMAL;
					ShellExecuteEx(&sei);
				}
				EndDialog(hDlg, TRUE);
				return TRUE;
			} else if (wParam == IDCANCEL) {
				EndDialog(hDlg, TRUE);
				return TRUE;
			}               
			break;
		default:
			return FALSE;
	}
	return FALSE;
}
*/
// Finds menu by name in list

menu_struct * find_menu(char * menu_sel)
{
	menu_struct * menu;

	for (menu = glob_menu; menu != NULL; menu = menu->nextmenu)
		if (!strcmp(menu->menuname,menu_sel))
			return menu;
	ab_message(ERROR_FINDING_MENU);   
	return NULL;
}

app_struct * find_app(app_struct * apps, char * app_sel)
{
	app_struct * app;

	if (!strcmp(app_sel, SEPARATOR_STRING))
		return NULL;
	for (app = apps; app != NULL; app = app->nextapp)
		if (!strcmp(app_sel,app->appname))
			return app;
	ab_message(ERROR_FINDING_APP);
	return NULL;
}

void save_menus(void)
{
	app_struct * pCurApp;
	menu_struct * pCurMenu;
	app_struct *next, *prev, *nexta;
	menu_struct *nextm, *prevm;
	char * datafile, msg[80];
	FILE * pDataFile;
	int i;
	
	_chdir(origdir);
	if (strcmp(sys_vars.appfile, ""))
		datafile = (char *)sys_vars.appfile;
	  else
		datafile = "default.ab";
	pDataFile = fopen(datafile, "wb");      // Open for binary write

	if (!pDataFile) {
		sprintf(msg, ERROR_OPENING_DATAFILE, datafile);
		ab_message(msg);
		return;
	}
	
	i = APPBAR_FILE_VERSION;
	fwrite(&i, sizeof(int), 1, pDataFile);
	for (pCurMenu = glob_menu; pCurMenu != NULL; pCurMenu = pCurMenu->nextmenu) {
		nextm = pCurMenu->nextmenu;
		prevm = pCurMenu->prevmenu;
		nexta = pCurMenu->nextapp;
		pCurMenu->nextapp = NULL;
		pCurMenu->nextmenu = NULL;
		pCurMenu->prevmenu = NULL;
		fwrite(pCurMenu, sizeof(menu_struct), 1, pDataFile);
		pCurMenu->nextapp = nexta;
		pCurMenu->nextmenu = nextm;
		pCurMenu->prevmenu = prevm;
		for (pCurApp = pCurMenu->nextapp; pCurApp != NULL; pCurApp = pCurApp->nextapp) {
			next = pCurApp->nextapp;
			prev = pCurApp->prevapp;
			pCurApp->nextapp = NULL;
			pCurApp->prevapp = NULL;
			fwrite(pCurApp, sizeof(app_struct), 1, pDataFile);
			pCurApp->nextapp = next;
			pCurApp->prevapp = prev;
		}
	}
	fclose(pDataFile);
}

void DoBrowse(int type, HWND parent) 
{ 
	OPENFILENAME ofn;
	char szFile[80];
	
	strcpy(szFile,""); 

	ofn.lStructSize       = sizeof(OPENFILENAME); 
	ofn.hwndOwner         = parent; 
	ofn.hInstance         = NULL; 
	ofn.lpstrFilter       = (type ? WAV_FILE_TYPES : EXE_FILE_TYPES); 
	ofn.lpstrCustomFilter = NULL; 
	ofn.nMaxCustFilter    = 0L; 
	ofn.nFilterIndex      = 1L; 
	ofn.lpstrFile         = szFile; 
	ofn.nMaxFile          = sizeof(szFile); 
	ofn.lpstrFileTitle    = NULL; 
	ofn.nMaxFileTitle     = 0; 
	ofn.lpstrInitialDir   = "C:\\"; 
	ofn.lpstrTitle        = (type ? FIND_WAV : FIND_EXE); 
	ofn.nFileOffset       = 0; 
	ofn.nFileExtension    = 0; 
	ofn.lpstrDefExt       = NULL; 
	ofn.lCustData         = 0; 
	ofn.Flags             = OFN_SHOWHELP | OFN_PATHMUSTEXIST
									 | OFN_FILEMUSTEXIST 
									 | OFN_HIDEREADONLY; 
	if (GetOpenFileName(&ofn))
		if (type) { // Wav file 
			SendMessage(GetDlgItem(parent, IDC_WAVNAME), WM_SETTEXT, 0, (LPARAM)ofn.lpstrFile);
			SetFocus(GetDlgItem(parent, IDOK));
		  } else {  // Application executable
			SendMessage(GetDlgItem(parent, IDC_EXENAME), WM_SETTEXT, 0, (LPARAM)ofn.lpstrFile);
			SetFocus(GetDlgItem(parent, IDOK));
		}
} 

///////////////////////////////////////////////////////////////////////////
//  C++ Constructors and Destructors                                     //
///////////////////////////////////////////////////////////////////////////

menu_struct::menu_struct()
{
	memset((void*)menuname, 0, sizeof(menuname));
	numapps = 0;
	nextmenu = NULL;
	prevmenu = NULL;
	nextapp = NULL;
}

menu_struct::~menu_struct()
{
	if (nextmenu == NULL) {
		if (prevmenu != NULL)
			prevmenu->nextmenu = NULL;
		  else
			glob_menu = NULL;
	  } 
	else if (prevmenu == NULL) {
		glob_menu = nextmenu;
		nextmenu->prevmenu = NULL;
	  } 
	else {
		if (prevmenu)
			prevmenu->nextmenu = nextmenu;
		if (nextmenu) 
			nextmenu->prevmenu = prevmenu;
	}
}

app_struct::app_struct()
{
	memset((void*)appexe, 0, sizeof(appexe));
	memset((void*)workingdir, 0, sizeof(workingdir));
	memset((void*)params, 0, sizeof(params));
	memset((void*)appname, 0, sizeof(appname));
	show = SW_SHOW;
	separator = FALSE;
	nextapp = NULL;
	prevapp = NULL;
}

app_struct::~app_struct()
{
	if (nextapp == NULL) {
		if (prevapp != NULL)
			prevapp->nextapp = NULL;
	  } 
	else if (prevapp == NULL)
		nextapp->prevapp = NULL;
	else {
		prevapp->nextapp = nextapp;
		nextapp->prevapp = prevapp;
	}
}
