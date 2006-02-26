/*
 *  tileQt_Progress.cpp
 * ---------------------
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
    if (qApp == NULL) NULL_Q_APP;
    *paddingPtr = Ttk_UniformPadding(0);
}

static void ProgressTroughElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_WIDGET(TileQt_QProgressBar_Hor_Widget);
    int orient = (int) clientData;
    Tcl_MutexLock(&tileqtMutex);
    QProgressBar& widget = *TileQt_QProgressBar_Hor_Widget;
    if (orient == TTK_ORIENT_HORIZONTAL) {
      widget.resize(b.width, b.height);
    } else {
      widget.resize(b.height, b.width);
    }
    widget.reset();
    widget.setCenterIndicator(false);
    widget.setPercentageVisible(false);
    QPixmap pixmap = QPixmap::grabWidget(&widget);
    if (orient == TTK_ORIENT_VERTICAL) {
      // Qt does not support vertical progress bars. Rotate it :-)
      QWMatrix matrix;
      matrix.rotate(270);
      pixmap = pixmap.xForm(matrix);
    }
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
    Tcl_MutexUnlock(&tileqtMutex);
}

static Ttk_ElementSpec ProgressTroughElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ProgressTroughElement),
    ProgressTroughElementOptions,
    ProgressTroughElementGeometry,
    ProgressTroughElementDraw
};

typedef struct {
    Tcl_Obj    *orientObj;
    Tcl_Obj    *lengthObj;
    Tcl_Obj    *modeObj;
    Tcl_Obj    *maximumObj;
    Tcl_Obj    *valueObj;
} ProgressBarElement;

static Ttk_ElementOptionSpec ProgressBarElementOptions[] = {
    { "-orient", TK_OPTION_ANY, Tk_Offset(ProgressBarElement, orientObj),
      "horizontal"},
    { "-length", TK_OPTION_PIXELS, Tk_Offset(ProgressBarElement, lengthObj),
      "100" },
    { "-mode", TK_OPTION_STRING_TABLE, Tk_Offset(ProgressBarElement, modeObj),
      "determinate" },
    { "-maximum", TK_OPTION_DOUBLE, Tk_Offset(ProgressBarElement, maximumObj),
      "100" },
    { "-value", TK_OPTION_DOUBLE, Tk_Offset(ProgressBarElement, valueObj),
      "0.0" },
    { NULL }
};

static void ProgressBarElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_WIDGET(TileQt_QProgressBar_Hor_Widget);
    int orient = (int) clientData, length;
    bool determinate = true;
    ProgressBarElement *pbar = (ProgressBarElement *) elementRecord;
    Tk_GetPixelsFromObj(NULL, tkwin, pbar->lengthObj, &length);
    if (strncmp(Tcl_GetString(pbar->modeObj), "determinate", 10) != 0)
        determinate = false;

    Tcl_MutexLock(&tileqtMutex);
    QProgressBar& widget = *TileQt_QProgressBar_Hor_Widget;
    if (orient == TTK_ORIENT_HORIZONTAL) {
      *widthPtr   = length/4 /*widget.sizeHint().width()*/;
      *heightPtr  = widget.sizeHint().height();
    } else {
      *widthPtr   = widget.sizeHint().height();
      *heightPtr  = length/4 /*widget.sizeHint().width()*/;
    }
    Tcl_MutexUnlock(&tileqtMutex);
    *paddingPtr = Ttk_UniformPadding(0);
}

static void ProgressBarElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_WIDGET(TileQt_QProgressBar_Hor_Widget);
    int orient = (int) clientData;
    ProgressBarElement *pbar = (ProgressBarElement *) elementRecord;
    int width = Tk_Width(tkwin), height = Tk_Height(tkwin);
    bool determinate = true;
    double value, maximum;
    Tcl_GetDoubleFromObj(NULL, pbar->valueObj, &value);
    Tcl_GetDoubleFromObj(NULL, pbar->maximumObj, &maximum);
    if (strncmp(Tcl_GetString(pbar->modeObj), "determinate", 10) != 0) {
      determinate = false;
    }
    
    int src_x = 0, src_y = 0, dest_x = 0, dest_y = 0;

    Tcl_MutexLock(&tileqtMutex);
    QProgressBar& widget = *TileQt_QProgressBar_Hor_Widget;
    double percentage = value/maximum;
    if (orient == TTK_ORIENT_HORIZONTAL) {
      if (!determinate) {
        widget.resize(b.width, height);
        percentage = 1.0;
        width = b.width;
        dest_x = b.x;
      } else {
        widget.resize(width, height);
      }
    } else {
      if (!determinate) {
        widget.resize(b.height, width);
        percentage = 1.0;
        height = b.height;
        dest_y = b.y;
      } else {
        widget.resize(height, width);
      }
    }
    widget.setProgress((int)(percentage*100.0));
    if (determinate) {
      widget.setCenterIndicator(true);
      widget.setPercentageVisible(true);
    } else {
      widget.setCenterIndicator(false);
      widget.setPercentageVisible(false);
    }
    widget.setFrameStyle(QFrame::NoFrame);
    QPixmap pixmap = QPixmap::grabWidget(&widget);
    if (orient == TTK_ORIENT_VERTICAL) {
      // Qt does not support vertical progress bars. Rotate it :-)
      QWMatrix matrix;
      matrix.rotate(270);
      pixmap = pixmap.xForm(matrix);
    }
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                           src_x, src_y, width, height, dest_x, dest_y);
    Tcl_MutexUnlock(&tileqtMutex);
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
            TTK_NODE("Vertical.Progressbar.pbar", TTK_PACK_BOTTOM|TTK_FILL_X))
TTK_END_LAYOUT

TTK_BEGIN_LAYOUT(HorizontalProgressBarLayout)
    TTK_GROUP("Horizontal.Progressbar.trough", TTK_FILL_BOTH,
        TTK_NODE("Horizontal.Progressbar.pbar", TTK_PACK_LEFT|TTK_FILL_Y))
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
