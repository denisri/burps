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

#include <burps/math/table.h>

using namespace burps;


BTable::BTable()
{
}


BTable::~BTable()
{
}


BTable* BTable::inverse() const
{
  return( new InvTable( *this ) );
}


//


InvTable::InvTable( const BTable & t ) : BTable(), _t( t.clone() )
{
}


InvTable::~InvTable()
{
  delete _t;
}


BTable* InvTable::clone() const
{
  return( new InvTable( *_t ) );
}


double InvTable::operate( double x ) const
{
  return( _t->inv( x ) );
}


double InvTable::inv( double x ) const
{
  return( _t->operate( x ) );
}


BTable* InvTable::inverse() const
{
  return( _t->clone() );
}


