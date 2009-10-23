/* 
 * File:   gtk_windowwatcher.h
 * Author: draco
 *
 * Created on October 23, 2009, 4:02 PM
 */

#ifndef _GTK_WINDOWWATCHER_H
#define	_GTK_WINDOWWATCHER_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct WatcherWindow {
    WnckWindow *source;
    gulong xid;
    WnckWindowState state;
    WnckWindowType type;
    gchar *name;
    gchar *application_name;
    gboolean *is_active;
    WnckWorkspace *workspace;
    gint workspace_number;
    gboolean visible_on_workspace;
    gint x;
    gint y;
    gint width;
    gint height;
} WatcherWindow;

gint    get_window_type (WnckWindowType type);
gchar   *create_window_node (WnckWindow *wnck_window);

#ifdef	__cplusplus
}
#endif

#endif	/* _GTK_WINDOWWATCHER_H */

