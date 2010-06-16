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

#ifndef BURPS_MATH_LOGTABLE_H
#define BURPS_MATH_LOGTABLE_H


#include <burps/math/table.h>

namespace burps
{

  class LogTable : public BTable
  {
  public:
    LogTable();
    virtual ~LogTable();

    virtual BTable* clone() const;

    virtual double operate( double x ) const;
    virtual double inv( double x ) const;

    static const double L;
    static const double l;
    static const double e;
  };

}


#endif


