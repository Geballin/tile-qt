/*
 *  tileQt_Scale.cpp
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
static Ttk_StateTable scale_statemap[] =
{
    {QStyle::Style_Default,                         TTK_STATE_DISABLED, 0},
    {QStyle::Style_Enabled|QStyle::Style_Down, 	    TTK_STATE_PRESSED, 0},
    {QStyle::Style_Enabled|QStyle::Style_HasFocus,  TTK_STATE_FOCUS, 0},
    {QStyle::Style_Enabled|QStyle::Style_MouseOver, TK_STATE_ACTIVE, 0},
    {QStyle::Style_Enabled,                         0, 0}
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
    //*heightPtr  = TileQt_QSlider_Widget->sizeHint().height();
    //*widthPtr   = TileQt_QSlider_Widget->sizeHint().width();
    *widthPtr = 60;
    *paddingPtr = Ttk_UniformPadding(4);
}

static void ScaleTroughElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    int orient = (int) clientData;
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    TileQt_QSlider_Widget->setBackgroundOrigin(QWidget::ParentOrigin);
    //TileQt_QSlider_Widget->setGeometry(b.x, b.y, b.width, b.height);
    TileQt_QSlider_Widget->resize(b.width, b.height);
    TileQt_QSlider_Widget->setMinValue(0);
    TileQt_QSlider_Widget->setMaxValue(100);
    TileQt_QSlider_Widget->setValue(0);
    //widget.setGeometry(b.x, b.y, b.width, b.height);

    QStyle::SFlags sflags = Ttk_StateTableLookup(scale_statemap, state);
    if (orient == TTK_ORIENT_HORIZONTAL) {
      TileQt_QSlider_Widget->setOrientation(Qt::Horizontal);
      sflags |= QStyle::Style_Horizontal;
    } else {
      TileQt_QSlider_Widget->setOrientation(Qt::Vertical);
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

    QStyle::SCFlags scflags = QStyle::SC_SliderGroove|
                              QStyle::SC_SliderTickmarks;
    QStyle::SCFlags activeflags = QStyle::SC_None;
    // printf("x=%d, y=%d, w=%d, h=%d\n", b.x, b.y, b.width, b.height);
    qApp->style().drawComplexControl(QStyle::CC_Slider, &painter,
          TileQt_QSlider_Widget,
          QRect(0, 0, b.width, b.height), qApp->palette().active(), sflags,
          scflags, activeflags);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.x);
}

static Ttk_ElementSpec ScaleTroughElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ScaleTroughElement),
    ScaleTroughElementOptions,
    ScaleTroughElementGeometry,
    ScaleTroughElementDraw
};

typedef struct {
} ScaleSliderElement;

static Ttk_ElementOptionSpec ScaleSliderElementOptions[] = {
    {NULL}
};

static void ScaleSliderElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    *widthPtr = *heightPtr =
        qApp->style().pixelMetric(QStyle::PM_SliderControlThickness,
                                  TileQt_QSlider_Widget);
    *paddingPtr = Ttk_UniformPadding(0);
}

static void ScaleSliderElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    return;
    int orient = (int) clientData;
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    TileQt_QSlider_Widget->setBackgroundOrigin(QWidget::ParentOrigin);
    //TileQt_QSlider_Widget->setGeometry(b.x, b.y, b.width, b.height);
    TileQt_QSlider_Widget->resize(b.width, b.height);
    TileQt_QSlider_Widget->setMinValue(0);
    TileQt_QSlider_Widget->setMaxValue(100);
    TileQt_QSlider_Widget->setValue(0);
    //widget.setGeometry(b.x, b.y, b.width, b.height);

    QStyle::SFlags sflags = Ttk_StateTableLookup(scale_statemap, state);
    if (orient == TTK_ORIENT_HORIZONTAL) {
      TileQt_QSlider_Widget->setOrientation(Qt::Horizontal);
      sflags |= QStyle::Style_Horizontal;
    } else {
      TileQt_QSlider_Widget->setOrientation(Qt::Vertical);
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

    QStyle::SCFlags scflags = QStyle::SC_SliderGroove|QStyle::SC_SliderHandle|
                              QStyle::SC_SliderTickmarks;
    QStyle::SCFlags activeflags = QStyle::SC_SliderHandle;
    // printf("x=%d, y=%d, w=%d, h=%d\n", b.x, b.y, b.width, b.height);
    qApp->style().drawComplexControl(QStyle::CC_Slider, &painter,
          TileQt_QSlider_Widget,
          QRect(0, 0, b.width, b.height), qApp->palette().active(), sflags,
          scflags, activeflags);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.x);
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

int TileQt_Init_Scale(Tcl_Interp *interp, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElementSpec(themePtr, "Horizontal.Scale.trough",
            &ScaleTroughElementSpec, (void *) TTK_ORIENT_HORIZONTAL);
    Ttk_RegisterElementSpec(themePtr, "Vertical.Scale.trough",
            &ScaleTroughElementSpec, (void *) TTK_ORIENT_VERTICAL);
    Ttk_RegisterElementSpec(themePtr, "Horizontal.Scale.slider",
            &ScaleSliderElementSpec, (void *) TTK_ORIENT_HORIZONTAL);
    Ttk_RegisterElementSpec(themePtr, "Vertical.Scale.slider",
            &ScaleSliderElementSpec, (void *) TTK_ORIENT_VERTICAL);
    
    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr,
	    "Horizontal.TScale", HorizontalScaleLayout);
    Ttk_RegisterLayout(themePtr,
	    "Vertical.TScale", VerticalScaleLayout);

    return TCL_OK;
}; /* TileQt_Init_Scale */
