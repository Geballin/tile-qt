/*
 *  tileQt_Menubutton.cpp
 * -------------------
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
 * Pushbuttons (Tk: "Menubutton")
 */
static TTK_StateTable menubutton_statemap[] =
{
    {QStyle::Style_Default                          , TTK_STATE_DISABLED, 0},
    {QStyle::Style_Enabled | QStyle::Style_Down     , TTK_STATE_PRESSED, 0},
    {QStyle::Style_Enabled | QStyle::Style_MouseOver, TTK_STATE_ACTIVE, 0},
    {QStyle::Style_Enabled | QStyle::Style_Active   , TTK_STATE_ALTERNATE, 0},
    {QStyle::Style_Enabled, 0, 0 }
};

typedef struct {
} MenubuttonDropdownElement;

static TTK_ElementOptionSpec MenubuttonDropdownElementOptions[] = {
    {NULL}
};

static void MenubuttonDropdownElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, TTK_Padding *paddingPtr)
{
    //*widthPtr = qApp->style().pixelMetric(QStyle::PM_MenuButtonIndicator);
    QComboBox    widget(TileQt_QWidget_Widget);
    QRect rc = qApp->style().querySubControlMetrics(QStyle::CC_ComboBox,
                           &widget, QStyle::SC_ComboBoxArrow);
    *widthPtr = rc.width();
    *paddingPtr = TTK_UniformPadding(0);
}

static void MenubuttonDropdownElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, TTK_Box b, unsigned state)
{
    QPixmap      pixmap(b.x+b.width, b.y+b.height);
    QPainter     painter(&pixmap);
    QComboBox    widget(TileQt_QWidget_Widget, 0);
    widget.resize(b.x+b.width, b.y+b.height);
    QStyle::SFlags sflags = TTK_StateTableLookup(menubutton_statemap, state);
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

static TTK_ElementSpec MenubuttonDropdownElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(MenubuttonDropdownElement),
    MenubuttonDropdownElementOptions,
    MenubuttonDropdownElementGeometry,
    MenubuttonDropdownElementDraw
};

typedef struct {
} MenubuttonElement;

static TTK_ElementOptionSpec MenubuttonElementOptions[] = {
    {NULL}
};

static void MenubuttonElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, TTK_Padding *paddingPtr)
{
    QComboBox    widget(TileQt_QWidget_Widget);
    *widthPtr   = widget.width();
    *heightPtr  = widget.height();
    *paddingPtr = TTK_UniformPadding(0);
}

static void MenubuttonElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, TTK_Box b, unsigned state)
{
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    QComboBox    widget(false, 0);
    widget.setBackgroundOrigin(QWidget::ParentOrigin);
    widget.setGeometry(b.x, b.y, b.width, b.height);
    QStyle::SFlags sflags = TTK_StateTableLookup(menubutton_statemap, state);
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

static TTK_ElementSpec MenubuttonElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(MenubuttonElement),
    MenubuttonElementOptions,
    MenubuttonElementGeometry,
    MenubuttonElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

TTK_BEGIN_LAYOUT(MenubuttonLayout)
    TTK_GROUP("Menubutton.button", TTK_FILL_BOTH,
	    TTK_GROUP("Menubutton.padding", TTK_FILL_BOTH,
                TTK_NODE("Menubutton.dropdown", TTK_PACK_RIGHT|TTK_FILL_Y)
		TTK_NODE("Menubutton.label", TTK_FILL_BOTH)))
TTK_END_LAYOUT

int TileQt_Init_Menubutton(Tcl_Interp *interp, TTK_Theme themePtr)
{
    /*
     * Register elements:
     */
    TTK_RegisterElementSpec(themePtr, "Menubutton.dropdown",
            &MenubuttonDropdownElementSpec, NULL);
    TTK_RegisterElementSpec(themePtr, "Menubutton.button",
            &MenubuttonElementSpec, NULL);

    /*
     * Register layouts:
     */
    TTK_RegisterLayout(themePtr, "TMenubutton", MenubuttonLayout);
    return TCL_OK;
}; /* TileQt_Init_Menubutton */
