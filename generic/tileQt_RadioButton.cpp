/*
 *  tileQt_RadioButton.cpp
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
static TTK_StateTable radiobutton_statemap[] =
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
} RadioButtonIndicatorElement;


static TTK_ElementOptionSpec RadioButtonIndicatorElementOptions[] = {
    {NULL}
};

static void RadioButtonIndicatorElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, TTK_Padding *paddingPtr)
{
    *widthPtr  = qApp->style().pixelMetric(QStyle::PM_ExclusiveIndicatorWidth);
    *heightPtr = qApp->style().pixelMetric(QStyle::PM_ExclusiveIndicatorHeight);
    *paddingPtr = TTK_MakePadding(0, 0, RadioButtonHorizontalPadding, 0);
}

static void RadioButtonIndicatorElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, TTK_Box b, unsigned state)
{
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    QRadioButton button(TileQt_QWidget_Widget);
    button.resize(b.width - RadioButtonHorizontalPadding, b.height);
    QStyle::SFlags sflags = TTK_StateTableLookup(radiobutton_statemap, state);
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
    qApp->style().drawControl(QStyle::CE_RadioButton, &painter, &button,
          QRect(0, 0, b.width - RadioButtonHorizontalPadding, b.height),
          qApp->palette().active(), sflags);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
}

static TTK_ElementSpec RadioButtonIndicatorElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(RadioButtonIndicatorElement),
    RadioButtonIndicatorElementOptions,
    RadioButtonIndicatorElementGeometry,
    RadioButtonIndicatorElementDraw
};

typedef struct {
} RadioButtonBorderElement;


static TTK_ElementOptionSpec RadioButtonBorderElementOptions[] = {
    {NULL}
};

static void RadioButtonBorderElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, TTK_Padding *paddingPtr)
{
    QRadioButton button(TileQt_QWidget_Widget);
    *widthPtr   = button.width();
    *heightPtr  = button.height();
    *paddingPtr = TTK_MakePadding(0, 0, 0, 0);
}

static void RadioButtonBorderElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, TTK_Box b, unsigned state)
{
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    QRadioButton button(TileQt_QWidget_Widget);	
    button.setBackgroundOrigin(QWidget::ParentOrigin);
    button.resize(b.width, b.height);
    //button.setGeometry(b.x, b.y, b.width, b.height);
    QStyle::SFlags sflags = TTK_StateTableLookup(radiobutton_statemap, state);
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
    qApp->style().drawControl(QStyle::CE_RadioButtonLabel, &painter, &button,
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

static TTK_ElementSpec RadioButtonBorderElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(RadioButtonBorderElement),
    RadioButtonBorderElementOptions,
    RadioButtonBorderElementGeometry,
    RadioButtonBorderElementDraw
};


/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

TTK_BEGIN_LAYOUT(RadiobuttonLayout)
     TTK_GROUP("Radiobutton.border", TTK_FILL_BOTH,
	 TTK_GROUP("Radiobutton.padding", TTK_FILL_BOTH,
	     TTK_NODE("Radiobutton.indicator", TTK_PACK_LEFT)
	     TTK_GROUP("Radiobutton.focus", TTK_PACK_LEFT,
		 TTK_NODE("Radiobutton.label", TTK_FILL_BOTH))))
TTK_END_LAYOUT

int TileQt_Init_RadioButton(Tcl_Interp *interp, TTK_Theme themePtr)
{
    /*
     * Register elements:
     */
    TTK_RegisterElementSpec(themePtr, "Radiobutton.border",
            &RadioButtonBorderElementSpec, NULL);
    TTK_RegisterElementSpec(themePtr, "Radiobutton.indicator",
            &RadioButtonIndicatorElementSpec, NULL);
    
    /*
     * Register layouts:
     */
    TTK_RegisterLayout(themePtr, "TRadiobutton", RadiobuttonLayout);
    
    return TCL_OK;
}; /* TileQt_Init_RadioButton */
