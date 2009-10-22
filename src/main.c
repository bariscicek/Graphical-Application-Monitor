/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) Barış Çiçek 2009 <draco@arginine>
 * 
 * gtk-windowwatcher is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gtk-windowwatcher is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define WNCK_I_KNOW_THIS_IS_UNSTABLE

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include <config.h>

#include <gtk/gtk.h>
#include <glade/glade.h>

#include <libwnck/libwnck.h>





#include "callbacks.h"

/* For testing propose use the local (not installed) glade file */
/* #define GLADE_FILE PACKAGE_DATA_DIR"/gtk_windowwatcher/glade/gtk_windowwatcher.glade" */
#define GLADE_FILE "gtk_windowwatcher.glade"

GladeXML *gxml;

GtkWidget*
create_window (void)
{
	GtkWidget *window;
	
	gxml = glade_xml_new (GLADE_FILE, NULL, NULL);
	
	/* This is important */
	glade_xml_signal_autoconnect (gxml);
	window = glade_xml_get_widget (gxml, "window");
	
	return window;
}

void
add_text (const gchar *rowtext)
{
	GtkWidget *textview;
	GtkTextBuffer *buffer;
	

	textview = glade_xml_get_widget (gxml, "textview");
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textview));
	gtk_text_buffer_insert_at_cursor (buffer, rowtext, -1);
	/* FIXME: don't call api twice instead add \n to rowtext */
	gtk_text_buffer_insert_at_cursor (buffer, "\n", -1);	
	//gtk_text_view_set_buffer (textview, buffer);
	
}

void
main (int argc, char *argv[])
{
    GtkWidget *window;
    WnckScreen *current_screen;
    GList *window_list = NULL;
    GList *item = NULL;
    gchar *name = NULL;



    gtk_set_locale ();
    gtk_init (&argc, &argv);


    current_screen = wnck_screen_get_default ();
    g_return_if_fail (current_screen != NULL);
    wnck_screen_force_update(current_screen);
    window_list = wnck_screen_get_windows (current_screen);
    name = wnck_screen_get_window_manager_name (current_screen);

    window = create_window ();
    for (item = g_list_first (window_list); item->next != NULL; item = item->next) {
        WnckApplication *application;
        gchar *log;
        gchar *app_name;
        gchar *window_title;
        time_t timestamp;

        application = wnck_window_get_application (item->data);
        app_name = wnck_application_get_name (application);
        window_title = wnck_window_get_name (item->data);
        timestamp = time (NULL);
        g_print("[%d] %s - %s\n", timestamp, app_name, window_title);
                
    }

    gtk_widget_show (window);

    gtk_main ();
}


