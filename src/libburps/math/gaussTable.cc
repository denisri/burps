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

#include <burps/math/gaussTable.h>
#include <math.h>

using namespace burps;


GaussTable::GaussTable() : LogTable()
{
}


GaussTable::~GaussTable()
{
}


BTable* GaussTable::clone() const
{
  return( new GaussTable );
}


double GaussTable::operate( double x ) const
{
  return( x*x );
}


double GaussTable::inv( double x ) const
{
  return( sqrt( x ) );
}


