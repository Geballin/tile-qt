/*
 *  tileQt_CheckButton.cpp
 * ------------------------
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
static Ttk_StateTable checkbutton_statemap[] =
{
    {QStyle::Style_Default|QStyle::Style_On,
                           TTK_STATE_DISABLED|TTK_STATE_SELECTED, 0},
    {QStyle::Style_Enabled|QStyle::Style_Down|QStyle::Style_On,
                           TTK_STATE_PRESSED|TTK_STATE_SELECTED, 0},
    {QStyle::Style_Enabled|QStyle::Style_MouseOver|QStyle::Style_On,
                           TTK_STATE_ACTIVE|TTK_STATE_SELECTED, 0},
    {QStyle::Style_Enabled|QStyle::Style_On,
                           TTK_STATE_SELECTED, 0},
    {QStyle::Style_Default|QStyle::Style_Off,
                           TTK_STATE_DISABLED, TTK_STATE_SELECTED},
    {QStyle::Style_Enabled|QStyle::Style_Down|QStyle::Style_Off,
                           TTK_STATE_PRESSED, TTK_STATE_SELECTED},
    {QStyle::Style_Enabled|QStyle::Style_MouseOver|QStyle::Style_Off,
                           TTK_STATE_ACTIVE, TTK_STATE_SELECTED},
    {QStyle::Style_Enabled|QStyle::Style_Off, 0,0 }
};

typedef struct {
} CheckButtonIndicatorElement;


static Ttk_ElementOptionSpec CheckButtonIndicatorElementOptions[] = {
    {NULL}
};

static void CheckButtonIndicatorElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    *widthPtr  = qApp->style().pixelMetric(QStyle::PM_IndicatorWidth);
    *heightPtr = qApp->style().pixelMetric(QStyle::PM_IndicatorHeight);
    *paddingPtr = Ttk_MakePadding(0, 0, CheckButtonHorizontalPadding, 0);
}

static void CheckButtonIndicatorElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    QCheckBox    button(TileQt_QWidget_Widget);
    button.resize(b.width - CheckButtonHorizontalPadding, b.height);
    QStyle::SFlags sflags = Ttk_StateTableLookup(checkbutton_statemap, state);
    if (TileQt_QPixmap_BackgroundTile &&
        !(TileQt_QPixmap_BackgroundTile->isNull())) {
        painter.fillRect(0, 0, b.width, b.height,
                         QBrush(QColor(255,255,255),
                         *TileQt_QPixmap_BackgroundTile));
    } else {
        painter.fillRect(0, 0, b.width, b.height,
                         qApp->palette().active().background());
    }

    qApp->style().drawControl(QStyle::CE_CheckBox, &painter, &button,
          QRect(0, 0, b.width - CheckButtonHorizontalPadding, b.height),
          qApp->palette().active(), sflags);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
}

static Ttk_ElementSpec CheckButtonIndicatorElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(CheckButtonIndicatorElement),
    CheckButtonIndicatorElementOptions,
    CheckButtonIndicatorElementGeometry,
    CheckButtonIndicatorElementDraw
};

typedef struct {
} CheckButtonBorderElement;


static Ttk_ElementOptionSpec CheckButtonBorderElementOptions[] = {
    {NULL}
};

static void CheckButtonBorderElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    QCheckBox button(TileQt_QWidget_Widget);
    *widthPtr   = button.width();
    *heightPtr  = button.height();
    *paddingPtr = Ttk_MakePadding(0, 0, 0, 0);
}

static void CheckButtonBorderElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    QCheckBox    button(TileQt_QWidget_Widget);	
    button.setBackgroundOrigin(QWidget::ParentOrigin);
    button.resize(b.width, b.height);
    //button.setGeometry(b.x, b.y, b.width, b.height);
    QStyle::SFlags sflags = Ttk_StateTableLookup(checkbutton_statemap, state);
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
    qApp->style().drawControl(QStyle::CE_CheckBoxLabel, &painter, &button,
          QRect(0, 0, b.width, b.height),
          qApp->palette().active(), sflags);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.x);
    /* Because we have drawn only the label of the radio button, the drawn area
     * contains a hole (for the indicator). Copy the last part of the widget
     * ontop of its begining, to erase this hole. Perhaps there is a better way
     * to get the proper background colour and avoid drawing the widget, just to
     * get the proper background colour... */
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    b.width/2, 0, b.width, b.height, b.x, b.y);
}

static Ttk_ElementSpec CheckButtonBorderElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(CheckButtonBorderElement),
    CheckButtonBorderElementOptions,
    CheckButtonBorderElementGeometry,
    CheckButtonBorderElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

TTK_BEGIN_LAYOUT(CheckbuttonLayout)
     TTK_GROUP("Checkbutton.border", TTK_FILL_BOTH,
	 TTK_GROUP("Checkbutton.padding", TTK_FILL_BOTH,
	     TTK_NODE("Checkbutton.indicator", TTK_PACK_LEFT)
	     TTK_GROUP("Checkbutton.focus", TTK_PACK_LEFT | TTK_STICK_W,
		 TTK_NODE("Checkbutton.label", TTK_FILL_BOTH))))
TTK_END_LAYOUT

int TileQt_Init_CheckButton(Tcl_Interp *interp, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElementSpec(themePtr, "Checkbutton.border",
            &CheckButtonBorderElementSpec, NULL);
    Ttk_RegisterElementSpec(themePtr, "Checkbutton.indicator",
            &CheckButtonIndicatorElementSpec, NULL);
    
    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr, "TCheckbutton", CheckbuttonLayout);
    
    return TCL_OK;
}; /* TileQt_Init_CheckButton */
