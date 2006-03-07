/*
 * $Id$
 *
 * Copyright (C) 2004-2006 Georgios Petasis
 *
 * The Tile-Qt theme is a Tk/Tile theme that uses Qt/KDE for drawing.
 */

#include "tileQt_QtHeaders.h"
#include "tileQt_Utilities.h"
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

/*
 * Exit Handler.
 */
static void TileQt_ExitProc(ClientData data) {
  //Tcl_MutexLock(&tileqtMutex);
  //TileQt_DestroyQApp();
  //Tcl_MutexUnlock(&tileqtMutex);
  Tcl_MutexLock(&tileqtMutex);
  // printf("TileQt_ExitProc: %d\n", TileQt_QAppCreated); fflush(NULL);
  if (TileQt_QAppCreated < 0) {
    Tcl_MutexUnlock(&tileqtMutex);
    return;
  }
  --TileQt_QAppCreated;
  if (TileQt_QAppCreated == 0) {
    // printf("TileQt_ExitProc: %d <- TileQt_DestroyQApp();\n",
    //       TileQt_QAppCreated); fflush(NULL);
    TileQt_DestroyQApp();
  }
  Tcl_MutexUnlock(&tileqtMutex);
  return;
}; /* TileQt_ExitProc */

/*
 * Helper Functions
 */
int Tileqt_ThemeName(ClientData clientData, Tcl_Interp *interp,
                                 int objc, Tcl_Obj *const objv[]) {
  if (objc != 1) {Tcl_WrongNumArgs(interp, 1, objv, ""); return TCL_ERROR;}
  Tcl_MutexLock(&tileqtMutex);
  if (qApp) {
    Tcl_SetResult(interp, (char *) qApp->style().name(), TCL_VOLATILE);
  } else {
    Tcl_SetResult(interp, "", TCL_STATIC);
  }
  Tcl_MutexUnlock(&tileqtMutex);
  return TCL_OK;
}; /* Tileqt_ThemeName */

int Tileqt_ThemeColour(ClientData clientData, Tcl_Interp *interp,
                                 int objc, Tcl_Obj *const objv[]) {
  static char *Methods[] = {
    "-active",     "-disabled",        "-inactive",
    "-background", "-foreground",      "-button",     "-light",
    "-dark",       "-mid",             "-text",       "-base",
    "-midlight",   "-brightText",      "-buttonText", "-shadow",
    "-highlight",  "-highlightedText", "-link",       "-linkVisited",
    (char *) NULL
  };
  enum methods {
    STT_ACTIVE,     STT_DISABLED,        STT_INACTIVE,
    CLR_background, CLR_foreground,      CLR_button,     CLR_light,
    CLR_dark,       CLR_mid,             CLR_text,       CLR_base,
    CLR_midlight,   CLR_brightText,      CLR_buttonText, CLR_shadow,
    CLR_highlight,  CLR_highlightedText, CLR_link,       CLR_linkVisited
  };
  int index;
  if (objc != 2 && objc != 3) {
    Tcl_WrongNumArgs(interp, 2, objv, "?-active|-disabled|-inactive? colour");
    return TCL_ERROR;
  }
  if (!qApp) {
    Tcl_SetResult(interp, "", TCL_STATIC);
    return TCL_OK;
  }
  Tcl_MutexLock(&tileqtMutex);
  QColorGroup colours = qApp->palette().active();
  QColor colour;
  for (int i = 1; i < objc; ++i) {
    if (Tcl_GetIndexFromObj(interp, objv[i], (const char **) Methods,
                            "method", 0, &index) != TCL_OK) return TCL_ERROR;
    switch ((enum methods) index) {
      case STT_ACTIVE:          {colours = qApp->palette().active();   break;}
      case STT_DISABLED:        {colours = qApp->palette().disabled(); break;}
      case STT_INACTIVE:        {colours = qApp->palette().inactive(); break;}
      case CLR_background:      {colour = colours.background();        break;}
      case CLR_foreground:      {colour = colours.foreground();        break;}
      case CLR_button:          {colour = colours.button();            break;}
      case CLR_light:           {colour = colours.light();             break;}
      case CLR_dark:            {colour = colours.dark();              break;}
      case CLR_mid:             {colour = colours.mid();               break;}
      case CLR_text:            {colour = colours.text();              break;}
      case CLR_base:            {colour = colours.base();              break;}
      case CLR_midlight:        {colour = colours.midlight();          break;}
      case CLR_brightText:      {colour = colours.brightText();        break;}
      case CLR_buttonText:      {colour = colours.buttonText();        break;}
      case CLR_shadow:          {colour = colours.shadow();            break;}
      case CLR_highlight:       {colour = colours.highlight();         break;}
      case CLR_highlightedText: {colour = colours.highlightedText();   break;}
      case CLR_link:            {colour = colours.link();              break;}
      case CLR_linkVisited:     {colour = colours.linkVisited();       break;}
    }
  }
  Tcl_SetResult(interp, (char *) colour.name().ascii(), TCL_VOLATILE);
  Tcl_MutexUnlock(&tileqtMutex);
  return TCL_OK;
}; /* Tileqt_ThemeColour */

int Tileqt_AvailableStyles(ClientData clientData, Tcl_Interp *interp,
                                 int objc, Tcl_Obj *const objv[]) {
  if (objc != 1) {Tcl_WrongNumArgs(interp, 1, objv, ""); return TCL_ERROR;}
  Tcl_MutexLock(&tileqtMutex);
  if (qApp) {
    QStringList styles = QStyleFactory::keys();
    Tcl_Obj* stylesObj = Tcl_NewListObj(0, NULL);
    for (QStringList::Iterator it = styles.begin(); it != styles.end(); ++it ) {
        Tcl_ListObjAppendElement(interp, stylesObj,
                        Tcl_NewStringObj((*it).utf8(), -1));
    }
    Tcl_SetObjResult(interp, stylesObj);
  } else {
    Tcl_SetResult(interp, "", TCL_STATIC);
  }
  Tcl_MutexUnlock(&tileqtMutex);
  return TCL_OK;
}; /* Tileqt_AvailableStyles */

int Tileqt_SetStyle(ClientData clientData, Tcl_Interp *interp,
                                 int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {Tcl_WrongNumArgs(interp, 1, objv, "style"); return TCL_ERROR;}
  Tcl_MutexLock(&tileqtMutex);
  if (qApp) {
    int len;
    const char* str = Tcl_GetStringFromObj(objv[1], &len);
    QString style = QString::fromUtf8(str, len);
    qApp->setStyle(style);
    TileQt_QPixmap_BackgroundTile =
                               TileQt_QWidget_Widget->paletteBackgroundPixmap();
  }
  Tcl_MutexUnlock(&tileqtMutex);
  return TCL_OK;
}; /* Tileqt_SetStyle */

extern "C" int DLLEXPORT
Tileqt_Init(Tcl_Interp *interp)
{
    Ttk_Theme themePtr;
    Tk_Window tkwin;
    char tmpScript[1024];

    if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL)
        return TCL_ERROR;
    if (Tk_InitStubs(interp,  TK_VERSION,  0) == NULL)
        return TCL_ERROR;

    /* The first thing we must do, is to retrieve a valid display. */
    Tcl_MutexLock(&tileqtMutex);
    if (TileQt_QAppCreated == 0) qApp = NULL;
    Tcl_MutexUnlock(&tileqtMutex);
    tkwin = Tk_MainWindow(interp);
    if (tkwin == NULL) return TCL_ERROR;

    themePtr  = Ttk_CreateTheme(interp, "tileqt", NULL);
    if (!themePtr) return TCL_ERROR;

    /*
     * Initialise Qt:
     */
    Tcl_MutexLock(&tileqtMutex);
    if (TileQt_QAppCreated == 0) TileQt_CreateQApp(interp);
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
    TileQt_Init_Scale(interp, themePtr);
    TileQt_Init_Arrows(interp, themePtr);
    Tcl_CreateExitHandler(&TileQt_ExitProc, 0);
    //Tcl_CreateThreadExitHandler(&TileQt_ExitProc, 0);
    
    /*
     * Register the TileQt package...
     */
    Tcl_CreateObjCommand(interp, "tile::theme::tileqt::currentThemeName",
                         Tileqt_ThemeName, (ClientData) NULL, NULL);
    Tcl_CreateObjCommand(interp,
                         "tile::theme::tileqt::currentThemeColour",
                         Tileqt_ThemeColour, (ClientData) NULL, NULL);
    Tcl_CreateObjCommand(interp,
                         "tile::theme::tileqt::availableStyles",
                         Tileqt_AvailableStyles, (ClientData) NULL, NULL);
    Tcl_CreateObjCommand(interp,
                         "tile::theme::tileqt::setStyle",
                         Tileqt_SetStyle, (ClientData) NULL, NULL);
    /* Save the name of the current theme... */
    strcpy(tmpScript, "namespace eval tile::theme::tileqt { variable theme ");
    if (qApp) {
      strcat(tmpScript, qApp->style().name());
    } else {
      strcat(tmpScript, "{}");
    }
    strcat(tmpScript, " };");
    Tcl_MutexUnlock(&tileqtMutex);
    
    if (Tcl_Eval(interp, tmpScript) != TCL_OK) {
      return TCL_ERROR;
    }
    if (Tcl_Eval(interp, initScript) != TCL_OK) {
      return TCL_ERROR;
    }
    Tcl_PkgProvide(interp, "tile::theme::tileqt", PACKAGE_VERSION);
    Tcl_PkgProvide(interp, PACKAGE_NAME, PACKAGE_VERSION);
    return TCL_OK;
}; /* TileQt_Init */

int DLLEXPORT
TileQt_Finish(Tcl_Interp *interp)
{
    Tcl_MutexLock(&tileqtMutex);
    if (TileQt_QAppCreated < 0) return 0;
    --TileQt_QAppCreated;
    if (TileQt_QAppCreated == 0) TileQt_DestroyQApp();
    Tcl_MutexUnlock(&tileqtMutex);
    return 0;
}; /* TileQt_Finish */
