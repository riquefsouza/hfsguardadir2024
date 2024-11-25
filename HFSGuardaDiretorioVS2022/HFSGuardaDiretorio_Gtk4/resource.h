#ifndef RESOURCE_H
#define RESOURCE_H
// ---------------------------------------------------------------------------
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <time.h>	
	#include <stdbool.h>
	#include <ctype.h>
	#include <locale.h>

	#include <gtk/gtk.h>
	#include <gdk/gdkkeysyms.h>
	#include <gdk-pixbuf/gdk-pixbuf.h>
	
	#include <glib.h>
	#include <glib-object.h>
	#include <glib/gstdio.h>
	#include <glib/gprintf.h>
	#include <glib/gfileutils.h>
	#include <gio/gio.h>
	
// ---------------------------------------------------------------------------
	#ifdef HAVE_CONFIG_H
		#include "config.h"
	#endif

	#ifdef G_OS_WIN32
		#include <windows.h>
	#else
		#include <unistd.h>
	#endif
// ---------------------------------------------------------------------------
	/* macros gettext padroes. */
	#ifdef ENABLE_NLS
	  #include <libintl.h>
	  #undef _
	  #define _(String) dgettext (PACKAGE, String)
	  #ifdef gettext_noop
		#define N_(String) gettext_noop (String)
	  #else
		#define N_(String) (String)
	  #endif
	#else
	  #define textdomain(String) (String)
	  #define gettext(String) (String)
	  #define dgettext(Domain,Message) (Message)
	  #define dcgettext(Domain,Message,Type) (Message)
	  #define bindtextdomain(Domain,Directory) (Domain)
	  #define _(String) (String)
	  #define N_(String) (String)
	#endif
// ---------------------------------------------------------------------------

extern const char* XPM_ARQUIVO[];
extern const char* XPM_ARQUIVO32[];
extern const char* XPM_CDOURO[];
extern const char* XPM_CDPRATA[];
extern const char* XPM_DIR_ABERTO[];
extern const char* XPM_DIR_ABERTO32[];
extern const char* XPM_DIRETORIO[];
extern const char* XPM_DIRETORIO32[];
extern const char* XPM_SPLASH[];

#endif
