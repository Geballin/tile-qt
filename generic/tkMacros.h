#include "tk.h"

typedef struct {
     long flags;
     Bool input;
     int initial_state; 
     Pixmap icon_pixmap;
     Window icon_window;
     int icon_x, icon_y;
     Pixmap icon_mask;
     XID window_group;
} XWMHints;

typedef struct Tk_FakeWmInfo {
    Tk_FakeWin *winPtr;		/* Pointer to main Tk information for
				 * this window. */
    Window reparent;		/* If the window has been reparented, this
				 * gives the ID of the ancestor of the window
				 * that is a child of the root window (may
				 * not be window's immediate parent).  If
				 * the window isn't reparented, this has the
				 * value None. */
    char *title;		/* Title to display in window caption.  If
				 * NULL, use name of widget.  Malloced. */
    char *iconName;		/* Name to display in icon.  Malloced. */
    XWMHints hints;		/* Various pieces of information for
				 * window manager. */
    char *leaderName;		/* Path name of leader of window group
				 * (corresponds to hints.window_group).
				 * Malloc-ed.  Note:  this field doesn't
				 * get updated if leader is destroyed. */
    Tk_FakeWin *masterPtr;	/* Master window for TRANSIENT_FOR property,
				 * or NULL. */
    Tk_Window icon;		/* Window to use as icon for this window,
				 * or NULL. */
    Tk_Window iconFor;		/* Window for which this window is icon, or
				 * NULL if this isn't an icon for anyone. */
    int withdrawn;		/* Non-zero means window has been withdrawn. */

    /*
     * In order to support menubars transparently under X, each toplevel
     * window is encased in an additional window, called the wrapper,
     * that holds the toplevel and the menubar, if any.  The information
     * below is used to keep track of the wrapper and the menubar.
     */

    Tk_FakeWin *wrapperPtr;	/* Pointer to information about the wrapper.
				 * This is the "real" toplevel window as
				 * seen by the window manager. Although
				 * this is an official Tk window, it
				 * doesn't appear in the application's
				 * window hierarchy.  NULL means that
				 * the wrapper hasn't been created yet. */
} Tk_FakeWmInfo;



#define Tk_RealToplevelWindow(tkwin)	((((Tk_FakeWmInfo *) (((Tk_FakeWin *) (tkwin))->dummy16))->wrapperPtr)->window)
