/*
 *  tileQt_Utilities.h
 * ----------------------
 *
 * This file is part of the Tile-Qt package, a Tk/Tile based theme that uses
 * Qt/KDE for drawing.
 *
 * Copyright (C) 2004-2005 by:
 * Georgios Petasis, petasis@iit.demokritos.gr,
 * Software and Knowledge Engineering Laboratory,
 * Institute of Informatics and Telecommunications,
 * National Centre for Scientific Research (NCSR) "Demokritos",
 * Aghia Paraskevi, 153 10, Athens, Greece.
 */

#include "tileQt_QtHeaders.h"

/* Global Symbols */
extern QScrollBar*    TileQt_QScrollBar_Widget; 
extern QComboBox*     TileQt_QComboBox_RW_Widget;
extern QComboBox*     TileQt_QComboBox_RO_Widget;
extern QWidget*       TileQt_QWidget_Widget;
extern QWidget*       TileQt_QWidget_WidgetParent;
extern QSlider*       TileQt_QSlider_Hor_Widget;
extern QSlider*       TileQt_QSlider_Ver_Widget;
extern QTabBar*       TileQt_QTabBar_Widget;
extern const QPixmap* TileQt_QPixmap_BackgroundTile;

/* Helper Functions */
extern QStyle::SFlags TileQt_TileStateToSFlags(unsigned int state);
extern void TileQt_StateInfo(int, Tk_Window);
extern void TileQt_CopyQtPixmapOnToDrawable(QPixmap&, Drawable, Tk_Window,
                                            int, int, int, int, int, int);
