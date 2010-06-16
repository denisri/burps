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

#include <burps/math/logTable.h>
#include <math.h>
#include <iostream>

using namespace burps;
using namespace std;

const double	LogTable::L( 6. / log( 2. ) );
const double	LogTable::l( 1. / L );
const double	LogTable::e( exp( log( 2. ) / 6. ) );


LogTable::LogTable() : BTable()
{
  cout << "L : " << L << endl;
  cout << "e : " << e << endl;
}


LogTable::~LogTable()
{
}


BTable* LogTable::clone() const
{
  return( new LogTable );
}


double LogTable::operate( double x ) const
{
  return( exp( x * l ) );
}


double LogTable::inv( double x ) const
{
  return( L * log( x ) );
}


