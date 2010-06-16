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

#include <burps/math/sigmoTable.h>
#include <math.h>

using namespace burps;


SigmoTable::SigmoTable() : LogTable()
{
}


SigmoTable::~SigmoTable()
{
}


BTable* SigmoTable::clone() const
{
  return( new SigmoTable );
}


double SigmoTable::operate( double x ) const
{
  return( 1. / ( 1 + LogTable::operate( -x * 2 ) ) );
}


double SigmoTable::inv( double x ) const
{
  return( x >= 0 ? -L * log( 1. / x - 1. ) * 0.5 : 0 );
}


