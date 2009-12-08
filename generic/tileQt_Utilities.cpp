/*
 *  tileQt_Utilities.cpp
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
#include "tileQt_TkHeaders.h"

void TileQt_StateInfo(int state, Tk_Window tkwin)
{
    printf("Widget: %s\n  ", Tk_PathName(tkwin));
    if (state & TTK_STATE_ACTIVE) {
      printf("TTK_STATE_ACTIVE %d ", TTK_STATE_ACTIVE);
    } 
    if (state & TTK_STATE_DISABLED) {
      printf("TTK_STATE_DISABLED %d ", TTK_STATE_DISABLED);
    } 
    if (state & TTK_STATE_FOCUS) {
      printf("TTK_STATE_FOCUS %d ", TTK_STATE_FOCUS);
    } 
    if (state & TTK_STATE_PRESSED) {
      printf("TTK_STATE_PRESSED %d ", TTK_STATE_PRESSED);
    } 
    if (state & TTK_STATE_SELECTED) {
      printf("TTK_STATE_SELECTED %d ", TTK_STATE_SELECTED);
    } 
    if (state & TTK_STATE_BACKGROUND) {
      printf("TTK_STATE_BACKGROUND %d ", TTK_STATE_BACKGROUND);
    } 
    if (state & TTK_STATE_ALTERNATE) {
      printf("TTK_STATE_ALTERNATE %d ", TTK_STATE_ALTERNATE);
    } 
    if (state & TTK_STATE_INVALID) {
      printf("TTK_STATE_INVALID %d ", TTK_STATE_INVALID);
    } 
    if (state & TTK_STATE_READONLY) {
      printf("TTK_STATE_READONLY %d ", TTK_STATE_READONLY);
    } 
    if (state & TTK_STATE_USER1) {
      printf("TTK_STATE_USER1 %d ", TTK_STATE_USER1);
    } 
    if (state & TTK_STATE_USER2) {
      printf("TTK_STATE_USER2 %d ", TTK_STATE_USER2);
    } 
    if (state & TTK_STATE_USER3) {
      printf("TTK_STATE_USER3 %d ", TTK_STATE_USER3);
    } 
    if (state & TTK_STATE_USER4) {
      printf("TTK_STATE_USER4 %d ", TTK_STATE_USER4);
    } 
    if (state & TTK_STATE_USER5) {
      printf("TTK_STATE_USER5 %d ", TTK_STATE_USER5);
    } 
    if (state & TTK_STATE_USER6) {
      printf("TTK_STATE_USER6 %d ", TTK_STATE_USER6);
    } 
//     if (state & TTK_STATE_USER7) {
//       printf("TTK_STATE_USER7 %d ", TTK_STATE_USER7);
//     }
    printf(" state=%d\n", state);
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

void TileQt_StoreStyleNameLowers(TileQt_WidgetCache *wc) {
  if (wc->lowerStyleName) delete wc->lowerStyleName;
  wc->lowerStyleName = new QString();
#ifdef TILEQT_QT_VERSION_4
  *(wc->lowerStyleName) = QString(wc->TileQt_Style->objectName()).toLower();
#endif /* TILEQT_QT_VERSION_4 */
}; /* TileQt_StoreStyleName */

bool TileQt_ThemeIs(TileQt_WidgetCache *wc, const char* name) {
  if (wc->lowerStyleName) return *(wc->lowerStyleName) == name;
  return false;
}; /* TileQt_ThemeIs */

/*
 * TileQt_StateTableLookup --
 * Look up an index from a statically allocated state table.
 */
unsigned int TileQt_StateTableLookup(Ttk_StateTable *map, unsigned int state) {
    return Ttk_StateTableLookup(map, state);
    int value = 0;
    while (map->onBits || map->offBits) {
      if (state & map->onBits) value |= map->index;
      ++map;
    }
    return value;
}; /* TileQt_StateTableLookup */
