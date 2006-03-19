/*
 *  tileQt_Utilities.h
 * ----------------------
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

#define NULL_Q_APP {printf("NULL qApp\n");fflush(NULL);return;}
#define NULL_PROXY_WIDGET(widget) \
   TileQt_WidgetCache *wc = (TileQt_WidgetCache *) clientData;\
   if (wc == NULL) {\
   printf("NULL ClientData: " STRINGIFY(widget) "!\n");fflush(NULL);return;}\
   if (wc->widget == NULL) {\
   printf("NULL Proxy Widget: %p->" STRINGIFY(widget) "!\n", wc);fflush(NULL);return;}
#define NULL_PROXY_ORIENTED_WIDGET(widget) \
   TileQt_WidgetCache *wc = (TileQt_WidgetCache *) clientData;\
   if (wc == NULL) {\
   printf("NULL ClientData: " STRINGIFY(widget) "!\n");fflush(NULL);return;}\
   if (wc->widget == NULL) {\
   printf("NULL Proxy Widget: %p->" STRINGIFY(widget) "!\n", wc);fflush(NULL);return;}\
   int orient = wc->orientation;
#define ENSURE_WIDGET_STYLE(widget) \
   if (&(widget.style()) != wc->TileQt_Style) widget.setStyle(wc->TileQt_Style);

TCL_DECLARE_MUTEX(tileqtMutex);

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

/* Global Symbols */

/* Helper Functions */
extern QStyle::SFlags TileQt_TileStateToSFlags(unsigned int state);
extern void TileQt_StateInfo(int, Tk_Window);
extern void TileQt_CopyQtPixmapOnToDrawable(QPixmap&, Drawable, Tk_Window,
                                            int, int, int, int, int, int);
