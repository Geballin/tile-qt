/*
 * $Id$
 *
 * Copyright (C) 2004-2005 Georgios Petasis
 *
 * The Tile-Qt theme is a Tk/Tile theme that uses Qt/KDE for drawing.
 */

#include "tileQt_QtHeaders.h"
#include "tileQt_Elements.h"
#include <tk.h>
#include "tkTheme.h"
#include <string.h>

static int TileQt_QAppCreated = 0;

extern int TileQt_CreateQApp(Tcl_Interp *interp);
extern void TileQt_DestroyQApp(void);

static char initScript[] =
    "namespace eval tileqt { };"
    "namespace eval tile::theme::tileqt { variable version "
                                                   PACKAGE_VERSION " };"
    "tcl_findLibrary tileqt $tile::theme::tileqt::version "
    "$tile::theme::tileqt::version tileqt.tcl TILEQT_LIBRARY tileqt::library;";

extern "C" int DLLEXPORT
Tileqt_Init(Tcl_Interp *interp)
{
    Ttk_Theme themePtr;
    Tk_Window tkwin;
    char tmpScript[1024];

    if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL)
	return TCL_ERROR;
    if (Tk_InitStubs(interp, TK_VERSION, 0) == NULL)
	return TCL_ERROR;

    /* The first thing we must do, is to retrieve a valid display. */
    tkwin = Tk_MainWindow(interp);
    if (tkwin == NULL) return TCL_ERROR;

    themePtr  = Ttk_CreateTheme(interp, "tileqt", NULL);
    if (!themePtr) return TCL_ERROR;

    /*
     * Initialise Qt:
     */
    if (!TileQt_QAppCreated) TileQt_CreateQApp(interp);
    ++TileQt_QAppCreated;

    /*
     * Register the various widgets...
     */
    TileQt_Init_Background(interp, themePtr);
    TileQt_Init_Button(interp, themePtr);
    TileQt_Init_CheckButton(interp, themePtr);
    TileQt_Init_RadioButton(interp, themePtr);
    TileQt_Init_Menubutton(interp, themePtr);
    TileQt_Init_ToolButton(interp, themePtr);
    TileQt_Init_Entry(interp, themePtr);
    TileQt_Init_Combobox(interp, themePtr);
    TileQt_Init_Labelframe(interp, themePtr);
    TileQt_Init_Scrollbar(interp, themePtr);
    TileQt_Init_Notebook(interp, themePtr);
    TileQt_Init_TreeView(interp, themePtr);
    TileQt_Init_Progress(interp, themePtr);
    //TileQt_Init_Scale(interp, themePtr);
    TileQt_Init_Arrows(interp, themePtr);
    
    /*
     * Register the TileQt package...
     */
    strcpy(tmpScript, "namespace eval tileqt { variable theme ");
    if (qApp) {
      strcat(tmpScript, qApp->style().name());
    } else {
      strcat(tmpScript, "{}");
    }
    strcat(tmpScript, " };");
    if (Tcl_Eval(interp, tmpScript) != TCL_OK)
	return TCL_ERROR;
    if (Tcl_Eval(interp, initScript) != TCL_OK)
	return TCL_ERROR;
    Tcl_PkgProvide(interp, PACKAGE_NAME, PACKAGE_VERSION);
    Tcl_PkgProvide(interp, "tile::theme::tileqt", PACKAGE_VERSION);
    return TCL_OK;
}; /* TileQt_Init */

int DLLEXPORT
TileQt_Finish(Tcl_Interp *interp)
{
    if (TileQt_QAppCreated < 0) return 0;
    --TileQt_QAppCreated;
    if (TileQt_QAppCreated < 1) TileQt_DestroyQApp();
    return 0;
}; /* TileQt_Finish */
