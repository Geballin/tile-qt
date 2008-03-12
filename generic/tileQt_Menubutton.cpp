/*
 *  tileQt_Menubutton.cpp
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
 * Pushbuttons (Tk: "Menubutton")
 */
static Ttk_StateTable menubutton_statemap[] =
{
#ifdef TILEQT_QT_VERSION_3
    {QStyle::Style_Default                          , TTK_STATE_DISABLED, 0},
    {QStyle::Style_Enabled | QStyle::Style_Down     , TTK_STATE_PRESSED, 0},
    {QStyle::Style_Enabled | QStyle::Style_MouseOver, TTK_STATE_ACTIVE, 0},
    {QStyle::Style_Enabled | QStyle::Style_Active   , TTK_STATE_ALTERNATE, 0},
    {QStyle::Style_Enabled, 0, 0 }
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    {QStyle::State_None                             , TTK_STATE_DISABLED, 0},
    {QStyle::State_Enabled | QStyle::State_Sunken   , TTK_STATE_PRESSED, 0},
    {QStyle::State_Enabled | QStyle::State_MouseOver, TTK_STATE_ACTIVE, 0},
    {QStyle::State_Enabled | QStyle::State_Active   , TTK_STATE_ALTERNATE, 0},
    {QStyle::State_Enabled, 0, 0 }
#endif /* TILEQT_QT_VERSION_4 */
};

typedef struct {
} MenubuttonDropdownElement;

static Ttk_ElementOptionSpec MenubuttonDropdownElementOptions[] = {
    {NULL}
};

static void MenubuttonDropdownElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_WIDGET(TileQt_QComboBox_RO_Widget);
    Tcl_MutexLock(&tileqtMutex);
#ifdef TILEQT_QT_VERSION_3
    QRect rc = wc->TileQt_Style->querySubControlMetrics(QStyle::CC_ComboBox,
                   wc->TileQt_QComboBox_RO_Widget, QStyle::SC_ComboBoxArrow);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    QStyleOptionComboBox option;
    option.initFrom(wc->TileQt_QComboBox_RO_Widget);
    option.subControls = QStyle::SC_ComboBoxArrow;
    QSize rc = wc->TileQt_Style->sizeFromContents(QStyle::CT_ComboBox, &option,
                   QSize(1, 1));
#endif /* TILEQT_QT_VERSION_4 */
    *widthPtr = rc.width();
    Tcl_MutexUnlock(&tileqtMutex);
    *paddingPtr = Ttk_UniformPadding(0);
}

static void MenubuttonDropdownElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
#ifdef TILEQT_QT_VERSION_3
    // if (qApp == NULL) NULL_Q_APP;
    // There is no need to re-paint the button. It has been paint along with the
    // field element (ComboboxFieldElementDraw). This is because Qt's Combobox
    // is a complex widget.
    // QPixmap      pixmap(b.x+b.width, b.y+b.height);
    // QPainter     painter(&pixmap);
    // QComboBox& widget = *TileQt_QComboBox_RO_Widget;
    // widget.resize(b.x+b.width, b.y+b.height);
    // QStyle::SFlags sflags = TileQt_StateTableLookup(menubutton_statemap, state);
    // QStyle::SCFlags scflags = QStyle::SC_ComboBoxFrame|QStyle::SC_ComboBoxArrow;
    // QStyle::SCFlags activeflags = QStyle::SC_None;
    // 
    // painter.fillRect(0, 0, b.width, b.height,
    //                  qApp->palette().active().brush(QColorGroup::Background));
    // // printf("x=%d, y=%d, w=%d, h=%d\n", b.x, b.y, b.width, b.height);
    // qApp->style().drawComplexControl(QStyle::CC_ComboBox, &painter, &widget,
    //       QRect(0, 0, b.x+b.width, b.y+b.height),
    //       qApp->palette().active(), sflags, scflags, activeflags);
    // TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
    //                                 b.x, b.y, b.width, b.height, b.x, b.y);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    // if (qApp == NULL) NULL_Q_APP;
    // NULL_PROXY_WIDGET(TileQt_QWidget_Widget);
    // Tcl_MutexLock(&tileqtMutex);
    // QPixmap     pixmap(b.width, b.height);
    // QPainter    painter(&pixmap);
    // QComboBox*  widget = wc->TileQt_QComboBox_RO_Widget;
    // widget->resize(b.width, b.height);
    // QStyleOptionComboBox option;
    // option.initFrom(widget); option.state |= 
    //   (QStyle::StateFlag) TileQt_StateTableLookup(menubutton_statemap, state);
    // option.subControls = QStyle::SC_ComboBoxArrow;
    // option.rect = QRect (0, 0, b.width, b.height);
    // wc->TileQt_Style->drawComplexControl(QStyle::CC_ComboBox, &option,
    //                                      &painter, widget);
    // TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
    //                                 0, 0, b.width, b.height, b.x, b.y);
    // Tcl_MutexUnlock(&tileqtMutex);
#endif /* TILEQT_QT_VERSION_4 */
}

static Ttk_ElementSpec MenubuttonDropdownElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(MenubuttonDropdownElement),
    MenubuttonDropdownElementOptions,
    MenubuttonDropdownElementGeometry,
    MenubuttonDropdownElementDraw
};

typedef struct {
} MenubuttonElement;

static Ttk_ElementOptionSpec MenubuttonElementOptions[] = {
    {NULL}
};

static void MenubuttonElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_WIDGET(TileQt_QComboBox_RO_Widget);
    Tcl_MutexLock(&tileqtMutex);
#ifdef TILEQT_QT_VERSION_3
    // QComboBox    widget(TileQt_QWidget_Widget);
    // *widthPtr   = widget.width();
    // *heightPtr  = widget.height();
    //*paddingPtr = Ttk_UniformPadding(0);
    // In order to get the correct padding, calculate the difference between the
    // frame & edit field rectangulars...
    QRect fr_rc = wc->TileQt_Style->querySubControlMetrics(QStyle::CC_ComboBox,
                  wc->TileQt_QComboBox_RO_Widget, QStyle::SC_ComboBoxFrame);
    QRect ef_rc = wc->TileQt_Style->querySubControlMetrics(QStyle::CC_ComboBox,
                  wc->TileQt_QComboBox_RO_Widget, QStyle::SC_ComboBoxEditField);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    QStyleOptionComboBox option;
    option.initFrom(wc->TileQt_QComboBox_RO_Widget);
    option.subControls = QStyle::SC_ComboBoxFrame;
    QRect fr_rc = wc->TileQt_Style->subControlRect(QStyle::CC_ComboBox,
         &option, QStyle::SC_ComboBoxFrame, wc->TileQt_QComboBox_RO_Widget);
    QRect ef_rc = wc->TileQt_Style->subControlRect(QStyle::CC_ComboBox,
         &option, QStyle::SC_ComboBoxEditField, wc->TileQt_QComboBox_RO_Widget);
#endif /* TILEQT_QT_VERSION_4 */
    *paddingPtr = Ttk_MakePadding(ef_rc.x() - fr_rc.x()           /* left   */,
                                  ef_rc.y() - fr_rc.y()           /* top    */,
                     fr_rc.width()  - ef_rc.width()  - ef_rc.x()  /* right  */,
                     fr_rc.height() - ef_rc.height() - ef_rc.y()  /* bottom */);
    Tcl_MutexUnlock(&tileqtMutex);
}

static void MenubuttonElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_WIDGET(TileQt_QComboBox_RO_Widget);
    Tcl_MutexLock(&tileqtMutex);
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    QComboBox&   widget = *wc->TileQt_QComboBox_RO_Widget;
#ifdef TILEQT_QT_VERSION_3
    widget.setBackgroundOrigin(QWidget::ParentOrigin);
#endif /* TILEQT_QT_VERSION_3 */
    widget.resize(b.width, b.height);
    TILEQT_PAINT_BACKGROUND(b.width, b.height);
    TILEQT_SET_FOCUS(state);
#ifdef TILEQT_QT_VERSION_3
    QStyle::SFlags sflags = TileQt_StateTableLookup(menubutton_statemap, state);
    QStyle::SCFlags scflags = QStyle::SC_ComboBoxFrame|QStyle::SC_ComboBoxArrow|
                              QStyle::SC_ComboBoxEditField;
    QStyle::SCFlags activeflags = QStyle::SC_ComboBoxFrame;
    // printf("x=%d, y=%d, w=%d, h=%d\n", b.x, b.y, b.width, b.height);
    wc->TileQt_Style->drawComplexControl(QStyle::CC_ComboBox, &painter, &widget,
          QRect(0, 0, b.width, b.height), qApp->palette().active(), sflags,
          scflags, activeflags);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    QStyleOptionComboBox option;
    option.initFrom(&widget); option.state |= 
      (QStyle::StateFlag) TileQt_StateTableLookup(menubutton_statemap, state);
    wc->TileQt_Style->drawComplexControl(QStyle::CC_ComboBox, &option,
                                         &painter, &widget);
#endif /* TILEQT_QT_VERSION_4 */
    TILEQT_CLEAR_FOCUS(state);
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
    Tcl_MutexUnlock(&tileqtMutex);
}

static Ttk_ElementSpec MenubuttonElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(MenubuttonElement),
    MenubuttonElementOptions,
    MenubuttonElementGeometry,
    MenubuttonElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

TTK_BEGIN_LAYOUT(MenubuttonLayout)
    TTK_GROUP("Menubutton.button", TTK_FILL_BOTH,
	    TTK_GROUP("Menubutton.padding", TTK_FILL_BOTH,
                TTK_NODE("Menubutton.dropdown", TTK_PACK_RIGHT|TTK_FILL_Y)
		TTK_NODE("Menubutton.label", TTK_FILL_BOTH)))
TTK_END_LAYOUT

int TileQt_Init_Menubutton(Tcl_Interp *interp,
                       TileQt_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Menubutton.dropdown",
            &MenubuttonDropdownElementSpec, (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "Menubutton.button",
            &MenubuttonElementSpec, (void *) wc[0]);

    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr, "TMenubutton", MenubuttonLayout);
    return TCL_OK;
}; /* TileQt_Init_Menubutton */
