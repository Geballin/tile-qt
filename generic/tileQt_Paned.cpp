/*
 *  tileQt_Paned.cpp
 * ---------------------
 *
 * This file is part of the Tile-Qt package, a Tk/Tile based theme that uses
 * Qt/KDE for drawing.
 *
 * Copyright (C) 2004-2008 by:
 * Georgios Petasis, petasis@iit.demokritos.gr,
 * Software and Knowledge Engineering Laboratory,
 * Institute of Informatics and Telecommunications,
 * National Centre for Scientific Research (NCSR) "Demokritos",
 * Aghia Paraskevi, 153 10, Athens, Greece.
 */

#include "tileQt_Utilities.h"
#include "tileQt_TkHeaders.h"
#include "tileQt_WidgetDefaults.h"

/*
 * Map between Tk/Tile & Qt/KDE state flags.
 */
static Ttk_StateTable paned_statemap[] =
{
#ifdef TILEQT_QT_VERSION_3
    {QStyle::Style_Default,                         TTK_STATE_DISABLED, 0},
    {QStyle::Style_Enabled|QStyle::Style_Down,      TTK_STATE_PRESSED, 0},
    {QStyle::Style_Enabled|QStyle::Style_HasFocus,  TTK_STATE_FOCUS, 0},
    {QStyle::Style_Enabled|QStyle::Style_MouseOver, TK_STATE_ACTIVE, 0},
    {QStyle::Style_Enabled,                         0, 0}
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    {QStyle::State_None,                            TTK_STATE_DISABLED, 0},
    {QStyle::State_Enabled|QStyle::State_Sunken,    TTK_STATE_PRESSED, 0},
    {QStyle::State_Enabled|QStyle::State_HasFocus,  TTK_STATE_FOCUS, 0},
    {QStyle::State_Enabled|QStyle::State_MouseOver, TK_STATE_ACTIVE, 0},
    {QStyle::State_Enabled,                         0, 0}
#endif /* TILEQT_QT_VERSION_4 */
};

typedef struct {
} PanedSashGripElement;

static Ttk_ElementOptionSpec PanedSashGripElementOptions[] = {
    {NULL}
};

static void PanedSashGripElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_ORIENTED_WIDGET(TileQt_QWidget_Widget);
    if (orient == TTK_ORIENT_HORIZONTAL) {
      *widthPtr = PMW(PM_SplitterWidth, 0);
    } else {
      *heightPtr = PMW(PM_SplitterWidth, 0);
    }
    *paddingPtr = Ttk_UniformPadding(PanedUniformPadding);
}

static void PanedSashGripElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_ORIENTED_WIDGET(TileQt_QWidget_Widget);
    Tcl_MutexLock(&tileqtMutex);
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    TILEQT_PAINT_BACKGROUND(b.width, b.height);
    TILEQT_SET_FOCUS(state);
#ifdef TILEQT_QT_VERSION_3
    QStyle::SFlags sflags = TileQt_StateTableLookup(paned_statemap, state);
    if (orient == TTK_ORIENT_HORIZONTAL) {
    } else {
      sflags |= QStyle::Style_Horizontal;
    }
    wc->TileQt_Style->drawPrimitive(QStyle::PE_Splitter, &painter,
          QRect(0, 0, b.width, b.height), qApp->palette().active(), sflags);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    QStyleOption option;
    option.state |= 
      (QStyle::StateFlag) TileQt_StateTableLookup(paned_statemap, state);
    wc->TileQt_Style->drawControl(QStyle::CE_Splitter, &option,
                                    &painter);
#endif /* TILEQT_QT_VERSION_4 */
    TILEQT_CLEAR_FOCUS(state);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
    Tcl_MutexUnlock(&tileqtMutex);
}; /* PanedSashGripElementDraw */

static Ttk_ElementSpec PanedSashGripElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(PanedSashGripElement),
    PanedSashGripElementOptions,
    PanedSashGripElementGeometry,
    PanedSashGripElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

TTK_BEGIN_LAYOUT(HorizontalSashLayout)
    TTK_GROUP("Sash.hsash", TTK_FILL_BOTH,
	TTK_NODE("Sash.hgrip", TTK_FILL_BOTH))
TTK_END_LAYOUT

TTK_BEGIN_LAYOUT(VerticalSashLayout)
    TTK_GROUP("Sash.vsash", TTK_FILL_BOTH,
	TTK_NODE("Sash.vgrip", TTK_FILL_BOTH))
TTK_END_LAYOUT

int TileQt_Init_Paned(Tcl_Interp *interp,
                       TileQt_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "hgrip",
	    &PanedSashGripElementSpec,  (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "vgrip",
	    &PanedSashGripElementSpec,  (void *) wc[1]);
    
    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr, "Horizontal.Sash", HorizontalSashLayout);
    Ttk_RegisterLayout(themePtr, "Vertical.Sash", VerticalSashLayout);

    return TCL_OK;
}; /* TileQt_Init_Paned */
