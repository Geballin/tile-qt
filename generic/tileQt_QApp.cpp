/*
 *  tileQt_QApp.c
 * ---------------
 *
 * This file is part of the Tile-Qt package, a Tk/Tile based theme that uses
 * Qt/KDE for drawing.
 *
 * Copyright (C) 2004-2006 by:
 * Georgios Petasis, petasis@iit.demokritos.gr,
 * Software and Knowledge Engineering Laboratory,
 * Institute of Informatics and Telecommunications,
 * National Centre for Scientific Research (NCSR) "Demokritos",
 * Aghia Paraskevi, 153 10, Athens, Greece.
 */

#include "tileQt_QtHeaders.h"
#include "tk.h"
#include "tkTheme.h"
#include "tkMacros.h"
TCL_DECLARE_MUTEX(tileqtMutex);
static bool TileQt_qAppOwner = false;

/* Pointers to some Qt/KDE widgets, whose style will be used for drawing. */
typedef struct TileQt_WidgetCache {
  QStyle*        TileQt_Style;
  bool           TileQt_Style_Owner;
  QWidget*       TileQt_smw;
  QScrollBar*    TileQt_QScrollBar_Widget; 
  QComboBox*     TileQt_QComboBox_RW_Widget;
  QComboBox*     TileQt_QComboBox_RO_Widget;
  QWidget*       TileQt_QWidget_Widget;
  QWidget*       TileQt_QWidget_WidgetParent;
  QSlider*       TileQt_QSlider_Hor_Widget;
  QSlider*       TileQt_QSlider_Ver_Widget;
  QProgressBar*  TileQt_QProgressBar_Hor_Widget;
  QTabBar*       TileQt_QTabBar_Widget;
  const QPixmap* TileQt_QPixmap_BackgroundTile;
  Tk_Window      TileQt_tkwin;
  Display*       TileQt_MainDisplay;
  Tcl_Interp*    TileQt_MainInterp;
  Atom           TileQt_KIPC_COMM_ATOM;
  int orientation;
} TileQt_WidgetCache;

// static int  TileQt_ClientMessageHandler(Tk_Window winPtr, XEvent *eventPtr);
// static int  TileQt_XEventHandler(ClientData clientdata, XEvent *eventPtr);
// static void TileQt_XEventHandlerVoid(ClientData clientdata, XEvent *eventPtr);

/*
 * TileQt_InterpDeleteProc:
 * This function will be called when the interpreter gets deleted. It must free
 * all allocated interp-specific memory segments.
 */
static void TileQt_InterpDeleteProc(ClientData clientData, Tcl_Interp *interp)
{
  TileQt_WidgetCache **wc_array = (TileQt_WidgetCache **) clientData;
  TileQt_WidgetCache *wc = wc_array[0];
//  if (wc->TileQt_smw) 
//    Tk_DeleteGenericHandler(&TileQt_XEventHandler, (ClientData) wc->TileQt_smw);
  if (wc->TileQt_QScrollBar_Widget)       delete wc->TileQt_QScrollBar_Widget;
  if (wc->TileQt_QComboBox_RO_Widget)     delete wc->TileQt_QComboBox_RO_Widget;
  if (wc->TileQt_QComboBox_RW_Widget)     {
    wc->TileQt_QComboBox_RW_Widget->setEditable(false);
    delete wc->TileQt_QComboBox_RW_Widget;
  }
  if (wc->TileQt_QSlider_Hor_Widget)      delete wc->TileQt_QSlider_Hor_Widget;
  if (wc->TileQt_QSlider_Ver_Widget)      delete wc->TileQt_QSlider_Ver_Widget;
  if (wc->TileQt_QProgressBar_Hor_Widget) delete wc->TileQt_QProgressBar_Hor_Widget;
  if (wc->TileQt_QTabBar_Widget)          delete wc->TileQt_QTabBar_Widget;
  if (wc->TileQt_QWidget_Widget)          delete wc->TileQt_QWidget_Widget;
  if (wc->TileQt_QWidget_WidgetParent)    delete wc->TileQt_QWidget_WidgetParent;
  if (wc->TileQt_smw)                     delete wc->TileQt_smw;
  Tcl_Free((char *) wc_array[0]);
  Tcl_Free((char *) wc_array[1]);
  Tcl_Free((char *) wc_array);
}; /* TileQt_InterpDeleteProc */

TileQt_WidgetCache **TileQt_CreateQApp(Tcl_Interp *interp)
{
    Tcl_MutexLock(&tileqtMutex);
    TileQt_WidgetCache **wc_array = (TileQt_WidgetCache **) 
                             Tcl_Alloc(sizeof(TileQt_WidgetCache*)*2);
    wc_array[0] = (TileQt_WidgetCache *) 
                             Tcl_Alloc(sizeof(TileQt_WidgetCache));
    wc_array[1] = (TileQt_WidgetCache *) 
                             Tcl_Alloc(sizeof(TileQt_WidgetCache));
    Tcl_SetAssocData(interp, "tileqt_widget_cache",
                     &TileQt_InterpDeleteProc, (ClientData) wc_array);
    TileQt_WidgetCache *wc = wc_array[0];
    memset(wc, 0, sizeof(TileQt_WidgetCache));
    wc->TileQt_MainInterp = interp;
    wc->TileQt_tkwin      = Tk_MainWindow(interp);
    if (wc->TileQt_tkwin != NULL && wc->TileQt_MainDisplay == None) {
      //Tk_MapWindow(TileQt_tkwin);
      Tk_MakeWindowExist(wc->TileQt_tkwin);
      wc->TileQt_MainDisplay = Tk_Display(wc->TileQt_tkwin);
    }
    if (wc->TileQt_MainDisplay == None) {
      Tcl_MutexUnlock(&tileqtMutex);
      Tcl_Free((char *) wc_array);
      return NULL;
    }
    /*
     * In order to create a Qt/KDE application, we need command line arguments.
     * As we don't have them, simply simulate them...
     */
    //initKdeSettings();
    if (!TileQt_qAppOwner && !qApp) {
      new QApplication(wc->TileQt_MainDisplay);
      TileQt_qAppOwner = true;
    }
    wc->TileQt_Style = &(qApp->style());
    wc->TileQt_Style_Owner = false;
    /* Create some needed widgets, which we will use for drawing. */
    wc->TileQt_QScrollBar_Widget        = new QScrollBar(0);
    // The following crashes wish at exit :-(
    wc->TileQt_QComboBox_RW_Widget      = new QComboBox(true,  0);
    wc->TileQt_QComboBox_RO_Widget      = new QComboBox(false, 0);
    wc->TileQt_QWidget_WidgetParent     = new QWidget(0);
    wc->TileQt_QWidget_Widget           = 
                                 new QWidget(wc->TileQt_QWidget_WidgetParent);
    wc->TileQt_QWidget_Widget->polish();
    wc->TileQt_QSlider_Hor_Widget       = new QSlider(Qt::Horizontal,
                                          wc->TileQt_QWidget_Widget, "hslider");
    wc->TileQt_QSlider_Hor_Widget->polish();
    wc->TileQt_QSlider_Ver_Widget       = new QSlider(Qt::Vertical,
                                          wc->TileQt_QWidget_Widget, "vslider");
    wc->TileQt_QSlider_Ver_Widget->polish();
    wc->TileQt_QProgressBar_Hor_Widget  = new QProgressBar(100, 0);
    wc->TileQt_QProgressBar_Hor_Widget->setCenterIndicator(false);
    wc->TileQt_QProgressBar_Hor_Widget->setPercentageVisible(false);
    wc->TileQt_QTabBar_Widget           = 
                                 new QTabBar(wc->TileQt_QWidget_Widget);
    wc->TileQt_QPixmap_BackgroundTile   =
                         (wc->TileQt_QWidget_Widget)->paletteBackgroundPixmap();
    wc->TileQt_QScrollBar_Widget->setMinValue(0);
    wc->TileQt_QScrollBar_Widget->setMaxValue(65535);
    wc->TileQt_QScrollBar_Widget->setValue(65535);
    wc->TileQt_QScrollBar_Widget->setPageStep(1);
    /* Register a Client Message handler, so as to catch style changes... */
    wc->TileQt_KIPC_COMM_ATOM = XInternAtom(wc->TileQt_MainDisplay,
                                     "KIPC_COMM_ATOM" , false);
    Atom TileQt_KDE_DESKTOP_WINDOW = XInternAtom(wc->TileQt_MainDisplay,
                                     "KDE_DESKTOP_WINDOW" , false);
    // Create a new window, and set the KDE_DESKTOP_WINDOW property on it
    // This window will then receive events from KDE when the style changes
    wc->TileQt_smw = new QWidget(0,0);
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
    //Tk_CreateGenericHandler(&TileQt_XEventHandler, (ClientData) wc->TileQt_smw);
    //XChangeProperty(qt_xdisplay(), wc->TileQt_smw->winId(),
    //                TileQt_KDE_DESKTOP_WINDOW, TileQt_KDE_DESKTOP_WINDOW,
    //                32, PropModeReplace, (unsigned char *)&data, 1);
    Tcl_MutexUnlock(&tileqtMutex);
    memcpy(wc_array[1], wc_array[0], sizeof(TileQt_WidgetCache));
    wc_array[0]->orientation = TTK_ORIENT_HORIZONTAL;
    wc_array[1]->orientation = TTK_ORIENT_VERTICAL;
    return wc_array;
}; /* TileQt_CreateQApp */

void TileQt_DestroyQApp(void)
{
    Tcl_MutexLock(&tileqtMutex);
    if (TileQt_qAppOwner) {
      if (qApp) {
        delete qApp;
        // printf("TileQt_DestroyQApp: qApp deleted!\n"); fflush(NULL);
        qApp = NULL;
      }
      TileQt_qAppOwner = false;
    }
    Tcl_MutexUnlock(&tileqtMutex);
}; /* TileQt_DestroyQApp */

// static int TileQt_ClientMessageHandler(Tk_Window winPtr, XEvent *eventPtr) {
//     printf("TileQt_ClientMessageHandler\n");
//     if (eventPtr->type != ClientMessage ||
//         eventPtr->xclient.message_type != TileQt_KIPC_COMM_ATOM) return False;
//     TileQt_DestroyQApp();
//     TileQt_CreateQApp(TileQt_MainInterp);
//     return True;
// } /* TileQt_XEventHandler */
// 
// static int TileQt_XEventHandler(ClientData clientData, XEvent *eventPtr) {
//     if (eventPtr->type != ClientMessage ||
//         eventPtr->xclient.message_type != TileQt_KIPC_COMM_ATOM) return False;
//     // printf("TileQt_XEventHandler\n"); fflush(NULL);
//     TileQt_DestroyQApp();
//     TileQt_CreateQApp(TileQt_MainInterp);
//     /* Notify the tile engine about the change... */
//     Tcl_Eval(TileQt_MainInterp,
//              "tile::theme::tileqt::kdeStyleChangeNotification");
//     return True;
// } /* TileQt_XEventHandler */
// 
// static void TileQt_XEventHandlerVoid(ClientData clientData, XEvent *eventPtr) {
//     printf("TileQt_XEventHandlerVoid\n");
//     if (eventPtr->type != ClientMessage ||
//         eventPtr->xclient.message_type != TileQt_KIPC_COMM_ATOM) return;
//     TileQt_DestroyQApp();
//     TileQt_CreateQApp(TileQt_MainInterp);
// } /* TileQt_XEventHandler */
