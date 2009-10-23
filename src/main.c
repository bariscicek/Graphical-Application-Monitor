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
#include <glib-2.0/glib.h>
#include <glade/glade.h>

#include <libwnck/libwnck.h>

#include "gtk_windowwatcher.h"





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



    gtk_set_locale ();
    gtk_init (&argc, &argv);


    current_screen = wnck_screen_get_default ();
    g_return_if_fail (current_screen != NULL);
    wnck_screen_force_update(current_screen);
    window_list = wnck_screen_get_windows (current_screen);

    window = create_window ();
    for (item = g_list_first (window_list); item->next != NULL; item = item->next) {
        WnckApplication *application;
        gchar *log;
        gchar *window_node;

        application = wnck_window_get_application (item->data);
        window_node = create_window_node(item->data);
        g_print ("%s", window_node);
                
    }

    gtk_widget_show (window);

    gtk_main ();
}

gchar *
create_window_node (WnckWindow *wnck_window)
{
    gchar *node_text;
    WatcherWindow *window;
    time_t timestamp;
        
    window = g_malloc(sizeof (WatcherWindow));
    node_text = g_malloc0 (1000 * sizeof (gchar));


    window->source = wnck_window;
    window->xid = wnck_window_get_xid(window->source);
    window->name = g_strdup (wnck_window_get_name(window->source));
    window->application_name = g_strdup (wnck_application_get_name(wnck_window_get_application(window->source)));
    window->state = wnck_window_get_state(window->source);
    window->type = get_window_type(wnck_window_get_window_type(window->source));
    window->workspace = wnck_window_get_workspace(window->source);
    window->workspace_number = wnck_workspace_get_number(window->workspace);
    window->is_active = wnck_window_is_active(window->source);
    window->visible_on_workspace = wnck_window_is_visible_on_workspace(window->source, window->workspace);
    wnck_window_get_geometry(window->source, &window->x, &window->y, &window->width, &window->height);

    /* get current timestamp in epoch unix timestamp */
    timestamp = time (NULL);

    g_sprintf (node_text, "<window>\n"
            "\t<xid>%d</xid>\n"
            "\t<timestamp>%d</timestamp>\n"
            "\t<name>%s</name>\n"
            "\t<appname>%s</appname>\n"
            "\t<state>%d</state>\n"
            "\t<type>%d</type>\n"
            "\t<active>%d</active>\n"
            "\t<visibleonworkspace>%d</visibleonworkspace>\n"
            "\t<workspace>%d</workspace>\n"
            "\t<geometry>%d %d %d %d</geometry>\n"
            "</window>\n",
            window->xid,
            timestamp,
            window->name,
            window->application_name,
            window->state,
            window->type,
            window->is_active,
            window->visible_on_workspace,
            window->workspace_number,
            window->x,
            window->y,
            window->width,
            window->height);
    
    return node_text;
}

gint
get_window_type (WnckWindowType type)
{
    gint window_type;

    switch (type) {
        case WNCK_WINDOW_NORMAL:
            window_type = 0;
            break;
        case WNCK_WINDOW_DESKTOP:
            window_type = 1;
            break;
        case WNCK_WINDOW_DOCK:
            window_type = 2;
            break;
        case WNCK_WINDOW_DIALOG:
            window_type = 3;
            break;
        case WNCK_WINDOW_TOOLBAR:
            window_type = 4;
            break;
        case WNCK_WINDOW_MENU:
            window_type = 5;
            break;
        case WNCK_WINDOW_UTILITY:
            window_type = 6;
            break;
        case WNCK_WINDOW_SPLASHSCREEN:
            window_type = 7;
            break;
        default:
            window_type = 8;
            break;
    }

    return window_type;
}
