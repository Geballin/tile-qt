/*
 *  tileQt_Combobox.cpp
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
static TTK_StateTable combotext_statemap[] =
{
    {QStyle::Style_Default,                         TTK_STATE_DISABLED, 0 },
    {QStyle::Style_Enabled|QStyle::Style_HasFocus,  TTK_STATE_FOCUS, 0 },
    {QStyle::Style_Enabled|QStyle::Style_MouseOver, TTK_STATE_PRESSED, 0 },
    {QStyle::Style_Enabled|QStyle::Style_MouseOver, TTK_STATE_ACTIVE, 0 },
    {QStyle::Style_Enabled,                         0, 0 }
};

typedef struct {
} ComboboxFieldElement;


static TTK_ElementOptionSpec ComboboxFieldElementOptions[] = {
    {NULL}
};

static void ComboboxFieldElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, TTK_Padding *paddingPtr)
{
    //QComboBox    widget(TileQt_QWidget_Widget);
    //*widthPtr   = widget.width();
    //*heightPtr  = widget.height();
    *paddingPtr = TTK_MakePadding(ComboboxHorizontalPadding, 0, 0, 0);
}

static void ComboboxFieldElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, TTK_Box b, unsigned state)
{
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    QComboBox    widget(false, 0);
    widget.setBackgroundOrigin(QWidget::ParentOrigin);
    widget.setGeometry(b.x, b.y, b.width, b.height);
    QStyle::SFlags sflags = TTK_StateTableLookup(combotext_statemap, state);
    QStyle::SCFlags scflags = QStyle::SC_ComboBoxFrame|QStyle::SC_ComboBoxArrow|
                              QStyle::SC_ComboBoxEditField;
    QStyle::SCFlags activeflags = QStyle::SC_ComboBoxFrame;
    
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
    qApp->style().drawComplexControl(QStyle::CC_ComboBox, &painter, &widget,
          QRect(0, 0, b.width, b.height), qApp->palette().active(), sflags,
          scflags, activeflags);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
}

static TTK_ElementSpec ComboboxFieldElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ComboboxFieldElement),
    ComboboxFieldElementOptions,
    ComboboxFieldElementGeometry,
    ComboboxFieldElementDraw
};

/*
 * Map between Tk/Tile & Qt/KDE state flags.
 */
static TTK_StateTable combobox_statemap[] =
{
    {QStyle::Style_Default,                         TTK_STATE_DISABLED, 0 },
    {QStyle::Style_Enabled|QStyle::Style_MouseOver, TTK_STATE_PRESSED, 0 },
    {QStyle::Style_Enabled|QStyle::Style_MouseOver, TTK_STATE_ACTIVE, 0 },
    {QStyle::Style_Enabled,                         0, 0 }
};

typedef struct {
} ComboboxArrowElement;


static TTK_ElementOptionSpec ComboboxArrowElementOptions[] = {
    {NULL}
};

static void ComboboxArrowElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, TTK_Padding *paddingPtr)
{
    QComboBox    widget(TileQt_QWidget_Widget);
    QRect rc = qApp->style().querySubControlMetrics(QStyle::CC_ComboBox,
                           &widget, QStyle::SC_ComboBoxArrow);
    *widthPtr = rc.width();
    *heightPtr = rc.height();
    *paddingPtr = TTK_UniformPadding(1);
}

static void ComboboxArrowElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, TTK_Box b, unsigned state)
{
    QPixmap      pixmap(b.x+b.width, b.y+b.height);
    QPainter     painter(&pixmap);
    QComboBox    widget(TileQt_QWidget_Widget, 0);
    widget.resize(b.x+b.width, b.y+b.height);
    QStyle::SFlags sflags = TTK_StateTableLookup(combobox_statemap, state);
    QStyle::SCFlags scflags = QStyle::SC_ComboBoxFrame|QStyle::SC_ComboBoxArrow;
    QStyle::SCFlags activeflags = QStyle::SC_None;
    
    painter.fillRect(0, 0, b.width, b.height,
                     qApp->palette().active().brush(QColorGroup::Background));
    // printf("x=%d, y=%d, w=%d, h=%d\n", b.x, b.y, b.width, b.height);
    qApp->style().drawComplexControl(QStyle::CC_ComboBox, &painter, &widget,
          QRect(0, 0, b.x+b.width, b.y+b.height),
          qApp->palette().active(), sflags, scflags, activeflags);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    b.x, b.y, b.width, b.height, b.x, b.y);
}

static TTK_ElementSpec ComboboxArrowElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ComboboxArrowElement),
    ComboboxArrowElementOptions,
    ComboboxArrowElementGeometry,
    ComboboxArrowElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

int TileQt_Init_Combobox(Tcl_Interp *interp, TTK_Theme themePtr)
{
    /*
     * Register elements:
     */
    TTK_RegisterElementSpec(themePtr, "Combobox.field",
            &ComboboxFieldElementSpec, NULL);
    TTK_RegisterElementSpec(themePtr, "Combobox.downarrow",
            &ComboboxArrowElementSpec, NULL);
    
    /*
     * Register layouts:
     */

    return TCL_OK;
}; /* TileQt_Init_Combobox */
