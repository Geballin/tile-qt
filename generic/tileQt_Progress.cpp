/*
 *  tileQt_Progress.cpp
 * ---------------------
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
static Ttk_StateTable progress_statemap[] =
{
    {QStyle::Style_Enabled, 0, 0 }
};

typedef struct {
} ProgressTroughElement;

static Ttk_ElementOptionSpec ProgressTroughElementOptions[] = {
    {NULL}
};

static void ProgressTroughElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    *paddingPtr = Ttk_UniformPadding(0);
}

static void ProgressTroughElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    int orient = (int) clientData;
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    QProgressBar widget(1, TileQt_QWidget_Widget);
    widget.resize(b.width, b.height);
    //widget.setGeometry(b.x, b.y, b.width, b.height);
    widget.setProgress(0);
    widget.setCenterIndicator(false);
    widget.setPercentageVisible(false);

    QStyle::SFlags sflags = Ttk_StateTableLookup(progress_statemap, state);
    if (orient == TTK_ORIENT_HORIZONTAL) {
      sflags |= QStyle::Style_Horizontal;
    }
    
    if (TileQt_QPixmap_BackgroundTile &&
        !(TileQt_QPixmap_BackgroundTile->isNull())) {
        painter.fillRect(0, 0, b.width, b.height,
                         QBrush(QColor(255,255,255),
                         *TileQt_QPixmap_BackgroundTile));
    } else {
        painter.fillRect(0, 0, b.width, b.height,
                         widget.paletteBackgroundColor());
                         //qApp->palette().active().background());
    }
    // printf("x=%d, y=%d, w=%d, h=%d\n", b.x, b.y, b.width, b.height);
    qApp->style().drawControl(QStyle::CE_ProgressBarGroove, &painter, &widget,
          QRect(0, 0, b.width, b.height),
          widget.colorGroup(), sflags);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.x);
}

static Ttk_ElementSpec ProgressTroughElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ProgressTroughElement),
    ProgressTroughElementOptions,
    ProgressTroughElementGeometry,
    ProgressTroughElementDraw
};

typedef struct {
} ProgressBarElement;

static Ttk_ElementOptionSpec ProgressBarElementOptions[] = {
    {NULL}
};

static void ProgressBarElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    //int orient = (int) clientData;
    //QProgressBar widget(TileQt_QWidget_Widget);
    //if (orient == TTK_ORIENT_HORIZONTAL) {
    //  *widthPtr   = widget.width();
    //  *heightPtr  = widget.height();
    //} else {
    //  *widthPtr   = widget.height();
    //  *heightPtr  = widget.width();
    //}
    int orient = (int) clientData;
    if (orient == TTK_ORIENT_HORIZONTAL) {
      *heightPtr = qApp->style().pixelMetric(QStyle::PM_ProgressBarChunkWidth)
                   + 2*ProgressBarInternalPadding;
    } else {
      *widthPtr   = qApp->style().pixelMetric(QStyle::PM_ProgressBarChunkWidth)
                   + 2*ProgressBarInternalPadding;
    }
    *paddingPtr = Ttk_UniformPadding(0);
}

static void ProgressBarElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    int orient = (int) clientData;
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    QProgressBar widget(100, TileQt_QWidget_Widget);
    //widget.resize(b.width, b.height);
    widget.setProgress(100);
    widget.setCenterIndicator(false);
    widget.setPercentageVisible(false);

    QStyle::SFlags sflags = Ttk_StateTableLookup(progress_statemap, state);
    if (orient == TTK_ORIENT_HORIZONTAL) {
      sflags |= QStyle::Style_Horizontal;
    }
    
    if (TileQt_QPixmap_BackgroundTile &&
        !(TileQt_QPixmap_BackgroundTile->isNull())) {
        painter.fillRect(0, 0, b.width, b.height,
                         QBrush(QColor(255,255,255),
                         *TileQt_QPixmap_BackgroundTile));
    } else {
        painter.fillRect(0, 0, b.width, b.height,
                         qApp->palette().active().background());
    }
    // printf("x=%d, y=%d, w=%d, h=%d\n", b.x, b.y, b.width, b.height);
    int w, h;
    qApp->style().drawControl(QStyle::CE_ProgressBarGroove, &painter, &widget,
          QRect(0, 0, b.width, b.height), widget.colorGroup(), sflags);
    w = b.width-2*ProgressBarInternalPadding;
    h = b.height-2*ProgressBarInternalPadding;
    if (w > ProgressBarInternalPadding && h > ProgressBarInternalPadding) {
      qApp->style().drawControl(QStyle::CE_ProgressBarContents, &painter,
            &widget, QRect(ProgressBarInternalPadding,
            ProgressBarInternalPadding, w, h),
            widget.colorGroup(), sflags);
    }
    if (orient == TTK_ORIENT_HORIZONTAL) {
      w = b.width - ProgressBarInternalPadding;
      h = b.height;
    } else {
      w = b.width;
      h = b.height - ProgressBarInternalPadding;
    } 
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin, 0, 0, w, h, b.x, b.x);
}

static Ttk_ElementSpec ProgressBarElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ProgressBarElement),
    ProgressBarElementOptions,
    ProgressBarElementGeometry,
    ProgressBarElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

TTK_BEGIN_LAYOUT(VerticalProgressBarLayout)
    TTK_GROUP("Vertical.Progress.trough", TTK_FILL_BOTH,
        TTK_GROUP("Vertical.Progress.padding", TTK_FILL_BOTH,
	    TTK_NODE("Vertical.Progress.bar", TTK_PACK_TOP)))
TTK_END_LAYOUT

TTK_BEGIN_LAYOUT(HorizontalProgressBarLayout)
    TTK_GROUP("Horizontal.Progress.trough", TTK_FILL_BOTH,
	TTK_NODE("Horizontal.Progress.bar", TTK_PACK_LEFT))
TTK_END_LAYOUT

int TileQt_Init_Progress(Tcl_Interp *interp, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElementSpec(themePtr, "Horizontal.Progress.trough",
            &ProgressTroughElementSpec, (void *) TTK_ORIENT_HORIZONTAL);
    Ttk_RegisterElementSpec(themePtr, "Vertical.Progress.trough",
            &ProgressTroughElementSpec, (void *) TTK_ORIENT_VERTICAL);
    Ttk_RegisterElementSpec(themePtr, "Horizontal.Progress.bar",
            &ProgressBarElementSpec, (void *) TTK_ORIENT_HORIZONTAL);
    Ttk_RegisterElementSpec(themePtr, "Vertical.Progress.bar",
            &ProgressBarElementSpec, (void *) TTK_ORIENT_VERTICAL);
    
    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr,
	    "Horizontal.TProgress", HorizontalProgressBarLayout);
    Ttk_RegisterLayout(themePtr,
	    "Vertical.TProgress", VerticalProgressBarLayout);

    return TCL_OK;
}; /* TileQt_Init_Progress */
