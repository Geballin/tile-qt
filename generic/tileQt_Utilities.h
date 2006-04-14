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

/* Global Symbols */

/* Helper Functions */
extern QStyle::SFlags TileQt_TileStateToSFlags(unsigned int state);
extern void TileQt_StateInfo(int, Tk_Window);
extern void TileQt_CopyQtPixmapOnToDrawable(QPixmap&, Drawable, Tk_Window,
                                            int, int, int, int, int, int);
extern void TileQt_StoreStyleNameLowers(TileQt_WidgetCache *wc);
extern bool TileQt_ThemeIs(TileQt_WidgetCache *wc, const char* name);
