/*
 *  tileQt_Scrollbar.cpp
 * ------------------------
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

#include "tileQt_Utilities.h"
#include <tk.h>
#include "tkTheme.h"
#include "tileQt_WidgetDefaults.h"

/*
 * Map between Tk/Tile & Qt/KDE state flags.
 */
static Ttk_StateTable scrollbar_statemap[] =
{
    {QStyle::Style_Default,                         TTK_STATE_DISABLED, 0 },
    {QStyle::Style_Enabled|QStyle::Style_Down,      TTK_STATE_PRESSED, 0 },
    {QStyle::Style_Enabled|QStyle::Style_MouseOver, TTK_STATE_ACTIVE, 0 },
    {QStyle::Style_Enabled, 0, 0 }
};

typedef struct {
} ScrollbarTroughElement;

static Ttk_ElementOptionSpec ScrollbarTroughElementOptions[] = {
    {NULL}
};

static void ScrollbarTroughElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (qApp == NULL) return;
    //int orient = (int) clientData;
    //if (orient == TTK_ORIENT_HORIZONTAL) {
    //  *heightPtr = qApp->style().pixelMetric(QStyle::PM_ScrollBarExtent,
    //                                         TileQt_QScrollBar_Widget);
    //  *widthPtr  = qApp->style().pixelMetric(QStyle::PM_ScrollBarSliderMin,
    //                                         TileQt_QScrollBar_Widget);
    //} else {
    //  *widthPtr  = qApp->style().pixelMetric(QStyle::PM_ScrollBarExtent,
    //                                         TileQt_QScrollBar_Widget);
    //  *heightPtr = qApp->style().pixelMetric(QStyle::PM_ScrollBarSliderMin,
    //                                         TileQt_QScrollBar_Widget);
    //}
    *paddingPtr = Ttk_UniformPadding(0);
}

static void ScrollbarTroughElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) return;
    /* We draw the whole scrollbar at once, but without the slider! */
    int orient = (int) clientData;
    int width, height;
    //TileQt_QScrollBar_Widget->resize(b.width, b.height);
    QStyle::SFlags sflags = Ttk_StateTableLookup(scrollbar_statemap, state);
    if (orient == TTK_ORIENT_HORIZONTAL) {
      width = 2*b.width; height = b.height;
      TileQt_QScrollBar_Widget->setOrientation(Qt::Horizontal);
      sflags |= QStyle::Style_Horizontal;
    } else {
      width = b.width; height = 2*b.height;
      TileQt_QScrollBar_Widget->setOrientation(Qt::Vertical);
    }
    TileQt_QScrollBar_Widget->resize(width, height);
    TileQt_QScrollBar_Widget->setValue(0);
    QPixmap      pixmap(width, height);
    QPainter     painter(&pixmap);
    if (TileQt_QPixmap_BackgroundTile &&
        !(TileQt_QPixmap_BackgroundTile->isNull())) {
        painter.fillRect(0, 0, width, height,
                         QBrush(QColor(255,255,255),
                         *TileQt_QPixmap_BackgroundTile));
    } else {
        painter.fillRect(0, 0, width, height,
                         qApp->palette().active().background());
    }
    /* Scrollbar Items:
     * QStyle::SC_ScrollBarAddLine -> Increament button
     * QStyle::SC_ScrollBarSubLine -> Decreament button
     * QStyle::SC_ScrollBarAddPage -> Area from slider -> Increament button
     * QStyle::SC_ScrollBarSubPage -> Area from slider -> Decreament button
     * QStyle::SC_ScrollBarFirst   -> ???
     * QStyle::SC_ScrollBarLast    -> ???
     * QStyle::SC_ScrollBarGroove  -> The area the slider can move...
     */
    QStyle::SCFlags scflags = QStyle::SC_All;
    QStyle::SCFlags activeflags = QStyle::SC_None;
    
    // printf("x=%d, y=%d, w=%d, h=%d\n", b.x, b.y, b.width, b.height);
    qApp->style().drawComplexControl(QStyle::CC_ScrollBar, &painter,
          TileQt_QScrollBar_Widget,
          QRect(0, 0, width, height), qApp->palette().active(), sflags,
          scflags, activeflags);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    width-b.width, height-b.height,
                                    b.width, b.height, b.x, b.y);
}

static Ttk_ElementSpec ScrollbarTroughElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ScrollbarTroughElement),
    ScrollbarTroughElementOptions,
    ScrollbarTroughElementGeometry,
    ScrollbarTroughElementDraw
};

typedef struct {
} ScrollbarThumbElement;

static Ttk_ElementOptionSpec ScrollbarThumbElementOptions[] = {
    {NULL}
};

static void ScrollbarThumbElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (qApp == NULL) return;
    int orient = (int) clientData;
    if (orient == TTK_ORIENT_HORIZONTAL) {
      *heightPtr = qApp->style().pixelMetric(QStyle::PM_ScrollBarExtent,
                                             TileQt_QScrollBar_Widget);
      *widthPtr  = qApp->style().pixelMetric(QStyle::PM_ScrollBarSliderMin,
                                             TileQt_QScrollBar_Widget);
      if (*heightPtr > 30)  *heightPtr =  30;
      if (*widthPtr  > 100) *widthPtr  = 100;
    } else {
      *widthPtr  = qApp->style().pixelMetric(QStyle::PM_ScrollBarExtent,
                                             TileQt_QScrollBar_Widget);
      *heightPtr = qApp->style().pixelMetric(QStyle::PM_ScrollBarSliderMin,
                                             TileQt_QScrollBar_Widget);
      if (*heightPtr > 100) *heightPtr = 100;
      if (*widthPtr  > 30)  *widthPtr  =  30;
                                             
    }
    *paddingPtr = Ttk_UniformPadding(0);
}

static void ScrollbarThumbElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) return;
    if (state & TTK_STATE_DISABLED) return;
    int orient = (int) clientData;
    //QPixmap      pixmap(b.width, b.height);
    QPixmap      pixmap = QPixmap::grabWindow(Tk_WindowId(tkwin));
    QPainter     painter(&pixmap);
    QStyle::SFlags sflags = Ttk_StateTableLookup(scrollbar_statemap, state);
    if (orient == TTK_ORIENT_HORIZONTAL) sflags |= QStyle::Style_Horizontal;
    // printf("x=%d, y=%d, w=%d, h=%d\n", b.x, b.y, b.width, b.height);
    qApp->style().drawPrimitive(QStyle::PE_ScrollBarSlider, &painter,
          QRect(0, 0, b.width, b.height), qApp->palette().active(), sflags);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
}

static Ttk_ElementSpec ScrollbarThumbElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ScrollbarThumbElement),
    ScrollbarThumbElementOptions,
    ScrollbarThumbElementGeometry,
    ScrollbarThumbElementDraw
};

typedef struct {
} ScrollbarUpArrowElement;

static Ttk_ElementOptionSpec ScrollbarUpArrowElementOptions[] = {
    {NULL}
};

static void ScrollbarUpArrowElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (qApp == NULL) return;
    int orient = (int) clientData;
    if (orient == TTK_ORIENT_HORIZONTAL) {
      TileQt_QScrollBar_Widget->setOrientation(Qt::Horizontal);
    } else {
      TileQt_QScrollBar_Widget->setOrientation(Qt::Vertical);
    }
    QRect rc = qApp->style().querySubControlMetrics(QStyle::CC_ScrollBar,
                        TileQt_QScrollBar_Widget, QStyle::SC_ScrollBarSubLine);
    if (rc.isValid()) {
      *widthPtr = rc.width();
      *heightPtr = rc.height();
    }
    *paddingPtr = Ttk_UniformPadding(0);
}

static void ScrollbarUpArrowElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) return;
    int orient = (int) clientData;
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    QStyle::SFlags sflags = Ttk_StateTableLookup(scrollbar_statemap, state);
    if (orient == TTK_ORIENT_HORIZONTAL) sflags |= QStyle::Style_Horizontal;
    if (TileQt_QPixmap_BackgroundTile &&
        !(TileQt_QPixmap_BackgroundTile->isNull())) {
        painter.fillRect(0, 0, b.width, b.height,
                         QBrush(QColor(255,255,255),
                         *TileQt_QPixmap_BackgroundTile));
    } else {
        painter.fillRect(0, 0, b.width, b.height,
                         qApp->palette().active().background());
    }
    qApp->style().drawPrimitive(QStyle::PE_ScrollBarSubLine, &painter,
          QRect(0, 0, b.width, b.height), qApp->palette().active(), sflags);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
}

static Ttk_ElementSpec ScrollbarUpArrowElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ScrollbarUpArrowElement),
    ScrollbarUpArrowElementOptions,
    ScrollbarUpArrowElementGeometry,
    ScrollbarUpArrowElementDraw
};

typedef struct {
} ScrollbarDownArrowElement;

static Ttk_ElementOptionSpec ScrollbarDownArrowElementOptions[] = {
    {NULL}
};

static void ScrollbarDownArrowElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (qApp == NULL) return;
    int orient = (int) clientData;
    if (orient == TTK_ORIENT_HORIZONTAL) {
      TileQt_QScrollBar_Widget->setOrientation(Qt::Horizontal);
    } else {
      TileQt_QScrollBar_Widget->setOrientation(Qt::Vertical);
    }
    QRect rc = qApp->style().querySubControlMetrics(QStyle::CC_ScrollBar,
                        TileQt_QScrollBar_Widget, QStyle::SC_ScrollBarAddLine);
    if (rc.isValid()) {
      *widthPtr = rc.width();
      *heightPtr = rc.height();
    }
    *paddingPtr = Ttk_UniformPadding(0);
}

static void ScrollbarDownArrowElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) return;
    int orient = (int) clientData;
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    QStyle::SFlags sflags = Ttk_StateTableLookup(scrollbar_statemap, state);
    if (orient == TTK_ORIENT_HORIZONTAL) sflags |= QStyle::Style_Horizontal;
    if (TileQt_QPixmap_BackgroundTile &&
        !(TileQt_QPixmap_BackgroundTile->isNull())) {
        painter.fillRect(0, 0, b.width, b.height,
                         QBrush(QColor(255,255,255),
                         *TileQt_QPixmap_BackgroundTile));
    } else {
        painter.fillRect(0, 0, b.width, b.height,
                         qApp->palette().active().background());
    }
    qApp->style().drawPrimitive(QStyle::PE_ScrollBarAddLine, &painter,
          QRect(0, 0, b.width, b.height), qApp->palette().active(), sflags);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
}

static Ttk_ElementSpec ScrollbarDownArrowElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ScrollbarDownArrowElement),
    ScrollbarDownArrowElementOptions,
    ScrollbarDownArrowElementGeometry,
    ScrollbarDownArrowElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

// TTK_BEGIN_LAYOUT(HorizontalScrollbarLayout)
//     TTK_GROUP("Horizontal.Scrollbar.trough", TTK_FILL_X,
//         TTK_NODE("Horizontal.Scrollbar.leftarrow", TTK_PACK_LEFT)
//         TTK_NODE("Horizontal.Scrollbar.rightarrow", TTK_PACK_RIGHT)
//         TTK_NODE("Horizontal.Scrollbar.thumb", TTK_FILL_BOTH))
// TTK_END_LAYOUT
// 
// TTK_BEGIN_LAYOUT(VerticalScrollbarLayout)
//     TTK_GROUP("Vertical.Scrollbar.trough", TTK_FILL_Y,
//         TTK_NODE("Vertical.Scrollbar.uparrow", TTK_PACK_TOP)
//         TTK_NODE("Vertical.Scrollbar.downarrow", TTK_PACK_BOTTOM)
//         TTK_NODE("Vertical.Scrollbar.thumb", TTK_FILL_BOTH))
// TTK_END_LAYOUT

int TileQt_Init_Scrollbar(Tcl_Interp *interp, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Horizontal.Scrollbar.trough",
            &ScrollbarTroughElementSpec, (void *) TTK_ORIENT_HORIZONTAL);
    Ttk_RegisterElement(interp, themePtr, "Vertical.Scrollbar.trough",
            &ScrollbarTroughElementSpec, (void *) TTK_ORIENT_VERTICAL);
    Ttk_RegisterElement(interp, themePtr, "Horizontal.Scrollbar.leftarrow",
            &ScrollbarUpArrowElementSpec, (void *) TTK_ORIENT_HORIZONTAL);
    Ttk_RegisterElement(interp, themePtr, "Vertical.Scrollbar.uparrow",
            &ScrollbarUpArrowElementSpec, (void *) TTK_ORIENT_VERTICAL);
    Ttk_RegisterElement(interp, themePtr, "Horizontal.Scrollbar.rightarrow",
            &ScrollbarDownArrowElementSpec, (void *) TTK_ORIENT_HORIZONTAL);
    Ttk_RegisterElement(interp, themePtr, "Vertical.Scrollbar.downarrow",
            &ScrollbarDownArrowElementSpec, (void *) TTK_ORIENT_VERTICAL);
    Ttk_RegisterElement(interp, themePtr, "Horizontal.Scrollbar.thumb",
            &ScrollbarThumbElementSpec, (void *) TTK_ORIENT_HORIZONTAL);
    Ttk_RegisterElement(interp, themePtr, "Vertical.Scrollbar.thumb",
            &ScrollbarThumbElementSpec, (void *) TTK_ORIENT_VERTICAL);
    Ttk_RegisterElement(interp, themePtr, "Scrollbar.grip",
            &ScrollbarTroughElementSpec, NULL);
    
    /*
     * Register layouts:
     */
    //Ttk_RegisterLayout(themePtr, "Vertical.TScrollbar",
    //        VerticalScrollbarLayout);
    //Ttk_RegisterLayout(themePtr, "Horizontal.TScrollbar",
    //        HorizontalScrollbarLayout);

    return TCL_OK;
}; /* TileQt_Init_Scrollbar */
