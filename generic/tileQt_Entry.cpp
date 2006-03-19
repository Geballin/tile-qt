/*
 *  tileQt_Entry.cpp
 * ------------------
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
static Ttk_StateTable entry_statemap[] =
{
    {QStyle::Style_Default,                         TTK_STATE_DISABLED, 0 },
    {QStyle::Style_Enabled|QStyle::Style_NoChange,  TTK_STATE_READONLY, 0 },
    {QStyle::Style_Enabled|QStyle::Style_HasFocus,  TTK_STATE_FOCUS, 0 },
    {QStyle::Style_Enabled|QStyle::Style_MouseOver, TTK_STATE_ACTIVE, 0 },
    {QStyle::Style_Enabled,                         0, 0 }
};

typedef struct {
} EntryFieldElement;


static Ttk_ElementOptionSpec EntryFieldElementOptions[] = {
    {NULL}
};

static void EntryFieldElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (qApp == NULL) NULL_Q_APP;
    *paddingPtr = Ttk_UniformPadding(EntryUniformPadding);
}

static void EntryFieldElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_WIDGET(TileQt_QWidget_Widget);
    Tcl_MutexLock(&tileqtMutex);
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    QStyle::SFlags sflags = Ttk_StateTableLookup(entry_statemap, state);
    painter.fillRect(0, 0, b.width, b.height,
                     qApp->palette().active().base());
    // printf("x=%d, y=%d, w=%d, h=%d\n", b.x, b.y, b.width, b.height);
    wc->TileQt_Style->drawPrimitive(QStyle::PE_PanelLineEdit, &painter,
          QRect(0, 0, b.width, b.height), qApp->palette().active(), sflags,
          QStyleOption(1,1));
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
    Tcl_MutexUnlock(&tileqtMutex);
}

static Ttk_ElementSpec EntryFieldElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(EntryFieldElement),
    EntryFieldElementOptions,
    EntryFieldElementGeometry,
    EntryFieldElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

int TileQt_Init_Entry(Tcl_Interp *interp,
                       TileQt_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Entry.field",
            &EntryFieldElementSpec, (void *) wc[0]);
    
    /*
     * Register layouts:
     */

    return TCL_OK;
}; /* TileQt_Init_Entry */
