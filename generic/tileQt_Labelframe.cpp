/*
 *  tileQt_Labelframe.cpp
 * -----------------------
 *
 * This file is part of the Tile-Qt package, a Tk/Tile based theme that uses
 * Qt/KDE for drawing.
 *
 * Copyright (C) 2004-2006 by:
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
static Ttk_StateTable labelframe_statemap[] =
{
    {QStyle::Style_Default,                         TTK_STATE_DISABLED, 0 },
    {QStyle::Style_Enabled,                         0, 0 }
};

typedef struct {
} LabelframeBorderElement;


static Ttk_ElementOptionSpec LabelframeBorderElementOptions[] = {
    {NULL}
};

static void LabelframeBorderElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (qApp == NULL) NULL_Q_APP;
    *paddingPtr = Ttk_UniformPadding(LabelframeUniformPadding);
}

static void LabelframeBorderElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_WIDGET(TileQt_QWidget_Widget);
    Tcl_MutexLock(&tileqtMutex);
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    QStyle::SFlags sflags = Ttk_StateTableLookup(labelframe_statemap, state);
    sflags |= QStyle::Style_Sunken;
    if (wc->TileQt_QPixmap_BackgroundTile &&
        !(wc->TileQt_QPixmap_BackgroundTile->isNull())) {
        painter.fillRect(0, 0, b.width, b.height,
                         QBrush(QColor(255,255,255),
                         *wc->TileQt_QPixmap_BackgroundTile));
    } else {
        painter.fillRect(0, 0, b.width, b.height,
                         qApp->palette().active().background());
    }
    // printf("x=%d, y=%d, w=%d, h=%d\n", b.x, b.y, b.width, b.height);
    wc->TileQt_Style->drawPrimitive(QStyle::PE_GroupBoxFrame, &painter,
          QRect(0, 0, b.width, b.height), qApp->palette().active(), sflags,
          QStyleOption(/*lineWidth*/1, /*midLineWidth*/0
                       /*frameShape*//*frameShadow*/));
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
    Tcl_MutexUnlock(&tileqtMutex);
}

static Ttk_ElementSpec LabelframeBorderElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(LabelframeBorderElement),
    LabelframeBorderElementOptions,
    LabelframeBorderElementGeometry,
    LabelframeBorderElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

TTK_BEGIN_LAYOUT(LabelframeLayout)
    /* Note: labelframe widget does its own layout */
    TTK_NODE("Labelframe.border", TTK_FILL_BOTH)
    TTK_NODE("Labelframe.text", TTK_FILL_BOTH)
TTK_END_LAYOUT

int TileQt_Init_Labelframe(Tcl_Interp *interp,
                       TileQt_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Labelframe.border",
            &LabelframeBorderElementSpec, (void *) wc[0]);
    
    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr, "TLabelframe", LabelframeLayout);

    return TCL_OK;
}; /* TileQt_Init_Labelframe */
