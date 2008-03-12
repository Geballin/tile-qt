/*
 *  tileQt_Scale.cpp
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
static Ttk_StateTable scale_statemap[] =
{
#ifdef TILEQT_QT_VERSION_3
    {QStyle::Style_Default,                         TTK_STATE_DISABLED, 0},
    {QStyle::Style_Enabled|QStyle::Style_Down,      TTK_STATE_PRESSED, 0},
    {QStyle::Style_Enabled|QStyle::Style_HasFocus,  TTK_STATE_FOCUS, 0},
    {QStyle::Style_Enabled|QStyle::Style_MouseOver, TK_STATE_ACTIVE, 0},
    {QStyle::Style_Enabled,                         0, 0}
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    {QStyle::State_None,                            TTK_STATE_DISABLED, 0},
    {QStyle::State_Enabled|QStyle::State_Sunken,    TTK_STATE_PRESSED, 0},
    {QStyle::State_Enabled|QStyle::State_HasFocus,  TTK_STATE_FOCUS, 0},
    {QStyle::State_Enabled|QStyle::State_MouseOver, TK_STATE_ACTIVE, 0},
    {QStyle::State_Enabled,                         0, 0}
#endif /* TILEQT_QT_VERSION_4 */
};

typedef struct {
} ScaleTroughElement;

static Ttk_ElementOptionSpec ScaleTroughElementOptions[] = {
    {NULL}
};

static void ScaleTroughElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_ORIENTED_WIDGET(TileQt_QSlider_Hor_Widget);
    QSlider* widget = NULL;
    if (orient == TTK_ORIENT_HORIZONTAL) {
      widget = wc->TileQt_QSlider_Hor_Widget;
    } else {
      NULL_PROXY_WIDGET(TileQt_QSlider_Ver_Widget);
      widget = wc->TileQt_QSlider_Ver_Widget;
    }
    Tcl_MutexLock(&tileqtMutex);
    widget->setRange(0, 100);
    widget->setValue(0);
    *widthPtr   = widget->sizeHint().width();
    *heightPtr  = widget->sizeHint().height();
    Tcl_MutexUnlock(&tileqtMutex);
    *paddingPtr = Ttk_UniformPadding(0);
}

static void ScaleTroughElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_ORIENTED_WIDGET(TileQt_QSlider_Hor_Widget);
    QSlider* widget = NULL;
    int width, height;
    QRect rc;
#ifdef TILEQT_QT_VERSION_4
    QStyleOptionSlider option;
#endif /* TILEQT_QT_VERSION_4 */
    if (orient == TTK_ORIENT_HORIZONTAL) {
      Tcl_MutexLock(&tileqtMutex);
      widget = wc->TileQt_QSlider_Hor_Widget;
      widget->resize(b.width, b.height);
#ifdef TILEQT_QT_VERSION_3
      rc = widget->sliderRect();
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
      option.initFrom(widget);
      rc = wc->TileQt_Style->subControlRect(QStyle::CC_Slider,
           &option, QStyle::SC_SliderHandle, widget);
#endif /* TILEQT_QT_VERSION_4 */
      width = b.width + rc.width(); height = b.height;
    } else {
      NULL_PROXY_WIDGET(TileQt_QSlider_Ver_Widget);
      Tcl_MutexLock(&tileqtMutex);
      widget = wc->TileQt_QSlider_Ver_Widget;
      widget->resize(b.width, b.height);
#ifdef TILEQT_QT_VERSION_3
      rc = widget->sliderRect();
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
      option.initFrom(widget);
      rc = wc->TileQt_Style->subControlRect(QStyle::CC_Slider,
           &option, QStyle::SC_SliderHandle, widget);
#endif /* TILEQT_QT_VERSION_4 */
      width = b.width; height = b.height + rc.height();
    }
    widget->setEnabled(state != TTK_STATE_DISABLED);
    widget->resize(width, height);
    widget->setRange(0, 100);
    widget->setValue(1);
    //widget->setTickmarks(QSlider::Above);
#ifdef TILEQT_QT_VERSION_3
    widget->setBackgroundOrigin(QWidget::ParentOrigin);
    widget->polish();
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    widget->ensurePolished();
#endif /* TILEQT_QT_VERSION_4 */
    // We cannot use qApp->style().drawComplexControl(QStyle::CC_Slider,...),
    // as (due to Qt bug ?), it doesn't work...
    TILEQT_SET_FOCUS(state);
    QPixmap pixmap = QPixmap::grabWidget(widget);
    TILEQT_CLEAR_FOCUS(state);

    // Try to redraw the whole window, to avoid drawing problems...
    // int bg_width = Tk_Width(tkwin), bg_height = Tk_Height(tkwin);
    // QPixmap      bg_pixmap(bg_width, bg_height);
    // QPainter     bg_painter(&bg_pixmap);
    // if (TileQt_QPixmap_BackgroundTile &&
    //     !(TileQt_QPixmap_BackgroundTile->isNull())) {
    //     bg_painter.fillRect(0, 0, bg_width, bg_height,
    //                         QBrush(QColor(255,255,255),
    //                         *TileQt_QPixmap_BackgroundTile));
    // } else {
    //     bg_painter.fillRect(0, 0, bg_width, bg_height,
    //                         qApp->palette().active().background());
    // }
    // TileQt_CopyQtPixmapOnToDrawable(bg_pixmap, d, tkwin,
    //                                 0, 0, bg_width, bg_height, 0, 0);
#ifdef TILEQT_QT_VERSION_3
    rc = widget->sliderRect();
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    option.initFrom(widget);
    rc = wc->TileQt_Style->subControlRect(QStyle::CC_Slider,
         &option, QStyle::SC_SliderHandle, widget);
#endif /* TILEQT_QT_VERSION_4 */
    // Copy the drawn widget, but skip the rectangle that has the handle.
    if (orient == TTK_ORIENT_HORIZONTAL) {
      TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                   0, 0, rc.x(), b.height, b.x, b.y);
      TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                   rc.x()+rc.width(), 0, width-(rc.x()+rc.width()),
                   b.height, rc.x(), b.y);
    } else {
      TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                   0, 0, b.width, rc.y(), b.x, b.y);
      TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                   0, rc.y()+rc.height(), b.width, height-(rc.y()+rc.height()),
                   b.x, rc.y());
    }
    Tcl_MutexUnlock(&tileqtMutex);
}

static Ttk_ElementSpec ScaleTroughElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ScaleTroughElement),
    ScaleTroughElementOptions,
    ScaleTroughElementGeometry,
    ScaleTroughElementDraw
};

typedef struct {
    Tcl_Obj *lengthObj;  /* the length of the slider (if a flat style) */
    Tcl_Obj *widthObj;   /* the width of the slider (height if horizontal) */
    Tcl_Obj *orientObj;  /* orientation of overall slider */
} ScaleSliderElement;

static Ttk_ElementOptionSpec ScaleSliderElementOptions[] = {
    {NULL}
};

static void ScaleSliderElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_ORIENTED_WIDGET(TileQt_QSlider_Hor_Widget);
    QSlider* widget = NULL;
    QRect rc;
    if (orient == TTK_ORIENT_HORIZONTAL) {
      widget = wc->TileQt_QSlider_Hor_Widget;
    } else {
      NULL_PROXY_WIDGET(TileQt_QSlider_Ver_Widget);
      widget = wc->TileQt_QSlider_Ver_Widget;
    }
    Tcl_MutexLock(&tileqtMutex);
    widget->setRange(0, 100);
    widget->setValue(50);
    widget->resize(widget->sizeHint().width(), widget->sizeHint().height());
#ifdef TILEQT_QT_VERSION_3
    rc = widget->sliderRect();
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    QStyleOptionSlider option;
    option.initFrom(widget);
    rc = wc->TileQt_Style->subControlRect(QStyle::CC_Slider,
         &option, QStyle::SC_SliderHandle, widget);
#endif /* TILEQT_QT_VERSION_4 */
    *widthPtr   = rc.width();
    *heightPtr  = rc.height();
    Tcl_MutexUnlock(&tileqtMutex);
    *paddingPtr = Ttk_UniformPadding(0);
}

static void ScaleSliderElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_ORIENTED_WIDGET(TileQt_QSlider_Hor_Widget);
    QSlider* widget = NULL;
    if (orient == TTK_ORIENT_HORIZONTAL) {
      widget = wc->TileQt_QSlider_Hor_Widget;
    } else {
      NULL_PROXY_WIDGET(TileQt_QSlider_Ver_Widget);
      widget = wc->TileQt_QSlider_Ver_Widget;
    }
    Tcl_MutexLock(&tileqtMutex);
#ifdef TILEQT_QT_VERSION_3
    widget->setBackgroundOrigin(QWidget::ParentOrigin);
#endif /* TILEQT_QT_VERSION_3 */
    widget->setEnabled(state != TTK_STATE_DISABLED);
    widget->setRange(0, 100);
    widget->setValue(50);
    // We cannot use qApp->style().drawComplexControl(QStyle::CC_Slider,...),
    // as (due to Qt bug ?), it doesn't work...
    QPixmap pixmap = QPixmap::grabWidget(widget);

    //QStyle::SFlags sflags = TileQt_StateTableLookup(scale_statemap, state);
    //QStyle::SCFlags activeflags = QStyle::SC_SliderHandle;
    //qApp->style().drawComplexControl(QStyle::CC_Slider, &painter, widget,
    //      QRect(0, 0, widget->width(), widget->height()),
    //      qApp->palette().active(), sflags, scflags, activeflags);
#ifdef TILEQT_QT_VERSION_3
    QRect rc = widget->sliderRect();
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    QStyleOptionSlider option;
    option.initFrom(widget);
    QRect rc = wc->TileQt_Style->subControlRect(QStyle::CC_Slider,
         &option, QStyle::SC_SliderHandle, widget);
#endif /* TILEQT_QT_VERSION_4 */
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                 rc.x(), rc.y(), b.width, b.height, b.x, b.y);
    Tcl_MutexUnlock(&tileqtMutex);
}

static Ttk_ElementSpec ScaleSliderElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ScaleSliderElement),
    ScaleSliderElementOptions,
    ScaleSliderElementGeometry,
    ScaleSliderElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

TTK_BEGIN_LAYOUT(VerticalScaleLayout)
        TTK_GROUP("Vertical.Scale.trough", TTK_FILL_BOTH,
            TTK_NODE("Vertical.Scale.slider", TTK_PACK_TOP) )
TTK_END_LAYOUT

TTK_BEGIN_LAYOUT(HorizontalScaleLayout)
        TTK_GROUP("Horizontal.Scale.trough", TTK_FILL_BOTH,
            TTK_NODE("Horizontal.Scale.slider", TTK_PACK_LEFT) )
TTK_END_LAYOUT

int TileQt_Init_Scale(Tcl_Interp *interp,
                       TileQt_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Horizontal.Scale.trough",
            &ScaleTroughElementSpec, (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "Vertical.Scale.trough",
            &ScaleTroughElementSpec, (void *) wc[1]);
    Ttk_RegisterElement(interp, themePtr, "Horizontal.Scale.slider",
            &ScaleSliderElementSpec, (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "Vertical.Scale.slider",
            &ScaleSliderElementSpec, (void *) wc[1]);
    
    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr,
            "Horizontal.TScale", HorizontalScaleLayout);
    Ttk_RegisterLayout(themePtr,
            "Vertical.TScale", VerticalScaleLayout);

    return TCL_OK;
}; /* TileQt_Init_Scale */
