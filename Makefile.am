## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src 

gtk_windowwatcherdocdir = ${prefix}/doc/gtk_windowwatcher
gtk_windowwatcherdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


EXTRA_DIST = $(gtk_windowwatcherdoc_DATA)


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(gtk_windowwatcherdocdir)
