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
    if (qApp == NULL) return;
    *paddingPtr = Ttk_UniformPadding(0);
}

static void ProgressTroughElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) return;
    int orient = (int) clientData;
    int width = Tk_Width(tkwin), height = Tk_Height(tkwin);
    QProgressBar widget(100, NULL);
    if (orient == TTK_ORIENT_HORIZONTAL) {
      widget.resize(width, height);
    } else {
      widget.resize(height, width);
    }
    widget.setProgress(0);
    //widget.setCenterIndicator(false);
    //widget.setPercentageVisible(false);
    QPixmap pixmap = QPixmap::grabWidget(&widget);
    if (orient == TTK_ORIENT_VERTICAL) {
      // Qt does not support vertical progress bars. Rotate it :-)
      QWMatrix matrix;
      matrix.rotate(270);
      pixmap = pixmap.xForm(matrix);
    }
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, width, height, 0, 0);
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
    if (qApp == NULL) return;
    int orient = (int) clientData;
    QProgressBar widget(100, NULL);
    if (orient == TTK_ORIENT_HORIZONTAL) {
      *widthPtr   = widget.sizeHint().width();
      *heightPtr  = widget.sizeHint().height();
    } else {
      *widthPtr   = widget.sizeHint().height();
      *heightPtr  = widget.sizeHint().width();
    }
    *paddingPtr = Ttk_UniformPadding(0);
}

static void ProgressBarElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) return;
    int orient = (int) clientData;
    int width = Tk_Width(tkwin), height = Tk_Height(tkwin);
    QProgressBar widget(100, NULL);
    double percentage;
    if (orient == TTK_ORIENT_HORIZONTAL) {
      widget.resize(width, height);
      percentage = double(b.width)/double(width);
    } else {
      widget.resize(height, width);
      percentage = double(b.height)/double(height);
    }
    // Determine the progress value by comparing the width of this box to the
    // total width of the window...
    widget.setProgress((int)(percentage*100.0));
    //widget.setCenterIndicator(false);
    //widget.setPercentageVisible(false);
    QPixmap pixmap = QPixmap::grabWidget(&widget);
    if (orient == TTK_ORIENT_VERTICAL) {
      // Qt does not support vertical progress bars. Rotate it :-)
      QWMatrix matrix;
      matrix.rotate(270);
      pixmap = pixmap.xForm(matrix);
    }
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, width, height, 0, 0);
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
    TTK_GROUP("Vertical.Progressbar.trough", TTK_FILL_BOTH,
            TTK_NODE("Vertical.Progressbar.pbar", TTK_PACK_TOP))
TTK_END_LAYOUT

TTK_BEGIN_LAYOUT(HorizontalProgressBarLayout)
    TTK_GROUP("Horizontal.Progressbar.trough", TTK_FILL_BOTH,
        TTK_NODE("Horizontal.Progressbar.pbar", TTK_PACK_LEFT))
TTK_END_LAYOUT

int TileQt_Init_Progress(Tcl_Interp *interp, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Horizontal.Progressbar.trough",
            &ProgressTroughElementSpec, (void *) TTK_ORIENT_HORIZONTAL);
    Ttk_RegisterElement(interp, themePtr, "Vertical.Progressbar.trough",
            &ProgressTroughElementSpec, (void *) TTK_ORIENT_VERTICAL);

    Ttk_RegisterElement(interp, themePtr, "Horizontal.Progressbar.pbar",
            &ProgressBarElementSpec, (void *) TTK_ORIENT_HORIZONTAL);
    Ttk_RegisterElement(interp, themePtr, "Vertical.Progressbar.pbar",
            &ProgressBarElementSpec, (void *) TTK_ORIENT_VERTICAL);
    
    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr,
            "Horizontal.TProgressbar", HorizontalProgressBarLayout);
    Ttk_RegisterLayout(themePtr,
            "Vertical.TProgressbar", VerticalProgressBarLayout);

    return TCL_OK;
}; /* TileQt_Init_Progress */
