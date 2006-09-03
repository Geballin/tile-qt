/*
 *  tileQt_Notebook.cpp
 * ---------------------
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
static Ttk_StateTable notebook_statemap[] =
{
#ifdef TILEQT_QT_VERSION_3
    {QStyle::Style_Default,                         TTK_STATE_DISABLED, 0},
    {QStyle::Style_Enabled|QStyle::Style_Selected,  TTK_STATE_SELECTED, 0},
    {QStyle::Style_Enabled|QStyle::Style_MouseOver, TTK_STATE_ACTIVE,   0},
    {QStyle::Style_Enabled|QStyle::Style_HasFocus,  TTK_STATE_FOCUS,    0},
    {QStyle::Style_Enabled,                         0,                  0},
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    {QStyle::State_None,                            TTK_STATE_DISABLED, 0},
    {QStyle::State_Enabled|QStyle::State_Selected,  TTK_STATE_SELECTED, 0},
    {QStyle::State_Enabled|QStyle::State_MouseOver, TTK_STATE_ACTIVE,   0},
    {QStyle::State_Enabled|QStyle::State_HasFocus,  TTK_STATE_FOCUS,    0},
    {QStyle::State_Enabled,                         0,                  0},
#endif /* TILEQT_QT_VERSION_4 */
};

#ifdef TILEQT_QT_VERSION_3
#define PM(pm) (wc->TileQt_Style->pixelMetric(QStyle::pm, \
                                              wc->TileQt_QTabBar_Widget))
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
#define PM(pm) (wc->TileQt_Style->pixelMetric(QStyle::pm, 0, \
                                              wc->TileQt_QTabBar_Widget))
#endif /* TILEQT_QT_VERSION_4 */

typedef struct {
} NotebookTabElement;


static Ttk_ElementOptionSpec NotebookTabElementOptions[] = {
    {NULL}
};

static void NotebookTabElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_WIDGET(TileQt_QTabBar_Widget);
    Tcl_MutexLock(&tileqtMutex);
    int PM_TabBarTabVSpace          = PM(PM_TabBarTabVSpace),
        PM_TabBarTabHSpace          = PM(PM_TabBarTabHSpace);
    Tcl_MutexUnlock(&tileqtMutex);
    *paddingPtr = Ttk_MakePadding(
           PM_TabBarTabHSpace/2,
           PM_TabBarTabVSpace/2,
           PM_TabBarTabHSpace/2,
           PM_TabBarTabVSpace/2);
}

static void NotebookTabElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_WIDGET(TileQt_QTabBar_Widget);
    int width = b.width, height = b.height;
    Tcl_MutexLock(&tileqtMutex);
    int PM_DefaultFrameWidth  = PM(PM_DefaultFrameWidth);

    if (TileQt_ThemeIs(wc, "bluecurve")) {
      PM_DefaultFrameWidth = 2;
    }

    // TileQt_StateInfo(state, tkwin);
#ifdef TILEQT_QT_VERSION_3
    QTab* tab = new QTab;
    QTab* tab1 = NULL, *tab2 = NULL;
#endif /* TILEQT_QT_VERSION_3 */
    if ((state & TTK_STATE_USER1) && (state & TTK_STATE_USER2)) {
      /* Only tab */
#ifdef TILEQT_QT_VERSION_3
      wc->TileQt_QTabBar_Widget->addTab(tab);
#endif /* TILEQT_QT_VERSION_3 */
    } else if (state & TTK_STATE_USER1) {
      /* Left-most tab */
#ifdef TILEQT_QT_VERSION_3
      wc->TileQt_QTabBar_Widget->addTab(tab);
      tab1 = new QTab;
      wc->TileQt_QTabBar_Widget->addTab(tab1);
#endif /* TILEQT_QT_VERSION_3 */
    } else if (state & TTK_STATE_USER2) {
      /* Right-most tab */
#ifdef TILEQT_QT_VERSION_3
      tab1 = new QTab;
      wc->TileQt_QTabBar_Widget->addTab(tab1);
      wc->TileQt_QTabBar_Widget->addTab(tab);
#endif /* TILEQT_QT_VERSION_3 */
    } else {
      /* A regular tab, in the middle of tab bar */
#ifdef TILEQT_QT_VERSION_3
      tab1 = new QTab;
      wc->TileQt_QTabBar_Widget->addTab(tab1);
      wc->TileQt_QTabBar_Widget->addTab(tab);
      tab2 = new QTab;
      wc->TileQt_QTabBar_Widget->addTab(tab2);
#endif /* TILEQT_QT_VERSION_3 */
    }
#ifdef TILEQT_QT_VERSION_3
    if (state & TTK_STATE_DISABLED) tab->setEnabled(false);
    else tab->setEnabled(true);
#endif /* TILEQT_QT_VERSION_3 */
    
    QPixmap      pixmap(width, height);
    QPainter     painter(&pixmap);
    TILEQT_PAINT_BACKGROUND(width, height);
#ifdef TILEQT_QT_VERSION_3
    QStyle::SFlags sflags = TileQt_StateTableLookup(notebook_statemap, state);
    wc->TileQt_Style->drawControl(QStyle::CE_TabBarTab, &painter,
          wc->TileQt_QTabBar_Widget, QRect(0, 0, width, height),
          qApp->palette().active(), sflags, QStyleOption(tab));
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    QStyleOption option;
    option.initFrom(wc->TileQt_QTabBar_Widget); option.state |= 
      (QStyle::StateFlag) TileQt_StateTableLookup(notebook_statemap, state);
    option.rect = QRect(0, 0, width, height);
    wc->TileQt_Style->drawControl(QStyle::CE_TabBarTab, &option,
                                  &painter, wc->TileQt_QTabBar_Widget);
#endif /* TILEQT_QT_VERSION_4 */
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
           0, 0, width, height, b.x, b.y + PM_DefaultFrameWidth);
#ifdef TILEQT_QT_VERSION_3
    if ((state & TTK_STATE_USER1) && (state & TTK_STATE_USER2)) {
      wc->TileQt_QTabBar_Widget->removeTab(tab);
    } else if (state & TTK_STATE_USER1) {
      wc->TileQt_QTabBar_Widget->removeTab(tab);
      wc->TileQt_QTabBar_Widget->removeTab(tab1);
    } else if (state & TTK_STATE_USER2) {
      wc->TileQt_QTabBar_Widget->removeTab(tab1);
      wc->TileQt_QTabBar_Widget->removeTab(tab);
    } else {
      wc->TileQt_QTabBar_Widget->removeTab(tab1);
      wc->TileQt_QTabBar_Widget->removeTab(tab);
      wc->TileQt_QTabBar_Widget->removeTab(tab2);
    }
#endif /* TILEQT_QT_VERSION_3 */
    Tcl_MutexUnlock(&tileqtMutex);
}

static Ttk_ElementSpec NotebookTabElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(NotebookTabElement),
    NotebookTabElementOptions,
    NotebookTabElementGeometry,
    NotebookTabElementDraw
};

typedef struct {
} NotebookClientElement;


static Ttk_ElementOptionSpec NotebookClientElementOptions[] = {
    {NULL}
};

static void NotebookClientElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_WIDGET(TileQt_QTabBar_Widget);
    int tabBarBaseHeight =
        wc->TileQt_Style->pixelMetric(QStyle::PM_TabBarBaseHeight,
#ifdef TILEQT_QT_VERSION_4
                                      0,
#endif /* TILEQT_QT_VERSION_4 */
                                      wc->TileQt_QTabBar_Widget);
    *paddingPtr = Ttk_MakePadding(NotebookClientUniformPadding,
           NotebookClientUniformPadding + tabBarBaseHeight,
           NotebookClientUniformPadding, NotebookClientUniformPadding);
}

static void NotebookClientElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_WIDGET(TileQt_QTabBar_Widget);
    Tcl_MutexLock(&tileqtMutex);
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    TILEQT_PAINT_BACKGROUND(b.width, b.height);
#ifdef TILEQT_QT_VERSION_3
    QStyle::SFlags sflags = TileQt_StateTableLookup(notebook_statemap, state);
    wc->TileQt_Style->drawPrimitive(QStyle::PE_PanelTabWidget, &painter,
            QRect(0, 0, b.width, b.height),
            qApp->palette().active(), sflags);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    QStyleOptionFrame option;
    option.initFrom(wc->TileQt_QTabBar_Widget);
    option.rect = QRect(0, 0, b.width, b.height);
    option.lineWidth = 1;
    option.state |= 
      (QStyle::StateFlag) TileQt_StateTableLookup(notebook_statemap, state);
    wc->TileQt_Style->drawPrimitive(QStyle::PE_FrameTabWidget, &option,
                                    &painter);
#endif /* TILEQT_QT_VERSION_4 */
    int tabBarBaseHeight =
        wc->TileQt_Style->pixelMetric(QStyle::PM_TabBarBaseHeight,
#ifdef TILEQT_QT_VERSION_4
                                      0,
#endif /* TILEQT_QT_VERSION_4 */
                                      wc->TileQt_QTabBar_Widget);
    if (tabBarBaseHeight) {
      TILEQT_PAINT_BACKGROUND(b.width, tabBarBaseHeight);
#ifdef TILEQT_QT_VERSION_3
      wc->TileQt_Style->drawPrimitive(QStyle::PE_TabBarBase, &painter,
              QRect(0, 0, b.width, tabBarBaseHeight),
              qApp->palette().active(), sflags);
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
     option.rect = QRect(0, 0, b.width, tabBarBaseHeight);
     wc->TileQt_Style->drawPrimitive(QStyle::PE_FrameTabBarBase, &option,
                                    &painter);
#endif /* TILEQT_QT_VERSION_4 */
    }
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                               0, 0, b.width, b.height, b.x, b.y);
    Tcl_MutexUnlock(&tileqtMutex);
}

static Ttk_ElementSpec NotebookClientElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(NotebookClientElement),
    NotebookClientElementOptions,
    NotebookClientElementGeometry,
    NotebookClientElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

int TileQt_Init_Notebook(Tcl_Interp *interp,
                         TileQt_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Notebook.tab",
                &NotebookTabElementSpec, (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "Notebook.client",
                &NotebookClientElementSpec, (void *) wc[0]);
    
    /*
     * Register layouts:
     */

    return TCL_OK;
}; /* TileQt_Init_Notebook */
