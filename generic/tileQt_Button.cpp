/*
 *  tileQt_Button.cpp
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
 * Pushbuttons (Tk: "Button")
 */
static Ttk_StateTable pushbutton_statemap[] =
{
    {QStyle::Style_Default                          , TTK_STATE_DISABLED, 0},
    {QStyle::Style_Enabled | QStyle::Style_Down     , TTK_STATE_PRESSED, 0},
    {QStyle::Style_Enabled | QStyle::Style_MouseOver, TTK_STATE_ACTIVE, 0},
    {QStyle::Style_Enabled | QStyle::Style_HasFocus , TTK_STATE_FOCUS, 0},
    {QStyle::Style_Enabled | QStyle::Style_Active   , TTK_STATE_ALTERNATE, 0},
    {QStyle::Style_Enabled, 0, 0 }
};

typedef struct {
} ButtonElement;

static Ttk_ElementOptionSpec ButtonElementOptions[] = {
    {NULL}
};

static void ButtonElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (qApp == NULL) return;
    // QPushButton button(TileQt_QWidget_Widget);
    // *widthPtr   = button.width();
    // *heightPtr  = button.height();
    *paddingPtr = Ttk_UniformPadding(0);
}

static void ButtonElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) return;
    QPixmap     pixmap(b.width, b.height);
    QPainter    painter(&pixmap);
    QPushButton button(TileQt_QWidget_Widget);	
    button.setBackgroundOrigin(QWidget::ParentOrigin);
    button.setGeometry(b.x, b.y, b.width, b.height);
    // QPoint p = button.backgroundOffset();
    // QPoint pos = button.pos();
    // TileQt_StateInfo(state, tkwin);
    QStyle::SFlags sflags = Ttk_StateTableLookup(pushbutton_statemap, state);
    /* Handle buggy styles, that do not check flags but check widget states. */
    if (state & TTK_STATE_ALTERNATE) {
        button.setDefault(true);
    } else {
        button.setDefault(false);
    }
    if (state & TTK_STATE_PRESSED) {
        button.setDown(true);
    } else {
        button.setDown(false);
    }
    // printf("state=%d, qt style=%d\n", state,
    //        Ttk_StateTableLookup(pushbutton_statemap, state));
    if (TileQt_QPixmap_BackgroundTile &&
        !(TileQt_QPixmap_BackgroundTile->isNull())) {
        painter.fillRect(0, 0, b.width, b.height,
                         QBrush(QColor(255,255,255),
                         *TileQt_QPixmap_BackgroundTile));
    } else {
        painter.fillRect(0, 0, b.width, b.height,
                         qApp->palette().active().background());
    }

    qApp->style().drawControl(QStyle::CE_PushButton, &painter, &button,
          QRect(0, 0, b.width, b.height), qApp->palette().active(), sflags);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
}

static Ttk_ElementSpec ButtonElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ButtonElement),
    ButtonElementOptions,
    ButtonElementGeometry,
    ButtonElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

TTK_BEGIN_LAYOUT(ButtonLayout)
    TTK_GROUP("Button.button", TTK_FILL_BOTH,
	    TTK_GROUP("Button.padding", TTK_FILL_BOTH,
		TTK_NODE("Button.label", TTK_FILL_BOTH)))
TTK_END_LAYOUT

int TileQt_Init_Button(Tcl_Interp *interp, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Button.button",
            &ButtonElementSpec, NULL);

    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr, "TButton", ButtonLayout);
    return TCL_OK;
}; /* TileQt_Init_Button */
