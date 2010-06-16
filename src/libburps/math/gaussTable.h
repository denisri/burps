/***************************************************************************
    copyright            : (C) 2003 by Denis Rivi�re
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

#ifndef BURPS_MATH_GAUSSTABLE_H
#define BURPS_MATH_GAUSSTABLE_H


#include <burps/math/logTable.h>

namespace burps
{

  class GaussTable : public LogTable
  {
  public:
    GaussTable();
    virtual ~GaussTable();

    virtual BTable* clone() const;

    virtual double operate( double x ) const;
    virtual double inv( double x ) const;
  };

}


#endif


