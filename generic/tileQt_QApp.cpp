/*
 *  tileQt_QApp.c
 * ---------------
 *
 * This file is part of the Tile-Qt package, a Tk/Tile based theme that uses
 * Qt/KDE for drawing.
 *
 * Copyright (C) 2004-2008 by:
 * Georgios Petasis, petasis@iit.demokritos.gr,
 * Software and Knowledge Engineering Laboratory,
 * Institute of Informatics and Telecommunications,
 * National Centre for Scientific Research (NCSR) "Demokritos",
 * Aghia Paraskevi, 153 10, Athens, Greece.
 */

#include "tileQt_QtHeaders.h"
#include "tileQt_Utilities.h"
#include "tileQt_TkHeaders.h"
static bool TileQt_qAppOwner = false;

/* In the following variable we store the XErrorHandler, before we install our
 * own, which filters out some XErrors... */
static int (*TileQt_TkXErrorHandler)(Display *displayPtr,
                                     XErrorEvent *errorPtr);
static int TileQt_XErrorHandler(Display *displayPtr, XErrorEvent *errorPtr);

static int  TileQt_XEventHandler(ClientData clientdata, XEvent *eventPtr);

/*
 * TileQt_InterpDeleteProc:
 * This function will be called when the interpreter gets deleted. It must free
 * all allocated interp-specific memory segments.
 */
static void TileQt_InterpDeleteProc(ClientData clientData, Tcl_Interp *interp) {
  TileQt_WidgetCache **wc_array = (TileQt_WidgetCache **) clientData;
  TileQt_WidgetCache *wc = wc_array[0];
  // printf("Tk_DeleteGenericHandler: %p\n", interp); fflush(NULL);
  Tk_DeleteGenericHandler(&TileQt_XEventHandler, (ClientData) interp);
  if (wc->lowerStyleName)                 delete wc->lowerStyleName;
  if (wc->TileQt_QScrollBar_Widget)       delete wc->TileQt_QScrollBar_Widget;
  if (wc->TileQt_QComboBox_RO_Widget)     delete wc->TileQt_QComboBox_RO_Widget;
  if (wc->TileQt_QComboBox_RW_Widget)     {
    wc->TileQt_QComboBox_RW_Widget->setEditable(false);
    delete wc->TileQt_QComboBox_RW_Widget;
  }
  if (wc->TileQt_QSlider_Hor_Widget)      delete wc->TileQt_QSlider_Hor_Widget;
  if (wc->TileQt_QSlider_Ver_Widget)      delete wc->TileQt_QSlider_Ver_Widget;
  if (wc->TileQt_QProgressBar_Hor_Widget) delete wc->TileQt_QProgressBar_Hor_Widget;
  if (wc->TileQt_QTabWidget_Widget)       delete wc->TileQt_QTabWidget_Widget;
  if (wc->TileQt_QListView_Widget)        delete wc->TileQt_QListView_Widget;
  if (wc->TileQt_QWidget_Widget)          delete wc->TileQt_QWidget_Widget;
  if (wc->TileQt_QWidget_WidgetParent)    delete wc->TileQt_QWidget_WidgetParent;
  if (wc->TileQt_smw)                     delete wc->TileQt_smw;
  Tcl_Free((char *) wc_array[0]);
  Tcl_Free((char *) wc_array[1]);
  Tcl_Free((char *) wc_array);
}; /* TileQt_InterpDeleteProc */

TileQt_WidgetCache **TileQt_CreateQApp(Tcl_Interp *interp) {
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
  wc->TileQt_MainInterp  = interp;
  wc->TileQt_tkwin       = Tk_MainWindow(interp);
  if (wc->TileQt_tkwin != NULL && wc->TileQt_MainDisplay == None) {
    // Tk_MapWindow(wc->TileQt_tkwin);
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
  if (!TileQt_qAppOwner && !qApp) {
    /* Set an error event handler that ignores QueryTree failures */
    TileQt_TkXErrorHandler = XSetErrorHandler(TileQt_XErrorHandler);
    // XSynchronize(wc->TileQt_MainDisplay, true);
    new QApplication(wc->TileQt_MainDisplay);
    TileQt_qAppOwner = true;
    /* As Qt registers also its own XError handler, reset our own... */
    XSetErrorHandler(TileQt_XErrorHandler);
  }
#ifdef TILEQT_QT_VERSION_3
  wc->TileQt_Style = &(qApp->style());
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
  wc->TileQt_Style = qApp->style();
#endif /* TILEQT_QT_VERSION_4 */
  wc->TileQt_Style_Owner = false;
  TileQt_StoreStyleNameLowers(wc);
  /* Create some needed widgets, which we will use for drawing. */
  wc->TileQt_QScrollBar_Widget        = new QScrollBar(0);
#ifdef TILEQT_QT_VERSION_3
  /* The following crashes wish at exit :-( */
  wc->TileQt_QComboBox_RW_Widget      = new QComboBox(true,  0);
  wc->TileQt_QComboBox_RO_Widget      = new QComboBox(false, 0);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
  wc->TileQt_QComboBox_RW_Widget      = new QComboBox;
  wc->TileQt_QComboBox_RO_Widget      = new QComboBox;
  wc->TileQt_QComboBox_RW_Widget->setEditable(true);
  wc->TileQt_QComboBox_RO_Widget->setEditable(false);
#endif /* TILEQT_QT_VERSION_4 */
  wc->TileQt_QWidget_WidgetParent     = new QWidget(0);
  wc->TileQt_QWidget_Widget           = 
                               new QWidget(wc->TileQt_QWidget_WidgetParent);
#ifdef TILEQT_QT_VERSION_3
  wc->TileQt_QWidget_Widget->polish();
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
  wc->TileQt_QWidget_Widget->ensurePolished();
#endif /* TILEQT_QT_VERSION_4 */
#ifdef TILEQT_QT_VERSION_3
  wc->TileQt_QSlider_Hor_Widget       = new QSlider(Qt::Horizontal,
                                        wc->TileQt_QWidget_Widget, "hslider");
  wc->TileQt_QSlider_Hor_Widget->polish();
  wc->TileQt_QSlider_Ver_Widget       = new QSlider(Qt::Vertical,
                                        wc->TileQt_QWidget_Widget, "vslider");
  wc->TileQt_QSlider_Ver_Widget->polish();
  wc->TileQt_QProgressBar_Hor_Widget  = new QProgressBar(100, 0);
  wc->TileQt_QProgressBar_Hor_Widget->setCenterIndicator(false);
  wc->TileQt_QProgressBar_Hor_Widget->setPercentageVisible(false);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
  wc->TileQt_QSlider_Hor_Widget       = new QSlider(Qt::Horizontal,
                                        wc->TileQt_QWidget_Widget);
  wc->TileQt_QSlider_Ver_Widget       = new QSlider(Qt::Vertical,
                                        wc->TileQt_QWidget_Widget);
  wc->TileQt_QProgressBar_Hor_Widget  = new QProgressBar;
  wc->TileQt_QProgressBar_Hor_Widget->setRange (0, 100);
  wc->TileQt_QProgressBar_Hor_Widget->setTextVisible(false);
  wc->TileQt_QSlider_Hor_Widget->setRange (0, 100);
  wc->TileQt_QSlider_Ver_Widget->setRange (0, 100);
  wc->TileQt_QSlider_Hor_Widget->ensurePolished();
  wc->TileQt_QSlider_Ver_Widget->ensurePolished();
#endif /* TILEQT_QT_VERSION_4 */

  wc->TileQt_QTabWidget_Widget        = 
                               new QTabWidget(wc->TileQt_QWidget_Widget);
  wc->TileQt_QTabBar_Widget           = NULL;
  if (wc->TileQt_QTabWidget_Widget) {
    ((TileQt_Widget*) wc->TileQt_QTabWidget_Widget)->set_visible();
    wc->TileQt_QTabBar_Widget = ((TileQt_QTabWidget *) 
                   wc->TileQt_QTabWidget_Widget)->get_tab_bar();
    if (wc->TileQt_QTabBar_Widget) {
      ((TileQt_Widget*) wc->TileQt_QTabBar_Widget)->set_visible();
    }
  }
  wc->TileQt_QListView_Widget = new QListView(wc->TileQt_QWidget_Widget);
  wc->TileQt_QPixmap_BackgroundTile   =
#ifdef TILEQT_QT_VERSION_3
                     (wc->TileQt_QWidget_Widget)->paletteBackgroundPixmap();
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
                     (wc->TileQt_QWidget_Widget)->palette().window().texture();
#endif /* TILEQT_QT_VERSION_4 */
#ifdef TILEQT_QT_VERSION_3
  wc->TileQt_QScrollBar_Widget->setMinValue(0);
  wc->TileQt_QScrollBar_Widget->setMaxValue(65535);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
  wc->TileQt_QScrollBar_Widget->setRange(0, 65535);
#endif /* TILEQT_QT_VERSION_4 */
  wc->TileQt_QScrollBar_Widget->setValue(65535);
  wc->TileQt_QScrollBar_Widget->setPageStep(1);
  /* Register a Client Message handler, so as to catch style changes... */
  Atom TileQt_KDE_DESKTOP_WINDOW = XInternAtom(wc->TileQt_MainDisplay,
                                   "KDE_DESKTOP_WINDOW" , false);
  /* Create a new window, and set the KDE_DESKTOP_WINDOW property on it
   * This window will then receive events from KDE when the style changes. */
  wc->TileQt_smw = new QWidget(0,0);
  long data = 1;
  // printf("Tk_CreateGenericHandler: %p\n", interp); fflush(NULL);
  Tk_CreateGenericHandler(&TileQt_XEventHandler, (ClientData) interp);
  XChangeProperty(qt_xdisplay(), wc->TileQt_smw->winId(),
                  TileQt_KDE_DESKTOP_WINDOW, TileQt_KDE_DESKTOP_WINDOW,
                  32, PropModeReplace, (unsigned char *)&data, 1);
  Tcl_MutexUnlock(&tileqtMutex);
  memcpy(wc_array[1], wc_array[0], sizeof(TileQt_WidgetCache));
  wc_array[0]->orientation = TTK_ORIENT_HORIZONTAL;
  wc_array[1]->orientation = TTK_ORIENT_VERTICAL;
  return wc_array;
}; /* TileQt_CreateQApp */

void TileQt_DestroyQApp(void) {
  Tcl_MutexLock(&tileqtMutex);
  if (TileQt_qAppOwner) {
    if (qApp) {
      delete qApp;
      // printf("TileQt_DestroyQApp: qApp deleted!\n"); fflush(NULL);
#ifdef TILEQT_QT_VERSION_3
      qApp = NULL;
#endif /* TILEQT_QT_VERSION_3 */
      XSetErrorHandler(TileQt_TkXErrorHandler);
    }
    TileQt_qAppOwner = false;
  }
  Tcl_MutexUnlock(&tileqtMutex);
}; /* TileQt_DestroyQApp */

static int TileQt_XErrorHandler(Display *displayPtr, XErrorEvent *errorPtr) {
  if (errorPtr->error_code == BadWindow &&
      errorPtr->request_code == 15 /* X_QueryTree */) return 0;
  else return TileQt_TkXErrorHandler(displayPtr, errorPtr);
}; /* TileQt_XErrorHandler */

static int TileQt_XEventHandler(ClientData clientData, XEvent *eventPtr) {
  const char *tcl_callback;
  int status;
  if (eventPtr->type != ClientMessage) return 0;
  Atom TileQt_KIPC_COMM_ATOM = XInternAtom(eventPtr->xclient.display,
                                           "KIPC_COMM_ATOM" , false);
  if (eventPtr->xclient.message_type != TileQt_KIPC_COMM_ATOM) return 0;
  /* The following data variable contains the type of the KIPC message,
   * As defined in kdelibs/kdecore/kipc.h:
   * PaletteChanged      = 0
   * StyleChanged        = 2
   * ToolbarStyleChanged = 6
   */
  switch (eventPtr->xclient.data.l[0]) {
    case 0:   /* PaletteChanged      */
      tcl_callback = "tile::theme::tileqt::kdePaletteChangeNotification";
      break;
    case 2:   /* StyleChanged        */
    case 6: { /* ToolbarStyleChanged */
      tcl_callback = "tile::theme::tileqt::kdeStyleChangeNotification";
      break;
    }
    default: {
      return 0;
    }
  }
  Tcl_Interp *interp = (Tcl_Interp *) clientData;
  if (interp == NULL) return 0;
  // printf("TileQt_XEventHandler: %p\n", interp); fflush(NULL);
  /* Notify the tile engine about the change... */
  status = Tcl_Eval(interp, tcl_callback);
  if (status != TCL_OK) Tcl_BackgroundError(interp);
  /* Do not remove True: As many interpreters may have registered this event
   * handler, allow Tk to call all of them! */
  return True;
} /* TileQt_XEventHandler */
