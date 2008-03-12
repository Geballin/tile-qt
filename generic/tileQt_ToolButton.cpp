/*
 *  tileQt_ToolButton.cpp
 * -----------------------
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
 * Toolbuttons (Tk: "Button")
 */
static Ttk_StateTable toolbutton_statemap[] =
{
#ifdef TILEQT_QT_VERSION_3
    {QStyle::Style_Default                          , TTK_STATE_DISABLED, 0},
    {QStyle::Style_Enabled | QStyle::Style_Down     , TTK_STATE_SELECTED, 0},
    {QStyle::Style_Enabled | QStyle::Style_Down     , TTK_STATE_PRESSED, 0},
    {QStyle::Style_Enabled | QStyle::Style_Raised   , TTK_STATE_ACTIVE, 0},
    {QStyle::Style_Enabled | QStyle::Style_HasFocus , TTK_STATE_FOCUS, 0},
    {QStyle::Style_Enabled | QStyle::Style_Active   , TTK_STATE_ALTERNATE, 0},
    {QStyle::Style_Enabled, 0, 0 }
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    {QStyle::State_None                             , TTK_STATE_DISABLED, 0},
    {QStyle::State_Enabled | QStyle::State_Sunken   , TTK_STATE_SELECTED, 0},
    {QStyle::State_Enabled | QStyle::State_Sunken   , TTK_STATE_PRESSED, 0},
    {QStyle::State_Enabled | QStyle::State_Raised   , TTK_STATE_ACTIVE, 0},
    {QStyle::State_Enabled | QStyle::State_HasFocus , TTK_STATE_FOCUS, 0},
    {QStyle::State_Enabled | QStyle::State_Active   , TTK_STATE_ALTERNATE, 0},
    {QStyle::State_Enabled, 0, 0 }
#endif /* TILEQT_QT_VERSION_4 */
};

typedef struct {
} ToolButtonElement;

static Ttk_ElementOptionSpec ToolButtonElementOptions[] = {
    {NULL}
};

static void ToolButtonElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (qApp == NULL) NULL_Q_APP;
    //QToolButton button(TileQt_QWidget_Widget);
    //*widthPtr   = button.width();
    //*heightPtr  = button.height();
    *paddingPtr = Ttk_UniformPadding(0);
}

static void ToolButtonElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_WIDGET(TileQt_QWidget_Widget);
    Tcl_MutexLock(&tileqtMutex);
    QPixmap     pixmap(b.width, b.height);
    QPainter    painter(&pixmap);
    QToolButton button(wc->TileQt_QWidget_Widget);	
#ifdef TILEQT_QT_VERSION_3
    button.setBackgroundOrigin(QWidget::ParentOrigin);
#endif /* TILEQT_QT_VERSION_3 */
    button.setGeometry(b.x, b.y, b.width, b.height);
    // TileQt_StateInfo(state, tkwin);
    /* Handle buggy styles, that do not check flags but check widget states. */
    //if (state & TTK_STATE_ALTERNATE) {
    //    button.setDefault(true);
    //} else {
    //    button.setDefault(false);
    //}
    if (state & TTK_STATE_PRESSED) {
        button.setDown(true);
    } else {
        button.setDown(false);
    }
    TILEQT_PAINT_BACKGROUND(b.width, b.height);
    TILEQT_SET_FOCUS(state);
#ifdef TILEQT_QT_VERSION_3
    QStyle::SFlags sflags = TileQt_StateTableLookup(toolbutton_statemap, state);
    QStyle::SCFlags scflags = QStyle::SC_ToolButton;
    QStyle::SCFlags activeflags = QStyle::SC_None;
    if (state & TTK_STATE_PRESSED) activeflags |= QStyle::SC_ToolButton;
    wc->TileQt_Style->drawComplexControl(QStyle::CC_ToolButton, &painter,
          &button, QRect(0, 0, b.width, b.height), button.colorGroup(), sflags,
          scflags, activeflags);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    QStyleOptionToolButton option;
    option.initFrom(&button); option.state |= 
      (QStyle::StateFlag) TileQt_StateTableLookup(toolbutton_statemap, state);
    wc->TileQt_Style->drawComplexControl(QStyle::CC_ToolButton, &option,
                                  &painter, &button);
#endif /* TILEQT_QT_VERSION_4 */
    // printf("state=%d, qt style=%d\n", state,
    //        TileQt_StateTableLookup(toolbutton_statemap, state));
    TILEQT_CLEAR_FOCUS(state);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
    Tcl_MutexUnlock(&tileqtMutex);
}

static Ttk_ElementSpec ToolButtonElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ToolButtonElement),
    ToolButtonElementOptions,
    ToolButtonElementGeometry,
    ToolButtonElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

TTK_BEGIN_LAYOUT(ToolbuttonLayout)
    TTK_GROUP("Toolbutton.border", TTK_FILL_BOTH,
	    TTK_GROUP("Toolbutton.padding", TTK_FILL_BOTH,
		TTK_NODE("Toolbutton.label", TTK_FILL_BOTH)))
TTK_END_LAYOUT

int TileQt_Init_ToolButton(Tcl_Interp *interp,
                       TileQt_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Toolbutton.border",
            &ToolButtonElementSpec, (void *) wc[0]);

    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr, "TToolbutton", ToolbuttonLayout);
    return TCL_OK;
}; /* TileQt_Init_ToolButton */
