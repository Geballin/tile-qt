/*
 *  tileQt_Button.cpp
 * -------------------
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
 * Pushbuttons (Tk: "Button")
 */
static Ttk_StateTable pushbutton_statemap[] =
{
#ifdef TILEQT_QT_VERSION_3
    {QStyle::Style_Default                          , TTK_STATE_DISABLED, 0},
    {QStyle::Style_Enabled | QStyle::Style_Down     , TTK_STATE_PRESSED, 0},
    {QStyle::Style_Enabled | QStyle::Style_MouseOver, TTK_STATE_ACTIVE, 0},
    {QStyle::Style_Enabled | QStyle::Style_HasFocus |
     QStyle::Style_FocusAtBorder                    , TTK_STATE_FOCUS, 0},
    {QStyle::Style_Enabled | QStyle::Style_ButtonDefault
                                                    , TTK_STATE_ALTERNATE, 0},
    {QStyle::Style_Enabled, 0, 0 }
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    {QStyle::State_None                             , TTK_STATE_DISABLED, 0},
    {QStyle::State_Enabled | QStyle::State_Sunken   , TTK_STATE_PRESSED, 0},
    {QStyle::State_Enabled | QStyle::State_MouseOver, TTK_STATE_ACTIVE, 0},
    {QStyle::State_Enabled | QStyle::State_HasFocus , TTK_STATE_FOCUS, 0},
    {QStyle::State_Enabled | QStyle::State_Active   , TTK_STATE_ALTERNATE, 0},
    {QStyle::State_Enabled, 0, 0 }
#endif /* TILEQT_QT_VERSION_4 */
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
    if (qApp == NULL) NULL_Q_APP;
    // NULL_PROXY_WIDGET(TileQt_QWidget_Widget);
    // QPushButton button(wc->TileQt_QWidget_Widget);
    // *widthPtr   = button.minimumWidth();
    // *heightPtr  = button.minimumHeight();
    *paddingPtr = Ttk_UniformPadding(PushButtonUniformPadding);
}

static void ButtonElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_WIDGET(TileQt_QWidget_Widget);
    Tcl_MutexLock(&tileqtMutex);
    QPixmap     pixmap(b.width, b.height);
    QPainter    painter(&pixmap);
    QPushButton button(wc->TileQt_QWidget_Widget);
#ifdef TILEQT_QT_VERSION_3
    button.setBackgroundOrigin(QWidget::ParentOrigin);
#endif /* TILEQT_QT_VERSION_3 */
    button.setGeometry(b.x, b.y, b.width, b.height);
    //if (state & TTK_STATE_ALTERNATE) {
    //    button.setDefault(true);
    //} else {
    //    button.setDefault(false);
    //}
    //if (state & TTK_STATE_PRESSED) {
    //    button.setDown(true);
    //} else {
    //    button.setDown(false);
    //}
    TILEQT_PAINT_BACKGROUND(b.width, b.height);
    TILEQT_SET_FOCUS(state);
#ifdef TILEQT_QT_VERSION_3
    // TileQt_StateInfo(state, tkwin);
    QStyle::SFlags sflags = TileQt_StateTableLookup(pushbutton_statemap, state);
    wc->TileQt_Style->drawControl(QStyle::CE_PushButton, &painter, &button,
          QRect(0, 0, b.width, b.height), qApp->palette().active(), sflags);
    // TileQt_QtStateInfo(sflags, tkwin);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    QStyleOptionButton option;
    option.initFrom(&button); option.state |= 
      (QStyle::StateFlag) TileQt_StateTableLookup(pushbutton_statemap, state);
    wc->TileQt_Style->drawControl(QStyle::CE_PushButton, &option,
                                  &painter, &button);
#endif /* TILEQT_QT_VERSION_4 */
    TILEQT_CLEAR_FOCUS(state);
    // printf("state=%d, qt style=%d\n", state,
    //        TileQt_StateTableLookup(pushbutton_statemap, state));

    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
    Tcl_MutexUnlock(&tileqtMutex);
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
	TTK_GROUP("Button.focus", TTK_FILL_BOTH, 
	    TTK_GROUP("Button.padding", TTK_FILL_BOTH,
		TTK_NODE("Button.label", TTK_FILL_BOTH))))
TTK_END_LAYOUT

int TileQt_Init_Button(Tcl_Interp *interp,
                       TileQt_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Button.button",
            &ButtonElementSpec, (void *) wc[0]);

    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr, "TButton", ButtonLayout);
    return TCL_OK;
}; /* TileQt_Init_Button */
