## Process this file with automake to produce Makefile.in

## Created by Anjuta

gladedir = $(datadir)/gtk_windowwatcher/glade
glade_DATA = gtk_windowwatcher.glade

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(GTK_WINDOWWATCHER_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = gtk_windowwatcher

gtk_windowwatcher_SOURCES = \
	callbacks.c \
	callbacks.h \
	main.c

gtk_windowwatcher_LDFLAGS = \
	-Wl,--export-dynamic

gtk_windowwatcher_LDADD = $(GTK_WINDOWWATCHER_LIBS)

EXTRA_DIST = $(glade_DATA)

# Remove glade directory on uninstall
uninstall-local:
	-rm -r $(gladedir)
	-rm -r $(datadir)/gtk_windowwatcher
