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
static Ttk_StateTable menubutton_statemap[] =
{
    {QStyle::Style_Default                          , TTK_STATE_DISABLED, 0},
    {QStyle::Style_Enabled | QStyle::Style_Down     , TTK_STATE_PRESSED, 0},
    {QStyle::Style_Enabled | QStyle::Style_MouseOver, TTK_STATE_ACTIVE, 0},
    {QStyle::Style_Enabled | QStyle::Style_Active   , TTK_STATE_ALTERNATE, 0},
    {QStyle::Style_Enabled, 0, 0 }
};

typedef struct {
} MenubuttonDropdownElement;

static Ttk_ElementOptionSpec MenubuttonDropdownElementOptions[] = {
    {NULL}
};

static void MenubuttonDropdownElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (qApp == NULL) return;
    QRect rc = qApp->style().querySubControlMetrics(QStyle::CC_ComboBox,
                          TileQt_QComboBox_RO_Widget, QStyle::SC_ComboBoxArrow);
    *widthPtr = rc.width();
    *paddingPtr = Ttk_UniformPadding(0);
}

static void MenubuttonDropdownElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) return;
    // There is no need to re-paint the button. It has been paint along with the
    // field element (ComboboxFieldElementDraw). This is because Qt's Combobox
    // is a complex widget.
    // QPixmap      pixmap(b.x+b.width, b.y+b.height);
    // QPainter     painter(&pixmap);
    // QComboBox& widget = *TileQt_QComboBox_RO_Widget;
    // widget.resize(b.x+b.width, b.y+b.height);
    // QStyle::SFlags sflags = Ttk_StateTableLookup(menubutton_statemap, state);
    // QStyle::SCFlags scflags = QStyle::SC_ComboBoxFrame|QStyle::SC_ComboBoxArrow;
    // QStyle::SCFlags activeflags = QStyle::SC_None;
    // 
    // painter.fillRect(0, 0, b.width, b.height,
    //                  qApp->palette().active().brush(QColorGroup::Background));
    // // printf("x=%d, y=%d, w=%d, h=%d\n", b.x, b.y, b.width, b.height);
    // qApp->style().drawComplexControl(QStyle::CC_ComboBox, &painter, &widget,
    //       QRect(0, 0, b.x+b.width, b.y+b.height),
    //       qApp->palette().active(), sflags, scflags, activeflags);
    // TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
    //                                 b.x, b.y, b.width, b.height, b.x, b.y);
}

static Ttk_ElementSpec MenubuttonDropdownElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(MenubuttonDropdownElement),
    MenubuttonDropdownElementOptions,
    MenubuttonDropdownElementGeometry,
    MenubuttonDropdownElementDraw
};

typedef struct {
} MenubuttonElement;

static Ttk_ElementOptionSpec MenubuttonElementOptions[] = {
    {NULL}
};

static void MenubuttonElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (qApp == NULL) return;
    // QComboBox    widget(TileQt_QWidget_Widget);
    // *widthPtr   = widget.width();
    // *heightPtr  = widget.height();
    //*paddingPtr = Ttk_UniformPadding(0);
    // In order to get the correct padding, calculate the difference between the
    // frame & edit field rectangulars...
    QRect fr_rc = qApp->style().querySubControlMetrics(QStyle::CC_ComboBox,
                      TileQt_QComboBox_RO_Widget, QStyle::SC_ComboBoxFrame);
    QRect ef_rc = qApp->style().querySubControlMetrics(QStyle::CC_ComboBox,
                      TileQt_QComboBox_RO_Widget, QStyle::SC_ComboBoxEditField);
    *paddingPtr = Ttk_MakePadding(ef_rc.x() - fr_rc.x()           /* left   */,
                                  ef_rc.y() - fr_rc.y()           /* top    */,
                     fr_rc.width()  - ef_rc.width()  - ef_rc.x()  /* right  */,
                     fr_rc.height() - ef_rc.height() - ef_rc.y()  /* bottom */);
}

static void MenubuttonElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) return;
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    QComboBox&   widget = *TileQt_QComboBox_RO_Widget;
    widget.setBackgroundOrigin(QWidget::ParentOrigin);
    widget.resize(b.width, b.height);
    QStyle::SFlags sflags = Ttk_StateTableLookup(menubutton_statemap, state);
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

static Ttk_ElementSpec MenubuttonElementSpec = {
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

int TileQt_Init_Menubutton(Tcl_Interp *interp, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Menubutton.dropdown",
            &MenubuttonDropdownElementSpec, NULL);
    Ttk_RegisterElement(interp, themePtr, "Menubutton.button",
            &MenubuttonElementSpec, NULL);

    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr, "TMenubutton", MenubuttonLayout);
    return TCL_OK;
}; /* TileQt_Init_Menubutton */
