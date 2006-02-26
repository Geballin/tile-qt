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
    {QStyle::Style_Default,                         TTK_STATE_DISABLED, 0},
    {QStyle::Style_Enabled|QStyle::Style_Selected,  TTK_STATE_SELECTED, 0},
    {QStyle::Style_Enabled|QStyle::Style_MouseOver, TTK_STATE_ACTIVE,   0},
    {QStyle::Style_Enabled|QStyle::Style_HasFocus,  TTK_STATE_FOCUS,    0},
    {QStyle::Style_Enabled,                         0,                  0},
};

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
    //PM_TabBarTabOverlap, PM_TabBarTabHSpace, PM_TabBarTabVSpace, PM_TabBarBaseHeight, PM_TabBarBaseOverlap,
    QTab tab;
    QRect rc = tab.rect();
    *widthPtr   = rc.width();
    *heightPtr  = rc.height();
    *paddingPtr = Ttk_UniformPadding(NotebookUniformPadding);
    //int tabOverlap = qApp->style().pixelMetric(QStyle::PM_TabBarTabOverlap,
    //                                           TileQt_QTabBar_Widget);
    //*paddingPtr = Ttk_MakePadding(hs, vs, hs, vs);
}

static void NotebookTabElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) NULL_Q_APP;
    NULL_PROXY_WIDGET(TileQt_QTabBar_Widget);
    Tcl_MutexLock(&tileqtMutex);
    int tabOverlap = qApp->style().pixelMetric(QStyle::PM_TabBarTabOverlap,
                                               TileQt_QTabBar_Widget);
    int tabBaseOverlap = qApp->style().pixelMetric(QStyle::PM_TabBarBaseOverlap,
                                                   TileQt_QTabBar_Widget);
    int borderWidth = qApp->style().pixelMetric(QStyle::PM_DefaultFrameWidth,
                                                   TileQt_QTabBar_Widget);
    QStyle::SFlags sflags = Ttk_StateTableLookup(notebook_statemap, state);
    //tabOverlap = 0;
    int width = b.width + 1*tabOverlap;
    int height = b.height + tabBaseOverlap + borderWidth;
    int x = (b.x > tabOverlap) ? b.x - tabOverlap: b.x;
    // x = b.x;
    width = b.width; x = b.x;
    QTab* tab = new QTab;
    QTab* tab1 = NULL, *tab2 = NULL;
    if ((state & TTK_STATE_USER1) && (state & TTK_STATE_USER2)) {
      TileQt_QTabBar_Widget->addTab(tab);
      x = b.x;
    } else if (state & TTK_STATE_USER1) {
      /* Left-most tab */
      TileQt_QTabBar_Widget->addTab(tab);
      tab1 = new QTab;
      TileQt_QTabBar_Widget->addTab(tab1);
      x = b.x;
    } else if (state & TTK_STATE_USER2) {
      tab1 = new QTab;
      TileQt_QTabBar_Widget->addTab(tab1);
      TileQt_QTabBar_Widget->addTab(tab);
    } else {
      tab1 = new QTab;
      TileQt_QTabBar_Widget->addTab(tab1);
      TileQt_QTabBar_Widget->addTab(tab);
      tab2 = new QTab;
      TileQt_QTabBar_Widget->addTab(tab2);
    }
    QPixmap      pixmap(width, height);
    QPainter     painter(&pixmap);
    if (TileQt_QPixmap_BackgroundTile &&
        !(TileQt_QPixmap_BackgroundTile->isNull())) {
        painter.fillRect(0, 0, width, height,
                         QBrush(QColor(255,255,255),
                         *TileQt_QPixmap_BackgroundTile));
    } else {
        painter.fillRect(0, 0, width, height,
                         qApp->palette().active().background());
    }
    // printf("x=%d, y=%d, w=%d, h=%d\n", b.x, b.y, b.width, b.height);
    qApp->style().drawControl(QStyle::CE_TabBarTab, &painter,
          TileQt_QTabBar_Widget, QRect(0, 0, width, height),
          qApp->palette().active(), sflags, QStyleOption(tab));
    TileQt_CopyQtPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, width, height, x, b.y);
    if ((state & TTK_STATE_USER1) && (state & TTK_STATE_USER2)) {
      TileQt_QTabBar_Widget->removeTab(tab);
    } else if (state & TTK_STATE_USER1) {
      /* Left-most tab */
      TileQt_QTabBar_Widget->removeTab(tab);
      TileQt_QTabBar_Widget->removeTab(tab1);
    } else if (state & TTK_STATE_USER2) {
      TileQt_QTabBar_Widget->removeTab(tab1);
      TileQt_QTabBar_Widget->removeTab(tab);
    } else {
      TileQt_QTabBar_Widget->removeTab(tab1);
      TileQt_QTabBar_Widget->removeTab(tab);
      TileQt_QTabBar_Widget->removeTab(tab2);
    }
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
    *paddingPtr = Ttk_UniformPadding(NotebookClientUniformPadding);
}

static void NotebookClientElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (qApp == NULL) NULL_Q_APP;
    Tcl_MutexLock(&tileqtMutex);
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    QStyle::SFlags sflags = Ttk_StateTableLookup(notebook_statemap, state);
    if (TileQt_QPixmap_BackgroundTile &&
        !(TileQt_QPixmap_BackgroundTile->isNull())) {
        painter.fillRect(0, 0, b.width, b.height,
                         QBrush(QColor(255,255,255),
                         *TileQt_QPixmap_BackgroundTile));
    } else {
        painter.fillRect(0, 0, b.width, b.height,
                         qApp->palette().active().background());
    }
    // printf("x=%d, y=%d, w=%d, h=%d\n", b.x, b.y, b.width, b.height);
    qApp->style().drawPrimitive(QStyle::PE_PanelTabWidget, &painter,
          QRect(0, 0, b.width, b.height), qApp->palette().active(), sflags);
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

int TileQt_Init_Notebook(Tcl_Interp *interp, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Notebook.tab",
                &NotebookTabElementSpec, NULL);
    Ttk_RegisterElement(interp, themePtr, "Notebook.client",
                &NotebookClientElementSpec, NULL);
    
    /*
     * Register layouts:
     */

    return TCL_OK;
}; /* TileQt_Init_Notebook */
