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
QWidget*       TileQt_smw                    = NULL;
QScrollBar*    TileQt_QScrollBar_Widget      = NULL; 
QComboBox*     TileQt_QComboBox_RW_Widget    = NULL;
QComboBox*     TileQt_QComboBox_RO_Widget    = NULL;
QWidget*       TileQt_QWidget_Widget         = NULL;
QWidget*       TileQt_QWidget_WidgetParent   = NULL;
QSlider*       TileQt_QSlider_Hor_Widget     = NULL;
QSlider*       TileQt_QSlider_Ver_Widget     = NULL;
QTabBar*       TileQt_QTabBar_Widget         = NULL;
const QPixmap* TileQt_QPixmap_BackgroundTile = NULL;

Tk_Window   TileQt_tkwin = NULL;
Display*    TileQt_MainDisplay = None;
Tcl_Interp* TileQt_MainInterp = NULL;
Atom        TileQt_KIPC_COMM_ATOM = None;

static int  TileQt_ClientMessageHandler(Tk_Window winPtr, XEvent *eventPtr);
static int  TileQt_XEventHandler(ClientData clientdata, XEvent *eventPtr);
static void TileQt_XEventHandlerVoid(ClientData clientdata, XEvent *eventPtr);

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
    TileQt_QComboBox_RW_Widget    = new QComboBox(true, 0, "");
    TileQt_QComboBox_RO_Widget    = new QComboBox(false, 0, "");
    TileQt_QWidget_WidgetParent   = new QWidget(0);
    TileQt_QWidget_Widget         = new QWidget(TileQt_QWidget_WidgetParent);
    TileQt_QWidget_Widget->polish();
    TileQt_QSlider_Hor_Widget     = new QSlider(Qt::Horizontal,
                                        TileQt_QWidget_Widget, "hslider");
    TileQt_QSlider_Hor_Widget->polish();
    TileQt_QSlider_Ver_Widget     = new QSlider(Qt::Vertical,
                                        TileQt_QWidget_Widget, "vslider");
    TileQt_QSlider_Ver_Widget->polish();
    TileQt_QTabBar_Widget         = new QTabBar(TileQt_QWidget_Widget);
    TileQt_QPixmap_BackgroundTile =
                               TileQt_QWidget_Widget->paletteBackgroundPixmap();
    TileQt_QScrollBar_Widget->setMinValue(0);
    TileQt_QScrollBar_Widget->setMaxValue(65535);
    TileQt_QScrollBar_Widget->setValue(65535);
    TileQt_QScrollBar_Widget->setPageStep(1);
    /* Register a Client Message handler, so as to catch style changes... */
    TileQt_KIPC_COMM_ATOM = XInternAtom(TileQt_MainDisplay,
                                     "KIPC_COMM_ATOM" , false);
    Atom TileQt_KDE_DESKTOP_WINDOW = XInternAtom(TileQt_MainDisplay,
                                     "KDE_DESKTOP_WINDOW" , false);
    // Create a new window, and set the KDE_DESKTOP_WINDOW property on it
    // This window will then receive events from KDE when the style changes
    QWidget* TileQt_smw = new QWidget(0,0);
    long data = 1;
    // XChangeProperty(TileQt_MainDisplay, Tk_RealToplevelWindow(TileQt_tkwin),
    //              TileQt_KDE_DESKTOP_WINDOW, TileQt_KDE_DESKTOP_WINDOW,
    //              32, PropModeReplace, (unsigned char *)&data, 1);
    // XChangeProperty(TileQt_MainDisplay, Tk_WindowId(TileQt_tkwin),
    //              TileQt_KDE_DESKTOP_WINDOW, TileQt_KDE_DESKTOP_WINDOW,
    //              32, PropModeReplace, (unsigned char *)&data, 1);
    //Tk_CreateClientMessageHandler(&TileQt_ClientMessageHandler);
    //Tk_CreateEventHandler(TileQt_tkwin, ClientMessage,
    //                     &TileQt_XEventHandlerVoid, 0);
    Tk_CreateGenericHandler(&TileQt_XEventHandler, (ClientData) TileQt_smw);
    XChangeProperty(qt_xdisplay(), TileQt_smw->winId(),
		    TileQt_KDE_DESKTOP_WINDOW, TileQt_KDE_DESKTOP_WINDOW,
		    32, PropModeReplace, (unsigned char *)&data, 1);
    return TCL_OK;
}; /* TileQt_CreateQApp */

void TileQt_DestroyQApp(void)
{
    if (TileQt_QScrollBar_Widget)    delete TileQt_QScrollBar_Widget;
    if (TileQt_QComboBox_RO_Widget)  delete TileQt_QComboBox_RO_Widget;
    if (TileQt_QComboBox_RW_Widget)  delete TileQt_QComboBox_RW_Widget;
    if (TileQt_QSlider_Hor_Widget)   delete TileQt_QSlider_Hor_Widget;
    if (TileQt_QSlider_Ver_Widget)   delete TileQt_QSlider_Ver_Widget;
    if (TileQt_QTabBar_Widget)       delete TileQt_QTabBar_Widget;
    if (TileQt_QWidget_Widget)       delete TileQt_QWidget_Widget;
    if (TileQt_QWidget_WidgetParent) delete TileQt_QWidget_WidgetParent;
    if (TileQt_smw)                  delete TileQt_smw;
    TileQt_QScrollBar_Widget    = NULL;
    TileQt_QComboBox_RO_Widget  = NULL;
    TileQt_QComboBox_RW_Widget  = NULL;
    TileQt_QSlider_Hor_Widget   = NULL;
    TileQt_QSlider_Ver_Widget   = NULL;
    TileQt_QTabBar_Widget       = NULL;
    TileQt_QWidget_Widget       = NULL;
    TileQt_QWidget_WidgetParent = NULL;
    TileQt_smw                  = NULL;
    
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
} /* TileQt_XEventHandler */

static int TileQt_XEventHandler(ClientData clientData, XEvent *eventPtr) {
    if (eventPtr->type != ClientMessage ||
        eventPtr->xclient.message_type != TileQt_KIPC_COMM_ATOM) return False;
    //printf("TileQt_XEventHandler\n");
    TileQt_DestroyQApp();
    TileQt_CreateQApp(TileQt_MainInterp);
    /* Notify the tile engine about the change... */
    Tcl_Eval(TileQt_MainInterp,
             "tile::theme::tileqt::kdeStyleChangeNotification");
    return True;
} /* TileQt_XEventHandler */

static void TileQt_XEventHandlerVoid(ClientData clientData, XEvent *eventPtr) {
    printf("TileQt_XEventHandlerVoid\n");
    if (eventPtr->type != ClientMessage ||
        eventPtr->xclient.message_type != TileQt_KIPC_COMM_ATOM) return;
    TileQt_DestroyQApp();
    TileQt_CreateQApp(TileQt_MainInterp);
} /* TileQt_XEventHandler */
