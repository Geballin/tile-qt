/*
 *  tileQt_Arrows.cpp
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
 * Map between Tk/Tile & Qt/KDE state flags.
 */
static Ttk_StateTable arrow_statemap[] =
{
    { QStyle::Style_Default, TTK_STATE_DISABLED, 0 },
    { QStyle::Style_Enabled | QStyle::Style_Down, TTK_STATE_PRESSED, 0 },
    { QStyle::Style_Enabled | QStyle::Style_MouseOver, TTK_STATE_ACTIVE, 0 },
    { QStyle::Style_Enabled | QStyle::Style_Active, TTK_STATE_ALTERNATE, 0 },
    { QStyle::Style_Enabled, 0, 0 }
};

static int ArrowElements[] = { ARROW_UP, ARROW_DOWN, ARROW_LEFT, ARROW_RIGHT };
typedef struct
{
    Tcl_Obj *sizeObj;
    Tcl_Obj *borderObj;
    Tcl_Obj *borderWidthObj;
    Tcl_Obj *reliefObj;
} ArrowElement;

static Ttk_ElementOptionSpec ArrowElementOptions[] =
{
    { "-arrowsize", TK_OPTION_PIXELS, Tk_Offset(ArrowElement,sizeObj),
        DEFAULT_ARROW_SIZE },
    { "-background", TK_OPTION_BORDER, Tk_Offset(ArrowElement,borderObj),
            DEFAULT_BACKGROUND },
    { "-borderwidth", TK_OPTION_PIXELS, Tk_Offset(ArrowElement,borderWidthObj),
            DEFAULT_BORDERWIDTH },
    { "-relief", TK_OPTION_RELIEF, Tk_Offset(ArrowElement,reliefObj),"raised" },
    { NULL }
};

static void
ArrowElementGeometry(
    void *clientData, void *elementRecord,
    Tk_Window tkwin, int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    ArrowElement *arrow = (ArrowElement *) elementRecord;
    int size = 12;

    Tk_GetPixelsFromObj(NULL, tkwin, arrow->sizeObj, &size);
    *widthPtr = *heightPtr = size;
}

static void
ArrowElementDraw(void *clientData, void *elementRecord,
    Tk_Window tkwin, Drawable d, Ttk_Box b, unsigned int state)
{
    ArrowElement *arrow = (ArrowElement *) elementRecord;
    int direction = *(int *)clientData;
    QStyle::SFlags sflags = Ttk_StateTableLookup(arrow_statemap ,state);
    QStyle::PrimitiveElement element = QStyle::PE_ArrowUp;
    //if (state == GTK_STATE_INSENSITIVE)
    //        sflags |= QStyle::Style_Off;
    //else if (state == GTK_STATE_PRELIGHT)
    //        sflags |= QStyle::Style_On;
    
    switch(direction)
    {
        case ARROW_UP:    element = QStyle::PE_ArrowUp;    break;
        case ARROW_DOWN:  element = QStyle::PE_ArrowDown;  break;
        case ARROW_LEFT:  element = QStyle::PE_ArrowLeft;  break;
        case ARROW_RIGHT: element = QStyle::PE_ArrowRight; break;
    }
    QPixmap     pixmap(b.width, b.height);
    QPainter    painter(&pixmap);
    if ((TileQt_QPixmap_BackgroundTile) &&
        (!TileQt_QPixmap_BackgroundTile->isNull())) {
       painter.fillRect(0, 0, b.width, b.height, QBrush(QColor(255,255,255),
               *TileQt_QPixmap_BackgroundTile));
    } else {
       painter.fillRect(0, 0, b.width, b.height,
               qApp->palette().active().brush(QColorGroup::Background));
    }    
    qApp->style().drawPrimitive(element, &painter,
          QRect(0, 0, b.width, b.height), qApp->palette().active(), sflags);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
}

static Ttk_ElementSpec ArrowElementSpec =
{
    TK_STYLE_VERSION_2,
    sizeof(ArrowElement),
    ArrowElementOptions,
    ArrowElementGeometry,
    ArrowElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */


int TileQt_Init_Arrows(Tcl_Interp *interp, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElementSpec(themePtr, "uparrow",
            &ArrowElementSpec, &ArrowElements[0]);
    Ttk_RegisterElementSpec(themePtr, "downarrow",
            &ArrowElementSpec, &ArrowElements[1]);
    Ttk_RegisterElementSpec(themePtr, "leftarrow",
            &ArrowElementSpec, &ArrowElements[2]);
    Ttk_RegisterElementSpec(themePtr, "rightarrow",
            &ArrowElementSpec, &ArrowElements[3]);
    Ttk_RegisterElementSpec(themePtr, "arrow",
            &ArrowElementSpec, &ArrowElements[0]);

    /*
     * Register layouts:
     */

    return TCL_OK;
}; /* TileQt_Init_Arrows */
