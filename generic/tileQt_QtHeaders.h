/*
 *  tileQt_QtHeaders.h
 * --------------------
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
#ifndef _TILEQT_QTHEADERS
#define _TILEQT_QTHEADERS

/* The following header file defines QT_VERSION.
 * It exists for both Qt 3.x & 4.x. */
#include "qglobal.h"

#if QT_VERSION >= 0x030000 && QT_VERSION < 0x040000
#define TILEQT_QT_VERSION_3 
/* Header Files for Qt 3.x */
#include <qt.h>
#include <qapplication.h>
#include <qwidget.h>
#include <qobject.h>
#include <qobjcoll.h>
#include <qwidcoll.h>
#include <qsize.h>
#include <qstyle.h>
#include <qstylefactory.h>
#include <qstyleplugin.h>
#include <qcdestyle.h>
#include <qcommonstyle.h>
#include <qcompactstyle.h>
#include <qinterlacestyle.h>
#include <qmotifplusstyle.h>
#include <qmotifstyle.h>
#include <qplatinumstyle.h>
#include <qsgistyle.h>
#include <qwindowsstyle.h>
#include <qtabwidget.h>
#include <qtooltip.h>
#include <qdatetime.h>
#include <qlistview.h>
#include <qtextstream.h>
#include <qdeepcopy.h>
#include <qstringlist.h> 
#include <qcolor.h>
#endif /* QT_VERSION >= 0x030000 && QT_VERSION < 0x040000 */

#if QT_VERSION >= 0x040000 && QT_VERSION < 0x050000
#define TILEQT_QT_VERSION_4
/* Header Files for Qt 4.x */
#include <Qt>
#include <QtCore>
#include <QtGui>
#endif /* QT_VERSION >= 0x040000 && QT_VERSION < 0x050000 */
#include <tk.h>

#ifdef TILEQT_QT_VERSION_4
#include <QX11Info>
#define qt_xdisplay QX11Info::display
using namespace Qt;
#endif /* TILEQT_QT_VERSION_4 */


typedef struct TileQt_WidgetCache {
  QStyle*        TileQt_Style;
  bool           TileQt_Style_Owner;
  QString*       lowerStyleName;
  QWidget*       TileQt_smw;
  QScrollBar*    TileQt_QScrollBar_Widget; 
  QComboBox*     TileQt_QComboBox_RW_Widget;
  QComboBox*     TileQt_QComboBox_RO_Widget;
  QWidget*       TileQt_QWidget_Widget;
  QWidget*       TileQt_QWidget_WidgetParent;
  QSlider*       TileQt_QSlider_Hor_Widget;
  QSlider*       TileQt_QSlider_Ver_Widget;
  QProgressBar*  TileQt_QProgressBar_Hor_Widget;
  QTabWidget*    TileQt_QTabWidget_Widget;
  QTabBar*       TileQt_QTabBar_Widget;
  QListView*     TileQt_QListView_Widget;
#ifdef TILEQT_QT_VERSION_3
  const QPixmap* TileQt_QPixmap_BackgroundTile;
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
  QPixmap        TileQt_QPixmap_BackgroundTile;
#endif /* TILEQT_QT_VERSION_4 */
  Tk_Window      TileQt_tkwin;
  Display*       TileQt_MainDisplay;
  Tcl_Interp*    TileQt_MainInterp;
  int orientation;
} TileQt_WidgetCache;

class TileQt_Widget : protected QWidget {
  public:
#ifdef TILEQT_QT_VERSION_3
    void set_visible(void)   {QWidget::setWState(WState_Visible);}
    void clear_visible(void) {QWidget::clearWState(WState_Visible);}
#endif /* TILEQT_QT_VERSION_3 */
#ifdef TILEQT_QT_VERSION_4
    void set_visible(void)   {}
    void clear_visible(void) {}
#endif /* TILEQT_QT_VERSION_4 */
}; /* TileQt_Widget */

class TileQt_QTabWidget : protected QTabWidget {
  public:
    QTabBar* get_tab_bar(void) const {return tabBar();}
}; /* TileQt_QTabWidget */

#endif
