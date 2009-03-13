##############################################################
#
# Visual C++ v4.x Makefile for AppBar
#
# You will need to set the LIBPATH and other variables.
# In VC4.x, you do this by running VCVARS32.BAT found
# in the BIN dir.
#
##############################################################
#           User configurable options
# Uncomment if debugging
#LDBG=-debug
#CDBG=-Zi

###### Uncomment if Windows NT 3.x
#OPSYS=-D_WINNT

###### Language (Uncomment your language)

#LANG=ENGLISH
LANG=GERMAN

#
##############################################################
# minimize size, Pentium opt, disable stack checking
CPPFLAGS=-O1 -Gs -G5 -W3 -DWIN32 -D_X86_ -D$(LANG) $(CDBG) $(OPSYS) -nologo
LINKOPTS=-subsystem:windows -machine:IX86 -nologo $(LDBG)

LIBS=kernel32.lib gdi32.lib winmm.lib user32.lib shell32.lib\
	 advapi32.lib comdlg32.lib ole32.lib uuid.lib
OBJS=appbar.obj util.obj
RES=appbar-$(LANG).res

all: appbar

appbar: $(OBJS) $(RES)
	link $(LINKOPTS) -out:appbar.exe \
	$(OBJS) $(RES) $(LIBS)

clean:
	del *.obj
	del *.res
	del *.exe
	del *.ncb
	del *.aps
