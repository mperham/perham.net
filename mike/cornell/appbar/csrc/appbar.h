#ifndef APPBAR_H
#define APPBAR_H

#define STRICT
#include <windows.h>            
#include <mmsystem.h>           // PlaySound
#include <shellapi.h>           // ShellExecute and SHAppBarMessage
#include <stdio.h>              // sprintf, fopen, fclose, fread, fwrite
#include <time.h>               // tzset, time, localtime
#include <io.h>                 // _filelength
#include <direct.h>
#include <shlobj.h>
#include "resource.h"
#include "strings.h"

#define AB_HEIGHT			(GetSystemMetrics(SM_CYMENU)+5)
#define AB_WIDTH			sys_vars.width
#define PATH_SIZE			128
// Colors for battery percentage
#define RED                 RGB(192,0,0)
#define BRIGHT_RED          RGB(255,0,0)
#define GREEN               RGB(0,128,0)
#define YELLOW              RGB(255,255,0)
// Version number for datafile format
#define APPBAR_FILE_VERSION 103
#define TRUE                1
#define FALSE               0
#define SYNC_TIMER			0xD000
#define TIME_UPDATE         0xE000
#define HIDE_TIMER          0xF000
#define WM_APPBAR           (WM_USER+1)
#define SEPARATOR_STRING    "-------"
#define UP                  VK_UP       // These 2 are needed for
#define DOWN                VK_DOWN     // switch_places()

#ifdef _WINNT       // overrides for NT differences
	#undef AB_HEIGHT
	#define AB_HEIGHT (GetSystemMetrics(SM_CYMENU)+10)
#endif

// Structures and classes

struct user_options {
	BOOL stayontop;                 // Does ab always float on top?
	BOOL chime;                     // Play sound every hour?
	BOOL date;                      // Display date on menu bar?
	BOOL memory;                    // Display free memory?
	BOOL bottom;                    // Place AppBar at bottom of screen?
	BOOL autohide;                  // Auto hide AppBar?
	BOOL time;
	BOOL user;
	char wavfile[PATH_SIZE];        // Path/filename of WAV file to play
};

struct ab_vars {
	int width;                  // Screen width  (i.e. 800)
	int height;                 // Screen height (ie 600)
	BOOL power;
	BOOL newshell;
	BOOL battery;               // AC or battery?
	char user[30];              // Optional username
	char appfile[PATH_SIZE];    // DAT filename
};

class app_struct {
  public:
	char appexe[PATH_SIZE],     // Path and name of executable
		 workingdir[PATH_SIZE], // Working dir
		 params[90],            // command line parameters
		 appname[30];           // Name of application for menubar
	DWORD show;                 // Maximize, Minimize, etc.
	BOOL separator;             // Separator before this app?
	app_struct *nextapp;        // Pointer to next app
	app_struct *prevapp;
	
	app_struct();
	~app_struct();
};

class menu_struct {
  public:
	char menuname[30];              // name of menu
	int numapps;                    // number of apps in menu
	menu_struct *nextmenu;          // pointer to next menu
	menu_struct *prevmenu;
	app_struct *nextapp;            // pointer to first app in menu
	
	menu_struct();
	~menu_struct();
};

// Used to find appliction structure based on a user-selected menu item

struct app_list {
	int appId;                      // menuID related to app (1000*m +a)
	app_struct *app;                // related app structure
	app_list *next;
};                         

// Used to make deleting and updating menu bar easier

struct menu_list {
	HMENU menuId;                   // Menu resource # related to menu
	menu_struct *menu;
	menu_list *next;
};

// used to pass new menu or app data to window procedure

struct hack {
	app_struct *app;
	menu_struct *menu;
	BOOL isnew;
};

extern int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmdline, int cmdshow);
extern LRESULT CALLBACK AppBarWinProc(HWND hWnd, UINT msg, WPARAM lParam, LPARAM wParam);
extern LRESULT CALLBACK AboutProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
extern LRESULT CALLBACK EditProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
extern LRESULT CALLBACK OptionsProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
extern LRESULT CALLBACK AppProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
extern LRESULT CALLBACK MenuProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
//extern LRESULT CALLBACK RunProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
extern BOOL execute_application(app_struct *app);
extern void error(char *err_msg);
extern BOOL init_app(void);
extern void save_reg_keys(void);
extern void make_new_reg_key(HKEY root);
extern void get_reg_keys(user_options *args);
extern void HideAppBar(BOOL hide);
extern BOOL setup_win(void);
extern BOOL read_in_apps(void);
extern BOOL create_appbar(void);
extern BOOL show_appbar(void);
extern void exit_appbar(BOOL error_exit);
extern void release_app_memory(void);
extern void killmenu(menu_struct *menu);
extern void destroy_window(void);
extern void save_menus(void);
extern void ab_message(char *msg);
extern void update_menus(void);
extern void kill_applist(void);
extern void killapp(app_struct * app);
extern app_struct * find_appId(UINT menuId);
extern app_struct * find_app(app_struct *apps, char *app_sel);
extern menu_struct * find_menu(char * menu_sel);
extern BOOL modify_time(void);
extern BOOL switch_places_m(menu_struct *menu, int dir);
extern BOOL switch_places_a(app_struct *app, int dir);
extern void DoBrowse(int type, HWND parent);
extern void draw_buttons(DRAWITEMSTRUCT *dw, UINT CtlID);
extern void parse_cmd_args(void);
extern void SlideWindow(int newy);
extern HRESULT GetLinkInfo(HWND hWnd, LPSTR lpszLinkName, LPSTR lpszPath, LPSTR lpszDir, LPSTR lpszArgs, int *show);
extern BOOL IsLink(char *filename);
extern void SyncTime(void);
#endif
