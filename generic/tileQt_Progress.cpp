/*
 *  tileQt_Progress.cpp
 * ---------------------
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

#include "tileQt_Utilities.h"
#include "tileQt_TkHeaders.h"
#include "tileQt_WidgetDefaults.h"

/*
 * Map between Tk/Tile & Qt/KDE state flags.
 */
#if 0
static Ttk_StateTable progress_statemap[] =
{
    {QStyle::Style_Default                          , TTK_STATE_DISABLED, 0},
    {QStyle::Style_Enabled | QStyle::Style_Down     , TTK_STATE_PRESSED, 0},
    {QStyle::Style_Enabled | QStyle::Style_MouseOver, TTK_STATE_ACTIVE, 0},
    {QStyle::Style_Enabled | QStyle::Style_HasFocus , TTK_STATE_FOCUS, 0},
    {QStyle::Style_Enabled | QStyle::Style_Active   , TTK_STATE_ALTERNATE, 0},
    {QStyle::Style_Enabled, 0, 0 }
};
#endif

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
    NULL_PROXY_ORIENTED_WIDGET(TileQt_QProgressBar_Hor_Widget);
    Tcl_MutexLock(&tileqtMutex);
    QProgressBar& widget = *wc->TileQt_QProgressBar_Hor_Widget;
    if (orient == TTK_ORIENT_HORIZONTAL) {
#ifdef TILEQT_QT_VERSION_3
      widget.resize(b.width, b.height);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
      widget.setOrientation(Qt::Horizontal);
#endif /* TILEQT_QT_VERSION_4 */
    } else {
#ifdef TILEQT_QT_VERSION_3
      widget.resize(b.height, b.width);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
      widget.setOrientation(Qt::Vertical);
#endif /* TILEQT_QT_VERSION_4 */
    }
    widget.reset();
#ifdef TILEQT_QT_VERSION_3
    widget.setCenterIndicator(false);
    widget.setPercentageVisible(false);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    widget.resize(b.width, b.height);
    widget.setTextVisible(false);
#endif /* TILEQT_QT_VERSION_4 */
    if (state & TTK_STATE_DISABLED) widget.setEnabled(false);
    TILEQT_SET_FOCUS(state);
    QPixmap pixmap = QPixmap::grabWidget(&widget);
    TILEQT_CLEAR_FOCUS(state);
#ifdef TILEQT_QT_VERSION_3
    if (orient == TTK_ORIENT_VERTICAL) {
      // Qt 3.x does not support vertical progress bars. Rotate it :-)
      QWMatrix matrix;
      matrix.rotate(270);
      pixmap = pixmap.xForm(matrix);
    }
#endif /* TILEQT_QT_VERSION_3 */
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

#define TO_CHAR_STAR (char *)

static Ttk_ElementOptionSpec ProgressBarElementOptions[] = {
    { TO_CHAR_STAR "-orient", TK_OPTION_ANY,
      Tk_Offset(ProgressBarElement, orientObj), TO_CHAR_STAR "horizontal"},
    { TO_CHAR_STAR "-length", TK_OPTION_PIXELS,
      Tk_Offset(ProgressBarElement, lengthObj), TO_CHAR_STAR "100" },
    { TO_CHAR_STAR "-mode", TK_OPTION_STRING_TABLE,
      Tk_Offset(ProgressBarElement, modeObj), TO_CHAR_STAR "determinate" },
    { TO_CHAR_STAR "-maximum", TK_OPTION_DOUBLE,
      Tk_Offset(ProgressBarElement, maximumObj), TO_CHAR_STAR "100" },
    { TO_CHAR_STAR "-value", TK_OPTION_DOUBLE,
      Tk_Offset(ProgressBarElement, valueObj), TO_CHAR_STAR "0.0" },
    { NULL }
};

static void ProgressBarElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_ORIENTED_WIDGET(TileQt_QProgressBar_Hor_Widget);
    int length;
    bool determinate = true;
    ProgressBarElement *pbar = (ProgressBarElement *) elementRecord;
    Tk_GetPixelsFromObj(NULL, tkwin, pbar->lengthObj, &length);
    if (strncmp(Tcl_GetString(pbar->modeObj), "determinate", 10) != 0)
        determinate = false;

    Tcl_MutexLock(&tileqtMutex);
    QProgressBar& widget = *wc->TileQt_QProgressBar_Hor_Widget;
#ifdef TILEQT_QT_VERSION_4
    widget.setOrientation(Qt::Horizontal);
#endif /* TILEQT_QT_VERSION_4 */
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
    NULL_PROXY_ORIENTED_WIDGET(TileQt_QProgressBar_Hor_Widget);
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
    QProgressBar& widget = *wc->TileQt_QProgressBar_Hor_Widget;
    double percentage = value/maximum*100.0;
    if (orient == TTK_ORIENT_HORIZONTAL) {
#ifdef TILEQT_QT_VERSION_4
      widget.setOrientation(Qt::Horizontal);
#endif /* TILEQT_QT_VERSION_4 */
      if (!determinate) {
        widget.resize(b.width, height);
#ifdef TILEQT_QT_VERSION_3
        widget.setTotalSteps(0);
#endif /* TILEQT_QT_VERSION_3 */
        percentage = 1.0;
        width = b.width;
        dest_x = b.x;
      } else {
        widget.resize(width, height);
#ifdef TILEQT_QT_VERSION_3
        widget.setTotalSteps(100);
#endif /* TILEQT_QT_VERSION_3 */
      }
    } else {
#ifdef TILEQT_QT_VERSION_4
      widget.setOrientation(Qt::Vertical);
#endif /* TILEQT_QT_VERSION_4 */
      if (!determinate) {
#ifdef TILEQT_QT_VERSION_3
        widget.resize(b.height, width);
        widget.setTotalSteps(0);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
        widget.resize(b.width, height);
#endif /* TILEQT_QT_VERSION_4 */
        percentage = 1.0;
        height = b.height;
        dest_y = b.y;
      } else {
#ifdef TILEQT_QT_VERSION_3
        widget.resize(height, width);
        widget.setTotalSteps(100);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
        widget.resize(width, height);
#endif /* TILEQT_QT_VERSION_4 */
      }
    }
#ifdef TILEQT_QT_VERSION_3
    widget.setProgress((int)(percentage));
    widget.setFrameStyle(QFrame::NoFrame);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    widget.setValue((int)(percentage));
#endif /* TILEQT_QT_VERSION_4 */
    if (state & TTK_STATE_DISABLED) {
      widget.setEnabled(false);
    } else {
      widget.setEnabled(true);
    }
    if (determinate) {
#ifdef TILEQT_QT_VERSION_3
      widget.setCenterIndicator(true);
      widget.setPercentageVisible(true);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
      widget.setTextVisible(true);
#endif /* TILEQT_QT_VERSION_4 */
    } else {
#ifdef TILEQT_QT_VERSION_3
      widget.setCenterIndicator(false);
      widget.setPercentageVisible(false);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
      widget.setTextVisible(false);
#endif /* TILEQT_QT_VERSION_4 */
    }
    QPixmap pixmap = QPixmap::grabWidget(&widget);
#ifdef TILEQT_QT_VERSION_3
    if (orient == TTK_ORIENT_VERTICAL) {
      // Qt 3.x does not support vertical progress bars. Rotate it :-)
      QWMatrix matrix;
      matrix.rotate(270);
      pixmap = pixmap.xForm(matrix);
    }
#endif /* TILEQT_QT_VERSION_3 */
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

int TileQt_Init_Progress(Tcl_Interp *interp,
                       TileQt_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Horizontal.Progressbar.trough",
            &ProgressTroughElementSpec, (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "Vertical.Progressbar.trough",
            &ProgressTroughElementSpec, (void *) wc[1]);

    Ttk_RegisterElement(interp, themePtr, "Horizontal.Progressbar.pbar",
            &ProgressBarElementSpec, (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "Vertical.Progressbar.pbar",
            &ProgressBarElementSpec, (void *) wc[1]);
    
    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr,
            "Horizontal.TProgressbar", HorizontalProgressBarLayout);
    Ttk_RegisterLayout(themePtr,
            "Vertical.TProgressbar", VerticalProgressBarLayout);

    return TCL_OK;
}; /* TileQt_Init_Progress */
