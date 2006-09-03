/*
 *  tileQt_Utilities.cpp
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
#include <tk.h>
#include "tkTheme.h"

#ifdef TILEQT_QT_VERSION_3
/*
 * TileQt_TileStateToSFlags
 * Convert tile states to Qt flags...
 */
void TileQt_QtStateInfo(QStyle::SFlags state, Tk_Window tkwin) {
    printf("Widget: %s\n  ", Tk_PathName(tkwin));
    if (state & QStyle::Style_Default) 
      printf("Style_Default %d ", QStyle::Style_Default);
    if (state & QStyle::Style_Enabled) 
      printf("Style_Enabled %d ", QStyle::Style_Enabled);
    if (state & QStyle::Style_Raised) 
      printf("Style_Raised %d ", QStyle::Style_Raised);
    if (state & QStyle::Style_Sunken) 
      printf("Style_Sunken %d ", QStyle::Style_Sunken);
    if (state & QStyle::Style_Off) 
      printf("Style_Off %d ", QStyle::Style_Off);
    if (state & QStyle::Style_NoChange) 
      printf("Style_NoChange %d ", QStyle::Style_NoChange);
    if (state & QStyle::Style_On) 
      printf("Style_On %d ", QStyle::Style_On);
    if (state & QStyle::Style_Down) 
      printf("Style_Down %d ", QStyle::Style_Down);
    if (state & QStyle::Style_Horizontal) 
      printf("Style_Horizontal %d ", QStyle::Style_Horizontal);
    if (state & QStyle::Style_HasFocus) 
      printf("Style_HasFocus %d ", QStyle::Style_HasFocus);
    if (state & QStyle::Style_Top) 
      printf("Style_Top %d ", QStyle::Style_Top);
    if (state & QStyle::Style_Bottom) 
      printf("Style_Bottom %d ", QStyle::Style_Bottom);
    if (state & QStyle::Style_FocusAtBorder) 
      printf("Style_FocusAtBorder %d ", QStyle::Style_FocusAtBorder);
    if (state & QStyle::Style_AutoRaise)
      printf("Style_AutoRaise %d ", QStyle::Style_AutoRaise);
    if (state & QStyle::Style_MouseOver) 
      printf("Style_MouseOver %d ", QStyle::Style_MouseOver);
    if (state & QStyle::Style_Up) 
      printf("Style_Up %d ", QStyle::Style_Up);
    if (state & QStyle::Style_Selected) 
      printf("Style_Selected %d ", QStyle::Style_Selected);
    if (state & QStyle::Style_Active) 
      printf("Style_Active %d ", QStyle::Style_Active);
    if (state & QStyle::Style_ButtonDefault) 
      printf("Style_ButtonDefault %d ", QStyle::Style_ButtonDefault);
    printf(" state=%d\n", state);
}; /* TileQt_QtStateInfo */

#endif /* TILEQT_QT_VERSION_3 */

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
    if (state & TTK_STATE_USER7) {
      printf("TTK_STATE_USER7 %d ", TTK_STATE_USER7);
    }
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
#ifdef TILEQT_QT_VERSION_3
  *(wc->lowerStyleName) = QString(wc->TileQt_Style->name()).lower();
#endif /* TILEQT_QT_VERSION_3 */
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
