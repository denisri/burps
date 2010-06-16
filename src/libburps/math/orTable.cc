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

#include <burps/math/orTable.h>
#include <math.h>

using namespace burps;


const double OrTable::log2( log( 2 ) );


OrTable::OrTable() : LogTable()
{
}


OrTable::~OrTable()
{
}


BTable* OrTable::clone() const
{
  return( new OrTable );
}


double OrTable::operate( double x ) const
{
  return( 1. - exp( - log2 * LogTable::operate( x ) ) );
}


double OrTable::inv( double x ) const
{
  return( x > 0 ? ( x < 1 ? L * log( - log(1 - x ) / log2 ) : 1 ) : 0 );
}


