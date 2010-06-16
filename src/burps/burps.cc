/***************************************************************************
    copyright            : (C) 2003 by Denis Rivière
    email                : nudz@free.fr
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <burps/gui/bwin.h>
#include <qapplication.h>
#include <qwindowsstyle.h>


int main( int argc, char** argv )
{
  QApplication::setColorSpec( QApplication::ManyColor );
  QApplication::setStyle( new QWindowsStyle );
  QApplication	a( argc, argv );
  BMain		*bm = new BMain;
  bm->show();
  a.setMainWidget( bm );
  return( a.exec() );
}


