This is the C version of the AppBar source code.  It uses raw Win32
API programming which means you get a lean and fast executable (are
you sick of 1.5 MB toolbars written in VB too?).

There are 3 user changable settings:

a) source debugging (you only need this if you are adding new features
   to Appbar);
b) language - right now you can set either English or German
c) OS - set if you are running WinNT 3.x.

Please see the makefile for more info.

PS the C source also has all the hooks for a Run... dialog.  It is not
supported but if you want to uncomment it, go ahead, just don't mail
me with problems.
