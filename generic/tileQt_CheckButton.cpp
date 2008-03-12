/*
 *  tileQt_CheckButton.cpp
 * ------------------------
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
static Ttk_StateTable checkbutton_statemap[] =
{
#ifdef TILEQT_QT_VERSION_3
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
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    {QStyle::State_None|QStyle::State_On,
                           TTK_STATE_DISABLED|TTK_STATE_SELECTED, 0},
    {QStyle::State_Enabled|QStyle::State_Sunken|QStyle::State_On,
                           TTK_STATE_PRESSED|TTK_STATE_SELECTED, 0},
    {QStyle::State_Enabled|QStyle::State_MouseOver|QStyle::State_On,
                           TTK_STATE_ACTIVE|TTK_STATE_SELECTED, 0},
    {QStyle::State_Enabled|QStyle::State_On,
                           TTK_STATE_SELECTED, 0},
    {QStyle::State_None|QStyle::State_Off,
                           TTK_STATE_DISABLED, TTK_STATE_SELECTED},
    {QStyle::State_Enabled|QStyle::State_Sunken|QStyle::State_Off,
                           TTK_STATE_PRESSED, TTK_STATE_SELECTED},
    {QStyle::State_Enabled|QStyle::State_MouseOver|QStyle::State_Off,
                           TTK_STATE_ACTIVE, TTK_STATE_SELECTED},
    {QStyle::State_Enabled|QStyle::State_Off, 0, 0}
#endif /* TILEQT_QT_VERSION_4 */
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
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_WIDGET(TileQt_Style);
    Tcl_MutexLock(&tileqtMutex);
#ifdef TILEQT_QT_VERSION_3
    *widthPtr  = wc->TileQt_Style->pixelMetric(QStyle::PM_IndicatorWidth);
    *heightPtr = wc->TileQt_Style->pixelMetric(QStyle::PM_IndicatorHeight);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    QStyleOptionButton option;
    QRect rc = wc->TileQt_Style->subElementRect(QStyle::SE_CheckBoxIndicator,
                   &option);
    *widthPtr  = rc.width();
    *heightPtr = rc.height();
#endif /* TILEQT_QT_VERSION_4 */
    Tcl_MutexUnlock(&tileqtMutex);
    *paddingPtr = Ttk_MakePadding(0, 0, CheckButtonHorizontalPadding, 0);
}

static void CheckButtonIndicatorElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_WIDGET(TileQt_QWidget_Widget);
    Tcl_MutexLock(&tileqtMutex);
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    QCheckBox    button(wc->TileQt_QWidget_Widget);
    button.resize(b.width - CheckButtonHorizontalPadding, b.height);
    TILEQT_PAINT_BACKGROUND(b.width, b.height);
    TILEQT_SET_FOCUS(state);
#ifdef TILEQT_QT_VERSION_3
    QStyle::SFlags sflags = TileQt_StateTableLookup(checkbutton_statemap, state);
    wc->TileQt_Style->drawControl(QStyle::CE_CheckBox, &painter, &button,
          QRect(0, 0, b.width - CheckButtonHorizontalPadding, b.height),
          qApp->palette().active(), sflags);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    QStyleOptionButton option;
    option.initFrom(&button); option.state |= 
      (QStyle::StateFlag) TileQt_StateTableLookup(checkbutton_statemap, state);
    wc->TileQt_Style->drawControl(QStyle::CE_CheckBox, &option,
                                  &painter, &button);
#endif /* TILEQT_QT_VERSION_4 */
    TILEQT_CLEAR_FOCUS(state);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
    Tcl_MutexUnlock(&tileqtMutex);
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
    if (qApp == NULL) NULL_Q_APP;
    *paddingPtr = Ttk_MakePadding(0, 0, 0, 0);
    // NULL_PROXY_WIDGET(TileQt_QWidget_Widget);
    // Tcl_MutexLock(&tileqtMutex);
    // QCheckBox button(wc->TileQt_QWidget_Widget);
    // *widthPtr   = button.width();
    // *heightPtr  = button.height();
    // Tcl_MutexUnlock(&tileqtMutex);
}

static void CheckButtonBorderElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_WIDGET(TileQt_QWidget_Widget);
    Tcl_MutexLock(&tileqtMutex);
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    QCheckBox    button(wc->TileQt_QWidget_Widget);
#ifdef TILEQT_QT_VERSION_3
    button.setBackgroundOrigin(QWidget::ParentOrigin);
#endif /* TILEQT_QT_VERSION_3 */
    button.resize(b.width, b.height);
    //button.setGeometry(b.x, b.y, b.width, b.height);
    TILEQT_PAINT_BACKGROUND(b.width, b.height);
    TILEQT_SET_FOCUS(state);
    // printf("x=%d, y=%d, w=%d, h=%d\n", b.x, b.y, b.width, b.height);
#ifdef TILEQT_QT_VERSION_3
    QStyle::SFlags sflags = TileQt_StateTableLookup(checkbutton_statemap, state);
    wc->TileQt_Style->drawControl(QStyle::CE_CheckBoxLabel, &painter, &button,
          QRect(0, 0, b.width, b.height),
          qApp->palette().active(), sflags);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    QStyleOptionButton option;
    option.initFrom(&button); option.state |= 
      (QStyle::StateFlag) TileQt_StateTableLookup(checkbutton_statemap, state);
    wc->TileQt_Style->drawControl(QStyle::CE_CheckBoxLabel, &option,
                                  &painter, &button);
#endif /* TILEQT_QT_VERSION_4 */
    TILEQT_CLEAR_FOCUS(state);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.x);
    /* Because we have drawn only the label of the radio button, the drawn area
     * contains a hole (for the indicator). Copy the last part of the widget
     * ontop of its begining, to erase this hole. Perhaps there is a better way
     * to get the proper background colour and avoid drawing the widget, just to
     * get the proper background colour... */
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    b.width/2, 0, b.width, b.height, b.x, b.y);
    Tcl_MutexUnlock(&tileqtMutex);
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

int TileQt_Init_CheckButton(Tcl_Interp *interp,
                       TileQt_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Checkbutton.border",
            &CheckButtonBorderElementSpec, (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "Checkbutton.indicator",
            &CheckButtonIndicatorElementSpec, (void *) wc[0]);
    
    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr, "TCheckbutton", CheckbuttonLayout);
    
    return TCL_OK;
}; /* TileQt_Init_CheckButton */
