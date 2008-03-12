/*
 *  tileQt_Utilities.h
 * ----------------------
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
#include "tileQt_Elements.h"

#define NULL_Q_APP {/*printf("NULL qApp\n");fflush(NULL);*/return;}
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


#define TILEQT_SET_FOCUS(state) \
   if (state & TTK_STATE_FOCUS) {TileQt_SetFocus(true);}
#define TILEQT_CLEAR_FOCUS(state) \
   if (state & TTK_STATE_FOCUS) {TileQt_SetFocus(false);}

#ifdef TILEQT_QT_VERSION_3
#define TILEQT_PAINT_BACKGROUND(width, height) \
    if (wc->TileQt_QPixmap_BackgroundTile && \
        !(wc->TileQt_QPixmap_BackgroundTile->isNull())) { \
        painter.fillRect(0, 0, width, height, \
                         QBrush(QColor(255,255,255), \
                         *(wc->TileQt_QPixmap_BackgroundTile))); \
    } else { \
        painter.fillRect(0, 0, width, height, \
                         qApp->palette().active().background());\
    }
#define TILEQT_PAINT_BACKGROUND_BASE(width, height) \
    if (wc->TileQt_QPixmap_BackgroundTile && \
        !(wc->TileQt_QPixmap_BackgroundTile->isNull())) { \
        painter.fillRect(0, 0, width, height, \
                         QBrush(QColor(255,255,255), \
                         *(wc->TileQt_QPixmap_BackgroundTile))); \
    } else { \
        painter.fillRect(0, 0, width, height, \
                         qApp->palette().active().base());\
    }
#endif /* TILEQT_QT_VERSION_3 */

#ifdef TILEQT_QT_VERSION_4
#define TILEQT_PAINT_BACKGROUND(width, height) \
    if (!(wc->TileQt_QPixmap_BackgroundTile.isNull())) { \
        painter.fillRect(0, 0, width, height, \
                         QBrush(QColor(255,255,255), \
                         wc->TileQt_QPixmap_BackgroundTile)); \
    } else { \
        painter.fillRect(0, 0, width, height, \
                         qApp->palette().color(QPalette::Normal, \
                                               QPalette::Window));\
    }
#define TILEQT_PAINT_BACKGROUND_BASE(width, height) \
    if (!(wc->TileQt_QPixmap_BackgroundTile.isNull())) { \
        painter.fillRect(0, 0, width, height, \
                         QBrush(QColor(255,255,255), \
                         wc->TileQt_QPixmap_BackgroundTile)); \
    } else { \
        painter.fillRect(0, 0, width, height, \
                         qApp->palette().color(QPalette::Normal, \
                                               QPalette::Base));\
    }
#endif /* TILEQT_QT_VERSION_4 */

#ifdef TILEQT_QT_VERSION_3
#define PMW(pm, w) (wc->TileQt_Style->pixelMetric(QStyle::pm, w))
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
#define PMW(pm, w) (wc->TileQt_Style->pixelMetric(QStyle::pm, 0, w))
#endif /* TILEQT_QT_VERSION_4 */

TCL_DECLARE_MUTEX(tileqtMutex);

/* Global Symbols */

/* Helper Functions */
#ifdef TILEQT_QT_VERSION_3
extern void TileQt_QtStateInfo(QStyle::SFlags, Tk_Window);
#endif /* TILEQT_QT_VERSION_3 */
extern void TileQt_StateInfo(int, Tk_Window);
extern void TileQt_CopyQtPixmapOnToDrawable(QPixmap&, Drawable, Tk_Window,
                                            int, int, int, int, int, int);
extern void TileQt_StoreStyleNameLowers(TileQt_WidgetCache *wc);
extern bool TileQt_ThemeIs(TileQt_WidgetCache *wc, const char* name);
extern unsigned int TileQt_StateTableLookup(Ttk_StateTable *, unsigned int);
extern void TileQt_SetFocus(bool focus);
