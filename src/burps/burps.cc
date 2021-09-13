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
#include <iostream>

using namespace std;


int main( int argc, char** argv )
{
  if( argc > 1 && ( string( argv[1] ) == "-h"
                    || string( argv[1] ) == "--help" ) )
  {
    cout << "burps -- computer version of roleplaying game system thought of "
      "during the 80's...\n";
    exit(0);
  }

  QApplication::setColorSpec( QApplication::ManyColor );
//   QApplication::setStyle( new QWindowsStyle );
  QApplication	a( argc, argv );
  BMain		*bm = new BMain;
  bm->show();
  return( a.exec() );
}


