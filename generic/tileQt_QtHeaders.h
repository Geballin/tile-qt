/*
 *  tileQt_QtHeaders.h
 * --------------------
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
#ifndef _TILEQT_QTHEADERS
#define _TILEQT_QTHEADERS

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
//#include <qfile.h>
//#include <qdir.h>
//#include <qtextstream.h>
//#include <qregexp.h>
#include <qtabwidget.h>
#include <qtooltip.h>
#include <qdatetime.h>
#include <qlistview.h>
#include <qtextstream.h>
#include <qdeepcopy.h>
#include <qstringlist.h> 
#include <qcolor.h>
#include <tk.h>

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
  QTabBar*       TileQt_QTabBar_Widget;
  const QPixmap* TileQt_QPixmap_BackgroundTile;
  Tk_Window      TileQt_tkwin;
  Display*       TileQt_MainDisplay;
  Tcl_Interp*    TileQt_MainInterp;
  int orientation;
} TileQt_WidgetCache;

#endif
