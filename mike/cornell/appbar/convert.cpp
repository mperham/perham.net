#include <stdio.h>
#include <string.h>

typedef long BOOL;
typedef unsigned long DWORD;

class app_struct {
  public:
	char appexe[80],            // Path and name of executable
		 workingdir[80],        // Working dir
		 params[90],            // command line parameters
		 appname[30];           // Name of application for menubar
	DWORD show;                 // Maximize, Minimize, etc.
	BOOL separator;             // Separator before this app?
	app_struct *nextapp;        // Pointer to next app
	app_struct *prevapp;
	
	app_struct();
	~app_struct() {};
};

class old_app_struct {
  public:
	char appexe[80],            // Path and name of executable
		 workingdir[80],        // Working dir
		 params[30],            // command line parameters
		 appname[30];           // Name of application for menubar
	BOOL separator;             // Separator before this app?
	app_struct *nextapp;        // Pointer to next app
	app_struct *prevapp;
	
	old_app_struct();
	~old_app_struct() {};
};

class menu_struct {
  public:
	char menuname[30];              // name of menu
	int numapps;                    // number of apps in menu
	menu_struct *nextmenu;          // pointer to next menu
	menu_struct *prevmenu;
	app_struct *nextapp;            // pointer to first app in menu
	
	menu_struct();
	~menu_struct() {};
};

void convert(char *name);
void change(old_app_struct *old, app_struct *knew);

void main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("\n\tUsage: %s datafilename\n\n", argv[0]);
		printf("Converts \"datafilename\" to the new AppBar 0.99 format.\n");
		printf("Saves a backup copy to \"$$backup.ab\".\n");
		return;
	}
	convert(argv[1]);
	printf("Done...\n");
}

void convert(char *name)
{               
	FILE *oldfile, *newfile;
	int i, ver, newver = 102;
	menu_struct *menu = new menu_struct;
	app_struct *app = new app_struct;
	old_app_struct *old = new old_app_struct;
	
	rename(name, "$$backup.ab");
	oldfile = fopen("$$backup.ab", "r");
	newfile = fopen(name, "wb");
	fread(&ver, sizeof(int), 1, oldfile);
	fwrite(&newver, sizeof(int), 1, newfile);
	if (ver != 100)	{		// old AppBar file version number
		printf("File is not an old AppBar (<= v0.98) datafile.");
		return;
	}
	while (fread(menu, sizeof(menu_struct), 1, oldfile)) {
		fwrite(menu, sizeof(menu_struct), 1, newfile);
 		if (menu->numapps)
			for (i=menu->numapps;i>0; i--) {
				if (!fread(old, sizeof(old_app_struct), 1, oldfile))
					break;
				change(old, app);
				fwrite(app, sizeof(app_struct), 1, newfile);
				delete app;
				app = new app_struct;  // clear new app structure
			}
	}
	fclose(oldfile);
	fclose(newfile);
	delete menu;
	delete app;
	return;
}

void change(old_app_struct *old, app_struct *knew)
{
	strcpy(knew->appexe, old->appexe);
	strcpy(knew->workingdir, old->workingdir);
	strcpy(knew->params, old->params);
	strcpy(knew->appname, old->appname);
	knew->show = 0;
	knew->separator = old->separator;
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

#define FALSE NULL

app_struct::app_struct()
{
	memset((void*)appexe, 0, sizeof(appexe));
	memset((void*)workingdir, 0, sizeof(workingdir));
	memset((void*)params, 0, sizeof(params));
	memset((void*)appname, 0, sizeof(appname));
	show = 0;
	separator = FALSE;
	nextapp = NULL;
	prevapp = NULL;
}

old_app_struct::old_app_struct()
{
	memset((void*)appexe, 0, sizeof(appexe));
	memset((void*)workingdir, 0, sizeof(workingdir));
	memset((void*)params, 0, sizeof(params));
	memset((void*)appname, 0, sizeof(appname));
	separator = FALSE;
	nextapp = NULL;
	prevapp = NULL;
}
