/*
 *  tileQt_Utilities.cpp
 * ----------------------
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
#include <tk.h>
#include "tkTheme.h"

/*
 * TileQt_TileStateToSFlags
 * Convert tile states to Qt flags...
 */
QStyle::SFlags TileQt_TileStateToSFlags(unsigned int state)
{
    switch (state)
    {
            case TTK_STATE_ACTIVE:
            case TTK_STATE_DISABLED:
            case TTK_STATE_FOCUS:
            case TTK_STATE_PRESSED:
            case TTK_STATE_SELECTED:
            case TTK_STATE_BACKGROUND:
            case TTK_STATE_ALTERNATE:
            case TTK_STATE_INVALID:
            case TTK_STATE_READONLY:
                    return QStyle::Style_Enabled | QStyle::Style_Down;
            default:
                    return QStyle::Style_Enabled;
    }
}

void TileQt_StateInfo(int state, Tk_Window tkwin)
{
    printf("Widget: %s\n  ", Tk_PathName(tkwin));
    if (state & TTK_STATE_ACTIVE) {
      printf("TTK_STATE_ACTIVE ");
    } else if (state & TTK_STATE_DISABLED) {
      printf("TTK_STATE_DISABLED ");
    } else if (state & TTK_STATE_FOCUS) {
      printf("TTK_STATE_FOCUS ");
    } else if (state & TTK_STATE_PRESSED) {
      printf("TTK_STATE_PRESSED ");
    } else if (state & TTK_STATE_SELECTED) {
      printf("TTK_STATE_SELECTED ");
    } else if (state & TTK_STATE_BACKGROUND) {
      printf("TTK_STATE_BACKGROUND ");
    } else if (state & TTK_STATE_ALTERNATE) {
      printf("TTK_STATE_ALTERNATE ");
    } else if (state & TTK_STATE_INVALID) {
      printf("TTK_STATE_INVALID ");
    } else if (state & TTK_STATE_READONLY) {
      printf("TTK_STATE_READONLY ");
    } else if (state & TTK_STATE_USER1) {
      printf("TTK_STATE_USER1 ");
    } else if (state & TTK_STATE_USER2) {
      printf("TTK_STATE_USER2 ");
    } else if (state & TTK_STATE_USER3) {
      printf("TTK_STATE_USER3 ");
    } else if (state & TTK_STATE_USER4) {
      printf("TTK_STATE_USER4 ");
    } else if (state & TTK_STATE_USER5) {
      printf("TTK_STATE_USER5 ");
    } else if (state & TTK_STATE_USER6) {
      printf("TTK_STATE_USER6 ");
    } else if (state & TTK_STATE_USER7) {
      printf("TTK_STATE_USER7");
    }
    printf("\n");
}; /* TileQt_StateInfo */

void TileQt_CopyQtPixmapOnToDrawable(QPixmap& pixmap, Drawable d,
            Tk_Window tkwin, int x, int y, int w, int h, int x1, int x2)
{
    XGCValues gcValues;
    gcValues.graphics_exposures = False;
    GC gc = Tk_GetGC(tkwin, GCForeground | GCBackground | GCGraphicsExposures,
                     &gcValues);
    XCopyArea(Tk_Display(tkwin), pixmap.handle(), d, gc,
              x, y, w, h, x1, x2);
    Tk_FreeGC(Tk_Display(tkwin), gc);
}; /* TileQt_CopyQtPixmapOnToDrawable */
