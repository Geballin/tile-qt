/*
 *  tileQt_QApp.c
 * ---------------
 *
 * This file is part of the Tile-Qt package, a Tk/Tile based theme that uses
 * Qt/KDE for drawing.
 *
 * Copyright (C) 2004-2005 by:
 * Georgios Petasis, petasis@iit.demokritos.gr,
 * Software and Knowledge Engineering Laboratory,
 * Institute of Informatics and Telecommunications,
 * National Centre for Scientific Research (NCSR) "Demokritos",
 * Aghia Paraskevi, 153 10, Athens, Greece.
 */

#include "tileQt_QtHeaders.h"
#include "tk.h"
#include "tkMacros.h"
bool TileQt_qAppOwner = false;

/* Pointers to some Qt/KDE widgets, whose style will be used for drawing. */
QScrollBar*    TileQt_QScrollBar_Widget      = NULL; 
QWidget*       TileQt_QWidget_Widget         = NULL;
QWidget*       TileQt_QWidget_WidgetParent   = NULL;
QSlider*       TileQt_QSlider_Widget         = NULL;
QTabBar*       TileQt_QTabBar_Widget         = NULL;
const QPixmap* TileQt_QPixmap_BackgroundTile = NULL;

Tk_Window   TileQt_tkwin = NULL;
Display*    TileQt_MainDisplay = None;
Tcl_Interp* TileQt_MainInterp = NULL;
Atom        TileQt_KIPC_COMM_ATOM = None;

static int TileQt_ClientMessageHandler(Tk_Window winPtr, XEvent *eventPtr);

int TileQt_CreateQApp(Tcl_Interp *interp)
{
    if (TileQt_tkwin == NULL) {
      TileQt_MainInterp = interp;
      TileQt_tkwin = Tk_MainWindow(interp);
      if (TileQt_tkwin != NULL && TileQt_MainDisplay == None) {
        //Tk_MapWindow(TileQt_tkwin);
        Tk_MakeWindowExist(TileQt_tkwin);
        TileQt_MainDisplay = Tk_Display(TileQt_tkwin);
      }
    }
    if (TileQt_MainDisplay == None) return TCL_ERROR;
    /*
     * In order to create a Qt/KDE application, we need command line arguments.
     * As we don't have them, simply simulate them...
     */
    //initKdeSettings();
    if (!qApp) {
      new QApplication(TileQt_MainDisplay);
      TileQt_qAppOwner = true;
    }
    /* Create some needed widgets, which we will use for drawing. */
    // QWidget* smw = new QWidget(0,0);
    TileQt_QScrollBar_Widget      = new QScrollBar(0);
    TileQt_QWidget_WidgetParent   = new QWidget(0);
    TileQt_QWidget_Widget         = new QWidget(TileQt_QWidget_WidgetParent);
    TileQt_QSlider_Widget         = new QSlider(TileQt_QWidget_Widget);
    TileQt_QWidget_Widget->polish();
    TileQt_QTabBar_Widget         = new QTabBar(TileQt_QWidget_Widget);
    TileQt_QPixmap_BackgroundTile =
                               TileQt_QWidget_Widget->paletteBackgroundPixmap();
    TileQt_QScrollBar_Widget->setMinValue(0);
    TileQt_QScrollBar_Widget->setMaxValue(65535);
    TileQt_QScrollBar_Widget->setValue(65535);
    TileQt_QScrollBar_Widget->setPageStep(1);
    /* Register a Client Message handler, so as to catch style changes... */
 //   TileQt_KIPC_COMM_ATOM = XInternAtom(TileQt_MainDisplay,
 //                                    "KIPC_COMM_ATOM" , false);
 //   Atom TileQt_KDE_DESKTOP_WINDOW = XInternAtom(TileQt_MainDisplay,
 //                                    "KDE_DESKTOP_WINDOW" , false);
 //   // Create a new window, and set the KDE_DESKTOP_WINDOW property on it
 //   // This window will then receive events from KDE when the style changes
 //   long data = 1;
 //   //printf("toplevel=%p, parent=%p\n", TileQt_tkwin, Tk_Parent(TileQt_tkwin));
 //   //printf("window=%p\n", Tk_RealToplevelWindow(TileQt_tkwin));
 //   XChangeProperty(TileQt_MainDisplay, smw->winId(),
 //                TileQt_KDE_DESKTOP_WINDOW, TileQt_KDE_DESKTOP_WINDOW,
 //                32, PropModeReplace, (unsigned char *)&data, 1);
//    XChangeProperty(TileQt_MainDisplay, Tk_RealToplevelWindow(TileQt_tkwin),
//                 TileQt_KDE_DESKTOP_WINDOW, TileQt_KDE_DESKTOP_WINDOW,
//                 32, PropModeReplace, (unsigned char *)&data, 1);
//    XChangeProperty(TileQt_MainDisplay, Tk_WindowId(TileQt_tkwin),
//                TileQt_KDE_DESKTOP_WINDOW, TileQt_KDE_DESKTOP_WINDOW,
//                32, PropModeReplace, (unsigned char *)&data, 1);
    //Tk_CreateClientMessageHandler(&TileQt_ClientMessageHandler);
    return TCL_OK;
}; /* TileQt_CreateQApp */

void TileQt_DestroyQApp(void)
{
    if (TileQt_QScrollBar_Widget)    delete TileQt_QScrollBar_Widget;
    if (TileQt_QWidget_Widget)       delete TileQt_QWidget_Widget;
    if (TileQt_QWidget_WidgetParent) delete TileQt_QWidget_WidgetParent;
    if (TileQt_QSlider_Widget)       delete TileQt_QSlider_Widget;
    if (TileQt_QTabBar_Widget)       delete TileQt_QTabBar_Widget;
    if (TileQt_qAppOwner) {
      if (qApp) delete qApp;
      qApp = 0;
    }
}; /* TileQt_DestroyQApp */

static int TileQt_ClientMessageHandler(Tk_Window winPtr, XEvent *eventPtr) {
    printf("TileQt_ClientMessageHandler\n");
    if (eventPtr->type != ClientMessage ||
        eventPtr->xclient.message_type != TileQt_KIPC_COMM_ATOM) return False;
    TileQt_DestroyQApp();
    TileQt_CreateQApp(TileQt_MainInterp);
    return True;
} /* TileQt_ClientMessageHandler */
