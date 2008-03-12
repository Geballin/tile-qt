/*
 *  tileQt_Scrollbar.cpp
 * ------------------------
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
static Ttk_StateTable scrollbar_statemap[] =
{
#ifdef TILEQT_QT_VERSION_3
    {QStyle::Style_Default,                         TTK_STATE_DISABLED, 0 },
    {QStyle::Style_Enabled|QStyle::Style_Down,      TTK_STATE_PRESSED, 0 },
    {QStyle::Style_Enabled|QStyle::Style_MouseOver, TTK_STATE_ACTIVE, 0 },
    {QStyle::Style_Enabled,                         0, 0 }
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    {QStyle::State_None,                            TTK_STATE_DISABLED, 0 },
    {QStyle::State_Enabled|QStyle::State_Sunken,    TTK_STATE_PRESSED, 0 },
    {QStyle::State_Enabled|QStyle::State_MouseOver, TTK_STATE_ACTIVE, 0 },
    {QStyle::State_Enabled,                         0, 0 }
#endif /* TILEQT_QT_VERSION_4 */
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
    if (qApp == NULL) NULL_Q_APP;
#ifdef TILEQT_QT_VERSION_3
    //NULL_PROXY_ORIENTED_WIDGET(TileQt_QScrollBar_Widget);
    //if (orient == TTK_ORIENT_HORIZONTAL) {
    //  *heightPtr = wc->TileQt_Style->pixelMetric(QStyle::PM_ScrollBarExtent,
    //                                         TileQt_QScrollBar_Widget);
    //  *widthPtr  = wc->TileQt_Style->pixelMetric(QStyle::PM_ScrollBarSliderMin,
    //                                         TileQt_QScrollBar_Widget);
    //} else {
    //  *widthPtr  = wc->TileQt_Style->pixelMetric(QStyle::PM_ScrollBarExtent,
    //                                         TileQt_QScrollBar_Widget);
    //  *heightPtr = wc->TileQt_Style->pixelMetric(QStyle::PM_ScrollBarSliderMin,
    //                                         TileQt_QScrollBar_Widget);
    //}
#endif /* TILEQT_QT_VERSION_3 */
    *paddingPtr = Ttk_UniformPadding(0);
}

static void ScrollbarTroughElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_ORIENTED_WIDGET(TileQt_QScrollBar_Widget);
    Tcl_MutexLock(&tileqtMutex);
    /* We draw the whole scrollbar at once, but without the slider! */
    int width, height;
    //TileQt_QScrollBar_Widget->resize(b.width, b.height);
#ifdef TILEQT_QT_VERSION_3
    QStyle::SFlags sflags = TileQt_StateTableLookup(scrollbar_statemap, state);
#endif /* TILEQT_QT_VERSION_3 */
    if (orient == TTK_ORIENT_HORIZONTAL) {
      width = 2*b.width; height = b.height;
      wc->TileQt_QScrollBar_Widget->setOrientation(Qt::Horizontal);
#ifdef TILEQT_QT_VERSION_3
      sflags |= QStyle::Style_Horizontal;
#endif /* TILEQT_QT_VERSION_3 */
    } else {
      width = b.width; height = 2*b.height;
      wc->TileQt_QScrollBar_Widget->setOrientation(Qt::Vertical);
    }
#ifdef TILEQT_SCROLLBAR_SIZE_DEBUG
    printf("ScrollbarTroughElementDraw: width=%d, height=%d, orient=%d\n",
            width, height, orient); fflush(0);
#endif /* TILEQT_SCROLLBAR_SIZE_DEBUG */
    wc->TileQt_QScrollBar_Widget->resize(width, height);
    wc->TileQt_QScrollBar_Widget->setValue(0);
    QPixmap      pixmap(width, height);
    QPainter     painter(&pixmap);
    TILEQT_PAINT_BACKGROUND(width, height);

#ifdef TILEQT_QT_VERSION_3
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
    
    wc->TileQt_Style->drawComplexControl(QStyle::CC_ScrollBar, &painter,
          wc->TileQt_QScrollBar_Widget,
          QRect(0, 0, width, height), qApp->palette().active(), sflags,
          scflags, activeflags);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    QStyleOptionSlider option;
    option.initFrom(wc->TileQt_QScrollBar_Widget); option.state |= 
      (QStyle::StateFlag) TileQt_StateTableLookup(scrollbar_statemap, state);
    wc->TileQt_Style->drawComplexControl(QStyle::CC_ScrollBar, &option,
                                  &painter, wc->TileQt_QScrollBar_Widget);
#endif /* TILEQT_QT_VERSION_4 */
    // printf("x=%d, y=%d, w=%d, h=%d\n", b.x, b.y, b.width, b.height);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    width-b.width, height-b.height,
                                    b.width, b.height, b.x, b.y);
    Tcl_MutexUnlock(&tileqtMutex);
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
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_ORIENTED_WIDGET(TileQt_QScrollBar_Widget);
    Tcl_MutexLock(&tileqtMutex);
    if (orient == TTK_ORIENT_HORIZONTAL) {
      *heightPtr = wc->TileQt_Style->pixelMetric(QStyle::PM_ScrollBarExtent,
#ifdef TILEQT_QT_VERSION_4
                                             0,
#endif /* TILEQT_QT_VERSION_4 */
                                             wc->TileQt_QScrollBar_Widget);
      *widthPtr  = wc->TileQt_Style->pixelMetric(QStyle::PM_ScrollBarSliderMin,
#ifdef TILEQT_QT_VERSION_4
                                             0,
#endif /* TILEQT_QT_VERSION_4 */
                                             wc->TileQt_QScrollBar_Widget);
      if (*heightPtr > 30)  *heightPtr =  30;
      if (*widthPtr  > 100) *widthPtr  = 100;
    } else {
      *widthPtr  = wc->TileQt_Style->pixelMetric(QStyle::PM_ScrollBarExtent,
#ifdef TILEQT_QT_VERSION_4
                                             0,
#endif /* TILEQT_QT_VERSION_4 */
                                             wc->TileQt_QScrollBar_Widget);
      *heightPtr = wc->TileQt_Style->pixelMetric(QStyle::PM_ScrollBarSliderMin,
#ifdef TILEQT_QT_VERSION_4
                                             0,
#endif /* TILEQT_QT_VERSION_4 */
                                             wc->TileQt_QScrollBar_Widget);
      if (*heightPtr > 100) *heightPtr = 100;
      if (*widthPtr  > 30)  *widthPtr  =  30;                                       }
    Tcl_MutexUnlock(&tileqtMutex);
    *paddingPtr = Ttk_UniformPadding(0);
#ifdef TILEQT_SCROLLBAR_SIZE_DEBUG
    printf("ScrollbarThumbElementGeometry: width=%d, height=%d, orient=%d\n",
            *widthPtr, *heightPtr, orient); fflush(0);
#endif /* TILEQT_SCROLLBAR_SIZE_DEBUG */
}

static void ScrollbarThumbElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) NULL_Q_APP;
    if (state & TTK_STATE_DISABLED) return;
    NULL_PROXY_ORIENTED_WIDGET(TileQt_QScrollBar_Widget);
    Tcl_MutexLock(&tileqtMutex);
    //QPixmap      pixmap(b.width, b.height);
    QPixmap      pixmap = QPixmap::grabWindow(Tk_WindowId(tkwin));
    QPainter     painter(&pixmap);
#ifdef TILEQT_QT_VERSION_3
    QStyle::SFlags sflags = TileQt_StateTableLookup(scrollbar_statemap, state);
    if (orient == TTK_ORIENT_HORIZONTAL) sflags |= QStyle::Style_Horizontal;
    wc->TileQt_Style->drawPrimitive(QStyle::PE_ScrollBarSlider, &painter,
          QRect(0, 0, b.width, b.height), qApp->palette().active(), sflags);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    wc->TileQt_QScrollBar_Widget->resize(b.width, b.height);
    wc->TileQt_QScrollBar_Widget->setValue(0);
    if (orient == TTK_ORIENT_HORIZONTAL) {
      wc->TileQt_QScrollBar_Widget->setOrientation(Qt::Horizontal);
    } else {
      wc->TileQt_QScrollBar_Widget->setOrientation(Qt::Vertical);
    }
    QStyleOptionSlider option;
    option.initFrom(wc->TileQt_QScrollBar_Widget); option.state |= 
      (QStyle::StateFlag) TileQt_StateTableLookup(scrollbar_statemap, state);
    option.subControls = QStyle::SC_ScrollBarGroove;
    wc->TileQt_Style->drawComplexControl(QStyle::CC_ScrollBar, &option,
                                  &painter, wc->TileQt_QScrollBar_Widget);
#endif /* TILEQT_QT_VERSION_4 */
    // printf("x=%d, y=%d, w=%d, h=%d\n", b.x, b.y, b.width, b.height);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
    Tcl_MutexUnlock(&tileqtMutex);
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
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_ORIENTED_WIDGET(TileQt_QScrollBar_Widget);
    Tcl_MutexLock(&tileqtMutex);
    if (orient == TTK_ORIENT_HORIZONTAL) {
      wc->TileQt_QScrollBar_Widget->setOrientation(Qt::Horizontal);
    } else {
      wc->TileQt_QScrollBar_Widget->setOrientation(Qt::Vertical);
    }
#ifdef TILEQT_QT_VERSION_3
    QRect rc = wc->TileQt_Style->querySubControlMetrics(QStyle::CC_ScrollBar,
                   wc->TileQt_QScrollBar_Widget, QStyle::SC_ScrollBarSubLine);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    QStyleOptionSlider option;
    option.initFrom(wc->TileQt_QScrollBar_Widget);
    QRect rc = wc->TileQt_Style->subControlRect(QStyle::CC_ScrollBar,
          &option, QStyle::SC_ScrollBarSubLine, wc->TileQt_QScrollBar_Widget);
#endif /* TILEQT_QT_VERSION_4 */
    if (rc.isValid()) {
      *widthPtr = rc.width();
      *heightPtr = rc.height();
      /* Qt Style Fixes: */
      if (TileQt_ThemeIs(wc, "keramik") || TileQt_ThemeIs(wc, "thinkeramik") ||
          TileQt_ThemeIs(wc, "shinekeramik")) {
        // Keramic & ThinKeramic are buggy: Their subcontrol metrics are for 2
        // buttons, not one. Find the smallest dimension, and return a
        // rectangle.
        if (*widthPtr  > 17) *widthPtr  = 17;
        if (*heightPtr > 17) *heightPtr = 17;
      } else if (TileQt_ThemeIs(wc, "sgi") ||
                 TileQt_ThemeIs(wc, "compact") ||
                 TileQt_ThemeIs(wc, "platinum") ||
                 TileQt_ThemeIs(wc, "motifplus") ||
                 TileQt_ThemeIs(wc, "cde") ||
                 TileQt_ThemeIs(wc, "motif") ||
                 TileQt_ThemeIs(wc, "windows")) {
        // These styles are buggy?: Some times one dimension is returned as 10,
        // others as 21.
        if (*widthPtr < *heightPtr) *widthPtr  = *heightPtr;
        if (*heightPtr < *widthPtr) *heightPtr = *widthPtr;
      }
    }
    Tcl_MutexUnlock(&tileqtMutex);
    *paddingPtr = Ttk_UniformPadding(0);
#ifdef TILEQT_SCROLLBAR_SIZE_DEBUG
    printf("ScrollbarUpArrowElementGeometry: width=%d, height=%d, orient=%d\n",
            *widthPtr, *heightPtr, orient); fflush(0);
#endif /* TILEQT_SCROLLBAR_SIZE_DEBUG */
}

static void ScrollbarUpArrowElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_ORIENTED_WIDGET(TileQt_QScrollBar_Widget);
    Tcl_MutexLock(&tileqtMutex);
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    TILEQT_PAINT_BACKGROUND(b.width, b.height);
#ifdef TILEQT_QT_VERSION_3
    QStyle::SFlags sflags = TileQt_StateTableLookup(scrollbar_statemap, state);
    if (orient == TTK_ORIENT_HORIZONTAL) sflags |= QStyle::Style_Horizontal;
    wc->TileQt_Style->drawPrimitive(QStyle::PE_ScrollBarSubLine, &painter,
          QRect(0, 0, b.width, b.height), qApp->palette().active(), sflags);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    wc->TileQt_QScrollBar_Widget->resize(b.width, b.height);
    wc->TileQt_QScrollBar_Widget->setValue(0);
    if (orient == TTK_ORIENT_HORIZONTAL) {
      wc->TileQt_QScrollBar_Widget->setOrientation(Qt::Horizontal);
    } else {
      wc->TileQt_QScrollBar_Widget->setOrientation(Qt::Vertical);
    }
    QStyleOptionSlider option;
    option.initFrom(wc->TileQt_QScrollBar_Widget); option.state |= 
      (QStyle::StateFlag) TileQt_StateTableLookup(scrollbar_statemap, state);
    option.subControls = QStyle::SC_ScrollBarSubLine;
    wc->TileQt_Style->drawComplexControl(QStyle::CC_ScrollBar, &option,
                                  &painter, wc->TileQt_QScrollBar_Widget);
#endif /* TILEQT_QT_VERSION_4 */
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
    Tcl_MutexUnlock(&tileqtMutex);
#ifdef TILEQT_SCROLLBAR_SIZE_DEBUG
    printf("ScrollbarUpArrowElementDraw: width=%d, height=%d, orient=%d\n",
            b.width, b.height, orient); fflush(0);
#endif /* TILEQT_SCROLLBAR_SIZE_DEBUG */
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
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_ORIENTED_WIDGET(TileQt_QScrollBar_Widget);
    Tcl_MutexLock(&tileqtMutex);
    if (orient == TTK_ORIENT_HORIZONTAL) {
      wc->TileQt_QScrollBar_Widget->setOrientation(Qt::Horizontal);
    } else {
      wc->TileQt_QScrollBar_Widget->setOrientation(Qt::Vertical);
    }
#ifdef TILEQT_QT_VERSION_3
    QRect rc = wc->TileQt_Style->querySubControlMetrics(QStyle::CC_ScrollBar,
                   wc->TileQt_QScrollBar_Widget, QStyle::SC_ScrollBarAddLine);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    QStyleOptionSlider option;
    option.initFrom(wc->TileQt_QScrollBar_Widget);
    QRect rc = wc->TileQt_Style->subControlRect(QStyle::CC_ScrollBar,
          &option, QStyle::SC_ScrollBarAddLine, wc->TileQt_QScrollBar_Widget);
#endif /* TILEQT_QT_VERSION_4 */
    if (rc.isValid()) {
      *widthPtr = rc.width();
      *heightPtr = rc.height();
      /* Qt Style Fixes: */
      // printf("%s\n", wc->TileQt_Style->name());
      if (TileQt_ThemeIs(wc, "keramik") || TileQt_ThemeIs(wc, "thinkeramik") ||
          TileQt_ThemeIs(wc, "shinekeramik")) {
        // Keramic & ThinKeramic are buggy: Their subcontrol metrics are for 2
        // buttons, not one. Find the smallest dimension, and return a
        // rectangle.
        if (orient == TTK_ORIENT_HORIZONTAL) {
          *heightPtr = 17;
          *widthPtr  = 34;
        } else {
          *heightPtr = 34;
          *widthPtr  = 17;
        }
      } else if (TileQt_ThemeIs(wc, "sgi") ||
                 TileQt_ThemeIs(wc, "compact") ||
                 TileQt_ThemeIs(wc, "platinum") ||
                 TileQt_ThemeIs(wc, "motifplus") ||
                 TileQt_ThemeIs(wc, "cde") ||
                 TileQt_ThemeIs(wc, "motif") ||
                 TileQt_ThemeIs(wc, "windows")) {
        // These styles are buggy?: Some times one dimension is returned as 10,
        // others as 21.
        if (*widthPtr < *heightPtr) *widthPtr  = *heightPtr;
        if (*heightPtr < *widthPtr) *heightPtr = *widthPtr;
      }
    }
    Tcl_MutexUnlock(&tileqtMutex);
    *paddingPtr = Ttk_UniformPadding(0);
#ifdef TILEQT_SCROLLBAR_SIZE_DEBUG
   printf("ScrollbarDownArrowElementGeometry: width=%d, height=%d, orient=%d\n",
            *widthPtr, *heightPtr, orient); fflush(0);
#endif /* TILEQT_SCROLLBAR_SIZE_DEBUG */
}

static void ScrollbarDownArrowElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_ORIENTED_WIDGET(TileQt_QScrollBar_Widget);
    Tcl_MutexLock(&tileqtMutex);
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    TILEQT_PAINT_BACKGROUND(b.width, b.height);
#ifdef TILEQT_QT_VERSION_3
    QStyle::SFlags sflags = TileQt_StateTableLookup(scrollbar_statemap, state);
    if (orient == TTK_ORIENT_HORIZONTAL) sflags |= QStyle::Style_Horizontal;
    wc->TileQt_Style->drawPrimitive(QStyle::PE_ScrollBarAddLine, &painter,
          QRect(0, 0, b.width, b.height), qApp->palette().active(), sflags);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    wc->TileQt_QScrollBar_Widget->resize(b.width, b.height);
    wc->TileQt_QScrollBar_Widget->setValue(0);
    if (orient == TTK_ORIENT_HORIZONTAL) {
      wc->TileQt_QScrollBar_Widget->setOrientation(Qt::Horizontal);
    } else {
      wc->TileQt_QScrollBar_Widget->setOrientation(Qt::Vertical);
    }
    QStyleOptionSlider option;
    option.initFrom(wc->TileQt_QScrollBar_Widget); option.state |= 
      (QStyle::StateFlag) TileQt_StateTableLookup(scrollbar_statemap, state);
    option.subControls = QStyle::SC_ScrollBarAddLine;
    wc->TileQt_Style->drawComplexControl(QStyle::CC_ScrollBar, &option,
                                  &painter, wc->TileQt_QScrollBar_Widget);
#endif /* TILEQT_QT_VERSION_4 */
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
    Tcl_MutexUnlock(&tileqtMutex);
#ifdef TILEQT_SCROLLBAR_SIZE_DEBUG
    printf("ScrollbarDownArrowElementDraw: width=%d, height=%d, orient=%d\n",
            b.width, b.height, orient); fflush(0);
#endif /* TILEQT_SCROLLBAR_SIZE_DEBUG */
}

static Ttk_ElementSpec ScrollbarDownArrowElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ScrollbarDownArrowElement),
    ScrollbarDownArrowElementOptions,
    ScrollbarDownArrowElementGeometry,
    ScrollbarDownArrowElementDraw
};

typedef struct {
} ScrollbarEmptyArrowElement;
static Ttk_ElementOptionSpec ScrollbarEmptyArrowElementOptions[] = {
    {NULL}
};

static void ScrollbarUpSubArrowElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    /* This function draws only if the element state is pressed or active. */
    if (state & TTK_STATE_PRESSED) {
     ScrollbarUpArrowElementDraw(clientData, elementRecord, tkwin, d, b,
                                 state);
    }
}

static void ScrollbarDownSubArrowElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    /* This function draws only if the element state is pressed. */
    if (state & TTK_STATE_PRESSED) {
      if (qApp == NULL) NULL_Q_APP;
      NULL_PROXY_ORIENTED_WIDGET(TileQt_QScrollBar_Widget);
#ifdef TILEQT_QT_VERSION_3
      QStyle::SFlags sflags = TileQt_StateTableLookup(scrollbar_statemap, state);
#endif /* TILEQT_QT_VERSION_3 */
      Tcl_MutexLock(&tileqtMutex);
      if (orient == TTK_ORIENT_HORIZONTAL) {
        QPixmap      pixmap(2*b.width, b.height);
        QPainter     painter(&pixmap);
#ifdef TILEQT_QT_VERSION_3
        sflags |= QStyle::Style_Horizontal;
        wc->TileQt_Style->drawPrimitive(QStyle::PE_ScrollBarAddLine, &painter,
              QRect(0, 0, 2*b.width, b.height),
              qApp->palette().active(), sflags);
#endif /* TILEQT_QT_VERSION_3 */
        TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                        16, 0, b.width-1, b.height, b.x, b.y);
      } else {
        QPixmap      pixmap(b.width, 2*b.height);
        QPainter     painter(&pixmap);
#ifdef TILEQT_QT_VERSION_3
        wc->TileQt_Style->drawPrimitive(QStyle::PE_ScrollBarAddLine, &painter,
              QRect(0, 0, b.width, 2*b.height),
              qApp->palette().active(), sflags);
#endif /* TILEQT_QT_VERSION_3 */
        TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                        0, 16, b.width, b.height-1, b.x, b.y);
      }
      Tcl_MutexUnlock(&tileqtMutex);
    }
}

static Ttk_ElementSpec ScrollbarUpSubArrowElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ScrollbarEmptyArrowElement),
    ScrollbarEmptyArrowElementOptions,
    ScrollbarUpArrowElementGeometry,
    ScrollbarUpSubArrowElementDraw
};

static Ttk_ElementSpec ScrollbarDownSubArrowElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ScrollbarEmptyArrowElement),
    ScrollbarEmptyArrowElementOptions,
    ScrollbarUpArrowElementGeometry,
    ScrollbarDownSubArrowElementDraw
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

int TileQt_Init_Scrollbar(Tcl_Interp *interp,
                       TileQt_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Horizontal.Scrollbar.trough",
      &ScrollbarTroughElementSpec, (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "Vertical.Scrollbar.trough",
      &ScrollbarTroughElementSpec, (void *) wc[1]);
    Ttk_RegisterElement(interp, themePtr, "Horizontal.Scrollbar.leftarrow",
      &ScrollbarUpArrowElementSpec, (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "Vertical.Scrollbar.uparrow",
      &ScrollbarUpArrowElementSpec, (void *) wc[1]);
    Ttk_RegisterElement(interp, themePtr, "Horizontal.Scrollbar.rightarrow",
      &ScrollbarDownArrowElementSpec, (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "Vertical.Scrollbar.downarrow",
      &ScrollbarDownArrowElementSpec, (void *) wc[1]);
    Ttk_RegisterElement(interp, themePtr, "Horizontal.Scrollbar.subleftarrow",
      &ScrollbarUpSubArrowElementSpec, (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "Vertical.Scrollbar.subuparrow",
      &ScrollbarUpSubArrowElementSpec, (void *) wc[1]);
    Ttk_RegisterElement(interp, themePtr, "Horizontal.Scrollbar.subrightarrow",
      &ScrollbarDownSubArrowElementSpec, (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "Vertical.Scrollbar.subdownarrow",
      &ScrollbarDownSubArrowElementSpec, (void *) wc[1]);
    Ttk_RegisterElement(interp, themePtr, "Horizontal.Scrollbar.thumb",
      &ScrollbarThumbElementSpec, (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "Vertical.Scrollbar.thumb",
      &ScrollbarThumbElementSpec, (void *) wc[1]);
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
